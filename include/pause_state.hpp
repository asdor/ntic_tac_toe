#ifndef __PAUSE_STATE_HPP__
#define __PAUSE_STATE_HPP__

#include "dialog_box.hpp"

class GameEngine;

struct PauseState : dialog_box<3>
{
    using base_type = dialog_box<3>;
    PauseState();

    void handle_input(int key, GameEngine& engine);
};

#endif // __PAUSE_STATE_HPP__
