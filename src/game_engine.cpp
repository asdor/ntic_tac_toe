#include <utility>
#include <variant>

#include "game_engine.hpp"

GameEngine::GameEngine() : cur_state_(std::in_place_type<MainMenuState>), prev_state_(std::nullopt), is_running_(true)
{
}

void GameEngine::load_prev_state()
{
    cur_state_ = std::move(prev_state_.value());
    prev_state_ = std::nullopt;
    draw_background();
}

int GameEngine::get_char()
{
    return std::visit([](auto&& state) { return state.get_char(); }, cur_state_);
}

void GameEngine::handle_input(int key)
{
    std::visit([key, this](auto&& state) { state.handle_input(key, *this); }, cur_state_);
}

void GameEngine::draw_background()
{
    std::visit([](auto&& state) { state.draw_background(); }, cur_state_);
}

void GameEngine::draw()
{
    std::visit([](auto&& state) { state.draw(); }, cur_state_);
}

bool GameEngine::running() const
{
    return is_running_;
}

void GameEngine::quit()
{
    is_running_ = false;
}
