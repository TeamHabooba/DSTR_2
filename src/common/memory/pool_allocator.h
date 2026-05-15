//pool_allОcator.h
#pragma once


#include "./alloc.h"
#include "../aliases/numeric.h"


namespace dstr {
  // Free chunk list node. Hidden from user, only inside the pool.
  struct free_node_t {
    free_node_t*  next; // Next free chunk
  };

  // Chunk metadata. Only inside the pool too.
  struct chunk_meta_t {
    usize index; //Chunk id inside the pool
    bool  in_use;
  };

  // Chunk - part of the pool
  struct chunk_t {
    u8*       base; // Chunk memory start
    usize     size; // Chunk size in bytes
  };

  struct pool_t {
    u8*           memory; // Whole memory block provided by OS
    usize         capacity; // Total size
    usize         offset;
    usize         chunk_size; // One chuck size. Always fixed.
    usize         chunk_count;
    chunk_meta_t* meta; // All chunks metadata
    free_node_t*  free_chunks; // Chunks returned by arenas
    void* owner; // Reserved for potential thread_local
  };


  inline bool pool_valid(pool_t* pool) {
    if (!pool) [[unlikely]] {
      return false;
    }
    return true;
  }

  inline bool size_valid(usize capacity, usize chunk_size) {
    const usize min_chunk = sizeof(u8*);
    if (chunk_size < min_chunk) {
      return false;
    }
    if (capacity < chunk_size) {
      return false;
    }
    if (chunk_size == 0) {
      return false;
    }
    if (capacity % chunk_size != 0) {
      return false;
    }
    return true;
  }


  inline bool pool_init(pool_t* pool, usize capacity, usize chunk_size) {
    if (!pool_valid(pool)) [[unlikely]] {
      return false;
    }
    if (!size_valid(capacity, chunk_size)) {
      return false;
    }
    const usize align = alignof(max_align_t);
    void* mem = os_alloc(capacity);
    if (!mem) {
      return false;
    }
    pool->memory = static_cast<u8*>(mem);
    pool->capacity = capacity;
    pool->offset = 0;
    pool->chunk_size = chunk_size;
    pool->free_chunks = nullptr;
    pool->owner = nullptr;
  }

  inline void pool_destroy(pool_t* pool) {
    os_free(pool->memory, pool->capacity);
    pool->memory = nullptr;
  }

  inline void* pool_aquire(pool_t* pool) {
    if (pool->free_chunks) {
      free_node_t* node = pool->free_chunks;
      pool->free_chunks = node->next;
      node->next = nullptr;
      return chunk->base;
    }
    if (pool->offset + pool->chunk_size > pool->capacity) {
      return nullptr;
    }
    u8* ptr = pool->memory + pool->offset;
    pool->offset + pool->chunk_size;
    return ptr;
  }

  inline void pool_release(pool_t* pool, u8* ptr) {
    
  }

}
