/**
 * @file Transaction.cppm
 * @module sqlite.transaction
 * @brief Module file for SQLiteCpp Transaction class.
 */

module;

#include <SQLiteCpp/Transaction.h>

export module sqlite.transaction;

export import sqlite.database;

import sqlite.sqlite3forward;

/**
 * @namespace sqlite
 * @brief The SQLite SQLite:: namespace
 */
export namespace sqlite {
    using SQLite::TransactionBehavior;
    using SQLite::Transaction;
}
