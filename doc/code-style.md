Complete C++ code style guideline for the project.  
Refer to the project lead if you find anything unspecified. But please,  
**READ THIS GUIDELINE THOROUGHLY FIRST**.

## Contents:
- [General Principles](#general-principles)
- [Indentation](#indentation)
- [Naming Conventions](#naming-conventions)
- [Braces Formatting](#braces-formatting)
- [Includes and Namespaces](#includes-and-namespaces)
- [Comments](#comments)
- [Class Structure and Member Order](#class-structure-and-member-order)
- [Visibility and Access](#visibility-and-access)
- [Type Aliases and Primitives](#type-aliases-and-primitives)
- [Pointers and Memory Management](#pointers-and-memory-management)
- [Error Handling](#error-handling)
- [Miscellaneous](#miscellaneous)
- [Quick Class Template](#quick-class-template)

---

### General Principles
- One class per file. A class `Player` -> `player.h` + `player.cpp`.
- Based on **Google C++ Style Guide** with project-specific extensions.
- Readability first — but unlike Java, be mindful of performance.  
  Avoid unnecessary copies. Prefer move semantics where applicable.
- Separate declaration (`.h`) from implementation (`.cpp`) strictly.
- Use `#pragma once` instead of traditional include guards.
- Encoding: UTF-8.

---

### Indentation
- Use **spaces** over tabs.
- Indent: **2 spaces** (Google default).
- Spaces:
  - One space after keywords: `if (x == 0) { ... }`
  - Spaces around binary operators: `int total = price * quantity;`
  - No space before `(` in function calls: `player.set_name(name);`
- Blank lines: use one blank line to separate logical sections
  (between field groups, between constructors and getters, etc.).
- Do _not_ add trailing whitespace.

---

### Naming Conventions
- **Classes / structs / enums**: `PascalCase` — `Player`, `GameSession`, `ItemType`.
- **Methods / functions / local variables**: `snake_case` — `get_name()`, `item_count`.
- **Private fields**: `snake_case` with a **trailing underscore** — `id_`, `name_`, `score_`.
- **Constants / enum values**: `UPPER_SNAKE_CASE` — `MAX_PLAYERS`, `ItemType::NONE`.
- **Namespaces**: lowercase — `namespace game { ... }`.
- **Type aliases**: short lowercase aliases — `i32`, `id_t`, `sptr<T>`.
- Avoid Hungarian notation and prefixes like `m_name`, `_name`, `pValue`.

Full breakdown table:

| Thing | Style | Example |
|---|---|---|
| Class | `PascalCase` | `PlayerStats` |
| Method | `snake_case` | `calculate_score()` |
| Local variable | `snake_case` | `item_count` |
| Private field | `snake_case_` | `name_`, `score_` |
| Constant | `UPPER_SNAKE_CASE` | `MAX_HEALTH` |
| Namespace | lowercase | `namespace engine` |
| Enum value | `UPPER_SNAKE_CASE` | `State::IDLE` |

---

### Braces Formatting
- Opening brace on **the same line** as the statement (K&R / Google style):
```cpp
if (is_alive) {
  respawn();
} else {
  end_game();
}
```
- Always use braces, even for single-line `if` bodies — **no exceptions**:
```cpp
// Good
if (score > 0) {
  save();
}

// Bad
if (score > 0)
  save();
```
- One declaration per line. Avoid `int x, y, z;`:
```cpp
// Good
int width;
int height;

// Bad
int width, height;
```
- Constructor initializer lists: each initializer on its own line, aligned after `:`:
```cpp
Player::Player()
    : id_{0},
      name_{""},
      score_{0},
      alive_{false} {}
```

---

### Includes and Namespaces
- Group includes in this order, with one blank line between groups:
  1. Standard library headers (`<string>`, `<mutex>`, `<memory>`, ...)
  2. Project-wide common headers (`"common/common.h"`)
  3. Other project headers (`"entities/player.h"`)
- No wildcard includes — specify each header explicitly:
```cpp
// Good
#include <string>
#include <vector>

// Bad
#include <bits/stdc++.h>
```
- In `.cpp` files, include the corresponding `.h` first.
- Namespace content is **not indented**:
```cpp
namespace game {

class Player {
  ...
};

} // namespace game
```
- Always close a namespace with a comment: `} // namespace game`.
- Do **not** use `using namespace std;` and any other `using namespace ...` globally.  
  Use explicit aliases in `common.h` where needed (`using std::string;` etc.).

---

### Comments
- Use `//` for all inline and section comments. Avoid `/* */` blocks.
- File-level comment: add a one-line `// filename.cpp` at the very top of each file:
```cpp
// player.cpp
#include "player.h"
```
- Use `// =====Section Name` banners to separate major sections inside `.cpp` files:
```cpp
// =====Private methods

// =====Constructors

// =====Getters
```
- Mark incomplete or unsafe spots with a short inline note:
```cpp
void set_target(const Player& player);
// add null-check
```
- Comment _why_, not _what_. Avoid restating the obvious:
```cpp
// Good: explains a non-obvious decision
// Using epsilon comparison because floating-point equality is unreliable
if (is_close(a, b, 1e-4)) { ... }

// Bad: just restates the code
// Increment score by 1
score_++;
```

---

### Class Structure and Member Order
Recommended order inside a class declaration (top → bottom):

1. `private` fields
2. `public` constructors
3. `public` comparison operators (`==`, `!=`)
4. `public` assignment operators (`=`)
5. `public` getters
6. `public` setters
7. `public` domain methods (core logic)
8. `friend` declarations (e.g. `operator<<`)

Example:
```cpp
class Player {
 private:
  id_t id_;
  string name_;
  i32 score_;
  bool alive_;

 public:
  // Ctors
  Player();
  Player(id_t id, string name, i32 score);
  Player(const Player& other);
  Player(Player&& other) noexcept;

  // Comparison ops
  bool operator==(const Player& other) const;
  bool operator!=(const Player& other) const;

  // Assignment ops
  Player& operator=(const Player& other);
  Player& operator=(Player&& other) noexcept;

  // Getters
  id_t id() const;
  string name() const;
  i32 score() const;
  bool is_alive() const;

  // Setters
  void set_id(id_t value);
  void set_name(string value);
  void set_score(i32 value);

  // Domain methods
  bool add_score(i32 amount);
  void reset();

  friend std::ostream& operator<<(std::ostream& os, const Player& p);
};
```

In `.cpp` files, implement sections in the **same order** as declared, each separated by a `// =====` banner.

---

### Visibility and Access
- All fields are `private`. Always. No exceptions.
- Use explicit getters and setters for external access.
- Getters must be `const` methods — always:
```cpp
string name() const;     // Good
string name();           // Bad — getter should never mutate state
```
- Setters take values by value for cheap types, by value or `const&` for larger ones:
  - Cheap (`int`, `bool`, `double`, enums): pass by value.
  - Strings and complex objects: pass by value (enables move optimization) or `const&`.
- `private` section comes **before** `public` in class declarations.
- Use `this->` only when strictly necessary — prefer direct field access:
```cpp
// Preferred
void Player::set_name(string name) {
  name_ = name;
}

// Also acceptable where disambiguation is needed
void Player::set_name(string name) {
  this->name_ = name;
}
```
- Define all constant variables as `constexpr`. Don't use `#define` for this.

---

### Type Aliases and Primitives
Defined in `common/common.h`. Use them consistently across the codebase — never raw platform-specific types directly:

| Alias | Meaning | Typical usage |
|---|---|---|
| `i32` |  `int32_t` | 32-bit signed integer |
| `id_t` | Unsigned entity ID | IDs for most entities |
| `lid_t` | Large / long ID | IDs for entities with bigger ID space |
| `sp<T>` | `std::shared_ptr<T>` | Shared ownership between objects |
| `wp<T>` | `std::weak_ptr<T>` | Weak pointer to an object owned by `sp<T>` |
| `up<T>` | `std::unique_ptr` | RAII-based pointer. Prefer this in most cases |
| `string` | `std::string` | All text (via `using std::string`) |
| `DateTime` | Wrapper over `struct tm` | Timestamps and dates |

Rationale: using aliases keeps the code readable and makes it easy to change the underlying type in one place if needed.
If you need to create your own alias,
prefer `using t = type` instead of `typedef`.
Never use `#define` for type aliasing.

---

### Pointers and Memory Management
- **Never use raw owning pointers**. You definitely *will* forget to `delete`.
Always use smart pointers.
- Use `sp<T>` (`std::shared_ptr<T>`) when multiple objects need to share ownership:
```cpp
sptr<Player> current_player_;   // shared between Session and Lobby, for example
```
- Use `wp<T>` (`std::weak_ptr<T>`) when multiple objects need to refer the same memory without owning it.
- Use `up<T>` (`std::unique_ptr<T>`) when ownership is exclusive and non-shared.
- Always check for `nullptr` before dereferencing a pointer.  
  Mark places where the check is missing with `// add null-check`:
```cpp
void set_owner(const Player& player) {
  *owner_ = player;
} // add null-check
```
- Never return raw pointers from public API. Return smart pointer or references instead.
- Prefer move semantics when passing large objects into setters — provide both overloads:
```cpp
void set_player(const Player& player);   // copy
void set_player(Player&& player);        // move
```

---

### Error Handling

- Do not use exceptions for control flow.
- Do not use raw bool returns for methods that can fail — use
`Result<T>` from `result.h` instead:

- - Result<T> — when the method returns a value or an error.
- - Result<void> — when the method returns nothing but can still fail.



```cpp
// Good — returns a value or an error
Result<i32> Player::compute_rank() const {
  if (score_ < 0) {
    return Err<i32>(ErrorCode::INVALID_ARGUMENT, "Score cannot be negative");
  }
  return Ok(score_ / 100);
}

// Good — no return value, but failure is possible
Result<void> Player::add_score(i32 amount) {
  if (amount <= 0) {
    return Err(ErrorCode::INVALID_ARGUMENT, "Amount must be positive");
  }
  score_ += amount;
  return Ok();
}
```

- Always use the `Ok(...)` and `Err(...)` helpers — do not construct `Result` or `Error` directly.
- Pick the `ErrorCode` that most accurately describes the failure. Do not use EXCEPTION as a substitute for proper error handling.
- Never silently discard a returned `Result`. Always check it via `is_ok()` / `is_error()` or the explicit operator bool:

```cpp
// Good
auto result = player.add_score(amount);
if (!result) {
  log_error(result.error().message());
  return;
}

// Also acceptable for compact checks
if (auto r = player.add_score(amount); !r) {
  log_error(r.error().message());
  return;
}

// Bad — result silently discarded
player.add_score(amount);
```

- Never call `.value()` without checking `is_ok()` first — it will `throw` if the result holds an error:

```cpp
// Good
auto result = player.compute_rank();
if (result.is_ok()) {
  display(result.value());
}

// Bad — potential throw if result holds an error
display(result.value());
```

- For multi-step operations, implement rollback if a step fails. Propagate the original Error outward without replacing it:

```cpp
auto r1 = step_one();
if (!r1) {
  return r1; // propagate as-is
}

auto r2 = step_two();
if (!r2) {
  rollback_step_one();
  return r2;
}
```

- Store human-readable error descriptions directly in `Error::message()` — a separate `err_msg_` field is no longer needed.
The message should explain the cause, not restate the error code:

```cpp
// Good
return Err<void>(ErrorCode::OUT_OF_RANGE, "Index 42 is out of bounds for size 10");

// Bad
return Err<void>(ErrorCode::OUT_OF_RANGE, "out of range error");
```

- Methods that are not yet implemented should return `Err()`
with no arguments — this automatically sets `ErrorCode::NOT_IMPLEMENTED`:

```cpp
Result<void> Player::sync_with_server() {
  return Err(); // NOT_IMPLEMENTED
}
```

---

### Miscellaneous
- Mark move constructors and move operators as `noexcept` if they genuinely cannot throw:
```cpp
Player(Player&& other) noexcept;
Player& operator=(Player&& other) noexcept;
```
- Use `std::exchange` in move constructors to reset moved-from fields to a valid empty state:
```cpp
Player::Player(Player&& other) noexcept
    : id_(std::exchange(other.id_, 0)),
      name_(std::move(other.name_)),
      score_(std::exchange(other.score_, 0)) {}
```
- Use `static_cast` explicitly when mixing integer and floating-point arithmetic — never rely on implicit conversion:
```cpp
// Good
double ratio = static_cast<double>(wins) / static_cast<double>(total);

// Bad — integer division silently truncates the result
double ratio = wins / total;
```
- Avoid magic numbers. Use named constants or enum values:
```cpp
// Good
if (health_ <= MIN_HEALTH) { ... }

// Bad
if (health_ <= 0) { ... }
```
- Never compare floating-point values with `==`. Use an epsilon-based utility:
```cpp
// Good
if (is_close(speed, target_speed, 1e-4)) { ... }

// Bad
if (speed == target_speed) { ... }
```

---

### Quick Class Template

`player.h`:
```cpp
// player.h
#pragma once

#include "common/common.h"
#include "common/result.h"


namespace game {


class Player {
 private:
  id_t id_;
  string name_;
  i32 score_;

 public:
  // Ctors
  Player() noexcept;
  Player(id_t id, string name, i32 score);
  Player(const Player& other);
  Player(Player&& other) noexcept;

  // Comparison ops
  bool operator==(const Player& other) const;
  bool operator!=(const Player& other) const;

  // Assignment ops
  Player& operator=(const Player& other);
  Player& operator=(Player&& other) noexcept;

  // Getters
  id_t id() const;
  string name() const;
  i32 score() const;

  // Setters
  void set_id(id_t value);
  void set_name(string value);
  void set_score(i32 value);

  // Domain methods
  Result<void> add_score(i32 amount);
  Result<void> reset();

  friend std::ostream& operator<<(std::ostream& os, const Player& p);
};


} // namespace game
```

`player.cpp`:
```cpp
// player.cpp
#include "player.h"


namespace game {


// =====Constructors
Player::Player() noexcept
    : id_{0},
      name_{""},
      score_{0} {}

Player::Player(id_t id, string name, i32 score)
    : id_{id},
      name_{name},
      score_{score} {}

Player::Player(const Player& other)
    : id_(other.id_),
      name_(other.name_),
      score_(other.score_) {}

Player::Player(Player&& other) noexcept
    : id_(std::exchange(other.id_, 0)),
      name_(std::move(other.name_)),
      score_(std::exchange(other.score_, 0)) {}

// =====Comparison ops
bool Player::operator==(const Player& other) const {
  return id_ == other.id_ && name_ == other.name_ && score_ == other.score_;
}

bool Player::operator!=(const Player& other) const {
  return !(*this == other);
}

// =====Assignment ops
Player& Player::operator=(const Player& other) {
  if (this != &other) {
    id_ = other.id_;
    name_ = other.name_;
    score_ = other.score_;
  }
  return *this;
}

Player& Player::operator=(Player&& other) noexcept {
  if (this != &other) {
    id_ = std::exchange(other.id_, 0);
    name_ = std::move(other.name_);
    score_ = std::exchange(other.score_, 0);
  }
  return *this;
}

// =====Getters
id_t Player::id() const { return id_; }
string Player::name() const { return name_; }
i32 Player::score() const { return score_; }

// =====Setters
void Player::set_id(id_t value) { id_ = value; }
void Player::set_name(string value) { name_ = value; }
void Player::set_score(i32 value) { score_ = value; }

// =====Domain methods
Result<void> Player::add_score(i32 amount) {
  if (amount <= 0) {
    return Err(ErrorCode::INVALID_ARGUMENT, "Amount must be positive");
  }
  score_ += amount;
  return Ok();
}

Result<void> Player::reset() {
  score_ = 0;
  return Ok();
}

// =====Output op
std::ostream& operator<<(std::ostream& os, const Player& p) {
  os << "Player \"" << p.name_ << "\", id: " << p.id_ << ", score: " << p.score_;
  return os;
}


} // namespace game
```
