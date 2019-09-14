#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <memory>

#include <ncurses.h>

enum class PlayerMark
{
    EMPTY_MARK = 0,
    X_MARK = 1,
    O_MARK = 2
};

std::string mark_to_string(PlayerMark mark);

PlayerMark next_mark(PlayerMark mark);

void draw_horz_line(WINDOW* win, size_t y0, size_t x0, size_t ncolumns, int l_ch, int c_ch, int r_ch);
void draw_vert_line(WINDOW* win, size_t y0, size_t x0, size_t ncolumns, int t_ch, int c_ch, int b_ch);

size_t wrap(int key, size_t min_val, size_t max_val);

using window_type_ = std::unique_ptr<WINDOW, decltype(&delwin)>;

#endif // __COMMON_HPP__
