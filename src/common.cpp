#include "common.hpp"

std::string mark_to_string(PlayerMark mark)
{
    if (mark == PlayerMark::EMPTY_MARK)
        return " ";
    else if (mark == PlayerMark::X_MARK)
        return "X";
    else
        return "O";
}

PlayerMark next_mark(PlayerMark mark)
{
    if (mark == PlayerMark::X_MARK)
        return PlayerMark::O_MARK;
    else if (mark == PlayerMark::O_MARK)
        return PlayerMark::X_MARK;
    else
        return PlayerMark::EMPTY_MARK;
}

void draw_horz_line(WINDOW* win, size_t y0, size_t x0, size_t ncolumns, int l_ch, int c_ch, int r_ch)
{
    mvwaddch(win, y0, x0, l_ch);
    mvwaddch(win, y0, x0 + ncolumns - 1, r_ch);

    wmove(win, y0, x0 + 1);
    whline(win, c_ch, ncolumns - 2);
}

void draw_vert_line(WINDOW* win, size_t y0, size_t x0, size_t nrows, int t_ch, int c_ch, int b_ch)
{
    mvwaddch(win, y0, x0, t_ch);
    mvwaddch(win, y0 + nrows - 1, x0, b_ch);

    wmove(win, y0 + 1, x0);
    wvline(win, c_ch, nrows - 2);
}

size_t wrap(int key, size_t min_val, size_t max_val)
{
    if (key > static_cast<int>(max_val))
        return min_val;
    else if (key < static_cast<int>(min_val))
        return max_val;
    else
        return static_cast<size_t>(key);
}
