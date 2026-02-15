/**
 * @file InvalidIDException.cppm
 * @module openjuice.engine.util:InvalidIDException
 * @brief Implementation of the InvalidIDException class.
 *
 * This file contains the implementation of the InvalidIDException class, which is used to handle invalid ID in ID queries.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.util:InvalidIDException;

import stdx;

BEGIN_MODULE_NAMESPACE(openjuice::engine::util);

/**
 * @class InvalidIDException
 * @brief Exception class for invalid IDs.
 *
 * @extends OutOfRangeException
 * 
 * The InvalidIDException class is used to handle exceptions related to invalid IDs in ID queries.
 */
export class InvalidIDException: public OutOfRangeException {
public:
    /**
     * @brief Constructor that initialises the exception with a message.
     * @param msg The exception message.
     */
    explicit InvalidIDException(const String& msg):
        OutOfRangeException(msg) {}
};

END_MODULE_NAMESPACE();
