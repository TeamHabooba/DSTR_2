# `src/common/string_helpers.h`

## Purpose
Inline text and display helpers for trimming input, formatting separators, centered titles, pauses, and enum display strings.

## Module
`common`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- `<algorithm>`
- `<cctype>`
- `<iomanip>`
- `<iostream>`
- `<sstream>`

### Project Files
- `<common/aliases/aliases.h>`
- `<common/enums.h>`
- `<common/strings/strings.h>`

## Namespaces
- `dstr`

## How It Works
The file follows the project pattern of small modules, dstr namespace ownership, project aliases, and explicit Result-returning APIs for fallible behavior.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- `TABLE_WIDTH`: Internal state used by the file API or domain object.
- `COL_IDX`: Internal state used by the file API or domain object.
- `COL_ID`: Internal state used by the file API or domain object.
- `COL_CITY`: Internal state used by the file API or domain object.
- `COL_AGE`: Internal state used by the file API or domain object.
- `COL_TRANSPORT`: Internal state used by the file API or domain object.
- `COL_DIST`: Internal state used by the file API or domain object.
- `COL_FACTOR`: Internal state used by the file API or domain object.
- `COL_DAYS`: Internal state used by the file API or domain object.
- `COL_EMISSION`: Internal state used by the file API or domain object.
- `start`: Internal state used by the file API or domain object.
- `end`: Internal state used by the file API or domain object.
- `size`: Tracks the number of currently active elements.
- `oss`: Internal state used by the file API or domain object.
- `padding`: Internal state used by the file API or domain object.
- `dummy`: Internal state used by the file API or domain object.

## Functions And Methods
- `).base();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `int size = static_cast<int>(s.size());`: Returns stored state directly without extra allocation or ownership transfer.
- `oss << std::fixed << std::setprecision(precision) << value;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `os << string(width, c) << '\n';`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `print_separator(os, '=', TABLE_WIDTH);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `int padding = (TABLE_WIDTH - static_cast<int>(title.size())) / 2;`: Returns stored state directly without extra allocation or ownership transfer.
- `os << string(padding, ' ');`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `getline(is, dummy);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

