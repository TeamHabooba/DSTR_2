# Contributing to DSTR 2

This file consolidates all organizational and workflow guidelines for Group 32.
Every team member is expected to read and follow this document before making any contribution.

---

## Table of Contents
- [Team Contacts](#team-contacts)
- [Directory Structure](#directory-structure)
- [Git Workflow](#git-workflow)
- [Pull Request Rules](#pull-request-rules)
- [Code Ownership](#code-ownership)
- [Meetings](#meetings)
- [Deadlines](#deadlines)
- [AI Usage Policy](#ai-usage-policy)
- [Grading Overview](#grading-overview)

---

## Team Contacts

| Role | Name | Student ID |
|---|---|---|
| Group Leader | Kurapatkin Aliaksandr | TP081705 |
| Member | Leon Frank Aminiel | TP082557 |
| Member | Mohamed Abdifatah Ali | TP082459 |

For urgent matters, use the WhatsApp group chat.
For code-related issues, open a GitHub issue or message the responsible member directly.

---

## Directory Structure

```
src/
├── common/           # Shared utilities — maintained by Alex
│   ├── common.h
│   └── strings/
│       └── strings.h
├── order_management/ # Alex (TP081705)
├── robot_assignment/ # Moha (TP082459)
└── robot_navigation/ # Leo (TP082557)

doc/
├── AssignmentT2.pdf
├── code-reqs.md
└── code-style.md
```

> [!IMPORTANT]
> Each member works **only** within their own directory.
> Do not create, edit, or delete files outside your assigned directory.
> If you find a bug in another member's code, report it to them directly — do not fix it yourself.

---

## Git Workflow

### Branches
- `main` — stable, submission-ready code only. Direct pushes are prohibited.
- `<your-name>` — your personal working branch.

**Example branch names:**
```
alex
moha
leo
```

### Commit Messages
Follow this format:
```
[module] Short imperative description

Optional longer body if needed.
```

**Examples:**
```
[order] Add enqueue logic for incoming orders
[robot] Fix skip logic for unavailable robots
[nav] Implement stack-based path reversal
[common] Add StringList utility to strings.h
```

- Use present tense: "Add feature" not "Added feature".
- Keep the first line under 72 characters.
- Reference issue numbers where relevant: `Fixes #12`.

---

## Pull Request Rules

1. **Never push directly to `main`.** Always open a Pull Request (PR).
2. Before opening a PR, make sure your code compiles cleanly with no warnings.
3. Remove any temporary `main()` functions before submitting a PR.
4. PR title must follow the same format as commit messages.
5. A team leader must review and approve before merging to `main`.
6. Describe what your PR does and any known limitations in the PR description.

---

## Code Ownership

| Directory / File | Owner | Contact if broken |
|---|---|---|
| `src/common/` | Alex (TP081705) | Alex |
| `src/order_management/` | Alex (TP081705) | Alex |
| `src/robot_assignment/` | Moha (TP082459) | Moha |
| `src/robot_navigation/` | Leo (TP082557) | Leo |
| `CMakeLists.txt` | Alex (TP081705) | Alex |
| `doc/` | All (read-only for members) | Alex |

If an error originates in a file that is not yours, **contact the owner ASAP** instead of modifying it.

---

## Meetings

- Attendance at all meetings is **mandatory**.
- Only critically important meetings will be held offline; routine syncs are online.
- If you cannot attend, notify the WhatsApp group **before** the meeting, not after.
- Unexplained absences count against your standing in the group.

---

## Deadlines

| Milestone | Date |
|---|---|
| Code submission to Moodle deadline | Wednesday of Week 14, 5:00 PM |
| Live presentation window | Week 14 Tuesday — Week 16 Friday |

**Submission format:**
- Upload `.cpp`, `.hpp`, and CSV/text files **individually** to Moodle.
- Do **not** upload a ZIP folder.

**ZIP naming** (keep for local archiving or if ZIP is allowed later):
```
G32_TP081705_TP082557_TP082459.zip
```

> [!WARNING]
> Missing the live presentation automatically results in **0 marks** for Lab Evaluation Work #2.

## Grading Overview

Total: **30 marks** (individual, within a group submission).

| Component | Marks | What is assessed |
|---|---|---|
| Problem-solving & implementation | 15 | Data structure choice, feature correctness, code quality, creativity |
| Q&A and justification | 15 | Ability to explain and justify design decisions, relevance to requirements |

Key grading factors:
- Correct and justified choice of data structure for your module.
- Code readability, meaningful names, comments, and indentation.
- Quality of individual contribution relative to team goals.
- Clarity and effectiveness during the live demonstration.
