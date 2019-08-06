#ifndef __UI_CELL_HPP__
#define __UI_CELL_HPP__

#include <ncurses.h>

#include "defs.hpp"

class ui_cell
{
public:
    ui_cell() : curr_y_(0), curr_x_(0) {}

    void draw(WINDOW* win) const
    {
        const size_t stride_y = defs::cell_height + 1;
        for (size_t y0 = 1; y0 < defs::board_height; y0 += stride_y)
        {
            for (size_t i = 0; i < defs::cell_height; ++i)
                draw_hor_line(win, y0 + i, 0);
        }

        int y0 = 0;
        draw_vert_line(win, y0, 0, ACS_ULCORNER, ACS_TTEE, ACS_URCORNER);
        y0 += stride_y;
        draw_vert_line(win, y0, 0, ACS_LTEE, ACS_PLUS, ACS_RTEE);
        y0 += stride_y;
        draw_vert_line(win, y0, 0, ACS_LTEE, ACS_PLUS, ACS_RTEE);
        y0 += stride_y;
        draw_vert_line(win, y0, 0, ACS_LLCORNER, ACS_BTEE, ACS_LRCORNER);

        const size_t stride_x = defs::cell_width + 1;
        mvwaddch(win, stride_y / 2, stride_x / 2, 'X');
        mvwaddch(win, stride_y / 2 + stride_y, stride_x / 2, 'O');
        // mvwaddch(win, 1, 2 + defs::cell_width + 1, 'O');
    }

private:
    static void draw_hor_line(WINDOW* win, int y0, int x0)
    {
        for (size_t i = 0; i < defs::board_width; i += defs::cell_width + 1)
            mvwaddch(win, y0, x0 + i, ACS_VLINE);
    }

    static void draw_vert_line(WINDOW* win, int y0, int x0, chtype l_border, chtype middle, chtype r_border)
    {
        mvwaddch(win, y0, x0, l_border);
        x0 += 1;

        for (size_t i = 0; i < defs::cell_width; ++i)
            mvwaddch(win, y0, x0 + i, ACS_HLINE);
        x0 += defs::cell_width;

        mvwaddch(win, y0, x0, middle);
        x0 += 1;

        for (size_t i = 0; i < defs::cell_width; ++i)
            mvwaddch(win, y0, x0 + i, ACS_HLINE);
        x0 += defs::cell_width;

        mvwaddch(win, y0, x0, middle);
        x0 += 1;

        for (size_t i = 0; i < defs::cell_width; ++i)
            mvwaddch(win, y0, x0 + i, ACS_HLINE);
        x0 += defs::cell_width;

        mvwaddch(win, y0, x0, r_border);
    }

    int curr_y_;
    int curr_x_;
};

#endif // __UI_CELL_HPP__
