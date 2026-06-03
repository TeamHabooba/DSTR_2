# `src/common/strings/cli.h`

## Purpose
Centralized CLI text constants: menu labels, prompts, user manual text, credits, and display messages.

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
This file contains compile-time CLI text constants only. The CLI includes these constants for all visible menu labels, prompts, execution controls, guide text, and credits so user-facing text stays centralized outside implementation logic.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- `NL`: Shared newline token for CLI output.
- `MSG_TASK_OPTION_1` / `MSG_TASK_OPTION_4`: Task menu labels updated for item-id task creation and assigned-task execution.
- `MSG_INPUT_EXECUTE_TASK`: Prompt used before starting an execution session for an assigned task.
- `MSG_TASK_PICKUP_FROM_ITEM`: Result text showing that pickup was derived from the item's storage location.
- `MSG_EXEC_*`: Execution menu labels, checkpoint names, path/stack headings, step messages, completion/cancellation messages, and blocked-exit warning.
- `MSG_GUIDE_2`: User manual task section updated to describe step-by-step execution with path tracking.

## Functions And Methods
- (none; constants only)

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; this file is part of the centralized strings module.
- Type vocabulary: follows where applicable; this file has little or no typed API surface.

