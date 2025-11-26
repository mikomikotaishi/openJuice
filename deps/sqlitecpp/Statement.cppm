/**
 * @file Statement.cppm
 * @module sqlite.statement
 * @brief Module file for SQLiteCpp Statement class.
 */

module;

#include <SQLiteCpp/Statement.h>

export module sqlite.statement;

export import sqlite.column;
export import sqlite.database;

import sqlite.sqlite3forward;

/**
 * @namespace sqlite
 * @brief The SQLite SQLite:: namespace
 */
export namespace sqlite {
    using SQLite::Statement;
}
