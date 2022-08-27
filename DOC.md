![alt text](https://github.com/HubTou/PyLists4C/blob/main/logo/pylists4c-logo.png "PyLists4C: Python-style lists for the C language")
# PyLists4C: Python-style lists for the C language
(Way more than) all you ever wanted to know about this library in one printable page!

## Installation
:construction: TODO

## Use within your own programs
If the library has been installed system-wide, you just have to:
* include the library header in your programs:
```C
#include <pylists4c.h>
```
* link the library with the rest of your objects. For example, if you're working on a Unix-like system, put something like this in your **makefile**:
```C
LDFLAGS=-lpylists4c
$(CC) $(CFLAGS) $LDFLAGS) $(MY_OBJECTS_FILES) -o $(MY_PROGRAM_NAME)
```

If you have only installed the library in your user account, you have to add:
* -I$(HOME)/include in the CFLAGS definition
* -L$(HOME)/lib in the LDFLAGS definition

# Data structures
## Glossary and conventions
* A **LIST** is an instance of linked list this library provides.
* An **element** is a node of a LIST.
* A **value** is the payload of an element of a LIST.
  * The values that you pass to the library's functions are never used directly and always copied before insertion into a LIST (we don't want dependencies with what's going on outside of the library).
  * The copies are also never re-used into other LISTs (as we don't want multiple references to an allocated variable either).
* An **index** is the position of an element in a LIST.
  * Like in Python, indexes are numbered from 0 when you go through a LIST from its beginning, or from -1 when you go through its end.
  * LISTs indexes, lengths and counts are of the C language **long** type. 
* An **homogeneous** LIST is a special kind of LIST where all values are of the same type.
* Pointers variable names are prefixed with a **p** character. Pointers to pointers with **pp** and so on.
  * Thus a ppList parameter means that you'll pass the address of your LIST, enabling the modification of the first element pointer or its NULL-ification if the LIST is emptied. 

## Specific types
### LIST type
The main data structure of this library is defined like this:
```C
// Double-linked variable content linked list cell:
typedef struct list
{
    void* pValue;

    ETYPE type;
    size_t size;

    struct list* pPrevious;
    struct list* pNext;
} LIST;
```
Design notes:
* In order to mix different types of *values* in a same LIST, we need a **type** variable to keep track of the kind of *value* a peculiar *element* will carry.
* As we want to use some custom types beyond standard C language types, we introduce the [ETYPE](DOC.md#etype-type) type to be able to use:
  * [STRING](DOC.md#string-type)s (C language \0 terminated character arrays),
  * sub-LISTs,
  * and user defined, self contained (that is to say, without pointers) STRUCTs.
* As the size of user defined STRUCTs is unknown (and furthermore can be of variable size inside a same LIST) and STRINGS can be allocated to larger character arrays than their current content, we also need a **size** variable to keep track of the space allocated to store the *value*.
  * If you use multiple kinds of STRUCTs in the same LIST, it is advised to start each of these STRUCTs with a fixed length field indicating its sub type.
* As all *elements* should have the same memory size, we use pointers for all *values*, not just STRINGs, LISTs and STRUCTS. Thus we need a **pValue** variable to point to the *value* of each *element*.

### ELEMENT type
An alias for a pointer to a LIST, defined like this:
```C
typedef LIST* ELEMENT;
```
Design notes:
* It's main use is to differenciate functions that return a whole LIST that would need to be freed after use, from those that return an ELEMENT of a LIST that must not be freed).
* The use of a variable-like name is meant to discourage the idea of freeing it, though as it's still a pointer its members will have to be accessed with "->" rather than "."...
* In order to obtain the *value* carried by an ELEMENT, you'll either have to:
  * cast its pointer to a void to a pointer of a known type, and then take its value before use.<br>For example, assuming you want to retrieve a "short" value, do:
```C
*((short*) element -> pValue)
```
  * or, more simply, use a [listValueXXX()](DOC.md#listvaluexxx) "getter" for the type you expect.<br>To continue the previous example, do:
```C
listValueShort(element)
```
  * The types available for XXX are: Char, UChar, Short, UShort, Int, UInt, Long, ULong, LongLong, ULongLong, Float, Double, LongDouble and String (with the U prefix standing for Unsigned).
  
### ITERATOR type
An alias for a pointer to a LIST, defined like this:
```C
typedef LIST* ITERATOR;
```
Design notes:
* It's main use is to walkthrough a LIST without restarting from its first element at each iteration.
* Like the ELEMENT type, it's also used to differenciate LISTs that would need to be freed after use, from pointers to walkthrough a LIST, that must not be freed.

Example use:
```C
LIST* pList = NULL;
ITERATOR i;
ELEMENT e;

// pList defined somewhere...

i = listSetIterator(pList);
while ((e = listNext(&i)) != NULL)
    /* do something */ ;
...
listClear(&pList);
```

### ETYPE type
It's defined like this:
```C
// Element TYPEs:
typedef enum
{
    ETYPE_UNDEFINED = -1,
    // Empty elements:
    ETYPE_NULL = 0, // Not implemented
    ETYPE_CHAR = 1,
    ETYPE_U_CHAR = 2,
    ETYPE_SHORT = 3,
    ETYPE_U_SHORT = 4,
    ETYPE_INT = 5,
    ETYPE_U_INT = 6,
    ETYPE_LONG = 7,
    ETYPE_U_LONG = 8,
    ETYPE_LONG_LONG = 9,
    ETYPE_U_LONG_LONG = 10,
    ETYPE_FLOAT = 21,
    ETYPE_DOUBLE = 22,
    ETYPE_LONG_DOUBLE = 23,
    // C-style strings (i.e.: \0 terminated character array):
    ETYPE_STRING = 31,
    // Homogeneous ARRAYs:
    ETYPE_ARRAY = 32, // Not implemented
    // Sub-LISTs:
    ETYPE_LIST = 33,
    // Python-style dictionaries for C:
    ETYPE_DICT = 34, // Not implemented
    // Self-contained structures without pointers:
    ETYPE_STRUCT = 35
} ETYPE;
```
Design notes:
* ETYPE_UNDEFINED is meant for internal use.
* The following types are placeholders for possible future extensions:
  * ETYPE_NULL for empty elements (I haven't found a use case for this yet),
  * ETYPE_ARRAY for our [ARRAYs](DOC.md#array-type) as we have defined them anyway (though the same functionalities could be achieved through sub-LISTs),
  * ETYPE_DICT for a possible complementary library of [Python-style dictionaries](https://www.w3schools.com/python/python_dictionaries.asp).

We provide convenience functions for each standard C language types, so you don't always have to pass *values* by address, provide the *type* and *size* parameters, or cast variables to specific types...

### ARRAY type
One thing we can't easily do in C language is to have directly indexed LIST *elements* (i.e.: MyList\[0], MyList\[1] and so on), though we provide a [listGet()](DOC.md#listgetn) base function to access the Nth *element* of a LIST.

In order to make this easier, we provide the [listToArray()](DOC.md#listtoarray) and [listFromArray()](DOC.md#listfromarray) base functions in order to convert between LISTs and ARRAYs.
These functions, however, only work on *homogeneous LISTs*.

An ARRAY is defined like this:
```C
// Generic self-contained array (for LIST from/to ARRAY conversions):
typedef struct array
{
    ETYPE type;
    size_t size;

    long length;

    union
    {
        void* pGeneric;
        char* pChar;
        unsigned char* pUChar;
        short* pShort;
        unsigned short* pUShort;
        int* pInt;
        unsigned int* pUInt;
        long* pLong;
        unsigned long* pULong;
        long long* pLongLong;
        unsigned long long* pULongLong;
        float* pFloat;
        double* pDouble;
        long double* pLongDouble;
        char** ppString;
        LIST** ppList;
        void** ppStruct;
    } u;
} ARRAY;
```
Design notes:
* An ARRAY has only one **type** and **size**, so it has *homogeneous values*.
* The number of *values* is given by the **length** variable.
* In order to be able to use the \[n] notation directly, we provide an union **u** with all possible subtypes.
  * We could have used the same scheme for the LIST data structure **pValue** variable but thought it would needlessly complexify things... 
* Every standard C language type is a pointer to (i.e.: a table of) that type.
* Being of unknown size to the C language, our custom types are pointers to pointers so their table indexation will work.

### LIST_STATS type
The [listStats()](DOC.md#liststats) function provides a way to collect several information in one LIST walkthrough.

It fills a data structure defined like this:
```C
// List statistics:
typedef struct
{
    long length; // Same as listLen() result

    long charCount;
    long uCharCount;
    long shortCount;
    long uShortCount;
    long intCount;
    long uIntCount;
    long longCount;
    long uLongCount;
    long longLongCount;
    long uLongLongCount;
    long floatCount;
    long doubleCount;
    long longDoubleCount;
    long stringCount;
    long listCount;
    long structCount;
    long unknownCount;

    unsigned long smallestString; // Without the \0 terminating character
    unsigned long largestString; // Without the \0 terminating character
    unsigned long smallestStruct;
    unsigned long largestStruct;

    long shortestList; // Number of elements at first level
    long longestList; // Number of elements at first level

    BOOLEAN isHomogeneous;
    ETYPE homogeneousType;
    size_t homogeneousSize; // STRUCTs could be of different sizes...

    LIST* pLastElement; // Same as listGetLast() result

    unsigned long memoryUsed; // Including eventual subLISTs
} LIST_STATS;
```

## Generic types
### BOOLEAN type
Just a simple boolean type, defined like this:
```C
#ifndef BOOLEAN_TYPE
#define BOOLEAN_TYPE
typedef enum
{
    FALSE = 0,
    TRUE = 1
} BOOLEAN;
#endif // BOOLEAN_TYPE
```
Design notes:
* Pragma protected as it may be defined elsewhere...

### STRING type
Just a simple C language string (\0 terminated character array), defined like this:
```C
#ifndef STRING_TYPE
#define STRING_TYPE
typedef char* STRING;
#endif // STRING_TYPE
```
Design notes:
* Introduced in order to make function prototypes more readable and avoid the "p" prefix for character arrays...
* Pragma protected as it may be defined elsewhere...

### STATUS type
Standard exit/return codes, defined like this:
```C
#ifndef STATUS_TYPE
#define STATUS_TYPE
typedef enum
{
    SUCCESS = 0,
    FAILURE = 1
} STATUS;
#endif // STATUS_TYPE
```
Design notes:
* Can be used both as an exit code for reporting errors to the shell (if you use [listSetFatalMallocErrors(TRUE)](DOC.md#listSetFatalMallocErrors)) or as a return code to your program calling function.
* Pragma protected as it may be defined elsewhere...

# Functions available
## Creating a list
### LIST declaration
Creates an empty list.

Example use:
```C
LIST* pList = NULL;
```
:no_entry: LISTs should only be allocated through the library's functions, so **never use LIST variables directly** (i.e.: LIST myList) or you won't be able to have empty LISTs, to change the first *element* easily or to clear your LISTs... 

### listCreateElement()
Creates an unlinked LIST element
```C
extern LIST* listCreateElement(void* pValue, ETYPE type, size_t size);
```
Used by all the functions adding elements to a LIST (it bears almost all the memory allocation stuff), this one is rather intended for internal use.

Example use, though you'd better just [listAppend()](DOC.md#listappend) your first value:
```C
long aLongValue = 42;
LIST* pList = listCreateElement(&aLongValue, ETYPE_LONG, sizeof(long));
// pList now is [42]
...
listClear(&pList);
// pList now is NULL
```

### list()
Creates a LIST from a Python-style list declaration string
```C
extern LIST* list(STRING string);
```
That's the LIST constructor for easy initilization of LISTs.

A LIST declaration string is a comma-separated list of:
* integer numbers (\[-]\[0-9]+) => converted to C language **long** type
* decimal numbers (\[-]\[0-9]+\\.\[0-9]+) => converted to C language **double** type
* strings ('.\*' or ".\*" with eventual embedded single or double quotes characters backslash-escaped) => converted to this library **STRING** type
* lists ([.\*]) => converted to this library **LIST** type
* All the rest is treated as garbage => converted to this library *empty* **STRING** type (so you can notice there was something wrong)

Please note:
* The decimal separator is a point, not a comma,
* You can have as many nested LISTs as you want,
* You can declare empty STRINGs or LISTs.

:construction: Exponents are not yet supported for decimal numbers.

:construction: There's currently no way to insert CHAR, SHORT, INT, LONG_LONG, UNSIGNED_\*, FLOAT and LONG_DOUBLE values in a LIST declaration strings.

:construction: Consequently, there's currently no way either to declare STRUCTs (we'll use simple braces for them). 

:warning: Contrarily to what Python does, you don't have to enclose your list declaration string in braces (for once, this is a Python syntax limitation!).

You don't have to enclose them in brackets either because that would be like saying you're already manipulating a LIST (and, indeed, you would create a single element LIST).

Example use:
```C
pList = list("123, 456.789, -987, 'abc', \"def\", garbage, ['r', 2, 'd', 2]");
// pList now is [123, 456.789, -987, 'abc', 'def', '', ['r', 2, 'd', 2]]
...
listClear(&pList);
```

### listFromTable()
Converts a C language table into a LIST
```C
extern LIST* listFromTable(void* pTable, ETYPE type, size_t size, long length); // listFromArray() wrapper
```
* *pTable* is just your 1 dimensional array pointer.
* *length* is the number of elements in your array.

Example use:
```C
long anArrayOfLongs[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 9};
long length = 9;
LIST* pList = listFromTable(anArrayOfLongs, ETYPE_LONG, sizeof(long), length);
// pList now is [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 9]
...
listClear(&pList);
```

## Adding & changing elements
### listAppend()
### listPush()
### listEnqueue()
Adds an element at the end of a LIST
```C
extern STATUS listAppend(LIST** ppList, void* pValue, ETYPE type, size_t size);
extern STATUS listPush(LIST** ppList, void* pValue, ETYPE type, size_t size); // listAppend() alias
extern STATUS listEnqueue(LIST** ppList, void* pValue, ETYPE type, size_t size); // listAppend() alias
```
* *ppList* is the address of your LIST pointer as the first element will change if your LIST was empty.

In case of FAILURE return code (which can only happen in case of memory allocation error), the existing LIST is unaffected.
If you don't want to test the result of each STATUS returning function call, you can use the [listSetFatalMallocErrors(TRUE)](DOC.md#listSetFatalMallocErrors) function at the start of your program to make it exit on any memory allocation error (anyway it'll be difficult to continue if there is no more memory available...)
 

Example use:
```C
LIST* pAstronauts = NULL;
static char* lastManOnTheMoon = "Gene Cernan";
long year = 1972;
...
listAppend(&pAstronauts, lastManOnTheMoon, ETYPE_STRING, strlen(lastManOnTheMoon) + 1);
// pAstronauts now is ['Gene Cernan']
listAppend(&pAstronauts, &year, ETYPE_LONG, sizeof(long));
// pAstronauts now is ['Gene Cernan', 1972]

// or, more simply:
// listAppendString(&pAstronauts, "Gene Cernan");
// listAppendLong(&pAstronauts, 1972);
...
listClear(&pAstronauts);
```

### listInsertFirst()
### listPrepend()
Adds an element at the start of a LIST
```C
extern STATUS listInsertFirst(LIST** ppList, void* pValue, ETYPE type, size_t size);
extern STATUS listPrepend(LIST** ppList, void* pValue, ETYPE type, size_t size); // listInsertFirst() alias
```
* *ppList* is the address of your LIST pointer as the first element will, by design, always change!

In case of FAILURE return code, the LIST is unaffected.

Example use:

```C
LIST* pAstronauts = list("'Gene Cernan', 1972");
static char* firstManOnTheMoon = "Neil Armstrong";
long year = 1969;
...
listInsertFirst(&pAstronauts, &year, ETYPE_LONG, sizeof(long));
// pAstronauts now is [1969, 'Gene Cernan', 1972]
listInsertFirst(&pAstronauts, firstManOnTheMoon, ETYPE_STRING, strlen(firstManOnTheMoon) + 1);
// pAstronauts now is ['Neil Armstrong', 1969, 'Gene Cernan', 1972]

// or, more simply:
// listInsertFirstLong(&pAstronauts, 1969);
// listInsertFirstString(&pAstronauts, "Neil Armstrong");
...
listClear(&pAstronauts);
```

### listInsert(n)
Inserts an element at the Nth position of a LIST
```C
extern STATUS listInsert(LIST** ppList, long n, void* pValue, ETYPE type, size_t size);
```
If *n* is greater than the LIST length, your element will be appended at the end of the LIST.

Example use:
```C
LIST* pList = list("2, 4, 6, 8");
long v = 5;
listInsert(&pList, 2, &v, ETYPE_LONG, sizeof(v));
// pList now is [2, 4, 5, 6, 8]

// or, more simply:
// listInsertLong(&pList, 2, 5);
```

### listInsertSorted()
Inserts an element in a sorted LIST
```C
extern STATUS listInsertSorted(LIST** ppList, void* pValue, ETYPE type, size_t size, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
```
* *reversed* is a BOOLEAN indicating the sort order (TRUE=descending, FALSE=ascending)
* *caseInsensitive* is a BOOLEAN specifying how to handle char and STRINgs (TRUE=case insensitive, FALSE=case sensitive)
* *noDuplicates* is a BOOLEAN indicating if duplicate values are discarded (TRUE=discarded, FALSE=inserted)

:warning: Assumes the LIST is already sorted or impredictible results will occur!

:warning: Contrarily to what Python does, it's possible to sort non *homogeneous* LISTs. In these cases, values will be grouped by ETYPE (in ascending [ETYPE value order](DOC.md#etype-type)).

:warning: STRUCTs sorting is crude by default (done with [memcmp()](https://www.freebsd.org/cgi/man.cgi?query=memcmp)...) but it can be improved by supplying your own comparison function with [listSetStructComparator()](DOC.md#listsetstructcomparator).

:warning: sub-LISTs are not sorted between themselves (*before* and *after* being hard to define...) but they are still added to the resulting LIST as we don't want to lose any element.

Example use:
```C
LIST* pList = list("2, 4, 6, 8");
long v = 5;
listInsertSorted(&pList, &v, ETYPE_LONG, sizeof(v), FALSE, FALSE, FALSE);
// pList now is [2, 4, 5, 6, 8]

// or, more simply:
// listInsertSortedLong(&pList, 5, FALSE, FALSE, FALSE);
```

### listChange(n)
Changes the value of the element at the Nth position of a LIST
```C
extern STATUS listChange(LIST* pList, long n, void* pValue, ETYPE type, size_t size);
extern STATUS listModify(LIST* pList, long n, void* pValue, ETYPE type, size_t size); // listChange() alias
```
In case of FAILURE return code (which can happen either if *n* is greater than the LIST length or in case of memory allocation error), the LIST is unaffected.

Else, only the *pValue* pointer is deallocated / reallocated.

```C
LIST* pFabFour = list("'john', 'paul', 'george', 'pete'");
static char* fourthMember = "ringo";

listChange(pFabFour, 3, fourthMember, ETYPE_STRING, strlen(fourthMember) + 1);
// pFabFour now is ['john', 'paul', 'george', 'ringo']

// or, more simply:
// listChangeString(pFabFour, 3, "ringo");
...
listClear(&pFabFour);
```

## Displaying lists
### listStr()
### listAscii()
### listRepr()
Returns a pointer to a string containing a [Python-style representated LIST](DOC.md#list) (you'll have to free it after use with [listFreeStr()](DOC.md#listfreestr)
```C
extern STRING listStr(LIST* pList);
extern STRING listAscii(LIST* pList); // listStr() alias
extern STRING listRepr(LIST* pList); // listStr() alias
```
:warning: By default, STRUCTs stringing is minimalist (we only string their address) but you can supply your own printing function with [listSetStructStringer()](DOC.md#listsetstructstringer).

:construction: Single quotes characters are not backslash-escaped (yet).

Example use:
```C
LIST* pList = list("'Yesterday', 'all', 'my', 'troubles', 'seemed', 'so', 'far', 'away'");
STRING printableString = listStr(pList);
// printableString now is "['Yesterday', 'all', 'my', 'troubles', 'seemed', 'so', 'far', 'away']"
...
listFreeStr(&printableString);
listClear(&pList);
```

### listFreeStr()
Frees the memory allocated to a LIST representation
```C
extern void listFreeStr(STRING*); // NB: passing the previous STRING by address to reset it
```
The STRING pointer is resetted to NULL after use.

Example use provided just above...

### listPrint()
Prints a [Python-style representated LIST](DOC.md#list) to stdout
```C
extern void listPrint(LIST* pList);
```
:warning: By default, STRUCTs printing is minimalist (we only print their address) but you can supply your own printing function with [listSetStructPrinter()](DOC.md#listsetstructprinter).

:construction: Single quotes characters are not backslash-escaped (yet).

Example use:
```C
LIST* pList = list("'Now', 'it', 'looks', 'as', 'though', 'they\'re', 'here', 'to', 'stay'");
listPrint(pList);
// "['Now', 'it', 'looks', 'as', 'though', 'they're', 'here', 'to', 'stay']" is printed to stdout
...
listClear(&pList);
```

### listDebug()
Prints all LIST details to stderr
```C
extern void listDebug(LIST* pList, STRING name);
```
* *name* is an optional STRING (you can pass NULL instead) containing the name of your LIST variable.

:warning: By default, STRUCTs debugging is minimalist (we only print their address) but you can supply your own debugging function with [listSetStructDebugger()](DOC.md#listsetstructdebugger).

Example use:
```C
LIST* pList = list("123, 456.789, 'abc', \"def\", ['r', 2, 'd', 2], []");
listDebug(pList, "pList");
// or, if you don't want to use your variable name in prints:
// listDebug(pList, NULL);
...
listClear(&pList);
```

Which would result in the following stderr display:
```
pList[0] = address: @0x800a0a000 / contents: @0x0 <-- 123 (long, 8 bytes) --> @0x800a0a030
pList[1] = address: @0x800a0a030 / contents: @0x800a0a000 <-- 456.789000 (double, 8 bytes) --> @0x800a0a060
pList[2] = address: @0x800a0a060 / contents: @0x800a0a030 <-- 'abc' (STRING, 4 bytes) --> @0x800a0a090
pList[3] = address: @0x800a0a090 / contents: @0x800a0a060 <-- 'def' (STRING, 4 bytes) --> @0x800a0a180
pList[4] = address: @0x800a0a180 / contents: @0x800a0a090 <-- see below (LIST*, 8 bytes) --> @0x800a0a150
pList[4][0] = address: @0x800a0a1b0 / contents: @0x0 <-- 'r' (STRING, 2 bytes) --> @0x800a0a1e0
pList[4][1] = address: @0x800a0a1e0 / contents: @0x800a0a1b0 <-- 2 (long, 8 bytes) --> @0x800a0a210
pList[4][2] = address: @0x800a0a210 / contents: @0x800a0a1e0 <-- 'd' (STRING, 2 bytes) --> @0x800a0a240
pList[4][3] = address: @0x800a0a240 / contents: @0x800a0a210 <-- 2 (long, 8 bytes) --> @0x0
pList[5] = address: @0x800a0a150 / contents: @0x800a0a180 <-- [] (LIST*, 8 bytes) --> @0x0
```

## Getting list information
### listLen()
Returns the number of elements in a LIST
```C
extern long listLen(LIST* pList);
```
Example use:
```C
LIST* pList = list("1, 2, 3");
long length = listLen(pList);
// length now is 3
...
listClear(&pList);
```

### listStats()
Fills statistics about a LIST in one walkthrough
```C
extern void listStats(LIST* pList, LIST_STATS* pStats);
```
Aside from providing unique information about a LIST (*homogeneous* status and details, memory footprint, etc.), this function main virtue is to do it in one walkthrough.

For once, the LIST_STATS variable doesn't need to be dynamically allocated. You can simply declare it as a variable.

Example use:
```C
LIST* pList = list("123, 456.789, 'abc', \"def\", ['r', 2, 'd', 2], []");
LIST_STATS stats;
listStats(pList, &stats);
listStatsPrint(stats, "pList");
...
listClear(&pList);
```

Which would result in the following stdout display:
```
pList:
  length=6
    longCount=1
    doubleCount=1
    stringCount=2
      smallestString=3 + 1
      largestString=3 + 1
    listCount=2
      shortestList=0
      longestList=4
  isHomogeneous=FALSE
  pLastElement=@0x800a0a150
  memoryUsed=460
```

### listStatsPrint()
Prints statistics about a LIST to stdout
```C
extern void listStatsPrint(LIST_STATS stats, STRING name);
```
* *name* is an optional STRING (you can pass NULL instead to get the default "list:") containing the name of your LIST variable.

Example use provided just above...

As you can see, only the relevant fields are displayed.

## Searching for elements
### listContains()
Tests if a value appears in a LIST
```C
extern BOOLEAN listContains(LIST* pList, void* pValue, ETYPE type, size_t size);
```
:warning: The value tested has to be of the same type, and for STRUCTs to be of the same size (i.e.: an int value of 2 is different from a long value of 2).

Example use:
```C
LIST* pPrimeNumbers = list("1, 2, 3, 5, 7, 11, 13, 17, 19");
long number = 14;

if (listContains(pPrimeNumbers, &number, ETYPE_LONG, sizeof(number)))
    printf("%ld is a prime number\n", number);
else
    printf("%ld is NOT a prime number\n", number);
// "14 is NOT a prime number\n" is printed to stdout
    
// or, more simply:
// if (listContainsLong(pPrimeNumbers, number))
...
listClear(&pPrimeNumbers);
```

### listCount()
Returns the number of elements with the specified value
```C
extern long listCount(LIST* pList, void* pValue, ETYPE type, size_t size);
```
Example use:
```C
LIST* pFruits = list("'apple', 'banana', 'mango', 'pear', 'banana'");
static char* fruit = "banana";
long count = listCount(pFruits, fruit, ETYPE_STRING, sizeof(fruit));
// count now is 2

// or, more simply:
// long count = listCountString(pFruits, "banana");
...
listClear(&pFruits);
```

### listIndex()
Returns the index of the first element with the specified value
```C
extern long listIndex(LIST* pList, void* pValue, ETYPE type, size_t size);
```
Or returns -1 if the element is not found.

Example use:
```C
LIST* pFruits = list("'apple', 'banana', 'mango', 'pear', 'banana'");
static char* fruit = "banana";
long i = listIndex(pFruits, fruit, ETYPE_STRING, sizeof(fruit));
// i now is 1
if (i >= 0)
    printf("%s found at index %ld\n", fruit, i);
// "banana found at index 1\n" is printed to stdout

// or, more simply:
// long i = listIndexString(pFruits, "banana");
...
listClear(&pFruits);
```

### listIndexAll()
### listFind()
### listSearch()
Returns a LIST of all the indexes of the elements with the specified value
```C
extern LIST* listIndexAll(LIST* pList, void* pValue, ETYPE type, size_t size);
extern LIST* listFind(LIST* pList, void* pValue, ETYPE type, size_t size); // listIndexAll() alias
extern LIST* listSearch(LIST* pList, void* pValue, ETYPE type, size_t size); // listIndexAll() alias
```

Example use:
```C
LIST* pFruits = list("'apple', 'banana', 'mango', 'pear', 'banana'");
static char* fruit = "banana";
LIST* pIndexes = listIndexAll(pFruits, fruit, ETYPE_STRING, sizeof(fruit));
// pIndexes now is [1, 4]
if (listLen(pIndexes) >= 0)
{
    printf("%s found at indexes ", fruit);
    listPrint(pIndexes);
}
// "banana found at indexes [1, 4]\n" is printed to stdout

// or, more simply:
// LIST* pIndexes = listIndexAllString(pFruits, "banana");
...
listClear(&pFruits);
listClear(&pIndexes);
```

## Working with numerical lists
### listMinXXX()
Returns the minimum value in the LIST for the XXX type
```C
extern char listMinChar(LIST* pList);
extern unsigned char listMinUChar(LIST* pList);
extern short listMinShort(LIST* pList);
extern unsigned short listMinUShort(LIST* pList);
extern int listMinInt(LIST* pList);
extern unsigned int listMinUInt(LIST* pList);
extern long listMinLong(LIST* pList);
extern unsigned long listMinULong(LIST* pList);
extern long long listMinLongLong(LIST* pList);
extern unsigned long long listMinULongLong(LIST* pList);
extern float listMinFloat(LIST* pList);
extern double listMinDouble(LIST* pList);
extern long double listMinLongDouble(LIST* pList);
```
If pList is NULL or if the LIST contains no elements of the requested ETYPE, the value returned will be meaningless (it will be the maximum one for the requested type).

Example use:
```C
LIST* pNumbers = list("128, 64, 32, 16, 8, 4, 2, 1");
long min = listMinLong(pList);
// min now is 1
...
listClear(&pNumbers);
```

### listMaxXXX()
Returns the maximum value in the LIST for the XXX type
```C
extern char listMaxChar(LIST* pList);
extern unsigned char listMaxUChar(LIST* pList);
extern short listMaxShort(LIST* pList);
extern unsigned short listMaxUShort(LIST* pList);
extern int listMaxInt(LIST* pList);
extern unsigned int listMaxUInt(LIST* pList);
extern long listMaxLong(LIST* pList);
extern unsigned long listMaxULong(LIST* pList);
extern long long listMaxLongLong(LIST* pList);
extern unsigned long long listMaxULongLong(LIST* pList);
extern float listMaxFloat(LIST* pList);
extern double listMaxDouble(LIST* pList);
extern long double listMaxLongDouble(LIST* pList);
```
If pList is NULL or if the LIST contains no elements of the requested ETYPE, the value returned will be meaningless (it will be the minimum one for the requested type).

Example use:
```C
LIST* pNumbers = list("128, 64, 32, 16, 8, 4, 2, 1");
long max = listMaxLong(pList);
// max now is 128
...
listClear(&pNumbers);
```

### listSumXXX()
Returns the sum of values in the LIST for the XXX type
```C
extern long listSumChar(LIST* pList);
extern unsigned long listSumUChar(LIST* pList);
extern long listSumShort(LIST* pList);
extern unsigned long listSumUShort(LIST* pList);
extern long listSumInt(LIST* pList);
extern unsigned long listSumUInt(LIST* pList);
extern long long listSumLong(LIST* pList);
extern unsigned long long listSumULong(LIST* pList);
extern long long listSumLongLong(LIST* pList);
extern unsigned long long listSumULongLong(LIST* pList);
extern double listSumFloat(LIST* pList);
extern long double listSumDouble(LIST* pList);
extern long double listSumLongDouble(LIST* pList);
```
:warning: There is no warning in cases of sum overflow, or precision losses.

Example use:
```C
LIST* pNumbers = list("128, 64, 32, 16, 8, 4, 2, 1");
long long sum = listSumLong(pList);
// sum now is 255
...
listClear(&pNumbers);
```

## Fetching elements
:no_entry: ELEMENTs and ITERATORs must never be freed or you'll disrupt the LIST they belong to!

:warning: Of course, beware of using ELEMENTS or ITERATORs if you have destroyed the underlying LIST element!

### listGet(n)
Returns the Nth ELEMENT of a LIST
```C
extern ELEMENT listGet(LIST* pList, long n);
```
*n* can be a positive or negative index.

NULL will be returned if the index requested is out of the LIST.

Otherwise the requested ELEMENT will be returned.

:no_entry: ELEMENTs must never be freed or you'll disrupt the LIST they belong to!

Example use:
```C
LIST* pList = list("'a', 'b', 'c'");
printf("%ld\n", listValueString(listGet(1)));
// "b\n" is printed to stdout
printf("%ld\n", listValueString(listGet(-2)));
// "b\n" is also printed to stdout
```

### listGetLast()
Returns the last ELEMENT of a LIST
```C
extern ELEMENT listGetLast(LIST* pList);
```
Equivalent to listGet(-1) though optimized as it's frequently used.

:no_entry: ELEMENTs must never be freed or you'll disrupt the LIST they belong to!

Example use:
```C
LIST* pList = list("'a', 'b', 'c'");
printf("%ld\n", listValueString(listGetLast()));
// "c\n" is printed to stdout
```

### listSetIterator()
Defines an ITERATOR from an ELEMENT of a LIST
```C
extern ITERATOR listSetIterator(ELEMENT element);
```
This function is really only here for the sake of readability, as you could, just as simply, affect a LIST* or ELEMENT variable to an ITERATOR...

:no_entry: ITERATORs must never be freed or you'll disrupt the LIST they belong to!

Example use:
```C
LIST* pList = list("1, 2, 3, 4, 5");
ITERATOR i = listSetIterator(pList);

// or, more simply:
// ITERATOR i = pList;
...
listClear(&pList);
```

### listNext()
Returns the next ELEMENT of a LIST starting from an ITERATOR
```C
extern ELEMENT listNext(ITERATOR* pIterator);
```
The main purpose of this function is to avoid making a walkthrough of your LIST each time you want to reach a new element.

The function will return NULL when there are no more elements to get.

:no_entry: ELEMENTs must never be freed or you'll disrupt the LIST they belong to!

Example use:
```C
LIST* pList = list("1, 2, 3, 4, 5");
ITERATOR i = listSetIterator(pList);
ELEMENT e;

while ((e = listNext(&i)) != NULL)
    /* do something with e */ ;
...
listClear(&pList);
```

### listPrevious()
Returns the previous ELEMENT of a LIST starting from an ITERATOR
```C
extern ELEMENT listPrevious(ITERATOR* pIterator);
```
The main purpose of this function is to avoid making a walkthrough of your LIST each time you want to reach a new element.

The function will return NULL when there are no more elements to get.

:no_entry: ELEMENTs must never be freed or you'll disrupt the LIST they belong to!

Example use:
```C
LIST* pList = list("1, 2, 3, 4, 5");
ITERATOR i = listSetIterator(getLast(pList)); // starting from the end of the LIST
ELEMENT e;

while ((e = listPrevious(&i)) != NULL)
    /* do something with e */ ;
...
listClear(&pList);
```

# Fetching elements values
### listValueXXX()
Returns the element value in the requested type
```C
extern char listValueChar(ELEMENT element);
extern unsigned char listValueUChar(ELEMENT element);
extern short listValueShort(ELEMENT element);
extern unsigned short listValueUShort(ELEMENT element);
extern int listValueInt(ELEMENT element);
extern unsigned int listValueUInt(ELEMENT element);
extern long listValueLong(ELEMENT element);
extern unsigned long listValueULong(ELEMENT element);
extern long long listValueLongLong(ELEMENT element);
extern unsigned long long listValueULongLong(ELEMENT element);
extern float listValueFloat(ELEMENT element);
extern double listValueDouble(ELEMENT element);
extern long double listValueLongDouble(ELEMENT element);
extern STRING listValueString(ELEMENT element);
```
Meant for use with the [listGet(n)](DOC.md#listgetn), [listGetlast()](DOC.md#listgetlast), [listNext()](DOC.md#listnext) and [listPrevious()](DOC.md#listprevious) functions if you want something fancier than pointer casting + value getting, and you know the types of the ELEMENTs in the LIST...

Example use:
```C
LIST* pList = list("1, 2, 3, 4, 5");
ITERATOR i;
ELEMENT e;

i = listSetIterator(pList);
while ((e = listNext(&i)) != NULL)
    printf("%ld\n", listValueLong(e));
// "1\n", "2\n", "3\n", "4\n" and "5\n" are printed to stdout
...
listClear(&pList);
```

## Testing lists
### listAreEqual()
Tests if two LISTs contain exactly the same values
```C
extern BOOLEAN listAreEqual(LIST* pList1, LIST* pList2);
```
:warning: "exactly the same values" means having the same value *and* the same type *and* the same allocated size!

Example use:
```C
LIST* pList1 = list("1, 2, 3");
LIST* pList2 = list("1, 2, 3, 4");

if (listAreEqual(pList1, pList2))
    printf("The lists are equal!\n");
else
    printf("The lists are NOT equal!\n");
// "The lists are NOT equal!\n" is printed to stdout
...
listClear(&pList1);
listClear(&pList2);
```

### listAreEqualCaseInsensitive()
Tests if two LISTs contain the same values, without regard to case
```C
extern BOOLEAN listAreEqualCaseInsensitive(LIST* pList1, LIST* pList2);
```
It's the same as above, but the CHAR, U_CHAR and STRING ETYPEs are compared without regard to case.

## Working with lists
### listCopy()
Returns a copy of the LIST (a full/deep copy as we don't want multiple references to the same values)
```C
extern LIST* listCopy(LIST* pList);
```
Example use;
```C
LIST* pList1 = list("1, 2, 3");
LIST* pList2 = NULL;

pList2 = listCopy(pList1);
// pList2 (and pList1) now is [1, 2, 3]
...
listClear(&pList1);
listClear(&pList2);
```

### listSlice(n, m)
### listSliceFrom(n)
### listSliceTo(m)
Returns a copy of a slice (i.e.: [n:m]) of a LIST
```C
extern LIST* listSlice(LIST* pList, long n, long m);
extern LIST* listSliceFrom(LIST* pList, long n);
extern LIST* listSliceTo(LIST* pList, long m);
```
*n* and *m* can be a positive or negative indexes (but *n* must be inferior or equal to *m*).

Depending on what you use, *n* and *m* values will go either from 0 to the length of your LIST, or -length to -1.

*n* is included in the results, but *m* is not.

You'll get a **copy** of a part of your LIST, so you'll have to free it after use.

Example uses:
```C
LIST* pList = list("0, 1, 2, 3, 4, 5, 6, 7, 8, 9");
LIST* pSlice = NULL;

pSlice = listSlice(pList, 1, 9); // same as Python pList[1:9]
// pSlice now is [1, 2, 3, 4, 5, 6, 7, 8]
listClear(&pSlice);

pSlice = listSliceTo(pList, 5); // same as Python pList[:5]
// pSlice now is [0, 1, 2, 3, 4]
listClear(&pSlice);

pSlice = listSliceFrom(pList, 5); // same as Python pList[5:]
// pSlice now is 5, 6, 7, 8, 9
listClear(&pSlice);

pSlice = listSlice(pList, -9, -1); // same as Python pList[-9:-1]
// pSlice now is [1, 2, 3, 4, 5, 6, 7, 8]
listClear(&pSlice);

pSlice = listSliceTo(pList, -5); // same as Python pList[:-5]
// pSlice now is [0, 1, 2, 3, 4]
listClear(&pSlice);

pSlice = listSliceFrom(pList, -5); // same as Python pList[-5:]
// pSlice now is 5, 6, 7, 8, 9
listClear(&pSlice);

listClear(&pList);
```

### listFilter()
### listComprehension()
Returns a filtered copy of the LIST according to a user defined function telling if an ELEMENT should be included or not
```C
extern LIST* listFilter(LIST* pList, BOOLEAN (*pMyInclusionFunction)(ELEMENT element));
extern LIST* listComprehension(LIST* pList, BOOLEAN (*pMyInclusionFunction)(ELEMENT element)); // listFilter() alias
```
:warning: listComprehension() currently only offers a subset of what can be done with list comprehension in Python...

Example use:
```C
#include <stdio.h>
#include <string.h>
#include <pylists4c.h>

BOOLEAN noEInStrings(ELEMENT element)
{
    if (element -> type == ETYPE_STRING)
        if (strchr(element -> pValue, 'e') || strchr(element -> pValue, 'E'))
            return FALSE;

    return TRUE;
}

int main(int argc, char *argv[])
{
    LIST* pList = NULL;
    LIST* pFilteredList = NULL;

    printf("Filtering strings containing the E letter:\n");
    pList = list("'la', 'disparition', 'est', 'un', 'livre', 'fameux', 'de', 'Georges', 'Perec'");
    listPrint(pList);
    // "['la', 'disparition', 'est', 'un', 'livre', 'fameux', 'de', 'Georges', 'Perec']" is printed to stdout
    pFilteredList = listFilter(pList, noEInStrings);
    listPrint(pFilteredList);
    // "['la', 'disparition', 'un']" is printed to stdout
    listClear(&pList);
    listClear(&pFilteredList);
}
```

### listConcat()
Returns a new LIST with the concatenation of the elements of LIST1 and LIST2
```C
extern LIST* listConcat(LIST* pList1, LIST* pList2);
```
It's like using Python "+" operator between lists...

Example use:
```C
LIST* pList1 = list("'a', 'b', 'c'");
LIST* pList2 = list("1, 2, 3");
LIST* pList3 = NULL;

pList3 = listConcat(pList1, pList2);
// pList3 now is ['a', 'b', 'c', 1, 2, 3]
// pList1 and pList2 are unchanged
...
listClear(&pList1);
listClear(&pList2);
listClear(&pList3);
```

### listExtend()
Adds a copy of the elements of the second LIST to the end of the first one
```C
extern void listExtend(LIST** ppList1, LIST* pList2);
```
Example use:
```C
LIST* pList1 = list("'a', 'b', 'c'");
LIST* pList2 = list("1, 2, 3");

listExtend(&pList1, pList2);
// pList1 now is ['a', 'b', 'c', 1, 2, 3]
// pList2 is unchanged
...
listClear(&pList1);
listClear(&pList2);
```

### listJoin()
Moves the elements of the second LIST to the end of the first one
```C
extern void listJoin(LIST** ppList1, LIST** ppList2);
extern void listStitch(LIST** ppList1, LIST** ppList2);// listJoin() alias
```
The second LIST is emptied (i.e.: NULL) after use.

Example use:
```C
LIST* pList1 = list("'a', 'b', 'c'");
LIST* pList2 = list("1, 2, 3");

listJoin(&pList1, &pList2);
// pList1 now is ['a', 'b', 'c', 1, 2, 3]
// pList2 now is NULL
...
listClear(&pList1);
listClear(&pList2);
```

## Changing list order
We follow the Python convention here:
* listSort(), listReverse(), listShuffle() modify the order of your LIST,
* while listSort**ed**(), listReverse**d**(), listShuffle**d**() return a re-ordered **copy** of your LIST.

### listSort()
Sorts a LIST
```C
extern STATUS listSort(LIST** ppList, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
```
This function sorts a LIST in ascending or descending order, with or without regard to case for Char, UChar and STRING values, with or without duplicate values in the resulting LIST.

By default (but you can change it with [listSetDefaultSort()](DOC.md#listsetdefaultsort)) it's based on [listSortedByInsertion()](DOC.md#listsortedbyinsertion), which itself is based on [listInsertSorted()](DOC.md#listinsertsorted), so check the caveats of that last function.

Example use:
```C
LIST* pList = list("2, 1, 4, 3");
listSort(&pList, FALSE, FALSE, FALSE);
// pList now is [1, 2, 3, 4]
...
listClear(&pList);
```

### listSorted()
Returns a sorted copy of a LIST
```C
extern LIST* listSorted(LIST* pList, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
```
Example use:
```C
LIST* pList = list("2, 1, 4, 3");
LIST* pSortedList = listSort(&pList, FALSE, FALSE, FALSE);
// pSortedList now is [1, 2, 3, 4]
// pList still is [2, 1, 4, 3]
...
listClear(&pList);
listClear(&pSortedList);
```

### listSortedByInsertion()
Returns a sorted copy of a LIST, using an [insertion sort](DOC.md#listinsertsorted) algorithm
```C
extern LIST* listSortedByInsertion(LIST* pList, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
```
This function is based on [listInsertSorted()](DOC.md#listinsertsorted), so check its caveats.

It may seems a little simple, but when it comes to sorting linked lists, such an algorithm is almost as good as any other...

It's meant to be called (by default) by the [listSort()](DOC.md#listsort) function, but you can still call it directly if you want to benchmark the efficiency of different sort algorithms on linked lists...

Example use:
```C
LIST* pDemiGods = list("'Ken', 'Dennis', 'Brian', 'bill', 'kirk', 'richard', 'bill', 'linus', 'guido'");
LIST* pSortedDemiGods = listSortedByInsertion(pDemiGods, FALSE, TRUE, TRUE);
// pSortedDemiGods now is ['bill', 'Brian', 'Dennis', 'guido', 'Ken', 'kirk', 'linus', 'richard']
// NB: Joy & Jolitz bills are factored
...
listClear(&pDemiGods);
listClear(&pSortedDemiGods);
```

### listSortedByQsort()
Returns a sorted copy of a LIST, using a [Quicksort](https://en.wikipedia.org/wiki/Quicksort) algorithm
```C
extern LIST* listSortedByQsort(LIST* pList, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
```
:warning: As Quicksort is made for sorting tables, we go through a [LIST to ARRAY to LIST conversion](DOC.md#lists-to-arrays-conversion). Thus it will only work on *homogeneous LISTs*.

The function is meant to be called by the [listSort()](DOC.md#listsort) function (if you set it as the new default with [listSetDefaultSort()](DOC.md#listsetdefaultsort)).

### listReverse()
Reverses the order of a LIST
```C
extern void listReverse(LIST** ppList);
```
This function just reverses the order of a LIST, it doesn't sort it.

Example use:
```C
LIST* pList = list("1, 2, 3, 4");
listReverse(&pList);
// pList now is [4, 3, 2, 1]
...
listClear(&pList);
```

### listReversed()
Returns a reversed copy of a LIST
```C
extern LIST* listReversed(LIST* pList);
```
Example use:
```C
LIST* pList = list("1, 2, 3, 4");
LIST* pReversedList = listReversed(&pList);
// pReversedList now is [4, 3, 2, 1]
// pList still is [1, 2, 3, 4]
...
listClear(&pList);
listClear(&pReversedList);
```

### listShuffle()
Shuffles a LIST
```C
extern STATUS listShuffle(LIST** ppList);
```
This function randomly shuffles the order of the elements of a LIST.

Example use:
```C
LIST* pList = list("1, 2, 3, 4");
listShuffle(&pList);
// pList could, for example, be [3, 1, 4, 2]
...
listClear(&pList);
```

### listShuffled()
Returns a shuffled copy of a LIST
```C
extern LIST* listShuffled(LIST** ppList);
```
Example use:
```C
LIST* pList = list("1, 2, 3, 4");
LIST* pShuffledList = listShuffled(&pList);
// pShuffledList could, for example, be [2, 4, 1, 3]
// pList still is [1, 2, 3, 4]
...
listClear(&pList);
listClear(&pShuffledList);
```

## Lists to arrays conversion
### listToArray()
Converts a LIST into an ARRAY (you'll have to free it after use with [listFreeArray()](DOC.md#listfreearray))
```C
extern ARRAY* listToArray(LIST* pList);
```
:warning: This only works on *homogeneous* LISTs. Else a NULL pointer will be returned.

:warning: The size of all STRING values is set to the longest one.

See the example use just below.

### listFromArray()
Converts an ARRAY into a LIST
```C
extern LIST* listFromArray(ARRAY* pArray);
```
This function is typically used to convert an ARRAY obtained through [listToArray()](DOC.md#listtoarray) back to a LIST.

:warning: The size of each STRING values is (re)set to the minimum required.

Here's a full example using the [Quicksort](https://en.wikipedia.org/wiki/Quicksort) algorithm to sort a LIST:
```C
#include <stdio.h>
#include <stdlib.h>
#include <pylists4c.h>

int longCompare(const void *p1, const void *p2)
{
    long left = *((long*) p1);
    long right = *((long*) p2);

    return ((left > right) - (left < right));
}

int main(int argc, char *argv[])
{
    LIST* pList;
    ARRAY* pArray;
    LIST* pSortedList;

    pList = list("8, 1, 3, 0, 2, 6, 4, 9, 5, 0, 7");
    pArray = listToArray(pList);
    qsort(pArray -> u.pLong, pArray -> length, pArray -> size, longCompare);
    pSortedList = listFromArray(pArray);
    listPrint(pSortedList);

    listClear(&pList);
    listFreeArray(&pArray);
    listClear(&pSortedList);
}
```

### listFreeArray()
Frees the memory allocated to an ARRAY
```C
extern void listFreeArray(ARRAY** ppArray);
```
The ARRAY pointer is resetted to NULL after use.

Example use provided just above...

## Removing elements
### listDelNth(n)
Removes the element at the specified position
```C
extern void listDelNth(LIST** ppList, long n);
```
Example use:
```C
LIST* pList = list("1, 2, 3");
listDelNth(&pList, 1);
// pList now is [1, 3]
...
listClear(&pList);
```

### listDelFirst()
Equivalent to listDelNth(0)
```C
extern void listDelFirst(LIST** ppList); // listDelNth(0) alias
```
Example use:
```C
LIST* pList = list("1, 2, 3");
listDelFirst(&pList);
pList now is [2, 3]
...
listClear(&pList);
```

### listDelLast()
Equivalent to listDelNth(-1)
```C
extern void listDelLast(LIST** ppList); // listDelNth(-1) alias
```
Example use:
```C
LIST* pList = list("1, 2, 3");
listDelLast(&pList);
// pList now is [1, 2]
...
listClear(&pList);
```

### listPopNth(n)
Removes the element at the specified position and returns it (you'll have to free it after use with listClear())
```C
extern LIST* listPopNth(LIST** ppList, long n);
```
Will return NULL if *n* is greater than the LIST length.

Example use:
```C
LIST* pList = list("1, 2, 3");
LIST* pElement = NULL;

pElement = listPopNth(&pList, 1);
// pList now is [1, 3]
printf("%ld\n", listValueLong(pElement);
// "2\n" is printed to stdout
...
listClear(&pElement);
listClear(&pList);
```

### listPopFirst()
### listDequeue()
Equivalent to listPopNth(0)
```C
extern LIST* listPopFirst(LIST** ppList); // listPopNth(-1) alias
extern LIST* listDequeue(LIST** ppList); // listPopNth(-1) alias
```
Example use:
```C
LIST* pList = list("1, 2, 3");
LIST* pElement = NULL;

pElement = listPopFirst(&pList);
// pList now is [2, 3]
printf("%ld\n", listValueLong(pElement);
// "1\n" is printed to stdout
...
listClear(&pElement);
listClear(&pList);
```

### listPop()
Equivalent to listPopNth(-1)
```C
extern LIST* listPop(LIST** ppList); // listPopNth(-1) alias
```
```C
LIST* pList = list("1, 2, 3");
LIST* pElement = NULL;

pElement = listPop(&pList);
// pList now is [1, 2]
printf("%ld\n", listValueLong(pElement);
// "3\n" is printed to stdout
...
listClear(&pElement);
listClear(&pList);
```

### listRemove()
Removes the first item with the specified value
```C
extern void listRemove(LIST** ppList, void* pValue, ETYPE type, size_t size);
```
Example use:
```C
LIST* pFruits = list("'apple', 'banana', 'mango', 'pear', 'banana'");
static char* fruit = "banana";

listRemove(&pFruits, fruit, ETYPE_STRING, strlen(fruit) + 1);
// pFruits now is ['apple', 'mango', 'pear', 'banana']

// or, more simply:
// listRemoveString(&pFruits, "banana");
...
listClear(&pFruits);
```

### listRemoveAll()
Removes all the items with the specified value
```C
extern void listRemoveAll(LIST** ppList, void* pValue, ETYPE type, size_t size);
```
Example use:
```C
LIST* pFruits = list("'apple', 'banana', 'mango', 'pear', 'banana'");
static char* fruit = "banana";

listRemoveAll(&pFruits, fruit, ETYPE_STRING, strlen(fruit) + 1);
// pFruits now is ['apple', 'mango', 'pear']

// or, more simply:
// listRemoveAllString(&pFruits, "banana");
...
listClear(&pFruits);
```

## Clearing lists
### listClear()
### listDel()
### listFree()
Removes all the elements of the LIST
```C
extern void listClear(LIST** ppList);
extern void listDel(LIST** ppList); // listClear() alias
extern void listFree(LIST** ppList); // listClear() alias
```
The LIST pointer is resetted to NULL after use.

:warning: Contrarily to what Python does, listDel() only clears the LIST (i.e.: reset it to 0 elements), but does not destroy it.

Example uses provided all through this documentation 😄...

## Structs handling
### listSetStructSize()
Sets the size of a STRUCT you want to compare
```C
extern void listSetStructSize(size_t size);
```
:warning: This function has to be called *before* any call to the STRUCT comparator function and each time the size changes.

### listSetStructComparator()
Sets the function to be used to compare STRUCTs
```C
extern void listSetStructComparator(int (*listStructComparator)(const void* pStruct1, const void* pStruct2));
```
By default, the supplied listCompareStructByMemcmp() function is used to compare STRUCTs, but if you intend to sort LISTs containing STRUCTs elements you'd better define your own function.

Example use:
```C
int myStructComparator(const void* pStruct1, const void* pStruct2)
{
    // my stuff
}

listSetStructComparator(myStructComparator);
```

### listSetStructStringer()
Sets the function to be used to string STRUCTs
```C
extern void listSetStructStringer(void (*listStructStringer)(STRING buffer, void* pStruct, size_t size));
```
The supplied listStringStructByDefault() function is used to string STRUCTs, but if you intend to print more useful information you'd better define your own function.

Example use:
```C
void myStructStringer(STRING buffer, void* pStruct, size_t size)
{
    // my stuff
}

listSetStructStringer(myStructStringer);
```

### listSetStructPrinter()
Sets the function to be used to print STRUCTs
```C
extern void listSetStructPrinter(void (*listStructPrinter)(void* pStruct, size_t size));
```
The supplied listPrintStructByDefault() function is used to print STRUCTs, but if you intend to print more useful information you'd better define your own function.

Example use:
```C
void myStructPrinter(void* pStruct, size_t size)
{
    // my stuff
}

listSetStructPrinter(myStructPrinter);
```

### listSetStructDebugger()
Sets the function to be used to debug STRUCTs
```C
extern void listSetStructDebugger(void (*listStructDebugger)(void* pStruct, size_t size));
```
The supplied listDebugStructByDefault() function is used to debug STRUCTs, but if you intend to print more useful information you'd better define your own function.

Example use:
```C
void myStructDebugger(void* pStruct, size_t size)
{
    // my stuff
}

listSetStructDebugger(myStructDebugger);
```

## Miscellaneous
### listSetDebugMessagesDisplay()
Sets whether or not to print debugging messages to stderr
```C
extern void listSetDebugMessagesDisplay(BOOLEAN display);
```
By default the library will print a few informative messages to stderr in case of errors. You can use this function with a FALSE parameter if you want to prevent that.

Example use:
```C
// Do the following near the beginning of your program.
listSetDebugMessagesDisplay(FALSE);
```

### listSetFatalMallocErrors()
Sets whether memory allocation errors are fatal or not
```C
extern void listSetFatalMallocErrors(BOOLEAN fatal);
```
If you want to avoid testing the return code of the STATUS returning functions, as in most cases they can only fail if there's a memory allocation error, you can set this to TRUE so they'll exit to the [shell](https://en.wikipedia.org/wiki/Shell_(computing)) with a FAILURE exit code. Anyway, your program will probably be in jeopardy if there's no memory left!

Example use:
```C
// Do the following near the beginning of your program.
listSetFatalMallocErrors(TRUE);
```

### listSetDefaultSort()
Sets the default sorting algorithm
```C
extern void listSetDefaultSort(LIST* (*defaultSortAlgorithm)(LIST* pList, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates));
```

Example use:
```C
listSetDefaultSort(listSortedByQsort);
```

### listGetAllocatedMemory()
Returns the quantity of allocated/unfreed memory used by this library
```C
extern unsigned long listGetAllocatedMemory();
```
You can use this for debugging purposes if you want to detect if you have [memory leaks](https://en.wikipedia.org/wiki/Memory_leak) in your programs...

Example use:
```C
// Do the following near the end of your program.
// If you have more than 0 bytes allocated, you probably have a memory leak somewhere...
printf("Allocated memory: %lu\n", listGetAllocatedMemory());
```
