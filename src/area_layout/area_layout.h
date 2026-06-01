// areА_layout.h
#pragma once


#include <common/graph/graph.h>


namespace dstr {


  class AreaLayout {
    static constexpr usize ROWS_DEFAULT = 7;
    static constexpr usize COLS_DEFAULT = 7;
    Graph<CellType, int> cells_;
    usize rows_;
    usize cols_;

  public:
    explicit AreaLayout(usize rows, usize cols);
    AreaLayout();

    CellType at(usize row, usize col) const;
    void set(usize row, usize col, CellType type);

  private:
    static usize to_graph_raw_id(usize row, usize col);
  };


}
