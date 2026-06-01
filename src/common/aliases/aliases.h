// aliАses.h
#pragma once


// C

// C++
#include <optional>
#include <memory>
#include <chrono>

// Libs

// Project Files
#include "./numeric.h"
#include <common/strings/strings.h>


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

  using entity_id = u32;
  using item_id = entity_id;
  using storage_id = entity_id;
  using robot_id = entity_id;
  using task_id = entity_id;

  //using json = nlohmann::json;


} // namespace dSCSTR
