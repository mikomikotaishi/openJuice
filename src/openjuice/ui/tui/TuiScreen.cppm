/**
 * @file TuiScreen.cppm
 * @module openjuice.ui.tui.TuiScreen
 * @brief Base class for all TUI screens
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui.TuiScreen;

export import :ScreenType;

import stdx;

import openjuice.engine.game;
import openjuice.engine.services;

import ftxui;

using stdx::mem::SharedPointer;

using openjuice::engine::game::Game;
using openjuice::engine::services::LocalizationService;

using namespace ftxui;

BEGIN_MODULE_NAMESPACE(openjuice::ui::tui);

/**
 * @class TuiScreen
 * @brief Abstract base class for all TUI screens
 */
export class TuiScreen {
protected:
    SharedPointer<Game> game; ///< A shared pointer to the game.
    Component component; ///< An abstract component
    Function<void(ScreenType)> screenSwitchCallback; ///< An callback for screen switching
    SharedPointer<LocalizationService> localization; ///< The injected localization service.

    /**
     * @brief Get the LocalizationService instance safely.
     *
     * @return Reference to the LocalizationService.
     */
    [[nodiscard]]
    const LocalizationService& getLocalizationService() const noexcept {
        return *localization;
    }

    /**
     * @brief Creates the screen component
     */
    virtual void createComponent() noexcept = 0;

    /**
     * @brief Constructor for the TuiScreen class
     *
     * @param game Shared pointer to the game
     * @param callback Function to call when switching screens
     * @param localization Shared pointer to the localization service
     */
    TuiScreen(SharedPointer<Game> game, Function<void(ScreenType)> callback, SharedPointer<LocalizationService> localization):
        game{game}, screenSwitchCallback{callback}, localization{localization} {}

    virtual ~TuiScreen() = default;
public:
    /**
     * @brief Get the FTXUI component for this screen
     *
     * @return The component
     */
    virtual Component getComponent() const noexcept {
        return component;
    }

    /**
     * @brief Called when the screen becomes active
     */
    virtual void onActivate() noexcept = 0;

    /**
     * @brief Called when the screen becomes inactive
     */
    virtual void onDeactivate() noexcept = 0;

    /**
     * @brief Update screen logic
     */
    virtual void update() noexcept = 0;

    /**
     * @brief Check if the screen requested exit
     *
     * @return True if exit was requested, else false
     */
    [[nodiscard]]
    virtual bool shouldExit() const noexcept {
        return false;
    }
};

END_MODULE_NAMESPACE();
