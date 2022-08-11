![alt text](https://github.com/HubTou/PyLists4C/blob/main/logo/pylists4c-logo.png "PyLists4C: Python-style lists for the C language")
# PyLists4C: Python-style lists for the C language
## Glossary and conventions
* A **LIST** is an instance of linked list this library provides.
* An **element** is a node of a LIST.
* A **value** is the payload of an element of a LIST.
* An **index** is the position of an element in a LIST.
  * Like in Python, indexes are numbered from 0 when you go through a LIST from its beginning, or from -1 when you go through its end.
  * LISTs indexes, lengths and counts are of the C language **long** type. 
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
  * ETYPE_ARRAY for our [ARRAYs](DOC.md#array-type) as we have defined them anyway (though the same functionalities could be achieved through sub-LISTs),
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
LIST* MyList = NULL;
```
LISTs should only be allocated through the library's functions, so **never use LIST variables directly** (ie: LIST MyList) or you won't be able to have empty LISTs, to change the first *element* easily or to clear your LIST... 

### listCreateElement()
Creates an unlinked LIST element
```C
extern LIST* listCreateElement(void* pValue, ETYPE type, size_t size);
```
Used by all the functions adding elements to a LIST, this one is rather intended for internal use.

Example use, though you'd better just [listAppend()](DOC.md#listappend) your first value:
```C
LIST* MyList = NULL;
long aLongValue = 42;
MyList = listCreateElement(&aLongValue, ETYPE_LONG, sizeof(long));
```

### list()
Creates a LIST from a Python-style list declaration string
```C
extern LIST* list(STRING string, char separator);
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
long anArrayOfLongs[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
long length = 9;
LIST* pList = listFromTable(anArrayOfLongs, ETYPE_LONG, sizeof(long), length);
...
listClear(&pList);
```

## Adding elements
### listAppend()
### listPush()
### listEnqueue()
Adds an element at the end of a LIST
```C
extern STATUS listAppend(LIST** ppList, void* pValue, ETYPE type, size_t size);
extern STATUS listPush(LIST** ppList, void* pValue, ETYPE type, size_t size); // listAppend() alias
extern STATUS listEnqueue(LIST** ppList, void* pValue, ETYPE type, size_t size); // listAppend() alias
```

### listInsertFirst()
### listPrepend()
Adds an element at the start of a LIST
```C
extern STATUS listInsertFirst(LIST** ppList, void* pValue, ETYPE type, size_t size);
extern STATUS listPrepend(LIST** ppList, void* pValue, ETYPE type, size_t size); // listInsertFirst() alias
```

### listInsert(n)
Inserts an element at the Nth position of a LIST
```C
extern STATUS listInsert(LIST** ppList, long n, void* pValue, ETYPE type, size_t size);
```

### listInsertSorted()
Inserts an element in a sorted LIST
```C
extern STATUS listInsertSorted(LIST** ppList, void* pValue, ETYPE type, size_t size, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
```

## Displaying lists
### listStr()
### listAscii()
### listRepr()
Returns a pointer to a string containing a Python-style (ie. [e1, e2...]) representated LIST (you'll have to free it after use with [listFreeStr()](DOC.md#listfreestr)
```C
extern STRING listStr(LIST* pList);
extern STRING listAscii(LIST* pList); // listStr() alias
extern STRING listRepr(LIST* pList); // listStr() alias
```

### listFreeStr()
Frees the memory allocated to a LIST representation
```C
extern void listFreeStr(STRING*); // NB: passing the previous STRING by address to reset it
```

### listPrint()
Prints a Python-style (ie. [e1, e2...]) representated LIST to stdout
```C
extern void listPrint(LIST* pList);
```

### listDebug()
Prints all LIST details to stderr
```C
extern void listDebug(LIST* pList, STRING name);
```

## Getting list information
### listLen()
Returns the number of elements in a LIST
```C
extern long listLen(LIST* pList);
```

### listStats()
Fills statistics about a LIST
```C
extern void listStats(LIST* pList, LIST_STATS* pStats);
```

### listStatsPrint()
Prints statistics about a LIST to stdout
```C
extern void listStatsPrint(LIST_STATS stats, STRING name);
```

## Searching for elements
### listContains()
Tests if a value appears in a LIST
```C
extern BOOLEAN listContains(LIST* pList, void* pValue, ETYPE type, size_t size);
```

### listCount()
Returns the number of elements with the specified value
```C
extern long listCount(LIST* pList, void* pValue, ETYPE type, size_t size);
```

### listIndex()
Returns the index of the first element with the specified value
```C
extern long listIndex(LIST* pList, void* pValue, ETYPE type, size_t size);
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
⚠️ There is no warning in cases of sum overflow, or precision losses.

## Fetching elements
### listGet(n)
Returns the Nth element of a LIST
```C
extern LIST* listGet(LIST* pList, long n);
```

### listGetLast()
Returns the last element of a LIST
```C
extern LIST* listGetLast(LIST* pList);
```

### listSlice(n, m)
### listSliceFrom(n)
### listSliceTo(m)
Returns a copy of a slice (ie. [n:m]) of a LIST
```C
extern LIST* listSlice(LIST* pList, long n, long m);
extern LIST* listSliceFrom(LIST* pList, long n);
extern LIST* listSliceTo(LIST* pList, long m);
```

## Changing elements
### listChange(n)
### listModify(n)
Changes the value of the element at the Nth position of a LIST
```C
extern STATUS listChange(LIST* pList, long n, void* pValue, ETYPE type, size_t size);
extern STATUS listModify(LIST* pList, long n, void* pValue, ETYPE type, size_t size); // listChange() alias
```

## Testing lists
### listAreEqual()
Tests if two LISTs contain exactly the same values
```C
extern BOOLEAN listAreEqual(LIST* pList1, LIST* pList2);
```

### listAreEqualCaseInsensitive()
Tests if two LISTs contain the same values, without regard to case
```C
extern BOOLEAN listAreEqualCaseInsensitive(LIST* pList1, LIST* pList2);
```

## Working with lists
### listCopy()
Returns a copy of the LIST (a full/deep copy as we don't want multiple references to the same values)
```C
extern LIST* listCopy(LIST* pList);
```

### listConcat()
Returns a new LIST with the concatenation of the elements of LIST1 and LIST2
```C
extern LIST* listConcat(LIST* pList1, LIST* pList2);
```

### listExtend()
Adds a copy of the elements of the second LIST to the end of the first one
```C
extern void listExtend(LIST** ppList1, LIST* pList2);
```

### listJoin()
### listStitch()
Moves the elements of the second LIST to the end of the first one
```C
extern void listJoin(LIST** ppList1, LIST** ppList2);
extern void listStitch(LIST** ppList1, LIST** ppList2);// listJoin() alias
```

## Changing list order**
### listSort()
Sorts a LIST
```C
extern STATUS listSort(LIST** ppList, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
```

### listSorted()
Returns a sorted copy of a LIST
```C
extern LIST* listSorted(LIST* pList, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
```

### listSortedByInsertion()
Returns a sorted copy of a LIST, using an insertion sort algorithm
```C
extern LIST* listSortedByInsertion(LIST* pList, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
```

### listReverse()
Reverses the order of a LIST
```C
extern void listReverse(LIST** ppList);
```

### listReversed()
Returns a reversed copy of a LIST
```C
extern LIST* listReversed(LIST* pList);
```

### listShuffle()
Shuffles a LIST
```C
extern STATUS listShuffle(LIST** ppList);
```

### listShuffled()
Returns a shuffled copy of a LIST
```C
extern LIST* listShuffled(LIST* extern void listPopNth(LIST** ppList, long n);
```

## Lists to arrays conversion
### listToArray()
Converts a LIST into an ARRAY (you'll have to free it after use with [listFreeArray()](DOC.md#listfreearray))
```C
extern ARRAY* listToArray(LIST* pList);
```

### listFromArray()
Converts an ARRAY into a LIST
```C
extern LIST* listFromArray(ARRAY* pArray);
```

### listFreeArray()
Frees the memory allocated to an ARRAY
```C
extern void listFreeArray(ARRAY** ppArray);
```

## Removing elements
### listDelNth(n)
Removes the element at the specified position
```C
extern void listDelNth(LIST** ppList, long n); // listPopNth() alias
```

### listDelFirst()
Equivalent to listDelNth(0)
```C
extern void listDelFirst(LIST** ppList); // listDelNth(0) alias
```

### listDelLast()
Equivalent to listDelNth(-1)
```C
extern void listDelLast(LIST** ppList); // listDelNth(-1) alias
```

### listPopNth(n)
Removes the element at the specified position and returns it (you'll have to free it after use with listClear())
```C
extern LIST* listPopNth(LIST** ppList, long n);
```

### listPopFirst()
### listDequeue()
Equivalent to listPopNth(0)
```C
extern LIST* listPopFirst(LIST** ppList); // listPopNth(-1) alias
extern LIST* listDequeue(LIST** ppList); // listPopNth(-1) alias
```

### listPop()
Equivalent to listPopNth(-1)
```C
extern LIST* listPop(LIST** ppList); // listPopNth(-1) alias
```

### listRemove()
Removes the first item with the specified value
```C
extern void listRemove(LIST** ppList, void* pValue, ETYPE type, size_t size);
```

### listRemoveAll()
Removes all the items with the specified value
```C
extern void listRemoveAll(LIST** ppList, void* pValue, ETYPE type, size_t size);
```

## Clearing lists
### listClear()
### listDel()
### listFree()
Removes all the elements of the LIST
```C
extern void listClear(LIST** ppList);
extern void listDel(LIST** ppList); // listClear() alias
extern void listFree(LIST** ppList); // listClear() alias```
```

## Miscellaneous
### listGetAllocatedMemory()
Returns the quantity of allocated/unfreed memory used by this library
```C
extern unsigned long listGetAllocatedMemory();
```

### listSetFatalMallocErrors()
Sets whether memory allocation errors are fatal or not
```C
extern void listSetFatalMallocErrors(BOOLEAN fatal);
```
