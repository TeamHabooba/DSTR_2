# Project Requirements
This file contains a proper explanation on what should be implemented and what are the coding rules.
Refere to [code-style.md](./code-style.md) file for a thorough explanation of coding
style convention used for this project.

## Functional
### General
- Split your source code in `.h` (or `.hpp`, `.hxx`, `.h++`) and `.cpp` (or `.cxx`, `.c++`) files.
First must be used for declarations only, second - for implementation.
- Write all your code within the `dstr` namespace.
- Don't use C-style conversions (e.g. `(int)(variable)`) or `std::reinterpret_cast`. Only explicit `std::static_cast` allowed.
- Change only your code. Never rewrite, delete or create files outside of your directory.
If any error occured in those files, please contact responsible team member(s) ASAP.
- Don't create your own `main()` functions. If you want to use one for testing, remove it before opening a pull request.
- Any collection types (`dstr::Array`, `dstr::List`, etc.) must be templates.

### Array
Basic data type: `dstr::Array`  
`dstr::Array` must be implemeted as a single
memory layout containing values of the same data type
with dynamic memory allocation (smart pointers and RAII).  

Experimental data type: `dstr::DynamicArray`  
An additional class `dstr::DynamicArray` must have
internal implementation must be the same as (or at least close to)
`std::vector`.

Refer to
[this](https://medium.com/@simonyihunie/arrays-vs-vectors-in-modern-c-a-detailed-comparison-with-examples-b797fefff7f7) 
or [this](https://stackoverflow.com/questions/6462985/c-stdvector-vs-array-in-the-real-world)
webpage to learn the difference between basic array, `std::array` and `std::vector`).

### List
Basic data type: `dstr::List`  
`dstr::List` must be a singly-linked list. As mentioned above,
use smart pointers and RAII instead of raw pointers.

Experimental data type: `dstr::DoubleList`  
Implement `dstr::DoubleList` class based on double linked list
structure. No raw pointers.

Refer to [this](https://www.geeksforgeeks.org/dsa/types-of-linked-list/)
webpage to learn about the different types of linked lists)

## Non-functional
- All coding style rules explained [here](./code-style.md).
- Join all the meetings. Only very important meetings will be offline.
- Complete all the tasks in time.
- If 2 rules above are not followed by a team member, they will be kicked from the group.
- If you have a reason for absence/deadline failure, mention it in WhatsApp group chat.
