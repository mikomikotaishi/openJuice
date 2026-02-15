/**
 * @file InvalidLanguageException.cppm
 * @module openjuice.engine.util:InvalidLanguageException
 * @brief Implementation of the InvalidLanguageException class.
 *
 * This file contains the implementation of the InvalidLanguageException class, which is used to handle invalid language exceptions.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.util:InvalidLanguageException;

import stdx;

BEGIN_MODULE_NAMESPACE(openjuice::engine::util);

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
     * @brief Constructor that initialises the exception with a message.
     * @param msg The exception message.
     */
    explicit InvalidLanguageException(const String& msg):
        InvalidArgumentException(msg) {}
};

END_MODULE_NAMESPACE();
