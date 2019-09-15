#include "pause_state.hpp"
#include "game/game_state.hpp"
#include "game_engine.hpp"
#include "main_menu_state.hpp"

PauseState::PauseState() : base_type("Pause menu", {"Resume", "Main menu", "Exit"})
{
}

void PauseState::handle_input(int key, GameEngine& engine)
{
    const int resp = base_type::handle_input(key);
    switch (resp)
    {
        case 0:
            // engine.set_state<GameState>();
            engine.load_prev_state();
            break;
        case 1:
            engine.set_state<MainMenuState>();
            break;
        case 2:
            engine.quit();
            break;
        default:
            break;
    }
}
