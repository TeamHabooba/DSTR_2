//pool_allОcator.h
#pragma once


#include "./alloc.h"
#include "../aliases/numeric.h"
#include <cstddef>


namespace dstr {


  // Chunk - part of the pool
  struct chunk_t {
    chunk_t*  next; // Next free chunk
    u8*       base; // Chunk memory start
    usize     size; // Chunk size in bytes
  };

  struct pool_t {
    u8*   memory; // Whole memory block provided by OS
    usize capacity; // Total size
    usize offset;
    usize chunk_size; // One chuck size. Always fixed. 
    chunk_t* free_chunks; // Chunks returned by arenas
    void* owner; // Reserved for potential thread_local
  };


  inline bool pool_init(pool_t* pool, usize capacity, usize chunk_size) {
    void* mem = os_alloc(capacity);
    if (!mem) {
      return false;
    }
    pool->memory = mem;
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

  inline void* pool_aquire(pool_t* pool, usize capacity) {

  }

  inline void pool_release() {

  }

}
