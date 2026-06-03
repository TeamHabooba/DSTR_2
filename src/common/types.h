// tУpes.h
#pragma once


#include <common/base.h>
#include <common/strings.h>

#include <cstdint>
#include <cstring>
#include <string>
#include <ctime>
#include <chrono>
#include <variant>


namespace dstr {


  enum class ErrorCode {
    OK = 0,
    INVALID_ARGUMENT,
    OUT_OF_RANGE,
    EMPTY_CONTAINER,
    VALIDATION_FAILED,
    INVALID_DIMENSIONS,
    IO_ERROR,
    EXCEPTION,
    TERMINATED,
    NOT_IMPLEMENTED
  };


  class Error {
    ErrorCode code_;
    std::string message_;

  public:
    Error() noexcept : code_(ErrorCode::OK) {}

    Error(ErrorCode code, std::string message)
      : code_(code), message_(std::move(message)) {
    }

    Error(ErrorCode code, std::string_view message)
      : code_(code), message_(message) {
    }

    constexpr ErrorCode code() const noexcept { return code_; }
    const std::string& message() const noexcept { return message_; }
    constexpr bool is_ok() const noexcept { return code_ == ErrorCode::OK; }
  };


  template<typename T>
  class Result {
    std::variant<T, Error> data_;

  public:
    // Success ctor
    Result(T value) : data_(std::move(value)) {}

    // Error ctor
    Result(Error error) : data_(std::move(error)) {}

    Result(ErrorCode code, std::string message)
      : data_(Error(code, std::move(message))) {
    }

    Result(const Result&) = default;
    Result(Result&&) noexcept = default;
    Result& operator=(const Result&) = default;
    Result& operator=(Result&&) noexcept = default;
    ~Result() = default;

    bool is_ok() const noexcept {
      return std::holds_alternative<T>(data_);
    }

    bool is_error() const noexcept {
      return std::holds_alternative<Error>(data_);
    }

    const T& value() const& {
      return std::get<T>(data_);
    }

    T& value()& {
      return std::get<T>(data_);
    }

    T&& value()&& {
      return std::get<T>(std::move(data_));
    }

    const Error& error() const& {
      return std::get<Error>(data_);
    }

    Error& error()& {
      return std::get<Error>(data_);
    }

    // Success check op
    explicit operator bool() const noexcept {
      return is_ok();
    }
  };


  // void specification
  template<>
  class Result<void> {
    Error error_;

  public:
    Result() noexcept : error_() {}

    Result(Error error) : error_(std::move(error)) {}

    Result(ErrorCode code, std::string message)
      : error_(code, std::move(message)) {
    }

    template<typename T>
    Result(Result<T> parametrised) {
      if (parametrised) {
        error_ = Error();
      }
      else {
        error_ = parametrised.error();
      }
    }

    bool is_ok() const noexcept {
      return error_.is_ok();
    }

    bool is_error() const noexcept {
      return !error_.is_ok();
    }

    const Error& error() const noexcept {
      return error_;
    }

    explicit operator bool() const noexcept {
      return is_ok();
    }
  };


  // helper functions for Result
  template<typename T>
  Result<T> Ok(T value) {
    return Result<T>(std::move(value));
  }

  inline Result<void> Ok() {
    return Result<void>();
  }

  template<typename T>
  Result<T> Err(ErrorCode code, std::string message) {
    return Result<T>(Error(code, std::move(message)));
  }

  inline Result<void> Err(ErrorCode code, std::string message) {
    return Result<void>(Error(code, std::move(message)));
  }

  template<typename T>
  Result<T> Err() {
    return Result<T>(Error(ErrorCode::NOT_IMPLEMENTED, strings::ERR_NOT_IMPLEMENTED));
  }

  inline Result<void> Err() {
    return Result<void>(Error(ErrorCode::NOT_IMPLEMENTED, strings::ERR_NOT_IMPLEMENTED));
  }


  class Time {
  private:
    uint16_t year_;
    uint8_t month_;
    uint8_t day_;
    uint32_t milliseconds_from_midnight_;
    int16_t timezone_offset_minutes_;

    uint8_t leap_second_;
    uint8_t is_dst_;
    uint16_t microseconds_;
    uint16_t reserved_;

    // Private ctor for internal usage
    Time(uint16_t year, uint8_t month, uint8_t day, uint32_t milliseconds_from_midnight,
      int16_t timezone_offset_minutes, uint8_t leap_second, uint8_t is_dst,
      uint16_t microseconds, uint16_t reserved) noexcept
      : year_(year), month_(month), day_(day),
      milliseconds_from_midnight_(milliseconds_from_midnight),
      timezone_offset_minutes_(timezone_offset_minutes),
      leap_second_(leap_second), is_dst_(is_dst),
      microseconds_(microseconds), reserved_(reserved) {
    }

  public:
    // Ctors

    Time() noexcept : Time(1970, 1, 1, 0, 0, 0, 0, 0, 0) {}


    // Static fabric instead of public ctors

    static Result<Time> create(uint16_t year, uint8_t month, uint8_t day,
      uint32_t milliseconds_from_midnight,
      int16_t timezone_offset_minutes = 0,
      uint8_t leap_second = 0,
      uint8_t is_dst = 0,
      uint16_t microseconds = 0,
      uint16_t reserved = 0) {
      Time t(year, month, day, milliseconds_from_midnight, timezone_offset_minutes,
        leap_second, is_dst, microseconds, reserved);

      auto validation = t.validate();
      if (!validation) {
        return Err<Time>(validation.error().code(), validation.error().message());
      }

      return Ok(t);
    }


    // Rule of five

    Time(const Time&) = default;
    Time(Time&&) noexcept = default;
    Time& operator=(const Time&) = default;
    Time& operator=(Time&&) noexcept = default;
    ~Time() = default;


    // Getters

    uint16_t year() const noexcept { return year_; }
    uint8_t month() const noexcept { return month_; }
    uint8_t day() const noexcept { return day_; }
    uint8_t hours() const noexcept { return milliseconds_from_midnight_ / 3600000; }
    uint8_t minutes() const noexcept { return (milliseconds_from_midnight_ % 3600000) / 60000; }
    uint8_t seconds() const noexcept { return (milliseconds_from_midnight_ % 60000) / 1000; }
    uint16_t milliseconds() const noexcept { return milliseconds_from_midnight_ % 1000; }
    uint32_t milliseconds_from_midnight() const noexcept { return milliseconds_from_midnight_; }
    int16_t timezone_offset_minutes() const noexcept { return timezone_offset_minutes_; }
    bool leap_second() const noexcept { return leap_second_ != 0; }
    bool is_dst() const noexcept { return is_dst_ != 0; }
    uint16_t microseconds() const noexcept { return microseconds_; }


    // Setters + validation

    Result<void> year(uint16_t value) noexcept {
      year_ = value;
      return validate();
    }

    Result<void> month(uint8_t value) noexcept {
      if (value < 1 || value > 12) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_MONTH_RANGE));
      }
      month_ = value;
      return Ok();
    }

    Result<void> day(uint8_t value) noexcept {
      if (value < 1 || value > 31) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_DAY_RANGE));
      }
      day_ = value;
      return Ok();
    }

    Result<void> hours(uint8_t value) noexcept {
      if (value > 23) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_HOUR_RANGE));
      }
      uint32_t current_minutes = (milliseconds_from_midnight_ % 3600000) / 60000;
      uint32_t current_seconds = (milliseconds_from_midnight_ % 60000) / 1000;
      uint32_t current_millis = milliseconds_from_midnight_ % 1000;
      milliseconds_from_midnight_ =
        value * 3600000 +
        current_minutes * 60000 +
        current_seconds * 1000 +
        current_millis;
      return Ok();
    }

    Result<void> minutes(uint8_t value) noexcept {
      if (value > 59) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_MINUTE_RANGE));
      }
      uint32_t current_hours = milliseconds_from_midnight_ / 3600000;
      uint32_t current_seconds = (milliseconds_from_midnight_ % 60000) / 1000;
      uint32_t current_millis = milliseconds_from_midnight_ % 1000;
      milliseconds_from_midnight_ =
        current_hours * 3600000 +
        value * 60000 +
        current_seconds * 1000 +
        current_millis;
      return Ok();
    }

    Result<void> seconds(uint8_t value) noexcept {
      if (value > 59) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_SECOND_RANGE));
      }
      uint32_t current_hours = milliseconds_from_midnight_ / 3600000;
      uint32_t current_minutes = (milliseconds_from_midnight_ % 3600000) / 60000;
      uint32_t current_millis = milliseconds_from_midnight_ % 1000;
      milliseconds_from_midnight_ =
        current_hours * 3600000 +
        current_minutes * 60000 +
        value * 1000 +
        current_millis;
      return Ok();
    }

    Result<void> milliseconds(uint16_t value) noexcept {
      if (value > 999) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_MILLISECOND_RANGE));
      }
      uint32_t current_hours = milliseconds_from_midnight_ / 3600000;
      uint32_t current_minutes = (milliseconds_from_midnight_ % 3600000) / 60000;
      uint32_t current_seconds = (milliseconds_from_midnight_ % 60000) / 1000;
      milliseconds_from_midnight_ =
        current_hours * 3600000 +
        current_minutes * 60000 +
        current_seconds * 1000 +
        value;
      return Ok();
    }

    Result<void> milliseconds_from_midnight(uint32_t value) noexcept {
      uint32_t max_millis = 86400000 + (leap_second_ ? 1000 : 0);
      if (value >= max_millis) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_MIDNIGHT_RANGE));
      }
      milliseconds_from_midnight_ = value;
      return Ok();
    }

    Result<void> timezone_offset_minutes(int16_t value) noexcept {
      if (!valid_timezone_offset(value)) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_TZ_RANGE));
      }
      timezone_offset_minutes_ = value;
      return Ok();
    }

    void leap_second(bool value) noexcept {
      leap_second_ = value ? 1 : 0;
    }

    void is_dst(bool value) noexcept {
      is_dst_ = value ? 1 : 0;
    }

    Result<void> set_microseconds(uint16_t value) noexcept {
      if (value >= 1000) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_MICROSECOND_RANGE));
      }
      microseconds_ = value;
      return Ok();
    }


    // Validation

    static bool valid_timezone_offset(int16_t timezone_offset_minutes) noexcept {
      return timezone_offset_minutes >= -720 && timezone_offset_minutes <= 840;
    }

    bool has_valid_timezone_offset() const noexcept {
      return valid_timezone_offset(timezone_offset_minutes_);
    }

    Result<void> validate() const noexcept {
      if (month_ < 1 || month_ > 12) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_INVALID_MONTH));
      }
      if (day_ < 1 || day_ > 31) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_INVALID_DAY));
      }
      uint32_t max_millis = 86400000 + (leap_second_ ? 1000 : 0);
      if (milliseconds_from_midnight_ >= max_millis) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_INVALID_MILLISECONDS));
      }
      if (!has_valid_timezone_offset()) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_INVALID_TZ));
      }
      if (microseconds_ >= 1000) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_INVALID_MICROSECONDS));
      }
      return Ok();
    }


    // Depricated

    std::string validate_legacy() const {
      auto result = validate();
      if (result.is_ok()) {
        return std::string(strings::TXT_EMPTY);
      }
      return result.error().message();
    }


    // Change to another timezone

    Result<void> move_to_timezone(int16_t target_timezone_offset_minutes) noexcept {
      if (!valid_timezone_offset(target_timezone_offset_minutes)) {
        return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_TARGET_TZ));
      }
      int32_t diff = target_timezone_offset_minutes - timezone_offset_minutes_;
      timezone_offset_minutes_ = target_timezone_offset_minutes;
      int64_t new_millis = static_cast<int64_t>(milliseconds_from_midnight_) + (diff * 60000);
      // Next day processing
      if (new_millis < 0) {
        // TODO: reduce a day
        new_millis += 86400000;
      }
      else if (new_millis >= 86400000) {
        // TODO: increase a day
        new_millis -= 86400000;
      }
      milliseconds_from_midnight_ = static_cast<uint32_t>(new_millis);
      return Ok();
    }


    // From/to std time types

    static Result<Time> from_tm(const std::tm& tm_info, int16_t tz_offset = 0) noexcept {
      Time result;
      result.year_ = tm_info.tm_year + 1900;
      result.month_ = tm_info.tm_mon + 1;
      result.day_ = tm_info.tm_mday;
      result.milliseconds_from_midnight_ =
        tm_info.tm_hour * 3600000 +
        tm_info.tm_min * 60000 +
        tm_info.tm_sec * 1000;
      result.timezone_offset_minutes_ = tz_offset;
      result.leap_second_ = 0;
      result.is_dst_ = tm_info.tm_isdst > 0 ? 1 : 0;
      result.microseconds_ = 0;
      result.reserved_ = 0;
      auto validation = result.validate();
      if (!validation) {
        return Err<Time>(validation.error().code(), validation.error().message());
      }
      return Ok(result);
    }

    static Result<Time> from_time_t(std::time_t t, int16_t tz_offset = 0) {
      auto tm_info = std::make_unique<tm>();
#ifdef _WIN32
      gmtime_s(tm_info.get(), &t);
#else
      tm_info = std::gmtime(&t);
#endif
      if (!tm_info) {
        return Err<Time>(ErrorCode::INVALID_ARGUMENT, std::string(strings::ERR_TIME_TIME_T));
      }
      return from_tm(*tm_info, tz_offset);
    }

    std::tm to_tm() const noexcept {
      std::tm tm_info = {};
      tm_info.tm_year = year_ - 1900;
      tm_info.tm_mon = month_ - 1;
      tm_info.tm_mday = day_;
      tm_info.tm_hour = hours();
      tm_info.tm_min = minutes();
      tm_info.tm_sec = seconds();
      tm_info.tm_isdst = is_dst_;
      return tm_info;
    }

    Result<std::time_t> to_time_t() const noexcept {
      auto validation = validate();
      if (!validation) {
        return Err<std::time_t>(validation.error().code(), validation.error().message());
      }
      std::tm tm_info = to_tm();
#ifdef _WIN32
      std::time_t result = _mkgmtime(&tm_info);
#else
      std::time_t result = timegm(&tm_info);
#endif
      if (result == -1) {
        return Err<std::time_t>(ErrorCode::INVALID_ARGUMENT, std::string(strings::ERR_TIME_TO_TIME_T));
      }
      return Ok(result);
    }

    // system_clock processing

    static Result<Time> from_system_clock(const std::chrono::system_clock::time_point& tp,
      int16_t tz_offset = 0) {
      std::time_t t = std::chrono::system_clock::to_time_t(tp);
      auto duration_since_epoch = tp.time_since_epoch();
      auto total_micros = std::chrono::duration_cast<std::chrono::microseconds>(duration_since_epoch).count();
      auto micros_in_second = total_micros % 1000000;
      uint16_t milliseconds_part = static_cast<uint16_t>(micros_in_second / 1000);
      uint16_t microseconds_part = micros_in_second % 1000;
      auto result = from_time_t(t, tz_offset);
      if (!result) {
        return result;
      }
      Time time = result.value();
      auto millis_result = time.milliseconds(milliseconds_part);
      if (!millis_result) {
        return Err<Time>(millis_result.error().code(), millis_result.error().message());
      }
      auto micros_result = time.set_microseconds(microseconds_part);
      if (!micros_result) {
        return Err<Time>(micros_result.error().code(), micros_result.error().message());
      }
      return Ok(time);
    }

    Result<std::chrono::system_clock::time_point> to_system_clock() const {
      auto time_t_result = to_time_t();
      if (!time_t_result) {
        return Err<std::chrono::system_clock::time_point>(
          time_t_result.error().code(),
          time_t_result.error().message());
      }
      auto tp = std::chrono::system_clock::from_time_t(time_t_result.value());
      tp += std::chrono::milliseconds(milliseconds());
      tp += std::chrono::microseconds(microseconds());
      return Ok(tp);
    }

    // system_clock::time_point ctor (for reverse compatibility)
    explicit Time(const std::chrono::system_clock::time_point& tp, int16_t tz_offset = 0) {
      auto result = from_system_clock(tp, tz_offset);
      if (result) {
        *this = result.value();
      }
      else {
        *this = Time(); // Fallback to the defaults
      }
    }


    // Serialization

    void to_bytes(uint8_t* buffer) const noexcept {
      std::memcpy(buffer, this, sizeof(Time));
    }

    static Result<Time> from_bytes(const uint8_t* buffer) {
      if (buffer == nullptr) {
        return Err<Time>(ErrorCode::INVALID_ARGUMENT, std::string(strings::ERR_TIME_BUFFER_NULL));
      }
      Time t;
      std::memcpy(&t, buffer, sizeof(Time));
      auto validation = t.validate();
      if (!validation) {
        return Err<Time>(validation.error().code(), validation.error().message());
      }
      return Ok(t);
    }


    // Comparison ops

    bool operator==(const Time& other) const noexcept {
      if (this == &other) return true;
      return std::memcmp(this, &other, sizeof(Time)) == 0;
    }

    bool operator!=(const Time& other) const noexcept {
      return !(*this == other);
    }

    bool operator<(const Time& other) const noexcept {
      if (year_ != other.year_) return year_ < other.year_;
      if (month_ != other.month_) return month_ < other.month_;
      if (day_ != other.day_) return day_ < other.day_;
      if (milliseconds_from_midnight_ != other.milliseconds_from_midnight_)
        return milliseconds_from_midnight_ < other.milliseconds_from_midnight_;
      return microseconds_ < other.microseconds_;
    }

    bool operator<=(const Time& other) const noexcept {
      return *this < other || *this == other;
    }

    bool operator>(const Time& other) const noexcept {
      return !(*this <= other);
    }

    bool operator>=(const Time& other) const noexcept {
      return !(*this < other);
    }


    // String values

    std::string to_string() const {
      char buffer[128];
      std::snprintf(buffer, sizeof(buffer),
        strings::FMT_TIME_STRING.data(),
        year_, month_, day_, hours(), minutes(), seconds(),
        milliseconds(), microseconds(),
        leap_second() ? strings::TXT_LEAP_SECOND.data() : strings::TXT_EMPTY.data(),
        timezone_offset_minutes_ / 60,
        static_cast<unsigned>(std::abs(timezone_offset_minutes_ % 60)),
        is_dst() ? strings::TXT_DST.data() : strings::TXT_EMPTY.data());
      return std::string(buffer);
    }

    std::string to_iso8601() const {
      char buffer[64];
      std::snprintf(buffer, sizeof(buffer),
        strings::FMT_TIME_ISO8601.data(),
        year_, month_, day_, hours(), minutes(), seconds(),
        milliseconds(),
        timezone_offset_minutes_ / 60,
        static_cast<unsigned>(std::abs(timezone_offset_minutes_ % 60)));
      return std::string(buffer);
    }


    // Current time

    static Result<Time> now() {
      auto t_now = std::chrono::system_clock::now();
      return from_system_clock(t_now);
    }
  };


  template<typename T>
  class Queue {
  private:
    Array<T> items_;
    usize front_;

  public:
    Queue();

    usize size() const;
    bool empty() const;

    Result<void> enqueue(const T& value);
    Result<T> dequeue();
    Result<T> peek() const;
    Result<T> at(usize index) const;
    void clear();

  };

  template<typename T>
  Queue<T>::Queue()
    : items_{},
    front_{ 0 } {
  }

  template<typename T>
  usize Queue<T>::size() const {
    return items_.size() - front_;
  }

  template<typename T>
  bool Queue<T>::empty() const {
    return size() == 0;
  }

  template<typename T>
  Result<void> Queue<T>::enqueue(const T& value) {
    items_.push_back(value);
    return Ok();
  }

  template<typename T>
  Result<T> Queue<T>::dequeue() {
    if (empty()) {
      return Err<T>(ErrorCode::EMPTY_CONTAINER, string(strings::ERR_QUEUE_EMPTY));
    }
    T value = items_.unchecked_at(front_);
    front_++;
    if (front_ > 0 && front_ * 2 >= items_.size()) {
      Array<T> compacted(items_.size() - front_);
      for (usize i = front_; i < items_.size(); i++) {
        compacted.push_back(items_.unchecked_at(i));
      }
      items_ = std::move(compacted);
      front_ = 0;
    }
    return Ok(value);
  }

  template<typename T>
  Result<T> Queue<T>::peek() const {
    if (empty()) {
      return Err<T>(ErrorCode::EMPTY_CONTAINER, string(strings::ERR_QUEUE_EMPTY));
    }
    return Ok(items_.unchecked_at(front_));
  }

  template<typename T>
  Result<T> Queue<T>::at(usize index) const {
    if (index >= size()) {
      return Err<T>(ErrorCode::OUT_OF_RANGE, string(strings::ERR_QUEUE_INDEX_RANGE));
    }
    return Ok(items_.unchecked_at(front_ + index));
  }

  template<typename T>
  void Queue<T>::clear() {
    items_.clear();
    front_ = 0;
  }


  template <typename T>
  class Array {
  private:
    std::unique_ptr<T[]> data_;
    usize size_;
    usize capacity_;

  public:
    // Ctors
    Array();
    explicit Array(usize initial_capacity);
    Array(const Array& other);
    Array(Array&& other) noexcept;

    // Comparison ops
    bool operator==(const Array& other) const;
    bool operator!=(const Array& other) const;

    // Assignment ops
    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    // Getters
    Result<T>       operator[](usize index);
    Result<const T> operator[](usize index) const;
    Result<T>       get(usize index);
    Result<const T> get(usize index) const;
    T& unchecked_at(usize index);
    const T& unchecked_at(usize index) const;
    usize           size() const;
    usize           capacity() const;
    bool            empty() const;

    // Domain methods — CRUD
    void          push_back(const T& value);
    Result<void>  insert(usize index, const T& value);
    Result<void>  update(usize index, const T& value);
    Result<void>  pop_back();
    Result<void>  remove(usize index);
    void          clear();

    // Domain methods — Sort
    template <typename Comparator>
    void bubble_sort(Comparator comp);

    template <typename Comparator>
    void insertion_sort(Comparator comp);

    template <typename Comparator>
    void quick_sort(Comparator comp);

    // Domain methods — Search
    template <typename KeyComp>
    usize linear_search(KeyComp key_comp) const;

    template <typename Comparator, typename KeyComp>
    usize binary_search(Comparator comp, KeyComp key_comp, const T& target) const;

    template <typename Comparator, typename KeyComp>
    usize jump_search(Comparator comp, KeyComp key_comp, const T& target) const;

    void print(std::ostream& os) const;

    // Output op
    friend std::ostream& operator<<(std::ostream& os, const Array<T>& arr) {
      for (usize i = 0; i < arr.size_; i++) {
        os << strings::TXT_LEFT_BRACKET << i << strings::TXT_RIGHT_BRACKET_SPACE
          << arr.data_[i] << strings::NL;
      }
      return os;
    }

  private:
    void grow();
    void swap_elements(usize i, usize j);

    template <typename Comparator>
    usize partition(Comparator comp, usize low, usize high);

    template <typename Comparator>
    void quick_sort_helper(Comparator comp, usize low, usize high);
  };

  constexpr i32 DEFAULT_CAPACITY = 8;

  // =====Constructors

  template <typename T>
  Array<T>::Array()
    : data_(std::make_unique<T[]>(DEFAULT_CAPACITY)),
    size_(0),
    capacity_(DEFAULT_CAPACITY) {
  }

  template <typename T>
  Array<T>::Array(usize initial_capacity)
    : data_(std::make_unique<T[]>(initial_capacity)),
    size_(0),
    capacity_(initial_capacity) {
  }

  template <typename T>
  Array<T>::Array(const Array& other)
    : data_(std::make_unique<T[]>(other.capacity_)),
    size_(other.size_),
    capacity_(other.capacity_) {
    for (usize i = 0; i < size_; i++) {
      data_[i] = other.data_[i];
    }
  }

  template <typename T>
  Array<T>::Array(Array&& other) noexcept
    : data_(std::move(other.data_)),
    size_(std::exchange(other.size_, 0)),
    capacity_(std::exchange(other.capacity_, 0)) {
  }

  // =====Comparison ops

  template <typename T>
  bool Array<T>::operator==(const Array& other) const {
    if (size_ != other.size_) {
      return false;
    }
    for (usize i = 0; i < size_; i++) {
      if (data_[i] != other.data_[i]) {
        return false;
      }
    }
    return true;
  }

  template <typename T>
  bool Array<T>::operator!=(const Array& other) const {
    return !(*this == other);
  }

  // =====Assignment ops

  template <typename T>
  Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
      data_ = std::make_unique<T[]>(other.capacity_);
      size_ = other.size_;
      capacity_ = other.capacity_;
      for (usize i = 0; i < size_; i++) {
        data_[i] = other.data_[i];
      }
    }
    return *this;
  }

  template <typename T>
  Array<T>& Array<T>::operator=(Array&& other) noexcept {
    if (this != &other) {
      data_ = std::move(other.data_);
      size_ = std::exchange(other.size_, 0);
      capacity_ = std::exchange(other.capacity_, 0);
    }
    return *this;
  }

  // =====Getters

  template <typename T>
  Result<T> Array<T>::operator[](usize index) {
    if (index >= size_) {
      return Err<T>(ErrorCode::OUT_OF_RANGE, string(strings::ERR_INVALID_ARGUMENT));
    }
    return Ok(data_[index]);
  }

  template <typename T>
  Result<const T> Array<T>::operator[](usize index) const {
    if (index >= size_) {
      return Err<const T>(ErrorCode::OUT_OF_RANGE, string(strings::ERR_INVALID_ARGUMENT));
    }
    return Ok<const T>(data_[index]);
  }

  template <typename T>
  Result<T> Array<T>::get(usize index) {
    return (*this)[index];
  }

  template <typename T>
  Result<const T> Array<T>::get(usize index) const {
    return (*this)[index];
  }

  template <typename T>
  T& Array<T>::unchecked_at(usize index) {
    return data_[index];
  }

  template <typename T>
  const T& Array<T>::unchecked_at(usize index) const {
    return data_[index];
  }

  template <typename T>
  usize Array<T>::size() const {
    return size_;
  }

  template <typename T>
  usize Array<T>::capacity() const {
    return capacity_;
  }

  template <typename T>
  bool Array<T>::empty() const {
    return size_ == 0;
  }

  // =====Domain methods

  template <typename T>
  void Array<T>::push_back(const T& value) {
    if (size_ == capacity_) {
      grow();
    }
    data_[size_] = value;
    size_++;
  }

  template <typename T>
  Result<void> Array<T>::insert(usize index, const T& value) {
    if (index > size_) {
      return Err(ErrorCode::OUT_OF_RANGE, string(strings::ERR_INVALID_ARGUMENT));
    }
    if (size_ == capacity_) {
      grow();
    }
    for (usize i = size_; i > index; i--) {
      data_[i] = data_[i - 1];
    }
    data_[index] = value;
    size_++;
    return Ok();
  }

  template <typename T>
  Result<void> Array<T>::update(usize index, const T& value) {
    if (index >= size_) {
      return Err(ErrorCode::OUT_OF_RANGE, string(strings::ERR_INVALID_ARGUMENT));
    }
    data_[index] = value;
    return Ok();
  }

  template <typename T>
  Result<void> Array<T>::pop_back() {
    if (size_ == 0) {
      return Err(ErrorCode::EMPTY_CONTAINER, string(strings::ERR_INVALID_ARGUMENT));
    }
    size_--;
    return Ok();
  }

  template <typename T>
  Result<void> Array<T>::remove(usize index) {
    if (index >= size_) {
      return Err(ErrorCode::OUT_OF_RANGE, string(strings::ERR_INVALID_ARGUMENT));
    }
    for (usize i = index; i < size_ - 1; i++) {
      data_[i] = data_[i + 1];
    }
    size_--;
    return Ok();
  }

  template <typename T>
  void Array<T>::clear() {
    size_ = 0;
  }

  // =====Sort algorithms

  template <typename T>
  template <typename Comparator>
  void Array<T>::bubble_sort(Comparator comp) {
    for (usize i = 0; i < size_ - 1; i++) {
      bool swapped = false;
      for (usize j = 0; j < size_ - i - 1; j++) {
        if (comp(data_[j + 1], data_[j])) {
          swap_elements(j, j + 1);
          swapped = true;
        }
      }
      if (!swapped) {
        break;
      }
    }
  }

  template <typename T>
  template <typename Comparator>
  void Array<T>::insertion_sort(Comparator comp) {
    for (usize i = 1; i < size_; i++) {
      T key = data_[i];
      usize j = i;
      while (j > 0 && comp(key, data_[j - 1])) {
        data_[j] = data_[j - 1];
        j--;
      }
      data_[j] = key;
    }
  }

  template <typename T>
  template <typename Comparator>
  void Array<T>::quick_sort(Comparator comp) {
    if (size_ <= 1) {
      return;
    }
    quick_sort_helper(comp, 0, size_ - 1);
  }

  // =====Search algorithms

  template <typename T>
  template <typename KeyComp>
  usize Array<T>::linear_search(KeyComp key_comp) const {
    for (usize i = 0; i < size_; i++) {
      if (key_comp(data_[i])) {
        return i;
      }
    }
    return -1;
  }

  template <typename T>
  template <typename Comparator, typename KeyComp>
  usize Array<T>::binary_search(Comparator comp, KeyComp key_comp, const T& target) const {
    if (size_ == 0) {
      return static_cast<usize>(-1);
    }
    usize low = 0;
    usize high = size_ - 1;
    while (low <= high) {
      usize mid = low + (high - low) / 2;
      if (key_comp(data_[mid])) {
        return mid;
      }
      else if (comp(data_[mid], target)) {
        low = mid + 1;
      }
      else {
        high = mid - 1;
      }
    }
    return -1;
  }

  template <typename T>
  template <typename Comparator, typename KeyComp>
  usize Array<T>::jump_search(Comparator comp, KeyComp key_comp, const T& target) const {
    if (size_ == 0) {
      return -1;
    }
    usize step = static_cast<usize>(std::sqrt(static_cast<double>(size_)));
    usize prev = 0;
    usize curr = step;
    while (curr < size_ && comp(data_[curr], target)) {
      prev = curr;
      curr += step;
    }
    if (curr >= size_) {
      curr = size_ - 1;
    }
    for (usize i = prev; i <= curr; i++) {
      if (key_comp(data_[i])) {
        return i;
      }
    }
    return -1;
  }

  // =====Analysis API

  template <typename T>
  void Array<T>::print(std::ostream& os) const {
    for (usize i = 0; i < size_; i++) {
      os << strings::TXT_LEFT_BRACKET << i << strings::TXT_RIGHT_BRACKET_SPACE
        << data_[i] << strings::NL;
    }
  }

  // =====Private helpers

  template <typename T>
  void Array<T>::grow() {
    if (capacity_ == 0) {
      capacity_ = DEFAULT_CAPACITY;
    }
    else {
      capacity_ = capacity_ * 2;
    }
    std::unique_ptr<T[]> new_data = std::make_unique<T[]>(capacity_);
    for (usize i = 0; i < size_; i++) {
      new_data[i] = data_[i];
    }
    data_ = std::move(new_data);
  }

  template <typename T>
  void Array<T>::swap_elements(usize i, usize j) {
    T temp = data_[i];
    data_[i] = data_[j];
    data_[j] = temp;
  }

  template <typename T>
  template <typename Comparator>
  usize Array<T>::partition(Comparator comp, usize low, usize high) {
    T pivot = data_[high];
    usize i = low - 1;
    for (usize j = low; j < high; j++) {
      if (comp(data_[j], pivot)) {
        i++;
        swap_elements(i, j);
      }
    }
    swap_elements(i + 1, high);
    return i + 1;
  }

  template <typename T>
  template <typename Comparator>
  void Array<T>::quick_sort_helper(Comparator comp, usize low, usize high) {
    if (low < high) {
      usize pivot_pos = partition(comp, low, high);
      quick_sort_helper(comp, low, pivot_pos - 1);
      quick_sort_helper(comp, pivot_pos + 1, high);
    }
  }


  // Class prototypes

  template<typename T, typename W>
  class Edge;

  template<typename T, typename W>
  class Node;

  template<typename T, typename W>
  class Graph;


  // Unique node index
  struct NodeId {
    usize index;
    u32 generation;

    bool operator==(NodeId other) const {
      return generation == other.generation && index == other.index;
    }

    bool operator!=(NodeId other) const {
      return !((*this) == other);
    }
  };


  /// <summary>
  /// Node slot. Contains and owns a node directly without std::optional or pointers.
  /// </summary>
  /// <typeparam name="T">Node content type.</typeparam>
  /// <typeparam name="W">Weight type. dstr::i32 by default.</typeparam>
  template<typename T, typename W>
  struct NodeSlot {
    Node<T, W> node;
    bool occupied;
    u32 generation;

    NodeSlot();
  };


  /// <summary>
  /// Graph edge. References a node using NodeId.
  /// </summary>
  /// <typeparam name="T">Node content type.</typeparam>
  /// <typeparam name="W">Weight type. dstr::i32 by default.</typeparam>
  template<typename T, typename W>
  class Edge {
    W weight_;
    NodeId target_;

  public:
    Edge();
    Edge(NodeId target, W weight = W());

    NodeId target() const;
    W weight() const;
    void set_weight(W weight);
  };


  template<typename T, typename W>
  class Node {
    T value_;
    Array<Edge<T, W>> links_;

  public:
    Node();
    Node(T value);

    const T& value() const;
    T& value();
    void set_value(T value);
    const Array<Edge<T, W>>& links() const;
    Array<Edge<T, W>>& links();
  };


  /// <summary>
  /// Graph class. Represented physically as a dynamic array. Physical representation is private.
  /// </summary>
  /// <typeparam name="T">Node content type.</typeparam>
  /// <typeparam name="W">Weight type. dstr::i32 by default.</typeparam>
  template<typename T, typename W = i32>
  class Graph {
    Array<NodeSlot<T, W>> slots_;
    W default_weight_;
    usize size_;

  public:
    Graph();
    Graph(W default_weight);

    Result<NodeId> add_node(T value);
    Result<void> set_node_value(NodeId id, T value);
    Result<void> remove_node(NodeId id);

    usize size() const;
    usize raw_size() const;
    Result<T> at(NodeId id) const;
    Result<T> at(usize raw_index) const;
    Result<Array<Edge<T, W>>> edges(NodeId id) const;
    Result<void> update(NodeId id, T value);
    Result<void> update(usize raw_index, T value);
    bool valid_node_id(NodeId id) const;
    bool occupied(NodeId id) const;
    bool occupied(usize raw_index) const;
    NodeId node_id_at(usize raw_index) const;

    Result<void> add_edge_bidirectional(NodeId from, NodeId to, W weight);
    Result<void> add_edge_directional(NodeId from, NodeId to, W weight);
    Result<void> add_edge(NodeId from, NodeId to, bool bidirectional = false);
    Result<void> add_edge(NodeId from, NodeId to, bool bidirectional, W weight);
    Result<void> edge_weight_directional(NodeId from, NodeId to, W weight);
    Result<void> edge_weight_bidirectional(NodeId from, NodeId to, W weight);
    Result<void> edge_weight(NodeId from, NodeId to, W weight, bool bidirectional = false);
    Result<void> remove_edge_directional(NodeId from, NodeId to);
    Result<void> remove_edge_bidirectional(NodeId from, NodeId to);
    Result<void> remove_edge(NodeId from, NodeId to, bool bidirectional = false);
    Result<W> edge_weight(NodeId from, NodeId to) const;
    bool edge_exists(NodeId from, NodeId to) const;
    Result<void> clear_edges(NodeId id);
    void clear_edges();

  private:
    Result<usize> find_edge_index(NodeId from, NodeId to) const;
    Result<void> validate_pair(NodeId from, NodeId to) const;

  };

  // =====NodeSlot<> struct

  template<typename T, typename W>
  NodeSlot<T, W>::NodeSlot()
    : node{},
    occupied{ false },
    generation{ 0 } {
  }


  // =====Edge<> class

  template<typename T, typename W>
  Edge<T, W>::Edge() : weight_{ W() }, target_{ NodeId{0, 0} } {}

  template<typename T, typename W>
  Edge<T, W>::Edge(NodeId target, W weight)
    : weight_{ weight }, target_{ NodeId(target) } {
  }

  template<typename T, typename W>
  NodeId Edge<T, W>::target() const {
    return target_;
  }

  template<typename T, typename W>
  W Edge<T, W>::weight() const {
    return weight_;
  }

  template<typename T, typename W>
  void Edge<T, W>::set_weight(W weight) {
    weight_ = weight;
  }


  // =====Node<> class

  template<typename T, typename W>
  Node<T, W>::Node() : value_{ T() }, links_{ Array<Edge<T,W>>() } {}

  template<typename T, typename W>
  Node<T, W>::Node(T value) : value_{ value }, links_{ Array<Edge<T,W>>() } {}

  template<typename T, typename W>
  const T& Node<T, W>::value() const {
    return value_;
  }

  template<typename T, typename W>
  T& Node<T, W>::value() {
    return value_;
  }

  template<typename T, typename W>
  void Node<T, W>::set_value(T value) {
    value_ = value;
  }

  template<typename T, typename W>
  const Array<Edge<T, W>>& Node<T, W>::links() const {
    return links_;
  }

  template<typename T, typename W>
  Array<Edge<T, W>>& Node<T, W>::links() {
    return links_;
  }


  // =====Graph<> class

  template<typename T, typename W>
  Graph<T, W>::Graph()
    : slots_{ Array<NodeSlot<T,W>>() },
    default_weight_{ W() },
    size_{ 0 } {
  }

  template<typename T, typename W>
  Graph<T, W>::Graph(W default_weight)
    : slots_{ Array<NodeSlot<T,W>>() },
    default_weight_{ default_weight },
    size_{ 0 } {
  }

  template<typename T, typename W>
  Result<NodeId> Graph<T, W>::add_node(T value) {
    for (usize i = 0; i < slots_.size(); i++) {
      auto& slot = slots_.unchecked_at(i);
      if (!slot.occupied) {
        slot.node = Node<T, W>(value);
        slot.occupied = true;
        slot.generation++;
        size_++;
        return Ok(NodeId{ i, slot.generation });
      }
    }
    NodeSlot<T, W> slot;
    slot.node = Node<T, W>(value);
    slot.occupied = true;
    slot.generation = 1;
    slots_.push_back(slot);
    size_++;
    return Ok(NodeId{ slots_.size() - 1, slot.generation });
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::set_node_value(NodeId id, T value) {
    if (!valid_node_id(id)) {
      return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_GRAPH_NODE_ID));
    }
    slots_.unchecked_at(id.index).node.set_value(value);
    return Ok();
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::remove_node(NodeId id) {
    if (!valid_node_id(id)) {
      return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_GRAPH_NODE_ID));
    }
    for (usize i = 0; i < slots_.size(); i++) {
      if (slots_.unchecked_at(i).occupied) {
        remove_edge_directional(node_id_at(i), id);
      }
    }
    auto& slot = slots_.unchecked_at(id.index);
    slot.occupied = false;
    slot.node = Node<T, W>();
    size_--;
    return Ok();
  }

  template<typename T, typename W>
  usize Graph<T, W>::size() const {
    return size_;
  }

  template<typename T, typename W>
  usize Graph<T, W>::raw_size() const {
    return slots_.size();
  }

  template<typename T, typename W>
  Result<T> Graph<T, W>::at(NodeId id) const {
    if (!valid_node_id(id)) {
      return Err<T>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_GRAPH_NODE_ID));
    }
    return Ok(slots_.unchecked_at(id.index).node.value());
  }

  template<typename T, typename W>
  Result<T> Graph<T, W>::at(usize raw_index) const {
    if (!occupied(raw_index)) {
      return Err<T>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_GRAPH_RAW_INDEX));
    }
    return Ok(slots_.unchecked_at(raw_index).node.value());
  }

  template<typename T, typename W>
  Result<Array<Edge<T, W>>> Graph<T, W>::edges(NodeId id) const {
    if (!valid_node_id(id)) {
      return Err<Array<Edge<T, W>>>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_GRAPH_NODE_ID));
    }
    return Ok(slots_.unchecked_at(id.index).node.links());
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::update(NodeId id, T value) {
    return set_node_value(id, value);
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::update(usize raw_index, T value) {
    if (!occupied(raw_index)) {
      return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_GRAPH_RAW_INDEX));
    }
    slots_.unchecked_at(raw_index).node.set_value(value);
    return Ok();
  }

  template<typename T, typename W>
  bool Graph<T, W>::valid_node_id(NodeId id) const {
    if (id.index >= slots_.size()) {
      return false;
    }
    const auto& slot = slots_.unchecked_at(id.index);
    return slot.occupied && slot.generation == id.generation;
  }

  template<typename T, typename W>
  bool Graph<T, W>::occupied(NodeId id) const {
    return valid_node_id(id);
  }

  template<typename T, typename W>
  bool Graph<T, W>::occupied(usize raw_index) const {
    return raw_index < slots_.size() && slots_.unchecked_at(raw_index).occupied;
  }

  template<typename T, typename W>
  NodeId Graph<T, W>::node_id_at(usize raw_index) const {
    const auto& slot = slots_.unchecked_at(raw_index);
    return NodeId{ raw_index, slot.generation };
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::add_edge_bidirectional(NodeId from, NodeId to, W weight) {
    auto first = add_edge_directional(from, to, weight);
    if (!first) {
      return first;
    }
    return add_edge_directional(to, from, weight);
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::add_edge_directional(NodeId from, NodeId to, W weight) {
    auto valid = validate_pair(from, to);
    if (!valid) {
      return valid;
    }
    auto& links = slots_.unchecked_at(from.index).node.links();
    auto existing = find_edge_index(from, to);
    if (existing) {
      links.unchecked_at(existing.value()).set_weight(weight);
      return Ok();
    }
    links.push_back(Edge<T, W>(to, weight));
    return Ok();
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::add_edge(NodeId from, NodeId to, bool bidirectional) {
    return add_edge(from, to, bidirectional, default_weight_);
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::add_edge(NodeId from, NodeId to, bool bidirectional, W weight) {
    if (bidirectional) {
      return add_edge_bidirectional(from, to, weight);
    }
    return add_edge_directional(from, to, weight);
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::edge_weight_directional(NodeId from, NodeId to, W weight) {
    auto edge_index = find_edge_index(from, to);
    if (!edge_index) {
      return Result<void>(edge_index);
    }
    slots_.unchecked_at(from.index).node.links().unchecked_at(edge_index.value()).set_weight(weight);
    return Ok();
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::edge_weight_bidirectional(NodeId from, NodeId to, W weight) {
    auto first = edge_weight_directional(from, to, weight);
    if (!first) {
      return first;
    }
    return edge_weight_directional(to, from, weight);
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::edge_weight(NodeId from, NodeId to, W weight, bool bidirectional) {
    if (bidirectional) {
      return edge_weight_bidirectional(from, to, weight);
    }
    return edge_weight_directional(from, to, weight);
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::remove_edge_directional(NodeId from, NodeId to) {
    auto edge_index = find_edge_index(from, to);
    if (!edge_index) {
      return Result<void>(edge_index);
    }
    return slots_.unchecked_at(from.index).node.links().remove(edge_index.value());
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::remove_edge_bidirectional(NodeId from, NodeId to) {
    auto first = remove_edge_directional(from, to);
    if (!first) {
      return first;
    }
    return remove_edge_directional(to, from);
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::remove_edge(NodeId from, NodeId to, bool bidirectional) {
    if (bidirectional) {
      return remove_edge_bidirectional(from, to);
    }
    return remove_edge_directional(from, to);
  }

  template<typename T, typename W>
  Result<W> Graph<T, W>::edge_weight(NodeId from, NodeId to) const {
    auto edge_index = find_edge_index(from, to);
    if (!edge_index) {
      return Err<W>(edge_index.error().code(), edge_index.error().message());
    }
    return Ok(slots_.unchecked_at(from.index).node.links().unchecked_at(edge_index.value()).weight());
  }

  template<typename T, typename W>
  bool Graph<T, W>::edge_exists(NodeId from, NodeId to) const {
    return find_edge_index(from, to).is_ok();
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::clear_edges(NodeId id) {
    if (!valid_node_id(id)) {
      return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_GRAPH_NODE_ID));
    }
    slots_.unchecked_at(id.index).node.links().clear();
    return Ok();
  }

  template<typename T, typename W>
  void Graph<T, W>::clear_edges() {
    for (usize i = 0; i < slots_.size(); i++) {
      if (slots_.unchecked_at(i).occupied) {
        slots_.unchecked_at(i).node.links().clear();
      }
    }
  }

  template<typename T, typename W>
  Result<usize> Graph<T, W>::find_edge_index(NodeId from, NodeId to) const {
    auto valid = validate_pair(from, to);
    if (!valid) {
      return Err<usize>(valid.error().code(), valid.error().message());
    }
    const auto& links = slots_.unchecked_at(from.index).node.links();
    for (usize i = 0; i < links.size(); i++) {
      if (links.unchecked_at(i).target() == to) {
        return Ok(i);
      }
    }
    return Err<usize>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_GRAPH_EDGE_NOT_FOUND));
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::validate_pair(NodeId from, NodeId to) const {
    if (!valid_node_id(from) || !valid_node_id(to)) {
      return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_GRAPH_NODE_ID));
    }
    return Ok();
  }


  template<typename T>
  class Stack {
  private:
    Array<T> items_;

  public:
    Stack();

    usize size() const;
    bool empty() const;

    Result<void> push(const T& value);
    Result<T> pop();
    Result<T> peek() const;
    Result<T> at(usize index) const;
    void clear();
  };

  template<typename T>
  Stack<T>::Stack() : items_{} {}

  template<typename T>
  usize Stack<T>::size() const {
    return items_.size();
  }

  template<typename T>
  bool Stack<T>::empty() const {
    return items_.empty();
  }

  template<typename T>
  Result<void> Stack<T>::push(const T& value) {
    items_.push_back(value);
    return Ok();
  }

  template<typename T>
  Result<T> Stack<T>::pop() {
    if (empty()) {
      return Err<T>(ErrorCode::EMPTY_CONTAINER, string(strings::ERR_STACK_EMPTY));
    }
    T value = items_.unchecked_at(items_.size() - 1);
    auto result = items_.pop_back();
    if (!result) {
      return Err<T>(result.error().code(), result.error().message());
    }
    return Ok(value);
  }

  template<typename T>
  Result<T> Stack<T>::peek() const {
    if (empty()) {
      return Err<T>(ErrorCode::EMPTY_CONTAINER, string(strings::ERR_STACK_EMPTY));
    }
    return Ok(items_.unchecked_at(items_.size() - 1));
  }

  template<typename T>
  Result<T> Stack<T>::at(usize index) const {
    if (index >= items_.size()) {
      return Err<T>(ErrorCode::OUT_OF_RANGE, string(strings::ERR_STACK_INDEX_RANGE));
    }
    return Ok(items_.unchecked_at(index));
  }

  template<typename T>
  void Stack<T>::clear() {
    items_.clear();
  }


  // How many items the queue can hold — change this to adjust capacity
  constexpr usize MAX_QUEUE_SIZE = 10;


  // A generic circular queue that works with any type T.
  // Items stored in a fixed array — no STL allowed.
  // head_index_ tracks where to start next assignment.
  // Modulo (%) wraps the index back to 0 when it reaches the end.
  template <typename T>
  class CircularQueue {
  private:
    T items_[MAX_QUEUE_SIZE]; // fixed array of items
    usize head_index_;        // index to start from on next assignment
    usize size_;              // how many items are registered

  public:
    // Ctors
    CircularQueue() noexcept
      : head_index_{ 0 },
      size_{ 0 } {
    }

    // Getters
    usize size() const { return size_; }
    bool is_empty() const { return size_ == 0; }
    bool is_full() const { return size_ >= MAX_QUEUE_SIZE; }
    const T& at(usize index) const { return items_[index]; }
    T& at(usize index) { return items_[index]; }
    void clear() {
      head_index_ = 0;
      size_ = 0;
    }

    // Add an item to the queue
    Result<void> enqueue(T item) {
      if (is_full()) {
        return Err<void>(ErrorCode::OUT_OF_RANGE, string(strings::ERR_QUEUE_FULL));
      }
      items_[size_] = item;
      size_++;
      return Ok();
    }

    // Returns a circular index — wraps around using %
    // offset = how many steps ahead from head_index_ to look
    usize circular_index(usize offset) const {
      return (head_index_ + offset) % size_;
    }

    // Move head_index_ to a specific position (wraps with %)
    void set_head(usize index) {
      head_index_ = index % size_;
    }
  };


} // namespace dstr
