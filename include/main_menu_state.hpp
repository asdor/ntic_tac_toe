#ifndef __MAIN_MENU_STATE_HPP__
#define __MAIN_MENU_STATE_HPP__

#include "dialog_box.hpp"

class game_engine;

struct main_menu_state : dialog_box<3>
{
    using base_type = dialog_box<3>;
    main_menu_state();

    void handle_input(int key, game_engine& engine);

    void draw();
};

#endif // __MAIN_MENU_STATE_HPP__
