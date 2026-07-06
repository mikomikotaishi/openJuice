/**
 * @file Observer.cppm
 * @module openjuice.engine.signals:Observer
 * @brief Module file defining the Observer interface and Subject abstract class.
 *
 * This file contains the definitions of the Observer interface and Subject abstract class.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.signals:Observer;

import stdx;

using stdx::collections::Vector;

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
        stdx::collections::erase(observers, observer);
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

END_MODULE_NAMESPACE();
