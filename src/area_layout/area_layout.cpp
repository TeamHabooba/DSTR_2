#include "area_layout.h"


namespace dstr {


  explicit AreaLayout::AreaLayout(usize rows, usize cols)
    : cells_{}, rows_{ rows }, cols_{ cols } { }

  AreaLayout::AreaLayout() : AreaLayout(ROWS_DEFAULT, COLS_DEFAULT) { }

  CellType AreaLayout::at(usize row, usize col) const {
    return cells_.at(to_graph_raw_id(row, col));
  }

  void AreaLayout::set(usize row, usize col, CellType type) {
    
  }

  usize AreaLayout::to_graph_raw_id(usize row, usize col) {
    return row * col + col;
  }
}
