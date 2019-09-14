#ifndef __GAME_STATE_HPP__
#define __GAME_STATE_HPP__

#include <memory>
#include <variant>

#include "board.hpp"
#include "common.hpp"
#include "game/game_type.hpp"

#include <ncurses.h>

class GameEngine;

class GameState
{
public:
    GameState();
    GameState(PlayerMark mark);
    void handle_input(int key, GameEngine& engine);
    int get_char();
    void draw();

private:
    void init_game_state();
    void draw_message_box();
    void draw_board_box();

    std::variant<PvP_Type, PvAI_Type> game_type_;
    GameBoard game_board_;
    window_type_ message_box_;
    window_type_ board_box_;
    size_t cursor_pos_y;
    size_t cursor_pos_x;
};

#endif // __GAME_STATE_HPP__
