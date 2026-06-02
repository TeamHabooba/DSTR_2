# `src/common/strings/errors.h`

## Purpose
Centralized error message constants used by Result-returning APIs.

## Module
`common/strings`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- (none)

### Project Files
- `"./base.h"`

## Namespaces
- `dstr`

## How It Works
This file contains compile-time string constants only. Other modules include these headers so UI text, domain tokens, and errors stay centralized.

## Types, Structs, Enums, And Aliases
- `class is`: class declared by this module.

## Fields
- (none declared in this file)

## Functions And Methods
- `SCSTR ERR_TRIM_ERROR = "trim() finished with an error.";`: Participates in the file API using project aliases and Result-based control flow where failures are possible.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; this file is part of the centralized strings module.
- Type vocabulary: follows where applicable; this file has little or no typed API surface.

