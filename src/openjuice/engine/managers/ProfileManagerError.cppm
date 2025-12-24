/**
 * @file ProfileManagerError.cppm
 * @module openjuice.engine.managers:ProfileManagerError
 * @brief Definition of the ProfileManagerError enum class.
 *
 * This file contains the definition of the ProfileManagerError enum class, which possible errors during profile manager loading.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.engine.managers:ProfileManagerError;

import std;

using std::fmt::FormatContext;
using std::fmt::FormatParseContext;
using std::fmt::Formatter;

BEGIN_MODULE_NAMESPACE(openjuice::engine::managers);

/**
 * @enum ProfileManagerError
 * @brief Enumeration of errors occuring in ProfileManager operations
 */
export enum class ProfileManagerError: u8 {
    DESERIALISATION_FAILED, ///< Deserialisation of profile data failed
    CORRUPTED_PROFILE_TOML, ///< The TOML file storing the profile is corrupted or has invalid data
    PROFILE_LOAD_FAILED, ///< Loading profile data failed
    PROFILE_SAVE_LOCATION_INVALID, ///< The profile save location is invalid
    PROFILE_SAVE_WRITE_FAILED, ///< Writing profile data to file failed
    PROFILE_SAVE_FAILED, ///< Saving profile data failed
};

END_MODULE_NAMESPACE();

using openjuice::engine::managers::ProfileManagerError;

template <>
struct Formatter<ProfileManagerError> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(ProfileManagerError err, FormatContext& ctx) {
        StringView name;
        switch (err) {
            case ProfileManagerError::DESERIALISATION_FAILED:
                name = "Deserialisation failed"; 
                break;
            case ProfileManagerError::CORRUPTED_PROFILE_TOML:
                name = "Corrupted profile TOML"; 
                break;
            case ProfileManagerError::PROFILE_LOAD_FAILED:
                name = "Profile load failed"; 
                break;
            case ProfileManagerError::PROFILE_SAVE_LOCATION_INVALID:
                name = "Profile save location invalid"; 
                break;
            case ProfileManagerError::PROFILE_SAVE_WRITE_FAILED:
                name = "Profile save write failed"; 
                break;
            case ProfileManagerError::PROFILE_SAVE_FAILED:
                name = "Profile save failed"; 
                break;
            default:
                std::sys::unreachable();
        }
        return std::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(ProfileManagerError);
