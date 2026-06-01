// areА_layout.h
#pragma once


#include <common/graph/graph.h>


namespace dstr {


  class AreaLayout {
    Graph<CellType, int> cells_;
    usize rows;
    usize cols;
  };


}
