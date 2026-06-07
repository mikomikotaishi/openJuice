/**
 * @file ThreadPool.cppm
 * @module openjuice.engine.game.ecs:ThreadPool
 * @brief Module of the ECS registry.
 *
 * This file contains the definitions for the thread pool class.
 * Based on kawa_ecs (https://github.com/superPuero/kawa_ecs)
 */

module;

#include "Macros.hpp"

export module openjuice.engine.game.ecs:ThreadPool;

import stdx;

using stdx::alloc::AlignValue;
using stdx::mem::Pointers;
using stdx::mem::UniquePointer;
using stdx::ranges::IotaView;
using stdx::sync::Barrier;
using stdx::thread::Thread;

BEGIN_MODULE_NAMESPACE(openjuice::engine::game::ecs);

/**
 * @class ThreadPool
 * @brief A thread pool implementation for parallel task execution.
 * 
 * This class manages a pool of worker threads that can execute tasks in parallel.
 * Tasks are divided into chunks and distributed across worker threads using a barrier
 * synchronisation mechanism. The pool remains active for the lifetime of the object,
 * with threads waiting at a barrier between task executions.
 * The thread pool creates threadCount + 1 tasks, with the main thread executing
 * the final task chunk.
 */
export class ThreadPool {
private:
    Barrier<> barrier; ///< Synchronisation barrier for coordinating thread execution.
    Function<void(usize, usize)> task = nullptr; ///< The current task function to execute.
    UniquePointer<Thread[]> threads; ///< Array of worker threads in the pool.
    UniquePointer<usize[]> starts; ///< Starting indices for each thread's work chunk.
    UniquePointer<usize[]> ends; ///< Ending indices for each thread's work chunk.
    const u32 threadCount = 0; ///< Number of worker threads in the pool.
    const u32 taskCount = 0; ///< Total number of tasks (threadCount + 1, including main thread).
    bool shouldJoin = false; ///< Flag indicating whether threads should terminate.
public:
    /**
     * @brief Construct a new ThreadPool object.
     * 
     * Creates a pool of worker threads that will wait at a barrier for tasks to execute.
     * Each thread runs in a loop, waiting for tasks at the barrier, executing them,
     * and then waiting again until the pool is destroyed.
     * 
     * @param threadCount The number of worker threads to create in the pool.
     *                    If 0, no threads are created and all work is done on the main thread.
     *
     * @note The actual number of task chunks is threadCount + 1, as the main thread
     * that calls execTask() also executes a chunk of work.
     */
    explicit ThreadPool(u32 threadCount):
        barrier(threadCount + 1),
        threads{
            threadCount > 0 
                ? reinterpret_cast<Thread*>(::operator new(sizeof(Thread) * threadCount, AlignValue{alignof(Thread)}))
                : nullptr
        },
        starts{Pointers::unique<usize[]>(threadCount + 1)},
        ends{Pointers::unique<usize[]>(threadCount + 1)},
        threadCount{threadCount},
        taskCount{threadCount + 1} {
        for (u32 i: IotaView(0u, threadCount)) {
            new (&threads[i])Thread([this, i] -> void {
                while (true) {
                    barrier.arrive_and_wait();
                    if (shouldJoin) {
                        barrier.arrive_and_wait();
                        return;
                    }
                    task(starts[i], ends[i]);
                    barrier.arrive_and_wait();
                }
            });
        }
    }

    /**
     * @brief Destroy the ThreadPool object.
     * 
     * Signals all worker threads to shut down by setting shouldJoin flag and
     * synchronising through the barrier. Waits for all threads to complete
     * their current work and join before returning.
     * 
     * @note This destructor blocks until all worker threads have been joined.
     */
    ~ThreadPool() {
        shouldJoin = true;
        barrier.arrive_and_wait(); // signal worker threads to shut down
        barrier.arrive_and_wait(); // synchronise before joining
        for (u32 i: IotaView(0u, threadCount)) {
            threads[i].join();
        }
    }

    /**
     * @brief Execute a task in parallel across all threads in the pool.
     * 
     * Divides the work into chunks and distributes them across worker threads.
     * The work range [0, work) is split into taskCount chunks, with any remainder
     * added to the last chunk. Each thread (including the calling thread) executes
     * the query function on its assigned range [start, end).
     * 
     * This function blocks until all threads have completed their work chunks.
     * 
     * @tparam Fn A callable type that accepts two usize parameters (start, end).
     *            Should have the signature: void(usize start, usize end).
     * 
     * @param query The function to execute on each chunk. Will be called with
     *              (start, end) indices defining the range to process.
     * @param work The total amount of work to divide (upper bound of the range).
     *             The work will be split across all threads in the pool.
     * 
     * @note The calling thread also participates in the work, executing the last chunk.
     * @note If a chunk would be empty (start >= end), it is skipped.
     * 
     * @par Example:
     * @code
     * ThreadPool pool(4);
     * pool.execTask([&](usize start, usize end) -> void {
     *     for (usize i: IotaView(start, end)) {
     *         processElement(i);
     *     }
     * }, 1000); // Process 1000 elements across 5 threads (4 workers + main)
     * @endcode
     */
    template <typename Fn>
    void execTask(Fn&& query, usize work) {
        task = Ops::forward<Fn>(query);
        usize chunk = work / taskCount;
        usize tail = work - chunk * taskCount;
        for (u32 i: IotaView(0u, taskCount)) {
            usize start = i * chunk;
            usize end = start + chunk + (i == taskCount - 1
                ? tail
                : 0);
            if (start >= end) {
                continue;
            }
            starts[i] = start;
            ends[i] = end;
        }
        barrier.arrive_and_wait();
        task(starts[taskCount - 1], ends[taskCount - 1]);
        barrier.arrive_and_wait();
    }
};

END_MODULE_NAMESPACE();
