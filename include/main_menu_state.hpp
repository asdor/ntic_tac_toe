#ifndef __MAIN_MENU_STATE_HPP__
#define __MAIN_MENU_STATE_HPP__

#include "dialog_box.hpp"
// #include "game_engine_fwd.hpp"

class GameEngine;

struct MainMenuState : dialog_box<3>
{
    using base_type = dialog_box<3>;
    MainMenuState();

    void handle_input(int key, GameEngine& engine);
};

#endif // __MAIN_MENU_STATE_HPP__
