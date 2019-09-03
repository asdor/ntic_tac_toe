#include "main_menu_state.hpp"
#include "choose_side_state.hpp"
#include "dialog_box.hpp"
#include "game_engine.hpp"
#include "player_side.hpp"

#include <ncurses.h>

MainMenuState::MainMenuState() : base_type("Main menu", {"Player vs Player", "Player vs AI", "Exit"})
{
}

void MainMenuState::handle_input(int key, GameEngine& engine)
{
    if (key == 'q')
        engine.quit();

    const int resp = base_type::handle_input(key);
    switch (resp)
    {
        case 0:
            engine.set_state<SideChoiceState>(PlayerSide::PLAYER_X);
            break;
        case 1:
            /* code */
            break;
        case 2:
            engine.quit();
            break;
        default:
            break;
    }
}
