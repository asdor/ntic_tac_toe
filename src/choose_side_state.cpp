#include "choose_side_state.hpp"
#include "dialog_box.hpp"
#include "game_engine.hpp"

#include <ncurses.h>

SideChoiceState::SideChoiceState(PlayerSide side) : base_type("Choose side", {"X", "O"}), side_(side)
{
}

void SideChoiceState::handle_input(int key, GameEngine& engine)
{
    if (key == 'q')
    {
        engine.quit();
    }
    base_type::handle_input(key);
}
