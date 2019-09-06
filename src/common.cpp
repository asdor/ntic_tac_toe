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

void draw_horz_line(WINDOW* win, size_t y0, size_t x0, size_t ncolumns, int c_ch, int l_ch, int r_ch)
{
    mvwaddch(win, y0, x0, l_ch);
    mvwaddch(win, y0, ncolumns - 1, r_ch);

    wmove(win, y0, x0 + 1);
    whline(win, c_ch, ncolumns - 2);
}
