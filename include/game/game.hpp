#include "board.hpp"

class GameEngine;

class GameState
{
    void handle_input(int key, GameEngine& engine);
private:
    GameBoard game_board_;
    GameType game_type;
}