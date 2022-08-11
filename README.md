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
* list shuffling
* list joining (beyond concatenation or extention)
* heap (push/pop) and queue (enqueue/dequeue) management aliases 
* statistics and debugging, including memory allocation followup

With:
* 46 base functions + 15 other intuitive aliases,
* 234 convenience type-oriented functions,
* high modularity so your linker only includes what you use in your own executables,
* and friendly [BSD license](License), for open and free usage.

## Base functions overview
Base function | Aliases | Description
--- | --- | ---
**Creating a list**||
[LIST](DOC.md#list-type)* MyList = NULL;||Creates an empty LIST
[listCreateElement()](DOC.md#listcreateelement)||Creates an unlinked LIST element
[list()](DOC.md#list)||Creates a LIST from a Python-style list declaration string
[listFromTable()](DOC.md#listfromtable)||Converts a C-language table into a LIST
**Adding elements**||
[listAppend()](DOC.md#listappend)|[listPush()](DOC.md#listpush)<br>[listEnqueue()](DOC.md#listenqueue)|Adds an element at the end of a LIST
[listInsertFirst()](DOC.md#listinsertfirst)|[listPrepend()](DOC.md#listprepend)|Adds an element at the start of a LIST
[listInsert(n)](DOC.md#listinsertn)||Inserts an element at the Nth position of a LIST
[listInsertSorted()](DOC.md#listinsertsorted)||Inserts an element in a sorted LIST
**Displaying lists**||
[listStr()](DOC.md#liststr)|[listAscii()](DOC.md#listascii)<br>[listRepr()](DOC.md#listrepr)|Returns a pointer to a string containing a Python-style (ie. [e1, e2...]) representated LIST<br>(you'll have to free it after use with [listFreeStr()](DOC.md#listfreestr))
[listFreeStr()](DOC.md#listfreestr)||Frees the memory allocated to a LIST representation
[listPrint()](DOC.md#listprint)||Prints a Python-style (ie. [e1, e2...]) representated LIST
[listDebug()](DOC.md#listdebug)||Prints all LIST details to stderr
**Getting list information**||
[listLen()](DOC.md#listlen)||Returns the number of elements in a LIST
[listStats()](DOC.md#liststats)||Fills statistics about a LIST
[listStatsPrint()](DOC.md#liststatsprint)||Prints statistics about a LIST
**Searching for elements**||
[listContains()](DOC.md#listcontains)||Tests if a value appears in a LIST
[listCount()](DOC.md#listcount)||Returns the number of elements with the specified value
[listIndex()](DOC.md#listindex)||Returns the index of the first element with the specified value
[listIndexAll()](DOC.md#listindexall)|[listFind()](DOC.md#listfind)<br>[listSearch()](DOC.md#listsearch)|Returns a LIST of all the indexes of the elements with the specified value
**Working with numerical lists**||
[listMaxXXX()](DOC.md#listmaxxxx)||Returns the maximum value in the LIST for the XXX type
[listMinXXX()](DOC.md#listminxxx)||Returns the minimum value in the LIST for the XXX type
[listSumXXX()](DOC.md#listsumxxx)||Returns the sum of values in the LIST for the XXX type
**Fetching elements**||
[listGet(n)](DOC.md#listgetn)||Returns the Nth element of a LIST (don't free it!)
[listGetLast()](DOC.md#listgetlast)||Returns the last element of a LIST (don't free it!)
[listSlice(n, m)](DOC.md#listslicenm)<br>[listSliceFrom(n)](DOC.md#listslicefromn)<br>[listSliceTo(m)](DOC.md#listslicetom)||Returns a copy of a slice (ie. [n:m]) of a LIST
**Changing elements**||
[listChange(n)](DOC.md#listchangen)|[listModify(n)](DOC.md#listmodifyn)|Changes the value of the element at the Nth position of a LIST
**Testing lists**||
[listAreEqual()](DOC.md#listareequal)||Tests if two LISTs contain exactly the same values
[listAreEqualCaseInsensitive()](DOC.md#listareequalcaseinsensitive)||Tests if two LISTs contain the same values, without regard to case
**Working with lists**||
[listCopy()](DOC.md#listcopy)||Returns a copy of the LIST (a full/deep copy as we don't want multiple references to the same values)
[listConcat()](DOC.md#listconcat)||Returns a new LIST with the concatenation of the elements of LIST1 and LIST2
[listExtend()](DOC.md#listextend)||Adds a copy of the elements of the second LIST to the end of the first one
[listJoin()](DOC.md#listjoin)|[listStitch()](DOC.md#liststitch)|Moves the elements of the second LIST to the end of the first one
**Changing list order**||
[listSort()](DOC.md#listsort)||Sorts a LIST
[listSorted()](DOC.md#listsorted)||Returns a sorted copy of a LIST
[listSortedByInsertion()](DOC.md#listsortedbyinsertion)||Returns a sorted copy of a LIST, using an insertion sort algorithm
[listReverse()](DOC.md#listreverse)||Reverses the order of a LIST
[listReversed()](DOC.md#listreversed)||Returns a reversed copy of a LIST
[listShuffle()](DOC.md#listshuffle)||Shuffles a LIST
[listShuffled()](DOC.md#listshuffled)||Returns a shuffled copy of a LIST
**Lists to arrays conversion**||
[listToArray()](DOC.md#listtoarray)||Converts a LIST into an ARRAY<br>(you'll have to free it after use with [listFreeArray()](DOC.md#listfreearray))
[listFromArray()](DOC.md#listfromarray)||Converts an ARRAY into a LIST
[listFreeArray()](DOC.md#listfreearray)||Frees the memory allocated to an ARRAY
**Removing elements**||
[listDelNth(n)](DOC.md#listdelnthn)|[listDelFirst()](DOC.md#listdelfirst) for n=0<br>[listDelLast()](DOC.md#listdellast) for n=-1|Removes the element at the specified position
[listPopNth(n)](DOC.md#listpopnthn)|[listPopFirst()](doc.md#listpopfirst) for n=0<br>[listDequeue()](DOC.md#listdequeue) for n=0<br>[listPop()](DOC.md#listpop) for n=-1|Removes the element at the specified position and returns it<br>(you'll have to free it after use with [listClear()](DOC.md#listclear))
[listRemove()](DOC.md#listremove)||Removes the first item with the specified value
[listRemoveAll()](DOC.md#listremoveall)||Removes all the items with the specified value
**Clearing lists**||
[listClear()](DOC.md#listclear)|[listDel()](DOC.md#listdel)<br>[listFree()](DOC.md#listfree)|Removes all the elements of the LIST
**Miscellaneous**||
[listGetAllocatedMemory()](DOC.md#listgetallocatedmemory)||Returns the quantity of allocated/unfreed memory used by this library
[listSetFatalMallocErrors()](DOC.md#listsetfatalmallocerrors)||Sets whether memory allocation errors are fatal or not

## Where to go from here?
Interested? Then go to the [documentation](DOC.md) to learn more about this library and find multiple examples.

Still missing something? Then go to the [discussions](https://github.com/HubTou/PyLists4C/discussions) and tell me!

Encountering issues? Then report it in the [issues](https://github.com/HubTou/PyLists4C/issues) section.

Happy with it? Then please help me promote this library.
