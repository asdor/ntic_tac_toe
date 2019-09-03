#ifndef __CHOOSE_SIDE_STATE_HPP__
#define __CHOOSE_SIDE_STATE_HPP__

#include "dialog_box.hpp"
#include "player_side.hpp"
// #include "game_engine_fwd.hpp"

class GameEngine;

struct SideChoiceState : dialog_box<2>
{
    using base_type = dialog_box<2>;
    SideChoiceState(PlayerSide side);

    void handle_input(int key, GameEngine& engine);

    PlayerSide side_;
};

#endif // __CHOOSE_SIDE_STATE_HPP__
