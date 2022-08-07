![alt text](https://github.com/HubTou/PyLists4C/blob/main/logo/pylists4c-logo.png "PyLists4C: Python-style lists for the C language")
# PyLists4C: Python-style lists for the C language
Coming back to the [C language](https://www.open-std.org/JTC1/SC22/WG14/www/standards) after 30+ years, and having discovered [Python](https://www.python.org/) in-between, I found it frustrating not having handy tools such as linked lists by default.

Of course, there were multiple libraries available for that, but none with the power of [what's available in Python](https://www.w3schools.com/python/python_lists.asp), or packaged with too many things that I didn't need.

So here's my attempt to fix this, with all I ever wanted from a C language linked list library...

## Features
This library provides [Python-style](https://docs.python.org/3/tutorial/datastructures.html) (within the limits of the C language syntax of course) doubly-linked lists:
* List items are ordered, changeable, and allow duplicate values.
* List items can be of any standard C data type, plus strings, sub-lists and self-contained (= without pointers) structs of variable sizes.
* A list can contain different data types at the same time.

Beyond Python lists emulation, you'll also find:
* conversion from or to arrays
* sorted insertion with optional removal of duplicate values
* list sorting by insertion or qsort (via array conversion)
* list shuffling
* list joining (beyond concatenation or extention)
* statistics and debugging, including memory allocation followup

With:
* 45 base functions + 10 other intuitive aliases,
* 221 convenience type-oriented functions,
* and high modularity so your linker only includes what you use in your own executables.

## Base functions overview
Base function | Aliases | Description
--- | --- | ---
**Creating a list**||
[LIST](DOC.md#list-type)* MyList = NULL;||Creates an empty LIST
listCreateElement()||Creates an unlinked LIST element
list()||Creates a LIST from a Python-style list declaration string
listFromTable()||Converts a C-language table into a LIST
**Adding elements**||
listAppend()|listPush()|Adds an element at the end of a LIST
listInsertFirst()|listPrepend()|Adds an element at the start of a LIST
listInsert(n)||Inserts an element at the Nth position of a LIST
listInsertSorted()||Inserts an element in a sorted LIST
**Getting list information**||
listLen()||Returns the number of elements in a LIST
listStats()||Fills statistics about a LIST
listStatsPrint()||Prints statistics about a LIST
**Fetching elements**||
listGet(n)||Returns the Nth element of a LIST
listGetLast()||Returns the last element of a LIST
listSlice(n, m)<br>listSliceFrom(n)<br>listSliceTo(m)||Returns a copy of a slice (ie. [n:m]) of a LIST
**Testing lists**||
listAreEqual()||Tests if two LISTs contain exactly the same values
listAreEqualCaseInsensitive()||Tests if two LISTs contain the same values, without regard to case
**Searching for elements**||
listContains()||Tests if a value appears in a LIST
listCount()||Returns the number of elements with the specified value
listIndex()||Returns the index of the first element with the specified value
listIndexAll()|listFind()<br>listSearch()|Returns a LIST of all the indexes of the elements with the specified value
**Working with lists**||
listCopy()||Returns a copy of the LIST (a full/deep copy as we don't want multiple references to the same values)
listConcat()||Returns a new LIST with the concatenation of the elements of LIST1 and LIST2
listExtend()||Adds a copy of the elements of the second LIST to the end of the first one
listJoin()|listStitch()|Moves the elements of the second LIST to the end of the first one
**Changing list order**||
listSort()||Sorts a LIST
listSorted()||Returns a sorted copy of a LIST
listSortedByInsertion()||Returns a sorted copy of a LIST, using an insertion sort algorithm
listReverse()||Reverses the order of a LIST
listReversed()||Returns a reversed copy of a LIST
listShuffle()||Shuffles a LIST
listShuffled()||Returns a shuffled copy of a LIST
**Removing elements**||
listPopNth(n)|listDelNth(n)<br>listPopFirst() for n=0<br>listPopLast() for n=-1<br>ListPop() for n=-1|Removes the element at the specified position
listRemove()||Removes the first item with the specified value
listRemoveAll()||Removes all the items with the specified value
**Clearing lists**||
listClear()|listDel()<br>listFree()|Removes all the elements of the LIST
**Working with numerical lists**||
listMaxXXX()||Returns the maximum value in the LIST for the XXX type
listMinXXX()||Returns the minimum value in the LIST for the XXX type
listSumXXX()||Returns the sum of values in the LIST for the XXX type
**Displaying lists**||
listStr()|listAscii()<br>listRepr()|Returns a pointer to a string containing a Python-style (ie. [e1, e2...]) representated LIST (which you'll need to free afterwards using listFreeStr())
listFreeStr()||Frees the memory allocated to a LIST representation
listPrint()||Prints a Python-style (ie. [e1, e2...]) representated LIST
listDebug()||Prints all LIST details to stderr
**Lists to arrays conversion**||
listToArray()||Converts a LIST into an ARRAY
listFromArray()||Converts an ARRAY into a LIST
listFreeArray()||Frees the memory allocated to an ARRAY
**Miscellaneous**||
listGetAllocatedMemory()||Returns the quantity of allocated/unfreed memory used by this library
listSetFatalMallocErrors()||Sets whether memory allocation errors are fatal or not

## Documentation
OK, I'm in! I want to [know everything](DOC.md) about this library!
