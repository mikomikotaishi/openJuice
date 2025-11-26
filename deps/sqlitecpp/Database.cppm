/**
 * @file Exception.cppm
 * @module sqlite.database
 * @brief Module file for SQLiteCpp Exception class.
 */

module;

#include <SQLiteCpp/Database.h>

export module sqlite.database;

import sqlite.sqlite3forward;

/**
 * @namespace sqlite
 * @brief The SQLite SQLite:: namespace
 */
export namespace sqlite {
    inline const int OPEN_READONLY = SQLite::OPEN_READONLY;
    inline const int OPEN_READWRITE = SQLite::OPEN_READWRITE;
    inline const int OPEN_CREATE = SQLite::OPEN_CREATE;
    inline const int OPEN_URI = SQLite::OPEN_URI;
    inline const int OPEN_MEMORY = SQLite::OPEN_MEMORY;
    inline const int OPEN_NOMUTEX = SQLite::OPEN_NOMUTEX;
    inline const int OPEN_FULLMUTEX = SQLite::OPEN_FULLMUTEX;
    inline const int OPEN_SHAREDCACHE = SQLite::OPEN_SHAREDCACHE;
    inline const int OPEN_PRIVATECACHE = SQLite::OPEN_PRIVATECACHE;
    inline const int OPEN_NOFOLLOW = SQLite::OPEN_NOFOLLOW;
    inline const int OK = SQLite::OK;
    inline const char* const VERSION = SQLite::VERSION;
    inline const int VERSION_NUMBER = SQLite::VERSION_NUMBER;

    using SQLite::getLibVersion;
    using SQLite::getLibVersionNumber;

    using SQLite::Header;
    using SQLite::Database;
}
