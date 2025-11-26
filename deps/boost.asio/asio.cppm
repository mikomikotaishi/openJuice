/**
 * @file asio.cppm
 * @module boost.asio
 * @brief Module file for Boost library asynchronous I/O operations.
 * @version 1.88.0
 */

module;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4244)
#pragma warning(disable: 4267)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wshadow"
#endif

#include <boost/asio.hpp>

#ifdef _MSC_VER
#pragma warning(pop)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

export module boost.asio;

/**
 * @namespace boost::asio
 * @brief The Boost boost:: namespace
 */
export namespace boost::asio {
    
}
