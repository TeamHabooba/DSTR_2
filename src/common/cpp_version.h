// cpp_vЕrsion.h
#pragma once


// Define cpp version
// MSVC
#ifdef _MSC_VER
  #if _MSVC_LANG >= 202302L
    #define CPP_VERSION 23
  #elif _MSVC_LANG >= 202002L
    #define CPP_VERSION 20
  #elif _MSVC_LANG >= 201703L
    #define CPP_VERSION 17
  #elif _MSVC_LANG >= 201402L
    #define CPP_VERSION 14
  #else
    #define CPP_VERSION 11
  #endif

// Other compilers
#else
  #if __cplusplus >= 202302L
    #define CPP_VERSION 23
  #elif __cplusplus >= 202002L
    #define CPP_VERSION 20
  #elif __cplusplus >= 201703L
    #define CPP_VERSION 17
  #elif __cplusplus >= 201402L
    #define CPP_VERSION 14
  #else
    #define CPP_VERSION 11
  #endif
#endif
