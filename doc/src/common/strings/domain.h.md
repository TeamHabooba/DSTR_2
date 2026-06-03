# `src/common/strings/domain.h`

## Purpose
Centralized domain and serialization text constants used by layout, files, statuses, and cell symbols.

## Module
`common/strings`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- (none)

### Project Files
- `"base.h"`

## Namespaces
- `dstr`

## How It Works
This file contains compile-time string constants only. Other modules include these headers so UI text, domain tokens, and errors stay centralized.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- `TXT_ARROW`: Shared route separator used when CLI prints path coordinates.
- `CELL_SYM_EMPTY`: Internal state used by the file API or domain object.
- `CELL_SYM_ROBOT`: Internal state used by the file API or domain object.
- `CELL_SYM_OBSTACLE`: Internal state used by the file API or domain object.
- `CELL_SYM_DROP_OFF`: Internal state used by the file API or domain object.
- `CELL_SYM_PICK_UP`: Internal state used by the file API or domain object.
- `CELL_SYM_STATION`: Internal state used by the file API or domain object.
- `CELL_SYM_NONE`: Internal state used by the file API or domain object.
- `CSV_ROBOTS_HEADER`: Internal state used by the file API or domain object.
- `CSV_TASKS_HEADER`: Internal state used by the file API or domain object.
- `CSV_ITEMS_HEADER`: Internal state used by the file API or domain object.
- `JSON_LAYOUT_ROWS`: Internal state used by the file API or domain object.
- `JSON_LAYOUT_COLS`: Internal state used by the file API or domain object.
- `JSON_LAYOUT_CSV`: Internal state used by the file API or domain object.
- `JSON_ROBOTS_CSV`: Internal state used by the file API or domain object.
- `JSON_TASKS_CSV`: Internal state used by the file API or domain object.
- `JSON_ITEMS_CSV`: Internal state used by the file API or domain object.
- `JSON_SECTION_LAYOUT`: Internal state used by the file API or domain object.
- `JSON_SECTION_ROBOTS`: Internal state used by the file API or domain object.
- `JSON_SECTION_TASKS`: Internal state used by the file API or domain object.
- `JSON_SECTION_ITEMS`: Internal state used by the file API or domain object.
- `JSON_OPEN`: Internal state used by the file API or domain object.
- `JSON_LAYOUT_ROWS_LINE`: Internal state used by the file API or domain object.
- `JSON_LAYOUT_COLS_LINE`: Internal state used by the file API or domain object.
- `JSON_LAYOUT_CSV_OPEN`: Internal state used by the file API or domain object.
- `JSON_ROBOTS_CSV_OPEN`: Internal state used by the file API or domain object.
- `JSON_TASKS_CSV_OPEN`: Internal state used by the file API or domain object.
- `JSON_ITEMS_CSV_OPEN`: Internal state used by the file API or domain object.
- `JSON_ARRAY_CLOSE_COMMA`: Internal state used by the file API or domain object.
- `JSON_ARRAY_CLOSE`: Internal state used by the file API or domain object.
- `JSON_CLOSE`: Internal state used by the file API or domain object.
- `ERR_TASK_ITEM_NOT_FOUND`: Domain error used when task creation references an item id absent from the rebuilt inventory index.

## Functions And Methods
- (none; constants only)

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; this file is part of the centralized strings module.
- Type vocabulary: follows where applicable; this file has little or no typed API surface.

