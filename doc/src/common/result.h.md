# ``src/common/result.h``

## Purpose
Project source file.

## Module
``common``

## File Kind
Header file: contains declarations and public API contracts.

## Includes
- ``string``
- ``variant``
- ``utility``
- ``common/strings/strings.h``

## Namespaces
- ``dstr``

## Types
- ``enum class ErrorCode``
- ``class Error``
- ``class Result``

## Fields
- ``code_``
- ``message_``
- ``error_``

## Functions And Methods
- ``constexpr ErrorCode code() const noexcept { return code_; }``
- ``const std::string& message() const noexcept { return message_; }``
- ``constexpr bool is_ok() const noexcept { return code_ == ErrorCode::OK; }``
- ``bool is_ok() const noexcept {``
- ``bool is_error() const noexcept {``
- ``explicit operator bool() const noexcept {``
- ``return is_ok();``
- ``const Error& error() const noexcept {``
- ``Result<T> Ok(T value) {``
- ``inline Result<void> Ok() {``
- ``Result<T> Err(ErrorCode code, std::string message) {``
- ``inline Result<void> Err(ErrorCode code, std::string message) {``
- ``Result<T> Err() {``
- ``inline Result<void> Err() {``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
