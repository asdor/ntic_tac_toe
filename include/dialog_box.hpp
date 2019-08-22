#ifndef __DIALOG_BOX_HPP__
#define __DIALOG_BOX_HPP__

#include <algorithm>
#include <array>
#include <ncurses.h>
#include <string>

template<size_t N>
class dialog_box
{
public:
    dialog_box(const std::string& title, const std::array<std::string, N>& choices)
        : title_(title), choices_(choices), dialog_window_(nullptr), highlight_(0), scr(stdscr)
    {
        int y_max = 0;
        int x_max = 0;
        getmaxyx(stdscr, y_max, x_max);

        // const size_t max_width = get_max_width();
        // const size_t height = N + 4;
        // const size_t width = max_width + 2;

        // dialog_window_ = newwin(height, width, y_max / 2 - height / 2, x_max / 2 - width / 2);
        dialog_window_ = newwin(6, x_max - 12, y_max - 8, 5);
        refresh();
        box(dialog_window_, 0, 0);
        wrefresh(dialog_window_);
    }

    int handle_input(int key)
    {
        switch (key)
        {
            case KEY_DOWN:
                next_choice();
                break;
            case KEY_UP:
                prev_choice();
            case KEY_ENTER:
                return highlight_;
            default:
                break;
        }

        return -1;
    }

    void draw()
    {
        // mvwprintw(dialog_window_, 0, 0, "lala");
        wclear(dialog_window_);
        // box(dialog_window_, 0, 0);
        wrefresh(dialog_window_);
    }

    ~dialog_box()
    {
        delwin(dialog_window_);
    }

private:
    void next_choice()
    {
    }

    void prev_choice()
    {
    }

    size_t get_max_width() const
    {
        auto comp = [](const std::string& s1, const std::string& s2) { return s1.size() < s2.size(); };

        const auto max_from_choice = std::max_element(choices_.begin(), choices_.end(), comp);

        const std::string max_str = std::max(title_, *max_from_choice, comp);
        return max_str.size();
    }

    std::string title_;
    std::array<std::string, N> choices_;
    WINDOW* dialog_window_;
    int highlight_;

    WINDOW* scr;
};

#endif // __DIALOG_BOX_HPP__
