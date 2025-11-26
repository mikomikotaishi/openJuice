/**
 * @file Exception.cppm
 * @module sqlite.exception
 * @brief Module file for SQLiteCpp Exception class.
 */

module;

#include <SQLiteCpp/Exception.h>

export module sqlite.exception;

import sqlite.sqlite3forward;

/**
 * @namespace sqlite
 * @brief The SQLite SQLite:: namespace
 */
export namespace sqlite {
    using SQLException = SQLite::Exception;
}
