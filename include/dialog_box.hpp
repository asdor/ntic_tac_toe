#ifndef __DIALOG_BOX_HPP__
#define __DIALOG_BOX_HPP__

#include <algorithm>
#include <array>
#include <memory>
#include <string>

#include "common.hpp"

#include <ncurses.h>

template<size_t N>
class dialog_box
{
public:
    dialog_box(const std::string& title, const std::array<std::string, N>& choices)
        : title_(title), choices_(choices), dialog_window_(nullptr, delwin), highlight_(0), win_height_(0), win_width_(0)
    {
        int y_max = 0;
        int x_max = 0;
        getmaxyx(stdscr, y_max, x_max);

        const size_t max_width = get_max_width();
        win_height_ = N + 4;
        win_width_ = max_width + 4;

        dialog_window_ = window_type_(newwin(win_height_, win_width_, y_max / 2 - win_height_ / 2, x_max / 2 - win_width_ / 2), delwin);
        clear();
        refresh();
        draw_items();
        curs_set(0);
        keypad(dialog_window_.get(), true);
    }

    int get_char()
    {
        return wgetch(dialog_window_.get());
    }

    int handle_input(int key)
    {
        switch (key)
        {
            case 'S':
            case 's':
                highlight_ = wrap(highlight_ + 1, 0, N - 1);
                break;
            case 'W':
            case 'w':
                highlight_ = wrap(highlight_ - 1, 0, N - 1);
                break;
            case 10:
                return highlight_;
            default:
                break;
        }

        return -1;
    }

    void draw()
    {
        for (size_t i = 0; i < N; ++i)
        {
            if (i == highlight_)
                wattron(dialog_window_.get(), A_REVERSE);
            else
                wattroff(dialog_window_.get(), A_REVERSE);

            mvwprintw(dialog_window_.get(), i + 3, 2, choices_[i].c_str());
        }
    }

private:
    void print_in_center(size_t y0, const std::string& str)
    {
        const size_t pos = (win_width_ - str.size()) / 2;
        mvwprintw(dialog_window_.get(), y0, pos, str.c_str());
    }

    void draw_items()
    {
        box(dialog_window_.get(), 0, 0);

        draw_horz_line(dialog_window_.get(), 2, 0, win_width_, ACS_HLINE, ACS_LTEE, ACS_RTEE);

        print_in_center(1, title_);

        for (size_t i = 0; i < N; ++i)
            mvwprintw(dialog_window_.get(), i + 3, 2, choices_[i].c_str());
    }

    size_t get_max_width() const
    {
        auto comp = [](const std::string& s1, const std::string& s2) { return s1.size() < s2.size(); };

        const auto max_from_choice = std::max_element(choices_.begin(), choices_.end(), comp);
        const std::string max_str = std::max(title_, *max_from_choice, comp);
        return max_str.size();
    }

    static size_t wrap(int key, size_t min_val, size_t max_val)
    {
        if (key > static_cast<int>(max_val))
            return min_val;
        else if (key < static_cast<int>(min_val))
            return max_val;
        else
            return static_cast<size_t>(key);
    }

    std::string title_;
    std::array<std::string, N> choices_;
    window_type_ dialog_window_;
    size_t highlight_;
    size_t win_height_;
    size_t win_width_;
};

#endif // __DIALOG_BOX_HPP__
