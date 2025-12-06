/**
 * @file BoardLibrary.cppm
 * @module openjuice.engine.board.BoardLibrary
 * @brief Implementation of the BoardLibrary class.
 *
 * This file contains the implementation of the BoardLibrary class, which is used to load and manage boards.
 */

module;

// Standard library headers are necessary here - there is no workaround
#include <filesystem>

#include "Macros.hpp"

export module openjuice.engine.board.BoardLibrary;

export import :BoardLibraryError;

import std;
import stdx;

import openjuice.engine.board.BoardInfo;
import openjuice.engine.managers.GlobalSettings;

import tomlpp;

using std::collections::Vector;
using std::fs::DirectoryEntry;
using std::fs::DirectoryIterator;
using std::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

namespace fs = std::fs;
namespace mem = std::mem;

using toml::TomlArray;
using toml::TomlTable;

BEGIN_MODULE_NAMESPACE(openjuice::engine::board);

/**
 * @class BoardLibrary
 * @brief Singleton class for loading and managing boards.
 *
 * The BoardLibrary class is a singleton class that loads and manages boards from files.
 */
export class BoardLibrary {
public:
    static constexpr StringView MAPS_DIR = "./maps"; ///< The maps directory path.
private:
    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("BoardLibrary"); ///< The logger instance.

    Vector<SharedPointer<BoardInfo>> boardList; ///< List of loaded boards.
    
    /**
     * @brief Private constructor to prevent instantiation.
     */
    BoardLibrary() {
        if (Expected<void, Error<BoardLibraryError>> r = loadBoards(); r) {
            LOGGER->info("Successfully loaded {} boards!", boardList.size());
        } else {
            LOGGER->warn(
                "Board libraries were not successfully initialised! Error: {}, {} boards successfully loaded",
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
    Expected<void, Error<BoardLibraryError>> loadBoards(StringView directory = MAPS_DIR) {
        #ifndef NDEBUG
        LOGGER->debug("Loading boards from directory: {}", directory);
        #endif
        
        if (!fs::exists(directory)) {
            return Unexpected<Error<BoardLibraryError>>(
                Tags::IN_PLACE,
                BoardLibraryError::DIRECTORY_NOT_FOUND,
                fmt::format("The directory {} was not found!", directory)
            );
        }
        for (const DirectoryEntry& entry: DirectoryIterator(directory)) {
            if (entry.is_regular_file() && entry.path().extension() == ".toml") {
                String boardPath = entry.path().string();
                TomlTable data = toml::parse_file(boardPath);

                u32 id = *data["id"].value<u32>();
                String boardName = *data["name"].value<String>();
                u8 boardWidth = *data["width"].value<u8>();
                u8 boardHeight = *data["height"].value<u8>();
                Array<Pair<u8, u8>, BoardInfo::MAX_PLAYERS> homePanels;

                const TomlArray* homePanelsData = data["homePanels"].as_array();
                if (homePanelsData) {
                    for (usize i = 0; i < homePanelsData->size() && i < BoardInfo::MAX_PLAYERS; ++i) {
                        const TomlArray* panel = (*homePanelsData)[i].as_array();
                        if (panel) {
                            if (panel->size() != 2) {
                                return Unexpected<Error<BoardLibraryError>>(
                                    Tags::IN_PLACE,
                                    BoardLibraryError::INVALID_TOML_ARRAY_SIZE,
                                    fmt::format("Invalid homePanels size: expected 2, got {}", panel->size())
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
                            return Unexpected<Error<BoardLibraryError>>(
                                Tags::IN_PLACE,
                                BoardLibraryError::INVALID_TOML_ARRAY,
                                "Invalid homePanels format!"
                            );
                        }
                    }
                } else {
                    return Unexpected<Error<BoardLibraryError>>(
                        Tags::IN_PLACE,
                        BoardLibraryError::INVALID_TOML_ARRAY,
                        "Invalid homePanels format!"
                    );
                }

                boardList.push_back(mem::make_shared<BoardInfo>(id, boardName, boardWidth, boardHeight, homePanels));
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
