# Project Requirements

This file contains a full explanation of what must be implemented and the applicable coding rules.
For coding style conventions, refer to [code-style.md](./code-style.md).

---

## Functional

### General
All modules must work together as one complete system following the workflow:
1. A new order is received.
2. The order is stored and prepared for processing.
3. A robot is assigned to the task.
4. The system identifies the item location.
5. A route is generated for the robot.
6. The robot moves step-by-step to the item.
7. After completing the task, the robot returns using the reverse path.

### Common
- Implementation must be located in the `src/common` directory.
- Must contain a `common.h` file for fast bulk `#include`.
- Must contain a `strings/` subdirectory with a `strings.h` file for fast bulk `#include`.

---

### Order Management Module
> Assignee: Alex (TP081705) — Suggested data structure: **Queue**

**Functional requirements:**
- Accept and record new customer orders into the system.
- Maintain an ordered list of all incoming requests.
- Process orders sequentially according to their arrival time (FIFO).
- Remove orders from the list once they are assigned to a robot.
- Display current pending and completed orders.
- Handle edge cases such as empty order lists or system overload.

**Key features:**
- Fair, sequential order processing.
- Real-time order status updates.
- Continuous support for new incoming orders.

**Expected outputs:**
- List of pending orders.
- List of completed/assigned orders.
- Status display per order.

---

### Robot Assignment Module
> Assignee: Moha (TP082459) — Suggested data structure: **Circular Queue**

**Functional requirements:**
- Maintain a list of all robots and their current status (available / busy / under maintenance).
- Assign tasks to robots in a continuous rotating cycle.
- Skip robots that are currently unavailable or under maintenance.
- Track task assignment history per robot.
- Ensure uninterrupted task allocation without restarting the assignment cycle.

**Key features:**
- Balanced workload distribution among all robots.
- Continuous and automated assignment process.
- Real-time robot availability tracking.

**Expected outputs:**
- Robot assignment list.
- Current robot handling each task.
- Robot status overview.

---

### Robot Navigation and Path Tracking Module
> Assignee: Leo (TP082557) — Suggested data structure: **Stack**

**Functional requirements:**
- Record each movement step taken by the robot (e.g., forward, left, right).
- Store the full path from starting point to destination.
- Allow the robot to reverse its path step-by-step after completing a task.
- Handle navigation issues such as obstacles or incorrect paths (backtracking).
- Simulate robot movement through logs or step-by-step visualization.

**Key features:**
- Accurate path tracking and movement recording.
- Reverse navigation capability for return journeys.
- Basic obstacle handling through backtracking.

**Expected outputs:**
- Forward movement path.
- Reverse path for returning.
- Complete navigation log.

> [!NOTE]
> Wait for the [Question 10](../README.md#q10) of Q&A section to be answered before implementing
> any other data structure than Stack.

---

### Item Search and Management Module *(Optional)*
> Would be assigned to a 4th team member if present.

**Functional requirements:**
- Store item details: Item ID, name, location.
- Insert new items into the system.
- Search for items by specific criteria (e.g., ID or name).
- Update or delete item records when necessary.
- Display items in a structured, sorted format.

**Key features:**
- Fast and efficient item lookup.
- Organized storage of item information.
- Easy management of item records.

**Expected outputs:**
- Search results for requested items.
- Updated item database.
- Organized item listing.

---

### Warehouse Layout and Navigation Module *(Optional)*
> Would be assigned to a 5th team member if present.

**Functional requirements:**
- Model the warehouse layout into structured sections (zones, aisles, shelves).
- Define connections between different locations.
- Provide navigation routes from one point to another.
- Support traversal through all warehouse sections.
- Integrate with the Robot Navigation module for path planning.

**Key features:**
- Structured representation of the warehouse layout.
- Efficient route generation.
- Scalable design for large warehouse environments.

**Expected outputs:**
- Visual or textual representation of the warehouse layout.
- Path between selected locations.
- Traversal results.

---

## Non-functional

### Code Structure
- Split source code into `.h` (or `.hpp`, `.hxx`, `.h++`) and `.cpp` (or `.cxx`, `.c++`) files.
  - Header files: declarations only.
  - Source files: implementation only.
- Write all code within the `dstr` namespace.
- Any collection types (`dstr::Array`, `dstr::List`, etc.) must be **templates**.
- Do not use STL built-in containers (`<list>`, `<vector>`, etc.) — all containers must be self-implemented.
  - Reference: [GeeksForGeeks — STL Containers](https://www.geeksforgeeks.org/containers-cpp-stl/)

### Casting and Type Safety
- Do not use C-style casts (e.g., `(int)(variable)`) or `std::reinterpret_cast`.
- Only explicit `std::static_cast` is permitted.

### File and Scope Discipline
- Only modify files within your own assigned directory.
- Never rewrite, delete, or create files outside your directory.
- If an error is found in another member's files, contact the responsible member immediately.
- Do not create your own `main()` functions. If needed for testing, remove it before opening a pull request.

### Coding Style
- Follow all rules defined in [code-style.md](./code-style.md).

### Team Conduct
> [!NOTE]
> This is a brief version. See [CONTRIBUTING.md](CONTRIBUTING.md) for proper explanation.
- Attend all meetings. Only critical meetings will be held offline.
- Complete all tasks on time.
- Failure to follow the two rules above may result in removal from the group.
- If you have a reason for absence or deadline failure, notify the team in the WhatsApp group chat in advance.
