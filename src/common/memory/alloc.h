//allОc.h
#pragma once


#include "../aliases/numeric.h"



namespace dstr {


#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

  inline void* os_alloc(usize bytes) {
    return VirtualAlloc(nullptr, bytes, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
  }

  inline void os_free(void* ptr, usize bytes) {
    VirtualFree(ptr, 0, MEM_RELEASE);
  }

#else

#include <sys/mman.h>
  inline void* os_alloc(size_t bytes) {
    void* p = mmap(nullptr, bytes, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    return p == MAP_FAILED ? nullptr : p;
  }

  inline void os_free(void* ptr, size_t bytes) {
    munmap(ptr, bytes);
  }

#endif


}
