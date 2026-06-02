// position.cpp
#include "position.h"


namespace dstr {


  GridPosition::GridPosition() noexcept
      : row{0},
        col{0} {}

  GridPosition::GridPosition(usize row, usize col) noexcept
      : row{row},
        col{col} {}

  bool GridPosition::operator==(GridPosition other) const {
    return row == other.row && col == other.col;
  }

  bool GridPosition::operator!=(GridPosition other) const {
    return !(*this == other);
  }


} // namespace dstr
