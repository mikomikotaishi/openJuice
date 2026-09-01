/**
 * @file ThreadPool.cppm
 * @module openjuice.engine.util:ThreadPool
 * @brief Definition of the ThreadPool class.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.util:ThreadPool;

import stdx;

using stdx::collections::Vector;
using stdx::ranges::IotaView;
using stdx::sync::Barrier;
using stdx::thread::Thread;

BEGIN_MODULE_NAMESPACE(openjuice::engine::util);

/**
 * @class ThreadPool
 * @brief A thread pool implementation for parallel task execution.
 * 
 * This class manages a pool of worker threads that can execute tasks in parallel.
 * Tasks are divided into chunks and distributed across worker threads using a barrier
 * synchronization mechanism. The pool remains active for the lifetime of the object,
 * with threads waiting at a barrier between task executions.
 * The thread pool creates threadCount + 1 tasks, with the main thread executing
 * the final task chunk.
 */
export class ThreadPool {
private:
    /**
     * @struct Range
     * @brief One task's half-open slice of the work.
     *
     * Kept together rather than in parallel start/end arrays so that a worker reads its whole
     * slice from one cache line. Only the main thread writes these, and only before a barrier the
     * workers read after, so packing them adjacently cannot cause false sharing.
     */
    struct Range {
        usize start = 0; ///< First index in the slice.
        usize end = 0; ///< One past the last index in the slice.
    };

    Barrier<> barrier; ///< Synchronization barrier for coordinating thread execution.
    Function<void(usize, usize)> task = nullptr; ///< The current task function to execute.
    Vector<Thread> threads; ///< Worker threads in the pool.
    Vector<Range> ranges; ///< Each task's slice of the current work, indexed by task number.
    const u32 taskCount = 0; ///< Total number of tasks (worker threads + 1, including main thread).
    bool shouldJoin = false; ///< Flag indicating whether threads should terminate.
public:
    /**
     * @brief Construct a new ThreadPool object.
     * @param threadCount The number of worker threads to create in the pool.
     * If 0, no threads are created and all work is done on the main thread.
     *
     * Creates a pool of worker threads that will wait at a barrier for tasks to execute.
     * Each thread runs in a loop, waiting for tasks at the barrier, executing them,
     * and then waiting again until the pool is destroyed.
     *
     * @note The actual number of task chunks is threadCount + 1, as the main thread
     * that calls execTask() also executes a chunk of work.
     */
    explicit ThreadPool(u32 threadCount):
        barrier{threadCount + 1},
        ranges{threadCount + 1},
        taskCount{threadCount + 1} {
        // Reserved up front so that no emplace_back below reallocates.
        threads.reserve(threadCount);

        for (u32 i: IotaView(0u, threadCount)) {
            threads.emplace_back([this, i] -> void {
                while (true) {
                    barrier.arrive_and_wait();
                    if (shouldJoin) {
                        barrier.arrive_and_wait();
                        return;
                    }
                    task(ranges[i].start, ranges[i].end);
                    barrier.arrive_and_wait();
                }
            });
        }
    }

    /**
     * @brief Destroy the ThreadPool object.
     *
     * Signals all worker threads to shut down by setting shouldJoin flag and
     * synchronizing through the barrier. Waits for all threads to complete
     * their current work and join before returning.
     *
     * @note This destructor blocks until all worker threads have been joined.
     */
    ~ThreadPool() {
        shouldJoin = true;
        barrier.arrive_and_wait(); // signal worker threads to shut down
        barrier.arrive_and_wait(); // synchronize before joining
        for (Thread& t: threads) {
            t.join();
        }
    }

    /**
     * @brief Execute a task in parallel across all threads in the pool.
     * @tparam Fn A callable type that accepts two usize parameters (start, end).
     * Should have the signature: void(usize start, usize end).
     * @param query The function to execute on each chunk. Will be called with
     * (start, end) indices defining the range to process.
     * @param work The total amount of work to divide (upper bound of the range).
     * The work will be split across all threads in the pool.
     *
     * Divides the work into chunks and distributes them across worker threads.
     * The work range [0, work) is split into taskCount chunks, with any remainder
     * added to the last chunk. Each thread (including the calling thread) executes
     * the query function on its assigned range [start, end).
     *
     * This function blocks until all threads have completed their work chunks.
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
     *
     * @note The calling thread also participates in the work, executing the last chunk.
     * @note If a chunk would be empty (start >= end), it is skipped.
     */
    template <typename Fn>
    void execTask(Fn&& query, usize work) {
        task = Ops::forward<Fn>(query);
        usize chunk = work / taskCount;
        usize tail = work - chunk * taskCount;
        for (u32 i: IotaView(0u, taskCount)) {
            const usize start = i * chunk;
            const usize end = start + chunk + (i == taskCount - 1 ? tail : 0);

            // Assigned even when the slice is empty. The workers read these unconditionally, so
            // skipping an index would leave it holding the previous call's slice and run that
            // slice a second time.
            ranges[i] = Range {
                .start = start,
                .end = end,
            };
        }
        barrier.arrive_and_wait();
        const Range& own = ranges[taskCount - 1];
        task(own.start, own.end);
        barrier.arrive_and_wait();
    }
};

END_MODULE_NAMESPACE();
