/**
 * @file ScreenHost.cppm
 * @module openjuice.ui.tui.TuiScreen:ScreenHost
 * @brief Capabilities a screen requires from whatever is hosting it.
 */

module;

#include "Macros.hpp"

export module openjuice.ui.tui.TuiScreen:ScreenHost;

import :ScreenType;

import stdx;

BEGIN_MODULE_NAMESPACE(openjuice::ui::tui);

/**
 * @class ScreenHost
 * @brief The interface a screen uses to talk back to the interface running it.
 *
 * Screens do not own navigation or the terminal, so anything that outlives a single screen is
 * requested through this interface rather than performed directly. It is implemented by the
 * interface that owns the screens (TextUserInterface), and deliberately not an engine service:
 * every capability here is tied to a running TUI, which the engine has no notion of.
 */
export class ScreenHost {
public:
    virtual ~ScreenHost() = default;

    /**
     * @brief Request a switch to a different screen.
     * @param type The screen to switch to
     */
    virtual void switchScreen(ScreenType type) noexcept = 0;

    /**
     * @brief Report a failure to the user in a dialog they must acknowledge.
     * @param message The message to show
     *
     * For failures the user needs to know about, as opposed to the technical cause, which the
     * service that failed is responsible for logging.
     */
    virtual void showError(StringView message) noexcept = 0;
};

END_MODULE_NAMESPACE();
