#include "game/board.hpp"

GameBoard::GameBoard() : score_{{PlayerMark::X_MARK, 0}, {PlayerMark::O_MARK, 0}}, message_("X turn"), board_({PlayerMark::EMPTY_MARK}), is_end_(false)
{
}

size_t GameBoard::get_score(PlayerMark mark) const
{
    return score_.at(mark);
}

const std::string& GameBoard::get_message() const
{
    return message_;
}

const std::array<PlayerMark, 9>& GameBoard::get_board() const
{
    return board_;
}

std::vector<size_t> GameBoard::possible_pos() const
{
    std::vector<std::size_t> positions;
    for (size_t i = 0; i < board_.size(); ++i)
    {
        if (board_[i] == PlayerMark::EMPTY_MARK)
            positions.push_back(i);
    }

    return positions;
}

bool GameBoard::set_mark(size_t pos, PlayerMark mark)
{
    if (board_[pos] != PlayerMark::EMPTY_MARK)
        return false;

    board_[pos] = mark;
    return true;
}

bool GameBoard::make_move(size_t pos, PlayerMark mark)
{
    if (!set_mark(pos, mark))
        return false;

    if (is_win())
    {
        message_ = mark_to_string(mark) + " win";
        ++score_[mark];
        is_end_ = true;
    }
    else if (is_draw())
    {
        message_ = "Draw";
        is_end_ = true;
    }
    else
    {
        set_turn(next_mark(mark));
    }

    return is_end_ == false;
}

bool GameBoard::is_win() const
{
    if (is_line_win())
        return true;

    if (check_three(0, 4, 8))
        return true;

    if (check_three(2, 4, 6))
        return true;

    return false;
}

bool GameBoard::is_draw() const
{
    return std::all_of(board_.begin(), board_.end(), [](const PlayerMark& mark) { return mark != PlayerMark::EMPTY_MARK; });
}

bool GameBoard::is_end() const
{
    return is_end_;
}

void GameBoard::new_round()
{
    board_.fill(PlayerMark::EMPTY_MARK);
    is_end_ = false;
}

void GameBoard::set_turn(PlayerMark mark)
{
    message_ = mark_to_string(mark) + " turn";
}

bool GameBoard::check_three(size_t ind0, size_t ind1, size_t ind2) const
{
    return board_[ind0] != PlayerMark::EMPTY_MARK && board_[ind0] == board_[ind1] && board_[ind1] == board_[ind2];
}

bool GameBoard::is_line_win() const
{
    for (size_t i = 0; i < 3; ++i)
    {
        if (check_three(i * 3, i * 3 + 1, i * 3 + 2))
            return true;

        if (check_three(i, i + 3, i + 2 * 3))
            return true;
    }

    return false;
}
