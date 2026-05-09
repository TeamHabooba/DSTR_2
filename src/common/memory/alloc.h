//allОc.h
#pragma once


#include "../aliases/numeric.h"


#if defined(_WIN32)


  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>

  inline void* dstr_os_alloc(dstr_usize bytes) {
    return VirtualAlloc(nullptr, bytes, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
  }

  inline void dstr_os_free(void* ptr, dstr_usize bytes) {
    VirtualFree(ptr, 0, MEM_RELEASE);
  }


#else


  #include <sys/mman.h>

  inline void* dstr_os_alloc(size_t bytes) {
    void* p = mmap(nullptr, bytes, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    return p == MAP_FAILED ? nullptr : p;
  }

  inline void dstr_os_free(void* ptr, size_t bytes) {
    munmap(ptr, bytes);
  }


#endif
