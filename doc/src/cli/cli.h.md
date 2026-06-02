# ``src/cli/cli.h``

## Purpose
Command-line interface and application state.

## Module
``cli``

## File Kind
Header file: contains declarations and public API contracts.

## Includes
- ``./app_state.h``

## Namespaces
- ``dstr``

## Types
No class, struct, or enum declarations were detected.

## Fields
No private-style fields with trailing underscore were detected.

## Functions And Methods
- ``Result<int> get_option(std::istream& is);``
- ``Result<void> cli_start(char* argv[], int argc, AppState& state);``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
