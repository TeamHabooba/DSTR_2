# DSTR 2
Data Structures and Algorithms Assignment Part 2  
(Lab Evaluation Work #2)  
30% of Semester Evaluation  
Group 32

## Contents
- [Team Members](#team-members)
- [Task Division](#task-division)
- [Assignment Question](#assignment-question)
- [Requirements](#requirements)
- [Build](#build)
- [Guidelines for Team Members](#guidelines-for-team-members)
- [Q&A](#q--a)

## Team Members
| Student ID | Name |
|---|---|
| TP081705 | Kurapatkin Aliaksandr |
| TP082557 | Leon Frank Aminiel |
| TP082459 | Mohamed Abdifatah Ali |

## Project Overview

This project implements a **Warehouse Robot Navigation System** for a simulated e-commerce warehouse.
Autonomous robots locate items, pick them from shelves, and deliver them to packing stations.
The system is built around four core data structure concepts: **Stack, Queue, Circular Queue, and Tree**.

### Full System Workflow
1. A new order is received
2. The order is stored and prepared for processing
3. A robot is assigned to the task
4. The system identifies the item location
5. A route is generated for the robot
6. The robot moves step-by-step to the item
7. After completing the task, the robot returns using the reverse path

## Task Division

### Modules

| Module | Assignee | Data Structure(s) |
|---|---|---|
| General functionality & Order Management | Alex (TP081705) | Graph |
| Robot Assignment | Moha (TP082459) | Circular Queue |
| Robot Navigation and Path Tracking | Leo (TP082557) | Stack |

A detailed set of requirements per module is described in [doc/code-reqs.md](doc/code-reqs.md).

### Module Summaries

**Order Management** — Accepts and records incoming customer orders, maintains an ordered list,
processes orders sequentially by arrival time, and removes them once assigned.

**Robot Assignment** — Maintains a list of robots and their statuses, assigns tasks in a continuous
rotating cycle, skips unavailable robots, and tracks assignments per robot.

**Robot Navigation and Path Tracking** — Records each movement step taken by a robot, stores the
full forward path, and enables step-by-step reverse navigation back to the starting point.

## Assignment Question
The full assignment PDF can be opened via [this link](./doc/AssignmentT2.pdf).

## Requirements
All [functional](doc/code-reqs.md#functional) and [non-functional](doc/code-reqs.md#non-functional)
project requirements are documented in [doc/code-reqs.md](doc/code-reqs.md).

Key constraints from the assignment:
- No STL built-in containers (`<list>`, `<vector>`, etc.) — all containers must be self-implemented.
- Each member must use at least one suitable data structure with appropriate algorithms.
- A single C++ prototype is submitted as a group; grading is individual.

## Build

The project uses CMake and C++20. The executable target is `DSTR`.

### Console build with CMake

From the repository root:

```powershell
cmake -S . -B build
cmake --build build
.\build\Debug\DSTR.exe
```

### Build and run with Visual Studio

1. Open Visual Studio.
2. Choose **File -> Open -> Project/Solution** or **File -> Open -> CMake Project**.
3. Go to the repository root directory and select `CMakeLists.txt`.
4. Wait until CMake configuration finishes.
5. Select the `DSTR.exe` target.
6. Press **Ctrl+F5** to run without debugging, or **F5** to run with debugging.

### Sample states

The `data/` directory contains some ready-to-load JSON states:
- `data/default_state.json`
- `data/blocked_route_state.json`
- `data/multi_robot_state.json`

Load them from the CLI through `Save / load files -> Load full state JSON`.

## Submission and Presentation

- **Code submission deadline:** **Wednesday** of Week 14, before 5:00 PM via Moodle.
- **File format:** Submit `.cpp`, `.hpp`, and CSV/text files individually — **no ZIP**.
- **Live presentation:** Scheduled between Week 14 Tuesday and Week 16 Friday (30 min per team, includes Q&A).
- **Missing the live presentation results in 0 marks.**

ZIP naming format (for reference only):  
`<GroupNo>_<leaderID>_<member1ID>_<member2ID>.zip`  
Example: `G32_TP081705_TP082557_TP082459.zip`

## Guidelines for Team Members
> [!TIP]
> If after reading all `.md` guidelines and the [Q&A](#q--a) section you still have questions,
> research in this order:
> 1. ChatGPT / DeepSeek / Grok / Claude *(be aware of potential coding mistakes if not context-pretrained)*
> 2. Perplexity + Google
> 3. YouTube
> 4. Reddit
> 5. StackOverflow *(highly effective if you know how to search; also try GPT with web/search mode pointing to SO)*
> 6. Group Leader

For contribution rules, branching, code style, and other organizational guidelines — see [CONTRIBUTING.md](CONTRIBUTING.md).

### Toolchain / Framework
| Tool | Choice |
|---|---|
| Language standard | C++ 20 |
| Target platform | Windows 10/11 |
| IDE | Any IDE or Text Editor that supports C++ |
| IDE (recommended) | Microsoft Visual Studio Community Edition |
| Build system | CMake |
| Version control | Git + GitHub (no CI pipeline) |
| Timing | `std::chrono` |
| Memory measurement | `sizeof()` operator |
| Unit Testing | Not required |
| Multithreading | Not required |

### Style and Naming Conventions
Google C++ Style with minor project-specific changes.  
Full guidelines: [doc/code-style.md](./doc/code-style.md)

### Documentation
Documentation can be done in either or both of the following ways:
1. Create a `.md` file in the `doc/` directory (no strict formatting required).
2. Write inline comments on each entity: classes, methods, fields, constants.

See [doc/code-style.md#comments](./doc/code-style.md#comments) for what must be mentioned.

## Q & A

All the questions we have that are related to the assignment are specified
in [this file](./doc/assumptions.md).
