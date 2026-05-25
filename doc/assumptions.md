# Contents
This file contains the specifications, assumptions and questions related to unclear
Assignment Question parts that we've encountered.

It also includes the Q&A section that contains the questions
that were asked directly to the supervisor (lecturer)
via MS Teams platform direct messages or face-to-face communication.

- [Assumptions](#assumptions)
- [Q&A Section](#q--a)

# Assumptions
The assignment contains several open-ended requirements related to robot navigation,
warehouse layout, path generation, obstacles, and submission structure. After asking
the lecturer for clarification, our group was informed that multiple approaches are
acceptable as long as the decisions are logical, well-justified, and properly implemented.

Based on this clarification, Group 32 proceeds with the following assumptions and design
decisions.

## A1
**Warehouse operating area**

The robot operating area is represented as a two-dimensional rectangular grid.

Each grid cell represents one logical warehouse position. The grid does not represent
real-world physical measurements such as metres or centimetres. It is an abstract
simulation model used for pathfinding and movement tracking.

**Justification:** A rectangular grid is simple to represent in C++, easy to convert into
a graph, and suitable for modelling warehouse aisles, shelves, obstacles, robot starting
positions, item pickup locations, and packing stations.

## A2
**Coordinate system**

Warehouse positions are represented using integer coordinates in the form:
```cpp
(row, column)
```
The top-left cell of the warehouse is treated as (0, 0).
Rows increase downward and columns increase to the right.

**Justification:** This is consistent with common two-dimensional array indexing in C++,
which makes implementation easier and reduces the layout ambiguity during testing and presentation.

## A3
**Cell types**

Each warehouse cell may have one of the following logical roles:
- empty path cell;
- obstacle cell;
- item pickup location;
- robot starting position;
- packing station.

A robot may move through empty path cells and may stop at item pickup locations,
robot starting positions, and packing stations. Obstacle cells are blocked and cannot
be entered.

**Justification:** This keeps the simulation transparent and clear while still supporting the
main warehouse navigation scenario.

## A4
**Robot movement rules**

Robots move one and only one cell at a time.
Only four-directional movement is allowed, which icludes:
- up;
- down;
- left;
- right.

Diagonal movement is not allowed.

**Justification:** Four-directional movement is easier to justify in a warehouse
environment because robots normally move along aisles rather than diagonally through
shelves or obstacles. It also keeps the graph representation and path tracking simpler.

## A5
**Graph representation for pathfinding**

The warehouse layout (grid) should be converted into a graph for pathfinding.

Each walkable cell is treated as a graph node. Edges are created between neighbouring
walkable cells if movement between them is allowed.

Obstacle cells are excluded from the graph.

**Justification:** The assignment requires navigation and pathfinding logic. A graph is
a suitable structure for representing possible movement paths in the warehouse.

## A6
**Edge weights and shortest path meaning**

All valid movements between adjacent cells have equal cost.

Therefore, the shortest path means the path with the minimum number of movement steps
between the start position and the destination.

If multiple shortest paths exist, any one valid shortest path is acceptable.

Justification: Equal movement cost is appropriate for a simplified warehouse
prototype. It avoids unnecessary complexity while still demonstrating graph-based
pathfinding.

## A7
**Pathfinding algorithm**

The pathfinding algorithm generates a valid route from the robot's current position to
the target location if such a route exists.

For an unweighted graph (area grid), Breadth-First Search (BFS) may be used to find the
shortest path in terms of number of steps.

If a path cannot be found, the system must report that the destination is unreachable.

Justification: BFS is suitable for shortest-path search in an unweighted graph.
It is also easier to explain and implement within the scope of a data structures and
algorithms assignment.

## A8
**Static obstacles**

The warehouse may contain static obstacles.

Static obstacles represent blocked cells such as walls, restricted areas, unavailable
aisles, or other fixed objects.

Robots cannot move into or through obstacle cells.

Justification: Obstacles make the navigation problem more realistic and demonstrate
that the graph/pathfinding logic can handle unavailable routes.

## A9
**Other robots as dynamic obstacles**

Other robots may be treated as dynamic obstacles during navigation.

In this prototype, the current positions of unavailable or active robots may be treated
as temporarily blocked cells during path generation.

> [!IMPORTANT]
> The system does not implement full real-time multi-robot collision avoidance,
> traffic control, deadlock detection, or time-based route reservation.

**Justification:** Treating other robots as temporary obstacles demonstrates awareness of
multi-robot navigation issues while keeping the implementation within the expected
prototype scope.

## A10
**Stack usage for path tracking**

The stack is used to store the movement path taken by a robot.

Each movement step is pushed onto the stack as the robot moves forward. When the robot
needs to return to its starting point, the stored path can be popped step by step to
simulate reverse navigation.

**Justification:** A stack follows Last-In-First-Out behaviour, which is suitable for
reversing a path. This directly supports the robot path tracking and return-path
requirement.

## A11
**Difference between graph pathfinding and stack path tracking**

The graph is used to calculate or represent possible movement routes in the warehouse.

The stack is used to record the actual path taken by the robot and to support reverse
movement.

Therefore, graph pathfinding and stack path tracking are treated as separate but related
parts of the navigation module.

**Justification:** This avoids confusing the purpose of the two data structures. The graph
helps decide where the robot can go, while the stack records where the robot has already
gone.

## A12
**Return path**

When a robot completes a task, it returns by reversing the path stored in the stack.

Each movement step taken by the robot is pushed onto the stack. During return navigation,
the robot pops the stack step by step and moves back through the previously visited
positions.

Before each return movement, the robot checks whether the next cell is still available.
If the next cell is free, the robot moves to it. If the next cell is temporarily occupied
by another robot, the robot waits and retries the same return step later.

> [!IMPORTANT]
> This prototype does not implement full real-time multi-robot rerouting during return.
> If a return path becomes permanently unavailable because of a static obstacle or changed
> layout, the situation is reported as a blocked return path.

**Justification:** A stack is suitable for reverse path tracking because it follows
Last-In-First-Out behaviour. Dynamic robot obstacles are handled by checking the next
cell before movement, while full real-time multi-robot rerouting is outside the scope of
this data structures and algorithms prototype.

## A13
**Warehouse layout and optional Module 5**

A minimal warehouse layout representation is required for robot navigation because the
system cannot perform pathfinding without knowing the positions of paths, obstacles,
items, robots, and packing stations.

Therefore, Group 32 implements the required warehouse layout functionality as supporting
logic inside the main prototype and navigation workflow.

The optional Warehouse Layout and Navigation Module is interpreted as an extended module
for more advanced layout-related features, not as a reason to omit basic layout handling
from the required navigation system.

**Justification:** Basic layout processing is necessary for graph construction and robot
navigation. Without a layout, the navigation module cannot function correctly.

## A14
**Scope limitation**

This project is a C++ data structures and algorithms prototype, not a real robotics
control system.

The system does ТЩЕ simulate:
- physical robot size;
- acceleration or speed;
- sensor errors;
- battery usage;
- real-time traffic control;
- mechanical movement constraints;
- wireless communication;
- real warehouse safety systems.

**Justification:** These topics are outside the expected scope of the assignment. The
focus of this prototype is the correct use of data structures and algorithms.

## A15
**Deterministic behaviour**

Where multiple valid decisions are possible, the system may use a fixed priority order
to keep the output predictable during testing and presentation.

For example, when several neighbouring cells are equally valid, the program may check
directions in a fixed order such as:
- up;
- right;
- down;
- left.

**Justification:** Deterministic behaviour makes the program easier to test, explain,
debug, and demonstrate during the live presentation.

## A16
**Submission structure**

The project may be developed using a multi-file and multi-folder structure indexed and stored
as a Git repository in GitHub.

For final submission, the group will follow *Moodle* and supervisor (lecturer)
instructions regarding which `.cpp`, `.hpp`, and data files must be uploaded.

If the submission system does not support folders, the group will make sure that the
submitted files can still be compiled and understood according to the instructions
provided in the `README.md`.

**Justification:** A multi-file structure improves development organization, while the
final submitted files must still follow the official submission requirements.

# Q&A

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

**Answer:** refer [this](#q-11052026-13500800).

### Q7
> What are the geometric characteristics of the robot operating area?

**Answer:** refer [this](#q-11052026-13500800).

### Q8
> Can the area have obstacles? Should robots treat each other as obstacles?

**Answer:** refer [this](#q-11052026-13500800).

### Q9
> Having multi-level project structure, should we still submit the files without `.zip`?

**Answer:** refer [this](#q-11052026-13500800).

### Q10
> "Robot Navigation and Path Tracking Module" requires both Stack (path tracking)
> and Graph (path finding) to be used. Moreover, "Navigation" won't be
> possible without warehouse layout processing. What is the point of
> `Module 5: Warehouse Layout and Navigation Module (Optional)` then?

**Answer:** refer to [this](#q-11052026-13500800).

### Q-07052026-19360800
On May 07th, 2026 at 19:36 (UTC+08) one of our team members has
contacted our supervisor (DSTR lecturer) and asked this question:
> `Good evening. JSON files still allowed for Part 2? To store robot, order and warehouse data.`

**Answer:** *(No answer was provided)*

### Q-11052026-13500800
On May 11th, 2026 at 13:50 (UTC+08) one of our team members addressed
a supervisor with a following question:  
> Hello. Just a follow-up for my previous question. In the meanwhile,
> after going through the Part 2 Task, we have the following questions:  
> Are all robot paths required to be the shortest?   
> What are the geometric characteristics of the robot operating area?
Should it be square, rectangle or any other shape?   
> Can the area have obstacles?
Should robots treat each other as obstacles?   
> Having multi-level project structure, should we still submit the files without .zip? How should we do it?   
> "Robot Navigation and Path Tracking Module" requires both Stack (path tracking) and Graph (path finding)
to be used. Moreover, "Navigation" won't be possible without warehouse layout processing.
What is the point of Module 5: Warehouse Layout and Navigation Module (Optional) then?

**Answer** (on May 12th, 2026 at 16:16 (UTC+08)):

> Most of the questions raised are intentionally left open-ended
as part of the project design. The purpose of this assignment is
not only to implement coding solutions, but also to demonstrate
your problem-solving skills, critical thinking skills, and ability
to make appropriate design decisions based on the given scenario.
 
> There may be multiple acceptable approaches as long
as your decisions are logical, well-justified, and properly implemented.
> Please treat this as an opportunity to apply your
understanding rather than expecting every specification to be explicitly predefined.

Based on the answer above, our team have made the design decisions documented in the
[Assumptions](#assumptions) section.
