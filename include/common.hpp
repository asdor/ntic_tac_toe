#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <memory>

#include <ncurses.h>

enum class PlayerMark
{
    EMPTY_MARK = 0,
    X_MARK,
    O_MARK
};

std::string mark_to_string(PlayerMark mark);

PlayerMark next_mark(PlayerMark mark);

void draw_horz_line(WINDOW* win, size_t y0, size_t x0, size_t ncolumns, int c_ch, int l_ch, int r_ch);

#endif // __COMMON_HPP__
