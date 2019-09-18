#ifndef __GAME_ENGINE_HPP__
#define __GAME_ENGINE_HPP__

#include <optional>
#include <utility>
#include <variant>

#include "choose_side_state.hpp"
#include "game/game_state.hpp"
#include "game/game_type.hpp"
#include "main_menu_state.hpp"
#include "pause_state.hpp"

class GameEngine
{
public:
    GameEngine();

    using state_type = std::variant<MainMenuState, SideChoiceState, GameState, PauseState>;
    template<class T, class... Args>
    void set_state(Args&&... args)
    {
        prev_state_ = std::nullopt;
        cur_state_.emplace<T>(std::forward<Args>(args)...);
    }

    template<class T, class... Args>
    void save_and_set_state(Args&&... args)
    {
        prev_state_ = std::move(cur_state_);
        cur_state_.emplace<T>(std::forward<Args>(args)...);
    }

    void load_prev_state();

    int get_char();
    void handle_input(int key);
    void draw();
    bool running() const;
    void quit();

private:
    void draw_background();

    state_type cur_state_;
    std::optional<state_type> prev_state_;
    bool is_running_;
};

#endif // __GAME_ENGINE_HPP__
