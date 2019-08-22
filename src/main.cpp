#include <ncurses.h>

#include "game_engine.hpp"

void main_loop()
{
    game_engine engine;
    while (engine.running())
    {
        // int key = getch();
        int key = 5;
        if (key != ERR)
            engine.handle_input(key);
        engine.draw();
    }
}

#include <stdio.h>

int main()
{
    // init screen and clean it
    auto win = initscr();
    if (win == nullptr)
        return -1;
    refresh();
    noecho();
    // cbreak();
    keypad(stdscr, true);

    halfdelay(1);
    main_loop();

    endwin();
    return 0;
}
