#include <utility>
#include <variant>

#include "game_engine.hpp"

GameEngine::GameEngine() : state_(std::in_place_type<MainMenuState>), is_running_(true)
{
}

int GameEngine::get_char()
{
    return std::visit([](auto&& state) { return state.get_char(); }, state_);
}

void GameEngine::handle_input(int key)
{
    std::visit([key, this](auto&& state) { state.handle_input(key, *this); }, state_);
}

void GameEngine::draw()
{
    std::visit([](auto&& state) { state.draw(); }, state_);
}

bool GameEngine::running() const
{
    return is_running_;
}

void GameEngine::quit()
{
    is_running_ = false;
}
