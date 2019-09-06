#include <algorithm>

#include "game/game_state.hpp"
#include "game_engine.hpp"

constexpr size_t cell_height = 3;
constexpr size_t cell_width = 7;
constexpr size_t board_height = cell_height * 3 + 4;
constexpr size_t board_width = cell_width * 3 + 4;

// constexpr size_t score_box_height = 4;
constexpr size_t message_box_height = 4;
constexpr size_t full_board_height = message_box_height + board_height;

GameState::GameState() : message_box_(nullptr, delwin), board_box_(nullptr, delwin)
{
    int y_max = 0;
    int x_max = 0;
    getmaxyx(stdscr, y_max, x_max);

    const size_t pos_y = (y_max - full_board_height) / 2;
    const size_t pos_x = (x_max - board_width) / 2;

    message_box_ = window_type_(newwin(message_box_height, board_width, pos_y, pos_x), delwin);
    board_box_ = window_type_(newwin(board_height, board_width, pos_y + message_box_height, pos_x), delwin);
}

void GameState::handle_input(int key, GameEngine& engine)
{
    if (key == 'q')
        engine.quit();
}

int GameState::get_char()
{
    wrefresh(message_box_.get());
    return wgetch(board_box_.get());
}

void GameState::draw()
{
    draw_message_box();
    draw_board_box();
}

void GameState::draw_message_box()
{
    box(message_box_.get(), 0, 0);

    const auto& score_map = game_board_.get_score();

    const std::string& x_str = std::to_string(score_map.at(PlayerMark::X_MARK));
    const std::string& o_str = std::to_string(score_map.at(PlayerMark::O_MARK));

    mvwprintw(message_box_.get(), 1, 2, "X: ");
    mvwprintw(message_box_.get(), 1, 2 + 3, x_str.c_str());

    mvwprintw(message_box_.get(), 2, 2, "O:");
    mvwprintw(message_box_.get(), 2, 2 + 3, o_str.c_str());

    const std::string& mes = game_board_.get_message();
    const size_t max_str_size = std::max(x_str.size(), o_str.size());
    const size_t line_pos = 2 + 3 + max_str_size + 1;

    draw_vert_line(message_box_.get(), 0, line_pos, message_box_height, ACS_VLINE, ACS_BTEE, ACS_TTEE);
    mvwprintw(message_box_.get(), 2, line_pos + (board_width - line_pos - mes.size()) / 2, mes.c_str());
}

void GameState::draw_board_box()
{
    box(board_box_.get(), 0, 0);
}
