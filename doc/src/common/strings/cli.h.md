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
The CLI keeps the AreaLayout visible above menus, reads numbered options, validates input with Result, mutates AppState, then pauses before redraw so output remains visible after screen clearing.

## Types, Structs, Enums, And Aliases
- (none declared in this file)

## Fields
- `NL`: Internal state used by the file API or domain object.

## Functions And Methods
- `SCSTR MSG_INPUT_STATUS = "Status (1 available, 2 busy, 3 maintenance): ";`: Returns stored state directly without extra allocation or ownership transfer.
- `SCSTR MSG_DESC_MEMBERS = "Group members are:\nTP081705 - Kurapatkin Aliaksandr (Alex) (Leader)\nTP082557 - Leon Frank Aminiel (Leo)\nTP082459 - Mohamed Abdif...`: Participates in the file API using project aliases and Result-based control flow where failures are possible.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; this file is part of the centralized strings module.
- Type vocabulary: follows where applicable; this file has little or no typed API surface.

