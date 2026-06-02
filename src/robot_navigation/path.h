// path.h
#pragma once

#include <common/array/array.h>
#include <common/position.h>
#include <common/result.h>
#include <common/stack/stack.h>


namespace dstr {


  class Path {
   private:
    Array<GridPosition> steps_;

   public:
    Path();

    usize size() const;
    bool empty() const;
    Result<GridPosition> at(usize index) const;
    Result<GridPosition> last() const;
    Result<void> push(GridPosition position);
    Result<Stack<GridPosition>> reverse_stack() const;
    void clear();
  };


} // namespace dstr
