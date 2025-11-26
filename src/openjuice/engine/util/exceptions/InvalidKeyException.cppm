/**
 * @file InvalidKeyException.cppm
 * @module openjuice.engine.util.Exceptions:InvalidKeyException
 * @brief Implementation of the InvalidKeyException class.
 *
 * This file contains the implementation of the InvalidKeyException class, which is used to handle invalid keys in TextManager key queries.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.util.Exceptions:InvalidKeyException;

import std;

BEGIN_MODULE_NAMESPACE(openjuice::engine::util);

/**
 * @class InvalidKeyException
 * @brief Exception class for invalid keys.
 *
 * @extends OutOfRangeException
 * 
 * The InvalidKeyException class is used to handle exceptions related to invalid keys in TextManager key queries.
 */
export class InvalidKeyException: public OutOfRangeException {
public:
    /**
     * @brief Constructor that initialises the exception with a message.
     * @param msg The exception message.
     */
    explicit InvalidKeyException(const String& msg):
        OutOfRangeException(msg) {}
};

END_MODULE_NAMESPACE();
