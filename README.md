![alt text](https://github.com/HubTou/PyLists4C/blob/main/logo/pylists4c-logo.png "PyLists4C: Python-style lists for the C language")
# PyLists4C: Python-style lists for the C language
Coming back to the [C language](https://www.open-std.org/JTC1/SC22/WG14/www/standards) after 30+ years, and having discovered [Python](https://www.python.org/) in-between, I found it frustrating not having handy tools such as linked lists by default.

Of course, there were multiple libraries available for that, but none with the power of [what's available in Python](https://www.w3schools.com/python/python_lists.asp), or packaged with too many things that I didn't need.

So here's my attempt to fix this, with all I ever wanted from a C language linked list library...

## Features
This library provides [Python-style](https://docs.python.org/3/tutorial/datastructures.html) doubly-linked lists:
* List items are ordered, changeable, and allow duplicate values.
* List items can be of any standard C data type, plus strings, sub-lists and self-contained (= without pointers) structs of variable sizes.
* A list can contain different data types at the same time.

Beyond Python lists emulation (within the limits of the C language syntax of course), you'll also find:
* conversion from or to arrays
* sorted insertion with optional removal of duplicate values
* list sorting by insertion or qsort (via array conversion)
* list shuffling
* list joining (beyond concatenation or extention)
* statistics and debugging, including memory allocation followup

With:
* 49 base functions + 9 other intuitive aliases,
* 221 convenience type-oriented functions,
* with high modularity so your linker only includes what you use in your own executables.

## Documentation
Ongoing...
