// path.cpp
#include "path.h"


namespace dstr {


  Path::Path() : steps_{} {}

  usize Path::size() const { return steps_.size(); }
  bool Path::empty() const { return steps_.empty(); }

  Result<GridPosition> Path::at(usize index) const {
    if (index >= steps_.size()) {
      return Err<GridPosition>(ErrorCode::OUT_OF_RANGE, string(strings::ERR_PATH_INDEX_RANGE));
    }
    return Ok(steps_.unchecked_at(index));
  }

  Result<GridPosition> Path::last() const {
    if (empty()) {
      return Err<GridPosition>(ErrorCode::EMPTY_CONTAINER, string(strings::ERR_PATH_EMPTY));
    }
    return Ok(steps_.unchecked_at(steps_.size() - 1));
  }

  Result<void> Path::push(GridPosition position) {
    steps_.push_back(position);
    return Ok();
  }

  Result<Stack<GridPosition>> Path::reverse_stack() const {
    Stack<GridPosition> stack;
    for (usize i = 0; i < steps_.size(); i++) {
      auto pushed = stack.push(steps_.unchecked_at(i));
      if (!pushed) {
        return Err<Stack<GridPosition>>(pushed.error().code(), pushed.error().message());
      }
    }
    return Ok(stack);
  }

  void Path::clear() {
    steps_.clear();
  }


} // namespace dstr
