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
| General functionality & Order Management | Alex (TP081705) | Queue |
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

### Q1
> What C++ standard should we use?

**Answer:** No restrictions from the lecturer. Group 32 uses C++ 20.

### Q2
> Is it allowed to use JSON files?

**Answer:** Yes, but only for this lecture (L3-ABA).

### Q3
> What about unit tests? Is it allowed or does it count as creativity?

**Answer:** Unit tests are not required and do not give additional marks.

### Q4
> How do we measure memory usage for data structures?

**Answer:** In-code measurements only, using `sizeof()`.

### Q5
> What is meant by "ONLY ONE (1)" prototype on page 5 of the assignment?

**Answer:** The entire group submits one unified C++ program. Each member implements their own module within it.

### Q6
> Are all robot paths required to be the shortest?

**Answer:** *(Pending supervisor clarification)*

### Q7
> What are the geometric characteristics of the robot operating area?

**Answer:** *(Pending supervisor clarification)*

### Q8
> Can the area have obstacles? Should robots treat each other as obstacles?

**Answer:** *(Pending supervisor clarification)*

### Q9
> Having multi-level project structure, should we still submit the files without `.zip`?

**Answer:** *(Pending supervisor clarification)*

### Q10
> "Robot Navigation and Path Tracking Module" requires both Stack (path tracking)
> and Graph (path finding) to be used. Moreover, "Navigation" won't be
> possible without warehouse layout processing. What is the point of
> `Module 5: Warehouse Layout and Navigation Module (Optional)` then?

**Answer:** *(Pending supervisor clarification)*
