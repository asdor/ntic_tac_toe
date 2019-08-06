#include <ncurses.h>

#include "ui_main.hpp"

void main_loop()
{
    ui_main game;
    bool main_loop = true;
    while (main_loop)
    {
        int key = getch();
        if (key == 'q')
            main_loop = false;

        game.draw();
    }
}

int main()
{
    // init screen and clean it
    initscr();
    noecho();
    // cbreak();
    keypad(stdscr, true);

    halfdelay(1);
    main_loop();

    endwin();
    return 0;
}
