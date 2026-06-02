# ``src/common/string_helpers.h``

## Purpose
Project source file.

## Module
``common``

## File Kind
Header file: contains declarations and public API contracts.

## Includes
- ``algorithm``
- ``cctype``
- ``iomanip``
- ``iostream``
- ``sstream``
- ``common/aliases/aliases.h``
- ``common/enums.h``
- ``common/strings/strings.h``

## Namespaces
- ``dstr``

## Types
No class, struct, or enum declarations were detected.

## Fields
No private-style fields with trailing underscore were detected.

## Functions And Methods
- ``inline string trim(const std::string& s) {``
- ``return isspace(static_cast<int>(c));``
- ``inline string pad_right(const string& s, const int width) {``
- ``inline string pad_left(const string& s, const int width) {``
- ``inline string format_float(const float value, const int precision) {``
- ``inline void print_separator(std::ostream& os, const char c, const int width) {``
- ``inline void print_header(std::ostream& os, const string& title) {``
- ``os << string(padding, ' ');``
- ``inline void await_return(std::istream& is) {``
- ``inline string robot_status_string(RobotStatus status) {``
- ``return string(strings::VAL_AVAILABLE);``
- ``return string(strings::VAL_BUSY);``
- ``return string(strings::VAL_MAINTENANCE);``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
