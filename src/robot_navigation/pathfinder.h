// pathfinder.h
#pragma once


#include <common/result.h>
#include <common/array/array.h>
#include <common/queue.h>
#include <area_layout/area_layout.h>
#include <robot_navigation/path.h>


namespace dstr {


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


} // namespace dstr
