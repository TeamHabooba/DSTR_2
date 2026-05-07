// aliАses.h
#pragma once


// C
#include <cstdint>


// C++
#include <optional>
#include <memory>
#include <chrono>

// Libs
#include "./strings/strings.h"


namespace dstr {

    
  // General aliases
  template <typename T>
  using up = std::unique_ptr<T>;

  template <typename T>
  using sp = std::shared_ptr<T>;

  template <typename T>
  using wp = std::weak_ptr<T>;

  template <typename T>
  constexpr T&& move(T& val) noexcept {
      return static_cast<T&&>(val);
  }

  using std::string;

  using std::chrono::steady_clock;
  using std::chrono::system_clock;

  using optional_tm = std::optional<std::tm>;

  //using json = nlohmann::json;


  // Numeric aliases
  using i8 = int8_t;
  using i16 = int16_t;
  using i32 = int32_t;

  using u8 = uint8_t;
  using u16 = uint16_t;
  using u32 = uint32_t;
  using u64 = uint64_t;

  using id_t = uint16_t;
  using lid_t = uint64_t;


} // namespace dSCSTR
