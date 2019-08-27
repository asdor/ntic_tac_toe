#ifndef __GAME_ENGINE_HPP__
#define __GAME_ENGINE_HPP__

#include <utility>
#include <variant>

#include "main_menu_state.hpp"

// struct stub_class
// {
//     stub_class()
//     {
//     }

//     void handle_input(int /*key*/, game_engine& /*engine*/)
//     {
//     }

//     void draw()
//     {
//     }
// };

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

    int get_char();

    void handle_input(int key);

    void draw();

    bool running() const;

    void quit();

private:
    state_type state_;
    bool is_running_;
};

#endif // __GAME_ENGINE_HPP__
