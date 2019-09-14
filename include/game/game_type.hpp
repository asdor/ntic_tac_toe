#ifndef __GAME_TYPE_HPP__
#define __GAME_TYPE_HPP__

#include <vector>

#include "common.hpp"


class GameBoard;

class PvP_Type
{
public:
    PvP_Type();
    void init();
    void on_enter(GameBoard& board, int pos);
    void reset(GameBoard& board);

private:
    PlayerMark cur_player_;
};

class PvAI_Type
{
public:
    PvAI_Type(PlayerMark user_mark);
    void init();
    void on_enter(GameBoard& board, int pos);
    void reset(GameBoard& board);

private:
    static size_t choose(const std::vector<std::size_t>& possible_pos);
    PlayerMark user_mark_;
    PlayerMark AI_mark_;
};

#endif // __GAME_TYPE_HPP__
