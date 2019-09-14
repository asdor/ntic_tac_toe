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
    GameBoard();

    size_t get_score(PlayerMark mark) const;

    const std::string& get_message() const;
    const std::array<PlayerMark, 9>& get_board() const;
    std::vector<size_t> possible_pos() const;

    bool set_mark(size_t pos, PlayerMark mark);
    bool make_move(size_t pos, PlayerMark mark);
    bool is_win() const;
    bool is_draw() const;
    bool is_end() const;

    void new_round();
    void set_turn(PlayerMark mark);

private:
    bool check_three(size_t ind0, size_t ind1, size_t ind2) const;
    bool is_line_win() const;

    std::map<PlayerMark, size_t> score_;
    std::string message_;
    std::array<PlayerMark, 9> board_;

    bool is_end_;
};

#endif // __BOARD_HPP__
