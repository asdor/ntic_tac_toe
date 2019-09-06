#ifndef __GAME_STATE_HPP__
#define __GAME_STATE_HPP__

#include <memory>

#include "board.hpp"
#include "common.hpp"

#include <ncurses.h>

class GameEngine;

class GameState
{
public:
    GameState();
    void handle_input(int key, GameEngine& engine);
    int get_char();
    void draw();

private:
    void draw_message_box();
    void draw_board_box();

    GameBoard game_board_;
    window_type_ message_box_;
    window_type_ board_box_;
};

#endif // __GAME_STATE_HPP__
