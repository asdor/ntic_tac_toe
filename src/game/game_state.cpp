#include <algorithm>

#include "game/game_state.hpp"
#include "game_engine.hpp"

constexpr size_t cell_height = 3;
constexpr size_t cell_width = 7;
constexpr size_t board_height = cell_height * 3 + 4;
constexpr size_t board_width = cell_width * 3 + 4;

constexpr size_t message_box_height = 5;
constexpr size_t full_board_height = message_box_height + board_height;

constexpr size_t board_stride_y = cell_height + 1;
constexpr size_t board_stride_x = cell_width + 1;

GameState::GameState() : message_box_(nullptr, delwin), board_box_(nullptr, delwin), cursor_pos_y(0), cursor_pos_x(0)
{
    int y_max = 0;
    int x_max = 0;
    getmaxyx(stdscr, y_max, x_max);

    const size_t pos_y = (y_max - full_board_height) / 2;
    const size_t pos_x = (x_max - board_width) / 2;

    message_box_ = window_type_(newwin(message_box_height, board_width, pos_y, pos_x), delwin);
    board_box_ = window_type_(newwin(board_height, board_width, pos_y + message_box_height, pos_x), delwin);
    curs_set(1);

    game_board_.set_mark(0, PlayerMark::X_MARK);
    game_board_.set_mark(1, PlayerMark::O_MARK);
    game_board_.set_mark(4, PlayerMark::X_MARK);
    game_board_.set_mark(8, PlayerMark::X_MARK);
    // game_board_.set_mark(0, PlayerMark::X_MARK);
    // game_board_.set_mark(0, PlayerMark::X_MARK);
}

void GameState::handle_input(int key, GameEngine& engine)
{
    if (key == 'q')
        engine.quit();

    switch (key)
    {
        case 'w':
        case 'W':
            cursor_pos_y = wrap(cursor_pos_y - 1, 0, 2);
            break;
        case 's':
        case 'S':
            cursor_pos_y = wrap(cursor_pos_y + 1, 0, 2);
            break;
        case 'a':
        case 'A':
            cursor_pos_x = wrap(cursor_pos_x - 1, 0, 2);
            break;
        case 'd':
        case 'D':
            cursor_pos_x = wrap(cursor_pos_x + 1, 0, 2);
            break;
        default:
            break;
    }
}

int GameState::get_char()
{
    wrefresh(message_box_.get());
    return wgetch(board_box_.get());
}

void GameState::draw()
{
    wclear(message_box_.get());
    wclear(board_box_.get());
    draw_message_box();
    draw_board_box();
    wmove(board_box_.get(), cell_height / 2 + 1 + cursor_pos_y * board_stride_y, cell_width / 2 + 1 + cursor_pos_x * board_stride_x);
}

void GameState::draw_message_box()
{
    box(message_box_.get(), 0, 0);

    const std::string x_str = std::to_string(game_board_.get_score(PlayerMark::X_MARK));
    const std::string o_str = std::to_string(game_board_.get_score(PlayerMark::O_MARK));
    const size_t left_line_pos = 1 + std::max(x_str.size(), o_str.size());
    const size_t right_line_pos = board_width - 1 - left_line_pos;

    draw_vert_line(message_box_.get(), 0, left_line_pos, message_box_height, ACS_TTEE, ACS_VLINE, ACS_BTEE);
    draw_horz_line(message_box_.get(), message_box_height / 2, 0, left_line_pos + 1, ACS_LTEE, ACS_HLINE, ACS_RTEE);
    mvwprintw(message_box_.get(), 1, left_line_pos - 1, "X");
    mvwprintw(message_box_.get(), 3, left_line_pos - x_str.size(), x_str.c_str());

    draw_vert_line(message_box_.get(), 0, right_line_pos, message_box_height, ACS_TTEE, ACS_VLINE, ACS_BTEE);
    draw_horz_line(message_box_.get(), message_box_height / 2, right_line_pos, left_line_pos + 1, ACS_LTEE, ACS_HLINE, ACS_RTEE);
    mvwprintw(message_box_.get(), 1, right_line_pos + 1, "O");
    mvwprintw(message_box_.get(), 3, right_line_pos + 1, o_str.c_str());

    const std::string mes = game_board_.get_message();
    mvwprintw(message_box_.get(), 2, (board_width - mes.size()) / 2, mes.c_str());
}

void GameState::draw_board_box()
{
    box(board_box_.get(), 0, 0);

    draw_horz_line(board_box_.get(), board_stride_y, 0, board_width, ACS_LTEE, ACS_HLINE, ACS_RTEE);
    draw_horz_line(board_box_.get(), 2 * board_stride_y, 0, board_width, ACS_LTEE, ACS_HLINE, ACS_RTEE);

    draw_vert_line(board_box_.get(), 0, board_stride_x, board_height, ACS_TTEE, ACS_VLINE, ACS_BTEE);
    draw_vert_line(board_box_.get(), 0, 2 * board_stride_x, board_height, ACS_TTEE, ACS_VLINE, ACS_BTEE);

    mvwaddch(board_box_.get(), cell_height + 1, cell_width + 1, ACS_PLUS);
    mvwaddch(board_box_.get(), cell_height + 1, 2 * board_stride_x, ACS_PLUS);
    mvwaddch(board_box_.get(), 2 * board_stride_y, cell_width + 1, ACS_PLUS);
    mvwaddch(board_box_.get(), 2 * board_stride_y, 2 * board_stride_x, ACS_PLUS);

    const auto& board = game_board_.get_board();
    for (size_t i = 0, y_pos = cell_height / 2 + 1; i < 3; ++i, y_pos += board_stride_y)
    {
        for (size_t j = 0, x_pos = cell_width / 2 + 1; j < 3; ++j, x_pos += board_stride_x)
        {
            char mark = mark_to_string(board[i * 3 + j]);
            mvwaddch(board_box_.get(), y_pos, x_pos, mark);
        }
    }
}
