# `src/common/math.h`

## Purpose
Small numeric helpers for floating-point equality with relative and absolute tolerance.

## Module
`common`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- `<cmath>`

### Project Files
- (none)

## Namespaces
- `dstr`

## How It Works
The file follows the project pattern of small modules, dstr namespace ownership, project aliases, and explicit Result-returning APIs for fallible behavior.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- `abs_tol`: Internal state used by the file API or domain object.
- `b_abs`: Internal state used by the file API or domain object.

## Functions And Methods
- `double a_abs = std::abs(a);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `double b_abs = std::abs(b);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `float a_abs = std::abs(a);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `float b_abs = std::abs(b);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows where applicable; this file has little or no typed API surface.

