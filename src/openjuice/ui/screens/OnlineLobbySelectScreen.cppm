/**
 * @file OnlineLobbySelectScreen.cppm
 * @module openjuice.ui.screens:OnlineLobbySelectScreen
 * @brief Definition of the OnlineLobbySelectScreen class.
 *
 * This is the lobby selection screen for multiplayer. It searches the local network for hosted
 * games through the networking service and lists them, with a private-lobby toggle, a mode tab, and
 * actions to refresh, search, go back, create a lobby, or join the selected one.
 */

module;

#include "Macros.hpp"

export module openjuice.ui.screens:OnlineLobbySelectScreen;

import stdx;

import openjuice.engine.game;
import openjuice.engine.localization;
import openjuice.engine.net;
import openjuice.ui.Screen;

import ftxui;

using stdx::collections::Vector;
using stdx::mem::SharedPointer;
using stdx::sync::Atomic;

using openjuice::engine::game::Game;
using openjuice::engine::localization::LocalizationService;
using openjuice::engine::net::NetworkingService;
using openjuice::ui::Screen;

using namespace ftxui;

BEGIN_MODULE_NAMESPACE(openjuice::ui::screens);

/**
 * @class OnlineLobbySelectScreen
 * @brief Multiplayer lobby selection screen implementation
 * @extends Screen
 */
export class OnlineLobbySelectScreen final: public Screen {
private:
    static constexpr i32 COL_NAME = 24;
    static constexpr i32 COL_PUBLIC = 8;
    static constexpr i32 COL_PLAYERS = 9;
    static constexpr i32 COL_TIMER = 8;
    static constexpr i32 COL_EVENTS = 10;
    static constexpr i32 COL_FIELD = 20;

    SharedPointer<NetworkingService> networking; ///< The injected networking service.

    bool showPrivate = false; ///< Whether private lobbies are shown in the list.
    Vector<String> tabNames = {"Normal"}; ///< Mode tabs; only one for now.
    i32 selectedTab = 0; ///< The currently selected mode tab.

    Vector<NetworkingService::DiscoveredLobby> visibleLobbies; ///< The lobbies currently shown, in list order. UI thread only.
    Vector<String> lobbyRows; ///< Pre-formatted, column-aligned row strings the menu displays.
    i32 selectedLobby = 0; ///< Index of the highlighted lobby in the list.
    Atomic<bool> lobbiesDirty = false; ///< Set from the discovery thread when new results arrive; drained on the UI thread.

    Component tabToggle; ///< Mode tab selector.
    Component privateCheckbox; ///< "Show private lobbies" toggle.
    Component lobbyMenu; ///< The selectable list of lobbies.
    Component refreshButton; ///< Re-queries the local network.
    Component searchButton; ///< Filters the list (placeholder).
    Component backButton; ///< Returns to the main menu.
    Component createButton; ///< Goes to lobby creation.
    Component joinButton; ///< Joins the selected lobby (unimplemented).

    bool initialized = false; ///< Whether the screen's components have been built.

    /**
     * @brief Pad or truncate text to a fixed column width.
     * @param text The text to fit.
     * @param width The target width in characters.
     * @return The text fitted to exactly @p width columns.
     */
    [[nodiscard]]
    static String fitColumn(StringView text, i32 width) noexcept {
        const usize target = static_cast<usize>(width);
        String out = String(text);

        if (out.size() > target) {
            out.resize(target);
        } else {
            out.append(target - out.size(), ' ');
        }

        return out;
    }

    /**
     * @brief Format one lobby as a single column-aligned row.
     * @param lobby The lobby to format.
     * @return The row string.
     */
    [[nodiscard]]
    static String formatRow(const NetworkingService::DiscoveredLobby& lobby) noexcept {
        return Ops::fmt(
            "{} {} {} {} {} {}",
            fitColumn(lobby.name, COL_NAME),
            fitColumn(lobby.passwordProtected ? "Private" : "Public", COL_PUBLIC),
            fitColumn(Ops::fmt("{}/{}", lobby.players, lobby.maxPlayers), COL_PLAYERS),
            fitColumn(lobby.timer, COL_TIMER),
            fitColumn(lobby.events, COL_EVENTS),
            fitColumn(lobby.fieldName, COL_FIELD)
        );
    }

    /**
     * @brief The header row, using the same column widths as the entries.
     * @return The header element.
     */
    [[nodiscard]]
    Element headerRow() const noexcept {
        return hbox({
            text(fitColumn("Lobby name", COL_NAME)) | bold,
            text(" "),
            text(fitColumn("Public", COL_PUBLIC)) | bold,
            text(" "),
            text(fitColumn("Players", COL_PLAYERS)) | bold,
            text(" "),
            text(fitColumn("Timer", COL_TIMER)) | bold,
            text(" "),
            text(fitColumn("Events", COL_EVENTS)) | bold,
            text(" "),
            text(fitColumn("Field name", COL_FIELD)) | bold,
        });
    }

    /**
     * @brief Rebuild the visible list from the latest discovery results.
     *
     * Runs on the UI thread. Pulls a fresh snapshot from the networking service, applies the
     * private-lobby filter, and regenerates the row strings. Keeps the selection in range.
     */
    void rebuildList() noexcept {
        visibleLobbies.clear();
        lobbyRows.clear();

        for (const NetworkingService::DiscoveredLobby& lobby: networking->collectLobbies()) {
            if (lobby.passwordProtected && !showPrivate) {
                continue;
            }

            lobbyRows.push_back(formatRow(lobby));
            visibleLobbies.push_back(lobby);
        }

        if (selectedLobby >= static_cast<i32>(lobbyRows.size())) {
            selectedLobby = lobbyRows.empty() ? 0 : static_cast<i32>(lobbyRows.size()) - 1;
        }
    }

    /**
     * @brief Join the currently selected lobby.
     *
     * Currently unimplemented beyond navigation intent: there is no join handshake yet, so this
     * only guards against an empty selection and reports when nothing is selected.
     */
    void joinSelected() noexcept {
        if (visibleLobbies.empty() || selectedLobby < 0 || selectedLobby >= static_cast<i32>(visibleLobbies.size())) {
            showError("No lobby selected to join.");
            return;
        }

        // TODO: perform the join handshake through the networking service, then switch to the lobby.
    }

    /**
     * @brief Creates the screen component
     */
    void createComponent() noexcept override final {
        if (initialized) {
            return;
        }

        privateCheckbox = Checkbox("Show private lobbies", &showPrivate);
        tabToggle = Toggle(&tabNames, &selectedTab);
        lobbyMenu = Menu(&lobbyRows, &selectedLobby);

        refreshButton = Button("Refresh", [this] -> void {
            networking->refreshDiscovery();
            rebuildList();
        });

        searchButton = Button("Search", [this] -> void {
            // TODO: filter the list by a search term.
        });

        backButton = Button("Back", [this] -> void {
            switchScreen(Screen::Of::MAIN_MENU);
        });

        createButton = Button("Create", [this] -> void {
            switchScreen(Screen::Of::ONLINE_LOBBY_CREATE);
        });

        joinButton = Button("Join", [this] -> void {
            joinSelected();
        });

        Component buttons = Container::Horizontal({
            refreshButton,
            searchButton,
            backButton,
            createButton,
            joinButton,
        });

        Component mainContainer = Container::Vertical({
            privateCheckbox,
            tabToggle,
            lobbyMenu,
            buttons,
        });

        Component componentWithEvents = CatchEvent(mainContainer, [this](Event event) -> bool {
            if (event == Event::Escape || event == Event::Character('q')) {
                switchScreen(Screen::Of::MAIN_MENU);
                return true;
            }
            return false;
        });

        component = Renderer(componentWithEvents, [this] -> Element {
            // Fold in any results the discovery thread reported since the last frame.
            if (lobbiesDirty.exchange(false)) {
                rebuildList();
            }

            Element list = lobbyRows.empty()
                ? text("Searching the local network for lobbies...") | dim | center
                : lobbyMenu->Render();

            return vbox({
                text("Multiplayer Lobbies") | bold | center,
                separator(),
                privateCheckbox->Render(),
                separator(),
                tabToggle->Render(),
                separator(),
                headerRow(),
                separator(),
                list
                    | vscroll_indicator | yframe
                    | size(HEIGHT, LESS_THAN, 14)
                    | flex,
                separator(),
                hbox({
                    refreshButton->Render(),
                    text(" "),
                    searchButton->Render(),
                    text(" "),
                    backButton->Render(),
                    text(" "),
                    createButton->Render(),
                    text(" "),
                    joinButton->Render(),
                }) | center,
            }) | border | flex;
        });

        initialized = true;
    }
public:
    /**
     * @brief Constructor for the OnlineLobbySelectScreen class
     * @param game Shared pointer to the game
     * @param host The interface running this screen
     * @param localization Shared pointer to the localization service
     * @param networking Shared pointer to the networking service
     */
    OnlineLobbySelectScreen(SharedPointer<Game> game, Host& host, SharedPointer<LocalizationService> localization, SharedPointer<NetworkingService> networking):
        Screen(game, host, localization), networking{networking} {
        createComponent();
    }

    /**
     * @brief Called when screen becomes active
     *
     * Starts searching the local network. The discovery callback only flags that new results are
     * waiting; the actual list rebuild happens on the UI thread in the render lambda.
     */
    void onActivate() noexcept override final {
        selectedLobby = 0;
        lobbiesDirty.store(true);

        static_cast<void>(networking->startDiscovery([this] -> void {
            lobbiesDirty.store(true);
        }));
    }

    /**
     * @brief Called when screen becomes inactive
     *
     * Stops the network search so no discovery traffic or thread outlives the screen being shown.
     */
    void onDeactivate() noexcept override final {
        networking->stopDiscovery();
    }

    /**
     * @brief Update screen
     */
    void update() noexcept override final {

    }
};

END_MODULE_NAMESPACE();
