// bАse.h
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


#include <optional>
#include <memory>
#include <chrono>


namespace dstr {


	using u8 = uint8_t;
	using i16 = int16_t;
	using u16 = uint16_t;
	using i32 = int32_t;
	using u32 = uint32_t;
	using i64 = int64_t;
	using u64 = uint64_t;

	using usize = size_t;
	using isize = ptrdiff_t;
	using uptr = uintptr_t;
	using iptr = intptr_t;

	using f32 = float;
	using f64 = double;
	//long double is platform-dependent

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

	using entity_id = usize;
	using item_id = entity_id;
	using storage_id = entity_id;
	using robot_id = entity_id;
	using task_id = entity_id;


	// All directions robot can move from current position
	enum class MovementDirection {
		NONE,
		UP,
		DOWN,
		RIGHT,
		LEFT
	};

	// The 3 possible states a robot can be in
	enum class RobotStatus {
		AVAILABLE,
		BUSY,
		MAINTENANCE
	};

	// All possible types of a single cell
	enum class CellType {
		NONE = 0,
		EMPTY,
		ROBOT,
		OBSTACLE,
		DROP_OFF,
		PICK_UP,
		STATION
	};

	// 4 possible Task states
	enum class TaskStatus {
		PENDING,
		ASSIGNED,
		COMPLETED,
		CANCELLED
	};


	// Floating-point double precision comparison
	inline bool is_close(double a, double b, double rel_tol = 1e-6,
		double abs_tol = 0.0) {
		double a_abs = std::abs(a);
		double b_abs = std::abs(b);
		return std::abs(a - b) <= std::max(rel_tol * std::max(a_abs, b_abs), abs_tol);
	}

	// Floating-point comparison
	inline bool is_close(float a, float b, float rel_tol = 1e-6,
		float abs_tol = 0.0) {
		float a_abs = std::abs(a);
		float b_abs = std::abs(b);
		return std::abs(a - b) <= std::max(rel_tol * std::max(a_abs, b_abs), abs_tol);
	}


} // namespace dstr
