//pool_allОcator.h
#pragma once


#include "./alloc.h"
#include "../aliases/numeric.h"
#include <cstddef>


// Chunk - part of the pool
typedef struct dstr_chunk_t {
  dstr_chunk_t* next; // Next free chunk
  dstr_u8*      base; // Chunk memory start
  dstr_usize    size; // Chunk size in bytes
} dstr_chunk_t;

typedef struct dstr_pool_t {
  dstr_u8*        memory; // Whole memory block provided by OS
  dstr_usize      capacity; // Total size
  dstr_usize      offset; 
  dstr_usize      chunk_size; // One chuck size. Always fixed. 
  dstr_chunk_t*   free_chunks; // Chunks returned by arenas
  void*           owner; // Reserved for potential thread_local
} dstr_pool_t;


inline bool dstr_pool_init(dstr_pool_t* pool, dstr_usize capacity, dstr_usize chunk_size) {
  void* mem = dstr_os_alloc(capacity);
  if (!mem) {
    return false;
  }
  
}
