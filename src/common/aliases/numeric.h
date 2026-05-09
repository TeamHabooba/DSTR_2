// dstr_tУpes.h
#pragma once


#ifdef __cplusplus
  #include <cstdint>
  #include <cstddef>
#else
  #include <stdint.h>
  #include <stddef.h>
#endif



// C-compatible
typedef uint8_t   dstr_u8;
typedef int16_t   dstr_i16;
typedef uint16_t  dstr_u16;
typedef int32_t   dstr_i32;
typedef uint32_t  dstr_u32;
typedef int64_t   dstr_i64;
typedef uint64_t  dstr_u64;
typedef size_t    dstr_usize;
typedef ptrdiff_t dstr_isize;

typedef size_t    dstr_usize;
typedef ptrdiff_t dstr_isize;
typedef uintptr_t dstr_uptr;   // pointer as int for arithmetics
typedef intptr_t  dstr_iptr;   // signed

typedef float     dstr_f32;
typedef double    dstr_f64;
//long double is platform-dependent


// С++
#ifdef __cplusplus


namespace dstr {


  using u8 = dstr_u8;
  using i16 = dstr_i16;
  using u16 = dstr_u16;
  using i32 = dstr_i32;
  using u32 = dstr_u32;
  using i64 = dstr_i64;
  using u64 = dstr_u64;

  using usize = dstr_usize;
  using isize = dstr_isize;
  using uptr = dstr_uptr;
  using iptr = dstr_iptr;

  using f32 = dstr_f32;
  using f64 = dstr_f64;


}


#endif
