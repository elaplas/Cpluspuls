considering that the memory is divided into four segments: data, heap, stack, and code, where do global variables, static variables, constant data types, local variables 
(defined and declared in functions), variables (in main function), pointers, and dynamically allocated space (using malloc and calloc) get stored in memory?



global variables -------> data 
static variables -------> data 
constant data types -----> code and/or data. Consider string literals for a situation when a constant itself would be stored in the data segment, and references to it would be embedded in the code
local variables(declared and defined in functions) --------> stack 
variables declared and defined in main function -----> stack (the teacher was trying to trick you)
pointers(ex: char *arr, int *arr) -------> heap data or stack, depending on the context. C lets you declare a global or a static pointer, in which case the pointer itself would end up in the data segment.
dynamically allocated space(using malloc, calloc, realloc) --------> heap

It is worth mentioning that "stack" is officially called "automatic storage class"

- Code Memory vs. Data Memory


Code memory: 
- It is read-only (some HW architectures allow to modify parts of the program memory)
- Stores the code/program instructions and (parts of code that don't vary like constants)

Data memory: 
- It is read-and-write
- Stores variables and (parts of program that can be modified)
- It consists of stack (for local variables), heap (dynamic allocated memory) and global variables

There are four storage classes in C programming language, which are as follows:
- auto 
  - auto is the default storage class for local variables
  - auto can only be used within functions, i.e. local variables
  - gets defined once it reaches the scope and destructed once it leaves the scope 


- extern
  - Makes a variable visible from once scope to another scope of the code 
  - When you use 'extern' the variable cannot be initialized

- static
  - gets allocated for the lifetime of the program
  - there is only one instance of it even if it is used across multiple objects of a class
  - gets initialized once in the whole lifetime of program if it is defined in a function and the function is called multiple times
  - allocated from the "data memory"

- register
  - temporary variable stored in CPU register
  - have no address/reference
  - faster access time



In general, processor instructions are placed in a segment you will call "code memory". 
This may actually reside in RAM and not in Flash or ROM. For example, on a PC, your code could be loaded from the hard drive into RAM and executed in RAM. 
Similarly with Flash, your code could be loaded from Flash into RAM and executed in RAM.

Constants, like numbers, can be placed into a Read-Only segment or in the Code Segment. 
Many processors can load constants from the Code Segment (see ARM and Intel assembly instructions). 
The Read-Only segment can live on a Read Only device, (ROM or Flash) or may live in RAM (or on a device like hard drive).
 All you can guarantee, is that the code will not write to the Read-Only segment.

Data Memory is different. The C++ language has at least 3 areas of "data" memory (where variables live): 1) Local (a.k.a. stack), 
where short lifetime variables reside; 2) Dynamic memory (a.k.a. heap), allocated by using new or malloc and 3) Automatic/Global variables. 
These memory areas can be placed anywhere, as long as the memory has read and write capabilities. 
They don't need to be fast, only read & write (for example, the hard drive can be used as data memory).

Memory organization is more complicated than having Code, Stack and Heap.
In the embedded systems world, memory can be place in non-standard locations 
and there may be a need to have more detailed memory segments so they can be placed in different areas. 
For example, an embedded system may want to place the constants into Flash so that they can be changed easily
(even though they may be more efficiently accessed in the Code Segment). Some code may want to be placed into the Boot Area of the processor 
(which is programmed by the processor manufacturer). Some embedded systems may have non-volatile memory (e.g. battery backed memory),
which can behave like Read-Only memory.


