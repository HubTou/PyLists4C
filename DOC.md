![alt text](https://github.com/HubTou/PyLists4C/blob/main/logo/pylists4c-logo.png "PyLists4C: Python-style lists for the C language")
# PyLists4C: Python-style lists for the C language
## Glossary and conventions
* A **LIST** is an instance of linked list this library provides.
* An **element** is a node of a LIST.
* A **value** is the payload of an element of a LIST.
* An **index** is the position of an element in a LIST.
  * Like in Python, indexes are numbered from 0 when you go through a LIST from its beginning, or from -1 when you go through its end.
  * LISTs indexes and lengths are of the C language **long** type. 
* An **homogeneous** LIST is a special kind of data structure where all values are of the same type.
* Pointers variable names are prefixed with a **p** character. Pointers to pointers with **pp** and so on.

# Data structures
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
  * STRINGs (C language NUL terminated character arrays),
  * sub-LISTs,
  * and user defined, self contained (that is to say, without pointers) STRUCTs.
* With Python-style lists, you can implement many other data types with sub LISTS (all kind of trees, for example).
* As the size of user defined STRUCTs is unknown (and furthermore can be of variable size inside a same LIST) and STRINGS can be allocated to larger character arrays than their current content, we need a **size** variable to keep track of the space allocated to store the *value*.
  * If you use multiple kinds of STRUCTs in the same LIST, it is advised to start each of these STRUCTs with a fixed length field indicating its sub type.
* As we want an *element* to have the same memory size, we use pointers for all *values*, not just STRINGs, LISTs and STRUCTS. Thus we need a **pValue** variable to point to the *value* of each *element*.

### ETYPE type
It's defined like this:
```C
// Element TYPEs:
typedef enum
{
    ETYPE_UNDEFINED = -1,
//  ETYPE_NULL = 0,
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
    // C-style strings (ie. 0 terminated character array):
    ETYPE_STRING = 31,
    // Homogeneous ARRAYs:
//  ETYPE_ARRAY = 32,
    // Sub-LISTs:
    ETYPE_LIST = 33,
    // Python-style dictionaries for C:
//  ETYPE_DICT = 34,
    // Self-contained structures without pointers:
    ETYPE_STRUCT = 35
} ETYPE;
```
Design notes:
* ETYPE_UNDEFINED is meant for internal use.
* The following types are placeholders for possible future extensions:
  * ETYPE_NULL for empty elements (I haven't found a use case for this yet),
  * ETYPE_ARRAY for our [ARRAYs](DOC.md#arraytype) as we have defined them anyway (though the same functionalities could be achieved through sub-LISTs),
  * ETYPE_DICT for a possible complementary library of [Python-style dictionaries](https://www.w3schools.com/python/python_dictionaries.asp).

We provide convenience functions for each standard C language types, so you don't always have to pass *values* by address, provide the *type* and *size* parameters, or cast variables to specific types.

### ARRAY type
One thing we can't easily do in C language is to have directly indexed LIST *elements* (ie: MyList\[0], MyList\[1] and so on), though we provide a [listGet()](DOC.md#listgetn) base function to access the Nth *element* of a LIST.

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
* In order to avoid casting, we provide an union **u** with all possible subtypes.
  * We could have used the same scheme for the LIST data structure **pValue** variable but thought it would needlessly complexify things... 
* Every standard C language type is a pointer to (ie. a table of) that type.
* Being of unknown size to the C language, our custom types are pointers to pointers so their table indexation will work.

### LIST_STATS type
The [listStats()](DOC.md#liststats) function provides a way to collect several information in one LIST walkthrough.

It fills a data structure defined like this:
```C
// List statistics:
typedef struct
{
    long length; // same as listLen() result

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

    unsigned long smallestString; // without the 0 terminating character
    unsigned long largestString; // without the 0 terminating character
    unsigned long smallestStruct;
    unsigned long largestStruct;

    long shortestList; // number of elements at first level
    long longestList; // number of elements at first level

    BOOLEAN isHomogeneous;
    ETYPE homogeneousType;
    size_t homogeneousSize; // STRUCTs could be of different sizes...

    LIST* pLastElement; // same as listGetLast() result

    unsigned long memoryUsed; // including eventual subLISTs
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

# Base functions
## Creating a list
### LIST declaration
Creates an empty list.

Example use:
```C
LIST* MyList = NULL;
```

LISTs should only be allocated through the library's functions, so **never use LIST variables directly** (ie: LIST MyList) or you won't be able to have empty LISTs, to change the first *element* easily or to clear your LIST... 

### listCreateElement()
Creates an unlinked LIST element

### list()
Creates a LIST from a Python-style list declaration string

### listFromTable()
Converts a C-language table into a LIST

## Adding elements
### listAppend()
### listPush()
Adds an element at the end of a LIST

### listInsertFirst()
### listPrepend()
Adds an element at the start of a LIST

### listInsert(n)
Inserts an element at the Nth position of a LIST

### listInsertSorted()
Inserts an element in a sorted LIST

## Getting list information
### listLen()
Returns the number of elements in a LIST

### listStats()
Fills statistics about a LIST

### listStatsPrint()
Prints statistics about a LIST

## Fetching elements
### listGet(n)
Returns the Nth element of a LIST

### listGetLast()
Returns the last element of a LIST

### listSlice(n, m)
### listSliceFrom(n)
### listSliceTo(m)
Returns a copy of a slice (ie. [n:m]) of a LIST

## Testing lists
### listAreEqual()
Tests if two LISTs contain exactly the same values

### listAreEqualCaseInsensitive()
Tests if two LISTs contain the same values, without regard to case

## Searching for elements
### listContains()
Tests if a value appears in a LIST

### listCount()
Returns the number of elements with the specified value

### listIndex()
Returns the index of the first element with the specified value

### listIndexAll()
### listFind()
### listSearch()
Returns a LIST of all the indexes of the elements with the specified value

## Working with lists
### listCopy()
Returns a copy of the LIST (a full/deep copy as we don't want multiple references to the same values)

### listConcat()
Returns a new LIST with the concatenation of the elements of LIST1 and LIST2

### listExtend()
Adds a copy of the elements of the second LIST to the end of the first one

### listJoin()
### listStitch()
Moves the elements of the second LIST to the end of the first one

## Changing list order**
### listSort()
Sorts a LIST

### listSorted()
Returns a sorted copy of a LIST

### listSortedByInsertion()
Returns a sorted copy of a LIST, using an insertion sort algorithm

### listReverse()
Reverses the order of a LIST

### listReversed()
Returns a reversed copy of a LIST

### listShuffle()
Shuffles a LIST

### listShuffled()
Returns a shuffled copy of a LIST

## Removing elements
### listPopNth(n)
### listDelNth(n)
Removes the element at the specified position

### listPopFirst()
Equivalent to listPopNth(0)

### listPopLast()
### ListPop()
Equivalent to listPopNth(-1)

### listRemove()
Removes the first item with the specified value

### listRemoveAll()
Removes all the items with the specified value

## Clearing lists
### listClear()
### listDel()
### listFree()
Removes all the elements of the LIST

## Working with numerical lists
### listMaxXXX()
Returns the maximum value in the LIST for the XXX type

### listMinXXX()
Returns the minimum value in the LIST for the XXX type

### listSumXXX()
Returns the sum of values in the LIST for the XXX type

## Displaying lists
### listStr()
### listAscii()
### listRepr()
Returns a pointer to a string containing a Python-style (ie. [e1, e2...]) representated LIST (which you'll need to free afterwards using listFreeStr())

### listFreeStr()
Frees the memory allocated to a LIST representation

### listPrint()
Prints a Python-style (ie. [e1, e2...]) representated LIST

### listDebug()
Prints all LIST details to stderr

## Lists to arrays conversion
### listToArray()
Converts a LIST into an ARRAY

### listFromArray()
Converts an ARRAY into a LIST

### listFreeArray()
Frees the memory allocated to an ARRAY

## Miscellaneous
### listGetAllocatedMemory()
Returns the quantity of allocated/unfreed memory used by this library

### listSetFatalMallocErrors()
Sets whether memory allocation errors are fatal or not
