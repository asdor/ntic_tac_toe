#include "choose_side_state.hpp"
#include "common.hpp"
#include "dialog_box.hpp"
#include "game_engine.hpp"

#include <ncurses.h>

SideChoiceState::SideChoiceState() : base_type("Choose player side", {"X", "O"})
{
}

void SideChoiceState::handle_input(int key, GameEngine& engine)
{
    if (key == 'q')
        engine.set_state<MainMenuState>();

    const int resp = base_type::handle_input(key);
    switch (resp)
    {
        case 0:
            engine.set_state<GameState>(PlayerMark::X_MARK);
            break;
        case 1:
            engine.set_state<GameState>(PlayerMark::O_MARK);
            break;
        default:
            break;
    }
}
