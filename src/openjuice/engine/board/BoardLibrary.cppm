/**
 * @file BoardLibrary.cppm
 * @module openjuice.engine.board:BoardLibrary
 * @brief Implementation of the BoardLibrary class.
 *
 * This file contains the implementation of the BoardLibrary class, which is used to load and manage boards.
 */

module;

#include "Macros.hpp"

export module openjuice.engine.board:BoardLibrary;

import stdx;
import :BoardInfo;

import openjuice.engine.managers;
import openjuice.engine.util;

import marzer.toml;

using stdx::collections::Vector;
using stdx::fmt::FormatContext;
using stdx::fmt::FormatParseContext;
using stdx::fmt::Formatter;
using stdx::fs::DirectoryEntry;
using stdx::fs::DirectoryIterator;
using stdx::mem::Pointers;
using stdx::mem::SharedPointer;
using stdx::ranges::IotaView;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::util::Constants;

using marzer::toml::TomlArray;
using marzer::toml::TomlTable;

BEGIN_MODULE_NAMESPACE(openjuice::engine::board);

/**
 * @class BoardLibrary
 * @brief Singleton class for loading and managing boards.
 *
 * The BoardLibrary class is a singleton class that loads and manages boards from files.
 */
export class BoardLibrary {
public:
    static constexpr StringView MAPS_DIR = Constants::MAPS_DIR; ///< The maps directory path.

    /**
     * @enum Error
     * @brief Enumeration of errors occuring in BoardLibrary operations
     */
    enum class Error: u8 {
        DIRECTORY_NOT_FOUND, ///< The directory containing boards was not found
        INVALID_TOML_ARRAY, ///< A TOML array was not valid or contained invalid data
        INVALID_TOML_ARRAY_SIZE, ///< A TOML array had an invalid size
        CORRUPTED_LIBRARY_TOML, ///< The TOML file storing the board library is corrupted or has invalid data
    };
private:
    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("BoardLibrary"); ///< The logger instance.

    Vector<SharedPointer<BoardInfo>> boardList; ///< List of loaded boards.
    
    /**
     * @brief Private constructor to prevent instantiation.
     */
    BoardLibrary() {
        if (Expected<void, ErrorDescription<Error>> r = loadBoards(); r) {
            LOGGER->info("Successfully loaded {} boards!", boardList.size());
        } else {
            LOGGER->warn(
                "Board libraries were not successfully initialised! ErrorDescription: {}, {} boards successfully loaded",
                r.error().message(),
                boardList.size()
            );
        }
    }

    /**
     * @brief Private destructor to prevent destruction.
     */
    ~BoardLibrary() = default;

    /**
     * @brief Deleted copy constructor to prevent copying.
     */
    BoardLibrary(const BoardLibrary&) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent copying.
     */
    BoardLibrary& operator=(const BoardLibrary&) = delete;
public:
    /**
     * @brief Get the singleton instance of BoardLibrary.
     *
     * @return The singleton instance.
     */
    [[nodiscard]]
    static BoardLibrary& getInstance() {
        static BoardLibrary instance;
        return instance;
    }

    /**
     * @brief Load boards into the boardList.
     *
     * @param directory (Optional) The directory to load maps from.
     */
    [[nodiscard]]
    Expected<void, ErrorDescription<Error>> loadBoards(StringView directory = MAPS_DIR) {
        #ifndef NDEBUG
        LOGGER->debug("Loading boards from directory: {}", directory);
        #endif
        
        if (!stdx::fs::exists(directory)) {
            return Unexpected<ErrorDescription<Error>>(
                Tags::IN_PLACE,
                Error::DIRECTORY_NOT_FOUND,
                stdx::fmt::format("The directory {} was not found!", directory)
            );
        }
        for (const DirectoryEntry& entry: DirectoryIterator(directory)) {
            if (entry.is_regular_file() && entry.path().extension() == ".toml") {
                String boardPath = entry.path().string();
                TomlTable data = marzer::toml::parse_file(boardPath);

                u32 boardId = data["id"].value_or<u32>(0);
                String boardName = data["name"].value_or<String>("");
                u8 boardWidth = data["width"].value_or<u8>(0);
                u8 boardHeight = data["height"].value_or<u8>(0);

                if (boardId == 0 || boardName.empty() || boardWidth == 0 || boardHeight == 0) {
                    return Unexpected<ErrorDescription<Error>>(
                        Tags::IN_PLACE,
                        Error::CORRUPTED_LIBRARY_TOML,
                        "Corrupted board library TOML file!"
                    );
                }

                Array<Pair<u8, u8>, BoardInfo::MAX_PLAYERS> homePanels;
                const TomlArray* homePanelsData = data["homePanels"].as_array();
                if (homePanelsData) {
                    for (usize i: IotaView(0uz, Math::min(static_cast<usize>(BoardInfo::MAX_PLAYERS), homePanelsData->size()))) {
                        const TomlArray* panel = (*homePanelsData)[i].as_array();
                        if (panel) {
                            if (panel->size() != 2) {
                                return Unexpected<ErrorDescription<Error>>(
                                    Tags::IN_PLACE,
                                    Error::INVALID_TOML_ARRAY_SIZE,
                                    stdx::fmt::format("Invalid homePanels size: expected 2, got {}", panel->size())
                                );
                            }
                            #ifndef NDEBUG
                            homePanels.at(i) = {
                                static_cast<u8>((*panel)[0].value_or(0)),
                                static_cast<u8>((*panel)[1].value_or(0))
                            };
                            #else
                            homePanels[i] = {
                                static_cast<u8>((*panel)[0].value_or(0)),
                                static_cast<u8>((*panel)[1].value_or(0))
                            };
                            #endif
                        } else {
                            return Unexpected<ErrorDescription<Error>>(
                                Tags::IN_PLACE,
                                Error::INVALID_TOML_ARRAY,
                                "Invalid homePanels format!"
                            );
                        }
                    }
                } else {
                    return Unexpected<ErrorDescription<Error>>(
                        Tags::IN_PLACE,
                        Error::INVALID_TOML_ARRAY,
                        "Invalid homePanels format!"
                    );
                }

                boardList.push_back(Pointers::shared<BoardInfo>(boardId, boardName, boardWidth, boardHeight, homePanels));
            }
        }

        #ifndef NDEBUG
        LOGGER->debug("Loading board library complete!");
        #endif

        return {};
    }

    /**
     * @brief Get the board information for a given ID.
     *
     * @param id The ID of the board (0 returns nullptr, representing no board).
     * @return SharedPointer to board information (nullptr if id is 0)
     */
    [[nodiscard]]
    SharedPointer<BoardInfo> getBoard(u32 id) const RELEASE_NOEXCEPT {
        #ifndef NDEBUG
        LOGGER->debug("Returning board ID: {}", id);
        #endif 

        return id > 0
            #ifndef NDEBUG
            ? boardList.at(id - 1)
            #else
            ? boardList[id - 1]
            #endif
            : nullptr;
    }

    /**
     * @brief Access board information by ID using array syntax.
     *
     * @param id The ID of the board (0 returns nullptr, representing no board).
     * @return SharedPointer to board information (nullptr if id is 0)
     */
    [[nodiscard]]
    SharedPointer<BoardInfo> operator[](u32 id) const noexcept(noexcept(getBoard(id))) {
        return getBoard(id);
    }
};

END_MODULE_NAMESPACE();

using openjuice::engine::board::BoardLibrary;

template <>
struct Formatter<BoardLibrary::Error> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::iterator format(BoardLibrary::Error err, FormatContext& ctx) {
        StringView name;
        switch (err) {
            case BoardLibrary::Error::DIRECTORY_NOT_FOUND:
                name = "Directory not found"; 
                break;
            case BoardLibrary::Error::INVALID_TOML_ARRAY:
                name = "Invalid TOML array"; 
                break;
            case BoardLibrary::Error::INVALID_TOML_ARRAY_SIZE:
                name = "Invalid TOML array size"; 
                break;
            case BoardLibrary::Error::CORRUPTED_LIBRARY_TOML:
                name = "Corrupted library TOML";
                break;
            default:
                System::unreachable();
        }
        return stdx::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(BoardLibrary::Error);
