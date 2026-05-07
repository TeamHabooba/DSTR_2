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
- #### TP081705
> Kurapatkin Aliaksandr  
- #### TP082557  
> Leon Frank Aminiel
- #### TP082459
> Mohamed Abdifatah Ali

## Requirements
All [functional](doc/code-reqs.md#functional) and [non-functional](doc/code-reqs.md#non-functional)
project requirements are mentioned in [doc/code-reqs.md](doc/code-reqs.md) file.

## Task Division

### Assignees
*General* functionality and *Order Management* - [Alex](#tp081705)  
*Robot Assignment Module* Implementation -  [Moha](#tp082459)   
*Robot Navigation and Path Tracking* Implementation - [Leo](#tp082557)   

*No Task Assigned* -  *---*

## Assignment Question
All the parts of this project are created following the initial assignment question.
The exact PDF document may be opened with [this link](./doc/AssignmentT2.pdf) 

## Guidelines for Team Members
> [!TIP]
> If it appears that after reading all the `.md` guidelines and [Q&A Section](#q--a) you
still have any questions, please follow this order to make
a research on the topic:
> 1. ChatGPT/DeepSeek/Grok/Claude
(Be aware of coding mistakes if not context-pretrained)
> 2. Perplexity + Google 
> 3. YouTube
> 4. Reddit
> 5. StackOverflow
(Actually the best one if u know how to find what you need.
So you can try it even before any GPT.
Or set GPT to "search"/"web" and ask it
to give the references from this website.)
> 6. Group Leader

### Toolchain/Framework
- For this assignment Group 32 is using C++ 20 standard.  
- Target platform: Windows 10/11.  
- Any IDE would be okay, yet Microsoft Visual Studio (Not Visual Studio Code) is recommended.
You don't have to use Enterprise (or any paid) edition.
Community Edition is enough for this assignment.  
- CMake is used as a building system.  
- Git + GitHub basic toolchain (without CI pipeline) would be used
for version control.   
- No building speed requirements.  
- Execution speed / time might be measured with standard `std::chrono` tools. No profiling toolchain required.  
- Memory usage might be measured with `sizeof()` operator.
- Multithreading implementation is not required.

### Style and Naming Conventions
We are using the C++ Google coding style with some minor changes.
The exact guidelines and coding style requirements can be found [here](./doc/code-style.md).

### Documentation
Documentation might be implemented in 2 ways:
1. Create your own `.md` file in `doc` directory. No formatting required.
2. Write comments on each entity: classes, methods, fields, constants.

You can pick one or do both.  
Check [this](./doc/code-style.md#comments) to understand what exactly do you need to mention in documentation.

## Q & A
Here would be stated all the unclear requirements and all other questions related to this assignment. Together with supervisor's answers.

### Q1
What C++ standard should we use?

#### Answer
There are no restrictions. So we will use C++ 20.

### Q2
Is it allowed to use JSON files?

#### Answer
Yes, but only for this lecture (L3-ABA).

### Q3
What about the unit tests? Is it allowed or redundant? Does it count as creativity?

#### Answer
It doesn't give additional marks and it isn't required.

### Q4
How do we measure the memory usage for the data structures?
Do we use profiling tools or just `sizeof()` operator?
If someone is coding with Visual Studio Code, what profiling tools should they use?

#### Answer
Only in-code measurements.

### Q5
What is meant by point #3 on the page 5 of assignment question:
**"ONLY ONE (1)"** prototype in this section?
We are not allowed to implement more than one component per member?

#### Answer
-

### Q6
Are all the robot pathes required to be the shortest?
Or the only requirement is for them to be correct?

#### Answer
-

### Q7
Robots are required to operate within a designated area.
What are the geometric characteristics of this area?

#### Answer
-

### Q8
Can area have obsticles? Should robots consider each other as obsticles?

#### Answer
-
