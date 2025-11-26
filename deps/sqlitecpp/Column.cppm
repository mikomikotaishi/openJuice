/**
 * @file Column.cppm
 * @module sqlite.column
 * @brief Module file for SQLiteCpp Column class.
 */

module;

#include <SQLiteCpp/Column.h>

export module sqlite.column;

import sqlite.sqlite3forward;

/**
 * @namespace sqlite
 * @brief The SQLite SQLite:: namespace
 */
export namespace sqlite {
    inline const int INTEGER = SQLite::INTEGER;
    inline const int FLOAT = SQLite::FLOAT;
    inline const int TEXT = SQLite::TEXT;
    inline const int BLOB = SQLite::BLOB;
    inline const int Null = SQLite::Null;

    using SQLite::Column;

    using SQLite::operator<<;
}
