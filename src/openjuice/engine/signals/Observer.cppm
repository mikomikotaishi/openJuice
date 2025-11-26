/**
 * @file Observer.cppm
 * @module openjuice.engine.signals.Observer
 * @brief Module file defining the Observer interface and Subject abstract class.
 *
 * This file contains the definitions of the Observer interface and Subject abstract class.
 */

module;

// Standard library headers are necessary here - there is no workaround
#include <vector>

#include "Macros.hpp"

export module openjuice.engine.signals.Observer;

import std;

using std::collections::Vector;
using std::meta::IsBaseOfValue;

namespace ranges = std::ranges;

BEGIN_MODULE_NAMESPACE(openjuice::engine::signals);

/**
 * @class Observer
 * @brief Abstract class representing an Observer.
 * @deprecated
 */
export class Observer {
public:
    /**
     * @brief Destroy the Observer object
     */
    virtual ~Observer() = default;

    /**
     * @brief Updates the Observer object
     * 
     * @param subject 
     */
    virtual void update(class Subject* subject) = 0;
};

/**
 * @class Subject
 * @brief Abstract class representing a subject.
 * @deprecated
 */
export class Subject {
private:
    Vector<Observer*> observers; ///< List of observers
public:
    /**
     * @brief Destroy the Subject object
     */
    virtual ~Subject() = default;

    /**
     * @brief Attaches an Observer to the Subject
     * 
     * @param observer 
     */
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    /**
     * @brief Detaches an Observer from the Subject
     * 
     * @param observer 
     */
    void detach(Observer* observer) {
        ranges::remove(observers, observer);
    }

    /**
     * @brief Notifies all Observers of the Subject
     */
    void notify() {
        for (Observer* observer: observers) {
            observer->update(this);
        }
    }
};

/**
 * @concept ExtendsObserver
 * @brief Concept that checks if a type extends the Observer class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsObserver = IsBaseOfValue<Observer, T>;

/**
 * @concept ExtendsSubject
 * @brief Concept that checks if a type extends the Subject class.
 *
 * @tparam T the type to check against
 */
export template <typename T>
concept ExtendsSubject = IsBaseOfValue<Subject, T>;

END_MODULE_NAMESPACE();
