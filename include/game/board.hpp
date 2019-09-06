#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <array>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

#include "common.hpp"

class GameBoard
{
public:
    GameBoard() : score_{{PlayerMark::X_MARK, 0}, {PlayerMark::O_MARK, 103}}, message_("X turn"), board_({PlayerMark::EMPTY_MARK}), is_end_(false)
    {

    }

    bool set_mark(size_t pos, PlayerMark mark)
    {
        if (board_[pos] != PlayerMark::EMPTY_MARK)
            return false;

        board_[pos] = mark;
        return true;
    }

    const std::map<PlayerMark, size_t>& get_score() const
    {
        return score_;
    }

    const std::string& get_message() const
    {
        return message_;
    }

    const std::array<PlayerMark, 9>& get_board() const
    {
        return board_;
    }

    auto possible_pos() const
    {
        std::vector<std::size_t> positions;
        for (size_t i = 0; i < board_.size(); ++i)
        {
            if (board_[i] == PlayerMark::EMPTY_MARK)
                positions.push_back(i);
        }

        return positions;
    }

    bool make_move(size_t pos, PlayerMark mark)
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

        return is_end_ == false;
    }

    bool is_win() const
    {
        if (is_equal_marks(1) || is_equal_marks(3))
            return true;

        if (check_three(0, 4, 8))
            return true;

        if (check_three(2, 4, 6))
            return true;

        return false;
    }

    bool is_draw() const
    {
        return std::all_of(board_.begin(), board_.end(), [](const PlayerMark& mark) {
            return mark != PlayerMark::EMPTY_MARK;
        });
    }

    bool is_end() const
    {
        return is_end_;
    }

    void new_round()
    {
        board_.fill(PlayerMark::EMPTY_MARK);
        is_end_ = false;
    }

private:
    bool check_three(size_t ind0, size_t ind1, size_t ind2) const
    {
        return board_[ind0] == board_[ind1] && board_[ind1] == board_[ind2];
    }

    bool is_equal_marks(size_t stride) const
    {
        for (size_t i = 0; i < 3; ++i)
        {
            if (check_three(i, i + stride, i + 2 * stride))
                return true;
        }

        return false;
    }

    std::map<PlayerMark, size_t> score_;
    std::string message_;
    std::array<PlayerMark, 9> board_;

    bool is_end_;
};

#endif // __BOARD_HPP__
