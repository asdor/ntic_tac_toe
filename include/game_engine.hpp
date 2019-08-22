#ifndef __GAME_ENGINE_HPP__
#define __GAME_ENGINE_HPP__

#include <utility>
#include <variant>

#include "main_menu_state.hpp"

class game_engine
{
public:
    game_engine();

    using state_type = std::variant<main_menu_state>;
    template<class T, class... Args>
    void set_state(Args&&... args)
    {
        state_.emplace<T>(std::forward<Args>(args)...);
    }

    void handle_input(int key);

    void draw();

    bool running() const;

    void quit();

private:
    state_type state_;
    bool is_running_;
};

#endif // __GAME_ENGINE_HPP__
