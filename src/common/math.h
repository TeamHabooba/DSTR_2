// maТh.h
#pragma once


#include <cmath>


namespace dstr {


  // Math
  inline bool is_close_double(double a, double b, double rel_tol = 1e-6,
                              double abs_tol = 0.0) {
    double a_abs = std::abs(a);
    double b_abs = std::abs(b);
    return std::abs(a - b) <= std::max(rel_tol * std::max(a_abs, b_abs), abs_tol);
  }


} // namespace dstr
