#ifndef __DEFS_HPP__
#define __DEFS_HPP__

#include <cstddef>

namespace defs
{
constexpr size_t cell_height = 3;
constexpr size_t cell_width = 7;
constexpr size_t board_height = cell_height * 3 + 4;
constexpr size_t board_width = 4 + 3 * cell_width;

} // namespace defs

#endif // __DEFS_HPP__
