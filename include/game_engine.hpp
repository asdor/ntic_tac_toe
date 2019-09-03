#ifndef __GAME_ENGINE_HPP__
#define __GAME_ENGINE_HPP__

#include <utility>
#include <variant>

#include "choose_side_state.hpp"
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

class GameEngine
{
public:
    GameEngine();

    using state_type = std::variant<MainMenuState, SideChoiceState>;
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
