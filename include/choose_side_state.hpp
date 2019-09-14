#ifndef __CHOOSE_SIDE_STATE_HPP__
#define __CHOOSE_SIDE_STATE_HPP__

#include "dialog_box.hpp"

class GameEngine;

struct SideChoiceState : dialog_box<2>
{
    using base_type = dialog_box<2>;
    SideChoiceState();

    void handle_input(int key, GameEngine& engine);
};

#endif // __CHOOSE_SIDE_STATE_HPP__
