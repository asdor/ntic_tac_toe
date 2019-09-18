#include <ncurses.h>

#include "game_engine.hpp"

void main_loop()
{
    GameEngine engine;
    while (engine.running())
    {
        engine.draw();
        int key = engine.get_char();
        if (key != ERR)
            engine.handle_input(key);
    }
}

int main()
{
    initscr();
    refresh();
    noecho();
    keypad(stdscr, true);

    main_loop();

    endwin();
    return 0;
}
