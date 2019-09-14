#include <algorithm>
#include <random>

#include "game/board.hpp"
#include "game/game_type.hpp"

PvP_Type::PvP_Type() : cur_player_(PlayerMark::X_MARK)
{
}

void PvP_Type::on_enter(GameBoard& board, int pos)
{
    if (board.make_move(pos, cur_player_))
        cur_player_ = next_mark(cur_player_);
}

void PvP_Type::reset(GameBoard& board)
{
    cur_player_ = PlayerMark::X_MARK;
    board.set_turn(cur_player_);
}

PvAI_Type::PvAI_Type(PlayerMark user_mark) : user_mark_(user_mark), AI_mark_(next_mark(user_mark))
{
}

void PvAI_Type::on_enter(GameBoard& board, int pos)
{
    if (board.make_move(pos, user_mark_))
    {
        const size_t ai_pos = choose(board.possible_pos());
        board.make_move(ai_pos, AI_mark_);
    }
}

void PvAI_Type::reset(GameBoard& board)
{
    if (AI_mark_ == PlayerMark::X_MARK)
    {
        const size_t ai_pos = choose(board.possible_pos());
        board.make_move(ai_pos, AI_mark_);
    }
    else
    {
        board.set_turn(user_mark_);
    }
}

size_t PvAI_Type::choose(const std::vector<std::size_t>& possible_pos)
{
    size_t pos = 0;
    std::sample(possible_pos.begin(), possible_pos.end(), &pos, 1, std::mt19937{std::random_device{}()});
    return pos;
}
