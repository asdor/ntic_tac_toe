#ifndef __UI_MAIN_HPP__
#define __UI_MAIN_HPP__

#include <ncurses.h>

#include "defs.hpp"
#include "ui_cell.hpp"

class ui_main
{
public:
    ui_main()
    {
        int y_max = 0;
        int x_max = 0;
        getmaxyx(stdscr, y_max, x_max);

        // const int d_box_height = 5;
        // const int d_box_width = x_max - 10;
        // const int d_y_pos = y_max - d_box_height - 2;
        // const int d_x_pos = 5;

        score_box_ = newwin(defs::board_height / 2 + 1, defs::board_width, y_max / 2 - defs::board_height / 2, x_max / 2);
        dialog_box_ = newwin(defs::board_height / 2 + 1, defs::board_width, y_max / 2, x_max / 2);

        // const int b_y_pos = d_y_pos - defs::board_height;
        // const int b_x_pos = d_x_pos;

        const int b_y_pos = y_max / 2 - defs::board_height / 2;
        const int b_x_pos = x_max / 2 - defs::board_width;

        board_ = newwin(defs::board_height, defs::board_width, b_y_pos, b_x_pos);
    }

    void draw() const
    {
        wclear(score_box_);
        wborder(score_box_, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LTEE, ACS_RTEE);
        // box(score_box_, 0, 0);
        wrefresh(score_box_);

        wclear(dialog_box_);
        wborder(dialog_box_, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_LTEE, ACS_RTEE, ACS_LLCORNER, ACS_LRCORNER);
        // box(dialog_box_, 0, 0);
        wrefresh(dialog_box_);

        wclear(board_);
        cell.draw(board_);
        wrefresh(board_);

        // int y_max = 0;
        // int x_max = 0;
        // getmaxyx(stdscr, y_max, x_max);
        // mvwaddch(stdscr, y_max / 2, x_max / 2, 'O');
    }

    ~ui_main()
    {
        delwin(board_);
        delwin(score_box_);
        delwin(dialog_box_);
    }

private:
    WINDOW* board_;
    WINDOW* score_box_;
    WINDOW* dialog_box_;

    ui_cell cell;
};

#endif // __UI_MAIN_HPP__
