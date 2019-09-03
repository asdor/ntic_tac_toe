#include <ncurses.h>

#include "game_engine.hpp"

void main_loop()
{
    GameEngine engine;
    while (engine.running())
    {
        int key = engine.get_char();
        if (key != ERR)
            engine.handle_input(key);

        engine.draw();
    }
}

int main()
{
    initscr();
    refresh();
    noecho();
    keypad(stdscr, true);

    halfdelay(1);
    main_loop();

    endwin();
    return 0;
}
