# `src/common/time.h`

## Purpose
Validated time value type with timezone handling, conversion helpers, byte serialization, and comparison operations.

## Module
`common`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- `<cstdint>`
- `<cstring>`
- `<string>`
- `<ctime>`
- `<chrono>`

### Project Files
- `"result.h"`

## Namespaces
- `dstr`

## How It Works
Time methods validate field ranges before conversion. Timezone movement adjusts milliseconds-from-midnight/day overflow, while chrono/tm conversions bridge to standard library time representations.

## Types, Structs, Enums, And Aliases
- `class Time`: Validated timestamp-like value object with date/time fields, timezone offset, fractional second data, conversion helpers, and serialization methods.

## Fields
- `year_`: Internal state used by the file API or domain object.
- `month_`: Internal state used by the file API or domain object.
- `day_`: Internal state used by the file API or domain object.
- `milliseconds_from_midnight_`: Stores an identifier or graph handle used for stable lookup.
- `timezone_offset_minutes_`: Internal state used by the file API or domain object.
- `leap_second_`: Internal state used by the file API or domain object.
- `is_dst_`: Internal state used by the file API or domain object.
- `microseconds_`: Internal state used by the file API or domain object.
- `reserved_`: Internal state used by the file API or domain object.
- `timezone_offset_minutes`: Internal state used by the file API or domain object.
- `validation`: Stores an identifier or graph handle used for stable lookup.
- `current_minutes`: Internal state used by the file API or domain object.
- `current_seconds`: Internal state used by the file API or domain object.
- `current_millis`: Internal state used by the file API or domain object.
- `current_hours`: Internal state used by the file API or domain object.
- `max_millis`: Internal state used by the file API or domain object.
- `result`: Internal state used by the file API or domain object.
- `diff`: Internal state used by the file API or domain object.
- `new_millis`: Internal state used by the file API or domain object.
- `tm_info`: Internal state used by the file API or domain object.
- `tz_offset`: Internal state used by the file API or domain object.
- `duration_since_epoch`: Internal state used by the file API or domain object.
- `total_micros`: Internal state used by the file API or domain object.
- `micros_in_second`: Internal state used by the file API or domain object.
- `milliseconds_part`: Internal state used by the file API or domain object.
- `microseconds_part`: Internal state used by the file API or domain object.
- `time`: Internal state used by the file API or domain object.
- `millis_result`: Internal state used by the file API or domain object.
- `micros_result`: Internal state used by the file API or domain object.
- `time_t_result`: Internal state used by the file API or domain object.

## Functions And Methods
- `auto validation = t.validate();`: Normalizes or converts time data only after field-range validation succeeds.
- `Time(const Time&) = default;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Time(Time&&) noexcept = default;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Time& operator=(const Time&) = default;`: Implements value comparison or copy/move behavior using the object identity fields defined by the class.
- `Time& operator=(Time&&) noexcept = default;`: Implements value comparison or copy/move behavior using the object identity fields defined by the class.
- `~Time() = default;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `uint32_t current_minutes = (milliseconds_from_midnight_ % 3600000) / 60000;`: Normalizes or converts time data only after field-range validation succeeds.
- `uint32_t current_seconds = (milliseconds_from_midnight_ % 60000) / 1000;`: Normalizes or converts time data only after field-range validation succeeds.
- `uint32_t max_millis = 86400000 + (leap_second_ ? 1000 : 0);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `auto result = validate();`: Normalizes or converts time data only after field-range validation succeeds.
- `int64_t new_millis = static_cast<int64_t>(milliseconds_from_midnight_) + (diff * 60000);`: Normalizes or converts time data only after field-range validation succeeds.
- `milliseconds_from_midnight_ = static_cast<uint32_t>(new_millis);`: Normalizes or converts time data only after field-range validation succeeds.
- `auto validation = result.validate();`: Normalizes or converts time data only after field-range validation succeeds.
- `auto tm_info = std::make_unique<tm>();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `gmtime_s(tm_info.get(), &t);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `tm_info = std::gmtime(&t);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `tm_info.tm_hour = hours();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `tm_info.tm_min = minutes();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `tm_info.tm_sec = seconds();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `auto validation = validate();`: Normalizes or converts time data only after field-range validation succeeds.
- `std::tm tm_info = to_tm();`: Normalizes or converts time data only after field-range validation succeeds.
- `std::time_t result = _mkgmtime(&tm_info);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `std::time_t result = timegm(&tm_info);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `std::time_t t = std::chrono::system_clock::to_time_t(tp);`: Normalizes or converts time data only after field-range validation succeeds.
- `auto duration_since_epoch = tp.time_since_epoch();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `auto total_micros = std::chrono::duration_cast<std::chrono::microseconds>(duration_since_epoch).count();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `uint16_t milliseconds_part = static_cast<uint16_t>(micros_in_second / 1000);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `auto result = from_time_t(t, tz_offset);`: Normalizes or converts time data only after field-range validation succeeds.
- `Time time = result.value();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `auto millis_result = time.milliseconds(milliseconds_part);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `auto micros_result = time.set_microseconds(microseconds_part);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `auto time_t_result = to_time_t();`: Normalizes or converts time data only after field-range validation succeeds.
- `time_t_result.error().message());`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `auto tp = std::chrono::system_clock::from_time_t(time_t_result.value());`: Normalizes or converts time data only after field-range validation succeeds.
- `tp += std::chrono::milliseconds(milliseconds());`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `tp += std::chrono::microseconds(microseconds());`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `auto result = from_system_clock(tp, tz_offset);`: Normalizes or converts time data only after field-range validation succeeds.
- `*this = result.value();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `*this = Time();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `std::memcpy(buffer, this, sizeof(Time));`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `std::memcpy(&t, buffer, sizeof(Time));`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `is_dst() ? strings::TXT_DST.data() : strings::TXT_EMPTY.data());`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `static_cast<unsigned>(std::abs(timezone_offset_minutes_ % 60)));`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `auto t_now = std::chrono::system_clock::now();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

