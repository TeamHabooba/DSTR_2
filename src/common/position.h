// position.h
#pragma once

#include <common/aliases/aliases.h>


namespace dstr {


struct GridPosition {
  usize row;
  usize col;

  GridPosition() noexcept;
  GridPosition(usize row, usize col) noexcept;

  bool operator==(GridPosition other) const;
  bool operator!=(GridPosition other) const;
};


} // namespace dstr
