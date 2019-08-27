#include "main_menu_state.hpp"
#include "dialog_box.hpp"
#include "game_engine.hpp"

#include "ncurses.h"

main_menu_state::main_menu_state() : base_type("Main menu", {"Player vs Player", "Player vs AI", "Exit"})
{
}

void main_menu_state::handle_input(int key, game_engine& engine)
{
    if (key == 'q')
    {
        engine.quit();
    }
    else
    {
        base_type::handle_input(key);
    }
}

void main_menu_state::draw()
{
    base_type::draw();
    // clear();
    // printw("Main menu!");
}