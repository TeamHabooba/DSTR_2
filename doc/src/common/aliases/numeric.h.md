# `src/common/aliases/numeric.h`

## Purpose
Project-wide numeric aliases that replace raw standard integer and size types in project APIs.

## Module
`common/aliases`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- `<cstdint>`
- `<cstddef>`

### Project Files
- (none)

## Namespaces
- `dstr`

## How It Works
Aliases compress standard-library and primitive spellings into project vocabulary. Domain id aliases share the same base type but document intent at API boundaries.

## Types, Structs, Enums, And Aliases
- `alias u8`: Unsigned 8-bit integer alias.
- `alias i16`: Signed 16-bit integer alias.
- `alias u16`: Unsigned 16-bit integer alias.
- `alias i32`: Signed 32-bit integer alias.
- `alias u32`: Unsigned 32-bit integer alias.
- `alias i64`: Signed 64-bit integer alias.
- `alias u64`: Unsigned 64-bit integer alias.
- `alias usize`: Unsigned size/index alias, mapped to size_t and used for counts and array indexes.
- `alias isize`: Signed size/index difference alias, mapped to ptrdiff_t.
- `alias uptr`: Unsigned pointer-sized integer alias.
- `alias iptr`: Signed pointer-sized integer alias.
- `alias f32`: 32-bit floating-point alias.
- `alias f64`: 64-bit floating-point alias.

## Fields
- (none declared in this file)

## Functions And Methods
- (none declared in this file)

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

