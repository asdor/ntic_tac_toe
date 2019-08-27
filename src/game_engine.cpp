#include <utility>
#include <variant>

#include "game_engine.hpp"

game_engine::game_engine() : state_(std::in_place_type<main_menu_state>), is_running_(true)
{
}

int game_engine::get_char()
{
    return std::visit([](auto&& state) { return state.get_char(); }, state_);
}

void game_engine::handle_input(int key)
{
    std::visit([key, this](auto&& state) { state.handle_input(key, *this); }, state_);
}

void game_engine::draw()
{
    std::visit([](auto&& state) { state.draw(); }, state_);
}

bool game_engine::running() const
{
    return is_running_;
}

void game_engine::quit()
{
    is_running_ = false;
}
