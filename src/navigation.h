#pragma once


#include <common/common.h>


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



  class Pathfinder {
  private:
    struct CachedPath {
      GridPosition start;
      GridPosition destination;
      u64 layout_version;
      Path path;
    };

    wp<AreaLayout> layout_;
    mutable Array<CachedPath> cache_;
    mutable u64 observed_layout_version_;

  public:
    Pathfinder();
    explicit Pathfinder(sp<AreaLayout> layout);

    void set_layout(sp<AreaLayout> layout);
    bool has_layout() const;
    void invalidate_cache() const;

    Result<Path> find_path(GridPosition start, GridPosition destination) const;
    Result<Stack<GridPosition>> reverse_path(const Path& path) const;

  private:
    Result<Path> find_cached(GridPosition start, GridPosition destination, u64 version) const;
    Result<void> cache_path(GridPosition start, GridPosition destination, u64 version, const Path& path) const;
    Result<Path> find_path_uncached(sp<AreaLayout> layout, GridPosition start, GridPosition destination) const;
    void refresh_cache_version(sp<AreaLayout> layout) const;
  };

  namespace {


    constexpr usize INVALID_INDEX = static_cast<usize>(-1);


  } // namespace


  // =====Constructors

  Pathfinder::Pathfinder()
    : layout_{},
    cache_{},
    observed_layout_version_{ 0 } {
  }

  Pathfinder::Pathfinder(sp<AreaLayout> layout)
    : layout_{ layout },
    cache_{},
    observed_layout_version_{ layout ? layout->version() : 0 } {
  }


  // =====Domain methods

  void Pathfinder::set_layout(sp<AreaLayout> layout) {
    layout_ = layout;
    observed_layout_version_ = layout ? layout->version() : 0;
    invalidate_cache();
  }

  bool Pathfinder::has_layout() const {
    return !layout_.expired();
  }

  void Pathfinder::invalidate_cache() const {
    cache_.clear();
  }

  Result<Path> Pathfinder::find_path(GridPosition start, GridPosition destination) const {
    auto layout = layout_.lock();
    if (!layout) {
      return Err<Path>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_PATHFINDER_NO_LAYOUT));
    }
    refresh_cache_version(layout);
    auto cached = find_cached(start, destination, layout->version());
    if (cached) {
      return cached;
    }
    auto computed = find_path_uncached(layout, start, destination);
    if (!computed) {
      return computed;
    }
    cache_path(start, destination, layout->version(), computed.value());
    return computed;
  }

  Result<Stack<GridPosition>> Pathfinder::reverse_path(const Path& path) const {
    return path.reverse_stack();
  }


  // =====Private helpers

  Result<Path> Pathfinder::find_cached(GridPosition start, GridPosition destination, u64 version) const {
    for (usize i = 0; i < cache_.size(); i++) {
      const auto& cached = cache_.unchecked_at(i);
      if (cached.layout_version == version && cached.start == start && cached.destination == destination) {
        return Ok(cached.path);
      }
    }
    return Err<Path>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_PATH_CACHE_MISS));
  }

  Result<void> Pathfinder::cache_path(
    GridPosition start,
    GridPosition destination,
    u64 version,
    const Path& path) const {
    CachedPath cached{ start, destination, version, path };
    cache_.push_back(cached);
    return Ok();
  }

  Result<Path> Pathfinder::find_path_uncached(
    sp<AreaLayout> layout,
    GridPosition start,
    GridPosition destination) const {
    if (!layout->valid_position(start) || !layout->valid_position(destination)) {
      return Err<Path>(ErrorCode::OUT_OF_RANGE, string(strings::ERR_PATH_ENDPOINT_RANGE));
    }
    if (!layout->walkable(start) || !layout->walkable(destination)) {
      return Err<Path>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_PATH_ENDPOINT_BLOCKED));
    }
    auto start_id = layout->node_id(start);
    auto destination_id = layout->node_id(destination);
    if (!start_id || !destination_id) {
      return Err<Path>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_PATH_ENDPOINT_NODE));
    }
    usize raw_count = layout->rows() * layout->cols();
    Array<bool> visited(raw_count);
    Array<usize> previous(raw_count);
    for (usize i = 0; i < raw_count; i++) {
      visited.push_back(false);
      previous.push_back(INVALID_INDEX);
    }
    Queue<NodeId> queue;
    queue.enqueue(start_id.value());
    visited.unchecked_at(start_id.value().index) = true;
    bool found = false;
    while (!queue.empty()) {
      auto current = queue.dequeue();
      if (!current) {
        return Err<Path>(current.error().code(), current.error().message());
      }
      if (current.value() == destination_id.value()) {
        found = true;
        break;
      }
      auto edges = layout->graph()->edges(current.value());
      if (!edges) {
        return Err<Path>(edges.error().code(), edges.error().message());
      }
      for (usize i = 0; i < edges.value().size(); i++) {
        NodeId next = edges.value().unchecked_at(i).target();
        if (!visited.unchecked_at(next.index)) {
          visited.unchecked_at(next.index) = true;
          previous.unchecked_at(next.index) = current.value().index;
          queue.enqueue(next);
        }
      }
    }
    if (!found) {
      return Err<Path>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_PATH_UNREACHABLE));
    }
    Stack<GridPosition> reversed;
    usize cursor = destination_id.value().index;
    while (cursor != INVALID_INDEX) {
      reversed.push(layout->from_graph_raw_id(cursor));
      if (cursor == start_id.value().index) {
        break;
      }
      cursor = previous.unchecked_at(cursor);
    }
    Path path;
    while (!reversed.empty()) {
      auto step = reversed.pop();
      if (!step) {
        return Err<Path>(step.error().code(), step.error().message());
      }
      path.push(step.value());
    }
    return Ok(path);
  }

  void Pathfinder::refresh_cache_version(sp<AreaLayout> layout) const {
    if (observed_layout_version_ != layout->version()) {
      observed_layout_version_ = layout->version();
      invalidate_cache();
    }
  }


} // namespace dstr
