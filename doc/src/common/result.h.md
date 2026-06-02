# `src/common/result.h`

## Purpose
Project Result/Error type used to propagate failures without throwing exceptions.

## Module
`common`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- `<string>`
- `<variant>`
- `<utility>`

### Project Files
- `<common/strings/strings.h>`

## Namespaces
- `dstr`

## How It Works
Result stores either a value or Error in a variant; Result<void> stores only an optional error. Ok/Err helpers build the correct specialization and keep call sites compact.

## Types, Structs, Enums, And Aliases
- `enum class ErrorCode`: enum class declared by this module.
- `class Error`: Small error payload carrying an ErrorCode and a user-facing message from the project strings module.
- `class Result`: Discriminated success/error wrapper. It replaces exception throwing at API boundaries and forces callers to check success before reading values.

## Fields
- `code_`: Internal state used by the file API or domain object.
- `message_`: Internal state used by the file API or domain object.
- `error_`: Internal state used by the file API or domain object.

## Functions And Methods
- `Result(const Result&) = default;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result(Result&&) noexcept = default;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result& operator=(const Result&) = default;`: Implements value comparison or copy/move behavior using the object identity fields defined by the class.
- `Result& operator=(Result&&) noexcept = default;`: Implements value comparison or copy/move behavior using the object identity fields defined by the class.
- `~Result() = default;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `error_ = Error();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `error_ = parametrised.error();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

