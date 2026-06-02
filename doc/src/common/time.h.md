# ``src/common/time.h``

## Purpose
Project source file.

## Module
``common``

## File Kind
Header file: contains declarations and public API contracts.

## Includes
- ``cstdint``
- ``cstring``
- ``string``
- ``ctime``
- ``chrono``
- ``result.h``

## Namespaces
- ``dstr``

## Types
- ``class Time``

## Fields
- ``year_``
- ``month_``
- ``day_``
- ``milliseconds_from_midnight_``
- ``timezone_offset_minutes_``
- ``leap_second_``
- ``is_dst_``
- ``microseconds_``
- ``reserved_``

## Functions And Methods
- ``return Ok(t);``
- ``uint16_t year() const noexcept { return year_; }``
- ``uint8_t month() const noexcept { return month_; }``
- ``uint8_t day() const noexcept { return day_; }``
- ``uint8_t hours() const noexcept { return milliseconds_from_midnight_ / 3600000; }``
- ``uint8_t minutes() const noexcept { return (milliseconds_from_midnight_ % 3600000) / 60000; }``
- ``uint8_t seconds() const noexcept { return (milliseconds_from_midnight_ % 60000) / 1000; }``
- ``uint16_t milliseconds() const noexcept { return milliseconds_from_midnight_ % 1000; }``
- ``uint32_t milliseconds_from_midnight() const noexcept { return milliseconds_from_midnight_; }``
- ``int16_t timezone_offset_minutes() const noexcept { return timezone_offset_minutes_; }``
- ``bool leap_second() const noexcept { return leap_second_ != 0; }``
- ``bool is_dst() const noexcept { return is_dst_ != 0; }``
- ``uint16_t microseconds() const noexcept { return microseconds_; }``
- ``Result<void> year(uint16_t value) noexcept {``
- ``return validate();``
- ``Result<void> month(uint8_t value) noexcept {``
- ``return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_MONTH_RANGE));``
- ``return Ok();``
- ``Result<void> day(uint8_t value) noexcept {``
- ``return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_DAY_RANGE));``
- ``Result<void> hours(uint8_t value) noexcept {``
- ``return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_HOUR_RANGE));``
- ``Result<void> minutes(uint8_t value) noexcept {``
- ``return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_MINUTE_RANGE));``
- ``Result<void> seconds(uint8_t value) noexcept {``
- ``return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_SECOND_RANGE));``
- ``Result<void> milliseconds(uint16_t value) noexcept {``
- ``return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_MILLISECOND_RANGE));``
- ``Result<void> milliseconds_from_midnight(uint32_t value) noexcept {``
- ``return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_MIDNIGHT_RANGE));``
- ``Result<void> timezone_offset_minutes(int16_t value) noexcept {``
- ``return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_TZ_RANGE));``
- ``void leap_second(bool value) noexcept {``
- ``void is_dst(bool value) noexcept {``
- ``Result<void> set_microseconds(uint16_t value) noexcept {``
- ``return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_MICROSECOND_RANGE));``
- ``static bool valid_timezone_offset(int16_t timezone_offset_minutes) noexcept {``
- ``bool has_valid_timezone_offset() const noexcept {``
- ``return valid_timezone_offset(timezone_offset_minutes_);``
- ``Result<void> validate() const noexcept {``
- ``return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_INVALID_MONTH));``
- ``return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_INVALID_DAY));``
- ``return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_INVALID_MILLISECONDS));``
- ``return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_INVALID_TZ));``
- ``return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_INVALID_MICROSECONDS));``
- ``std::string validate_legacy() const {``
- ``return std::string(strings::TXT_EMPTY);``
- ``Result<void> move_to_timezone(int16_t target_timezone_offset_minutes) noexcept {``
- ``return Err(ErrorCode::VALIDATION_FAILED, std::string(strings::ERR_TIME_TARGET_TZ));``
- ``else if (new_millis >= 86400000) {``
- ``static Result<Time> from_tm(const std::tm& tm_info, int16_t tz_offset = 0) noexcept {``
- ``return Ok(result);``
- ``static Result<Time> from_time_t(std::time_t t, int16_t tz_offset = 0) {``
- ``return from_tm(*tm_info, tz_offset);``
- ``std::tm to_tm() const noexcept {``
- ``Result<std::time_t> to_time_t() const noexcept {``
- ``return Ok(time);``
- ``Result<std::chrono::system_clock::time_point> to_system_clock() const {``
- ``return Ok(tp);``
- ``explicit Time(const std::chrono::system_clock::time_point& tp, int16_t tz_offset = 0) {``
- ``void to_bytes(uint8_t* buffer) const noexcept {``
- ``static Result<Time> from_bytes(const uint8_t* buffer) {``
- ``std::string to_string() const {``
- ``return std::string(buffer);``
- ``std::string to_iso8601() const {``
- ``static Result<Time> now() {``
- ``return from_system_clock(t_now);``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
