/**
 * @file Exceptions.cppm
 * @module openjuice.engine.util:Exceptions
 * @brief Exception classes used in the program.
 *
 * This file contains the implementation of exceptions used in the program.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.util:Exceptions;

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
     * @brief Constructor that initializes the exception with a message.
     * @param msg The exception message.
     */
    explicit InvalidIDException(const String& msg):
        OutOfRangeException(msg) {}
};

/**
 * @class InvalidKeyException
 * @brief Exception class for invalid keys.
 *
 * @extends OutOfRangeException
 *
 * The InvalidKeyException class is used to handle exceptions related to invalid keys in LocalizationService key queries.
 */
export class InvalidKeyException: public OutOfRangeException {
public:
    /**
     * @brief Constructor that initializes the exception with a message.
     * @param msg The exception message.
     */
    explicit InvalidKeyException(const String& msg):
        OutOfRangeException(msg) {}
};

/**
 * @class InvalidLanguageException
 * @brief Exception class for invalid languages.
 *
 * @extends InvalidArgumentException (stdx::invalid_argument)
 *
 * The InvalidLanguageException class is used to handle exceptions related to invalid languages.
 */
export class InvalidLanguageException: public InvalidArgumentException {
public:
    /**
     * @brief Constructor that initializes the exception with a message.
     * @param msg The exception message.
     */
    explicit InvalidLanguageException(const String& msg):
        InvalidArgumentException(msg) {}
};

END_MODULE_NAMESPACE();
