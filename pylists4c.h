// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#ifndef PYLISTS4C_H
#define PYLISTS4C_H
/******************************************************************************/
// LIBRARY: PyLists4C
// FUNCTIONS:
//   Creating a list:
//     LIST* MyList = NULL;
//       Creates an empty LIST
//     listCreateElement():
//       Creates an unlinked LIST element
//     list():
//       Creates a LIST from a Python-style LIST declaration string
//     listFromTable():
//       Converts a C language table into a LIST
//
//   Adding & changing elements:
//     listAppend() / listPush() / listEnqueue():
//       Adds an element at the end of a LIST
//     listInsertFirst() / listPrepend():
//       Adds an element at the start of a LIST
//     listInsert(n):
//       Inserts an element at the Nth position of a LIST
//     listInsertSorted():
//       Inserts an element in a sorted LIST
//     listInsertList():
//       Inserts a copy of the elements of a LIST at the Nth position of another LIST
//     listChange(n):
//       Changes the value of the element at the Nth position of a LIST
//     listChangeSlice():
//       Changes the elements at the defined LIST slice with those from the second LIST
//
//   Displaying lists:
//     listStr() / listAscii() / listRepr():
//       Returns a pointer to a string containing a Python-style LIST representation
//     listFreeStr():
//       Frees the memory allocated to a Python-style LIST representation
//     listPrint():
//       Prints a Python-style LIST representation to stdout
//     listDebug():
//       Prints all LIST details to stderr
//
//   Getting list information:
//     listLen():
//       Returns the number of elements in a LIST
//     listStats():
//       Fills statistics about a LIST in one walkthrough
//     listStatsPrint():
//       Prints statistics about a LIST to stdout
//
//   Searching for elements:
//     listContains():
//       Tests if a value appears in a LIST
//     listCount():
//       Returns the number of elements with the specified value
//     listIndex():
//       Returns the index of the first element with the specified value
//     listIndexAll() / listFind() / listSearch():
//       Returns a LIST of all the indexes of the elements with the specified value
//
//   Working with numerical lists:
//     listMaxXXX():
//       Returns the maximum value in the LIST for the XXX type
//     listMinXXX():
//       Returns the minimum value in the LIST for the XXX type
//     listSumXXX():
//       Returns the sum of values in the LIST for the XXX type
//
//   Fetching elements:
//     listGet():
//       Returns the Nth LIST_ELEMENT of a LIST
//     listGetLast():
//       Returns the last LIST_ELEMENT of a LIST
//     listSetIterator():
//       Defines a LIST_ITERATOR from an LIST_ELEMENT of a LIST
//     listNext():
//       Returns the next LIST_ELEMENT of a LIST starting from a LIST_ITERATOR
//     listPrevious():
//       Returns the previous LIST_ELEMENT of a LIST starting from a LIST_ITERATOR
//
//   Fetching elements values:
//     listValueXXX():
//       Returns the element value in the requested type
//
//   Testing lists:
//     listAreEqual():
//       Tests if two LISTs contain the same values
//
//   Working with lists:
//     listCopy():
//       Returns a copy of the LIST (a full/deep copy as we don't want multiple
//       references to the same values)
//     listSlice(n, m):
//     listSliceFrom(n):
//     listSliceTo(m):
//       Returns a copy of a slice (ie. [n:m]) of a LIST
//     listFilter():
//       Returns a filtered copy of the LIST according to a user defined function
//       telling if an ELEMENT should be included or not
//     listComprehension() / listForEach():
//       Returns a new LIST according to a user defined function producing 0-N
//       elements for each LIST_ELEMENT
//     listConcat():
//       Returns a new LIST with the concatenation of the elements of LIST1 and LIST2
//     listExtend():
//       Adds a copy of the elements of the second LIST to the end of the first one
//     listJoin():
//       Moves the elements of the second LIST to the end of the first one
//     listSplit(n):
//       Cuts a LIST in two parts and returns a pointer to the second part
//     listHalve():
//       Cuts a LIST in two and returns a pointer to the second half
//
//   Changing list order:
//     listSort():
//       Sorts a LIST
//     listSorted():
//       Returns a sorted copy of a LIST
//     listSetDefaultSort():
//       Sets the default sorting algorithm
//     listSortedByInsertion():
//       Returns a sorted copy of a LIST, using an insertion sort algorithm
//     listSortedByQsort():
//       Returns a sorted copy of a LIST, using an Quicksort algorithm
//     listReverse():
//       Reverses the order of a LIST
//     listReversed():
//       Returns a reversed copy of a LIST
//     listShuffle():
//       Shuffles a LIST
//     listShuffled():
//       Returns a shuffled copy of a LIST
//
//   Lists to arrays conversion:
//     listToArray():
//       Converts a LIST into an ARRAY
//     listFromArray():
//       Converts an ARRAY into a LIST
//     listFreeArray():
//       Frees the memory allocated to an ARRAY
//
//   Removing elements:
//     listDelNth() / listDelFirst() for n=0 / listDelLast() for n=-1:
//       Removes the element at the specified position
//     listDelSlice(n, m):
//       Removes the elements at the specified slice
//     listPopNth() / listPopFirst() for n=0 / listDequeue() for n=0 / listPop() for n=-1:
//       Removes the element at the specified position and returns it
//       (you'll have to free it after use with listClear())
//     listRemove():
//       Removes the first item with the specified value
//     listRemoveAll():
//       Removes all the items with the specified value
//     listRemoveDuplicates():
//       Removes adjacent duplicate items in a sorted LIST
//
//   Clearing lists:
//     listClear() / listDel() / listFree():
//       Removes all the elements of the LIST
//
//   Structs handling:
//     listSetStructSize():
//       Sets the size of a STRUCT you want to compare
//     listSetStructComparator():
//       Sets the function to be used to compare STRUCTs
//     listCompareStructByMemcmp():
//       Default handling of STRUCTs comparison
//     listCompareStructReversed():
//       Compare STRUCTs elements in reverse order
//     listSetStructStringer():
//       Sets the function to be used to string STRUCTs
//     listStringStructByDefault():
//       Default handling of STRUCTs stringing
//     listSetStructPrinter():
//       Sets the function to be used to print STRUCTs to stdout
//     listPrintStructByDefault():
//       Default handling of STRUCTs printing
//     listSetStructDebugger():
//       Sets the function to be used to debug STRUCTs to stderr
//     listDebugStructByDefault():
//       Default handling of STRUCTs debugging
//
//   Miscellaneous:
//     listSetDebugMessagesDisplay():
//       Sets whether or not to print debugging messages to stderr
//     listSetFatalMallocErrors():
//       Sets whether memory allocation errors are fatal or not
//     listGetAllocatedMemory():
//       Returns the quantity of allocated/unfreed memory used by this library
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

// Macros for compilation as a Dynamic Link Library (DLL) on Windows:
#if defined _WIN32 || defined _WIN64
# define strcasecmp _stricmp
# pragma clang diagnostic ignored "-Wignored-attributes"
# define IMPORT __declspec(dllimport)
# define EXPORT __declspec(dllexport)
#else
# define IMPORT
# define EXPORT
#endif
#define INTERNAL

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

// Double-linked variable content linked list cell:
typedef struct list
{
    void* pValue;

    ETYPE type;
    size_t size;

    struct list* pPrevious;
    struct list* pNext;
} LIST;

// An element of a LIST
typedef LIST* LIST_ELEMENT;

// A LIST iterator
typedef LIST* LIST_ITERATOR;

#ifndef BOOLEAN_TYPE
#define BOOLEAN_TYPE
typedef enum
{
    FALSE = 0,
    TRUE = 1
} BOOLEAN;
#endif // BOOLEAN_TYPE

#ifndef STRING_TYPE
#define STRING_TYPE
typedef char* STRING;
#endif // STRING_TYPE

// List statistics:
typedef struct
{
    long length; // Same as listLen() result

    long nullCount;
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
    long arrayCount;
    long listCount;
    long dictCount;
    long structCount;
    long unknownCount;

    unsigned long smallestString; // Without the \0 terminating character
    unsigned long largestString; // Without the \0 terminating character
    unsigned long smallestStruct;
    unsigned long largestStruct;

    long shortestArray;
    long longestArray;
    long shortestList; // Number of elements at first level
    long longestList; // Number of elements at first level
    long shortestDict;
    long longestDict;

    BOOLEAN isHomogeneous;
    ETYPE homogeneousType;
    size_t homogeneousSize; // STRUCTs could be of different sizes...

    LIST* pLastElement; // Same as listGetLast() result

    unsigned long memoryUsed; // Including eventual subLISTs
} LIST_STATS;

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

#ifndef STATUS_TYPE
#define STATUS_TYPE
typedef enum
{
    SUCCESS = 0,
    FAILURE = 1
} STATUS;
#endif // STATUS_TYPE

// Function prototypes:
// NB:
// - LIST** parameters imply that your original LIST pointer could be modified)
// - LIST positions, counts or lengths are of long type
extern IMPORT LIST* listCreateElement(void* pValue, ETYPE type, size_t size);
extern IMPORT LIST* list(STRING string);
extern IMPORT LIST* listFromTable(void* pTable, ETYPE type, size_t size, long length); // listFromArray() wrapper

extern IMPORT STATUS listAppend(LIST** ppList, void* pValue, ETYPE type, size_t size);
#define listPush listAppend
#define listEnqueue listAppend
extern IMPORT STATUS listInsertFirst(LIST** ppList, void* pValue, ETYPE type, size_t size);
#define listPrepend listInsertFirst
extern IMPORT STATUS listInsert(LIST** ppList, long n, void* pValue, ETYPE type, size_t size);
extern IMPORT STATUS listInsertSorted(LIST** ppList, void* pValue, ETYPE type, size_t size, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
extern IMPORT void listInsertList(LIST** ppTarget, long n, LIST* pSource);
extern IMPORT STATUS listChange(LIST* pList, long n, void* pValue, ETYPE type, size_t size);
extern IMPORT void listChangeSlice(LIST** ppTarget, long n, long m, LIST* pSource);

extern IMPORT STRING listStr(LIST* pList);
#define listAscii listStr
#define listRepr listStr
extern IMPORT void listFreeStr(STRING*); // NB: passing the previous STRING by address to reset it
extern IMPORT void listPrint(LIST* pList);
extern IMPORT void listDebug(LIST* pList, STRING name);

extern IMPORT long listLen(LIST* pList);
extern IMPORT void listStats(LIST* pList, LIST_STATS* pStats);
extern IMPORT void listStatsPrint(LIST_STATS stats, STRING name);

extern IMPORT BOOLEAN listContains(LIST* pList, void* pValue, ETYPE type, size_t size);
extern IMPORT long listCount(LIST* pList, void* pValue, ETYPE type, size_t size);
extern IMPORT long listIndex(LIST* pList, void* pValue, ETYPE type, size_t size);
extern IMPORT LIST* listIndexAll(LIST* pList, void* pValue, ETYPE type, size_t size);
#define listFind listIndexAll
#define listSearch listIndexAll

extern IMPORT LIST_ELEMENT listGet(LIST* pList, long n);
extern IMPORT LIST_ELEMENT listGetLast(LIST* pList);
extern IMPORT LIST_ITERATOR listSetIterator(LIST_ELEMENT element);
extern IMPORT LIST_ELEMENT listNext(LIST_ITERATOR* pIterator);
extern IMPORT LIST_ELEMENT listPrevious(LIST_ITERATOR* pIterator);

extern IMPORT char listValueChar(LIST_ELEMENT element);
extern IMPORT unsigned char listValueUChar(LIST_ELEMENT element);
extern IMPORT short listValueShort(LIST_ELEMENT element);
extern IMPORT unsigned short listValueUShort(LIST_ELEMENT element);
extern IMPORT int listValueInt(LIST_ELEMENT element);
extern IMPORT unsigned int listValueUInt(LIST_ELEMENT element);
extern IMPORT long listValueLong(LIST_ELEMENT element);
extern IMPORT unsigned long listValueULong(LIST_ELEMENT element);
extern IMPORT long long listValueLongLong(LIST_ELEMENT element);
extern IMPORT unsigned long long listValueULongLong(LIST_ELEMENT element);
extern IMPORT float listValueFloat(LIST_ELEMENT element);
extern IMPORT double listValueDouble(LIST_ELEMENT element);
extern IMPORT long double listValueLongDouble(LIST_ELEMENT element);
extern IMPORT STRING listValueString(LIST_ELEMENT element);

extern IMPORT BOOLEAN listAreEqual(LIST* pList1, LIST* pList2, BOOLEAN caseInsensitive);

extern IMPORT LIST* listCopy(LIST* pList);
extern IMPORT LIST* listSlice(LIST* pList, long n, long m);
extern IMPORT LIST* listSliceFrom(LIST* pList, long n);
extern IMPORT LIST* listSliceTo(LIST* pList, long m);
extern IMPORT LIST* listFilter(LIST* pList, BOOLEAN (*pMyInclusionFunction)(LIST_ELEMENT element));
extern IMPORT LIST* listComprehension(LIST* pList, LIST* (*pMyListComprehensionFunction)(LIST_ELEMENT element));
#define listForEach listComprehension
extern IMPORT LIST* listConcat(LIST* pList1, LIST* pList2);
extern IMPORT void listExtend(LIST** ppList1, LIST* pList2);
extern IMPORT void listJoin(LIST** ppList1, LIST** ppList2);
extern IMPORT LIST* listSplit(LIST** ppList, long n);
extern IMPORT LIST* listHalve(LIST* pList); // listSplit() wrapper

extern IMPORT STATUS listSort(LIST** ppList, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
extern IMPORT LIST* listSorted(LIST* pList, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
extern IMPORT void listSetDefaultSort(LIST* (*defaultSortAlgorithm)(LIST* pList, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates));
extern IMPORT LIST* listSortedByInsertion(LIST* pList, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
extern IMPORT LIST* listSortedByQsort(LIST* pList, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
extern IMPORT void listReverse(LIST** ppList);
extern IMPORT LIST* listReversed(LIST* pList);
extern IMPORT STATUS listShuffle(LIST** ppList);
extern IMPORT LIST* listShuffled(LIST* pList);

extern IMPORT ARRAY* listToArray(LIST* pList);
extern IMPORT LIST* listFromArray(ARRAY* pArray);
extern IMPORT void listFreeArray(ARRAY** ppArray);

extern IMPORT void listDelNth(LIST** ppList, long n);
#define listDelFirst(ppList) listDelNth(ppList, 0)
#define listDelLast(ppList) listDelNth(ppList, -1)
extern IMPORT void listDelSlice(LIST** ppList, long n, long m);
extern IMPORT LIST* listPopNth(LIST** ppList, long n);
#define listPopFirst(ppList) listPopNth(ppList, 0)
#define listPopDequeue(ppList) listPopNth(ppList, 0)
#define listPop(ppList) listPopNth(ppList, -1)
extern IMPORT void listRemove(LIST** ppList, void* pValue, ETYPE type, size_t size);
extern IMPORT void listRemoveAll(LIST** ppList, void* pValue, ETYPE type, size_t size);
extern IMPORT void listRemoveDuplicates(LIST* pList);

extern IMPORT void listClear(LIST** ppList);
#define listDel(ppList) listClear(ppList)
#define listFree(ppList) listClear(ppList)

extern IMPORT void listSetStructSize(size_t size);
extern IMPORT void listSetStructComparator(int (*listStructComparator)(const void* pStruct1, const void* pStruct2));
extern IMPORT int listCompareStructByMemcmp(const void *p1, const void *p2);
extern IMPORT int listCompareStructReversed(const void *p1, const void *p2);
extern IMPORT void listSetStructStringer(void (*listStructStringer)(STRING buffer, void* pStruct, size_t size));
extern IMPORT void listStringStructByDefault(STRING buffer, void* pStruct, size_t size);
extern IMPORT void listSetStructPrinter(void (*listStructPrinter)(void* pStruct, size_t size));
extern IMPORT void listPrintStructByDefault(void* pStruct, size_t size);
extern IMPORT void listSetStructDebugger(void (*listStructDebugger)(void* pStruct, size_t size));
extern IMPORT void listDebugStructByDefault(void* pStruct, size_t size);

extern IMPORT void listSetDebugMessagesDisplay(BOOLEAN display);
extern IMPORT void listSetFatalMallocErrors(BOOLEAN fatal);
extern IMPORT unsigned long listGetAllocatedMemory();

// Convenience type-oriented aliases:
// NB: values are not passed by address
extern IMPORT STATUS listAppendChar(LIST** ppList, char value);
#define listPushChar listAppendChar
#define listEnqueueChar listAppendChar
extern IMPORT STATUS listInsertFirstChar(LIST** ppList, char value);
#define listPrependChar listInsertFirstChar
extern IMPORT STATUS listInsertChar(LIST** ppList, long n, char value);
extern IMPORT STATUS listInsertSortedChar(LIST** ppList, char value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
extern IMPORT STATUS listChangeChar(LIST* pList, long n, char value);
extern IMPORT BOOLEAN listContainsChar(LIST* pList, char value);
extern IMPORT long listCountChar(LIST* pList, char value);
extern IMPORT long listIndexChar(LIST* pList, char value);
extern IMPORT LIST* listIndexAllChar(LIST* pList, char value);
#define listFindChar listIndexAllChar
#define listSearchChar listIndexAllChar
extern IMPORT void listRemoveChar(LIST** ppList, char value);
extern IMPORT void listRemoveAllChar(LIST** ppList, char value);
extern IMPORT char listMinChar(LIST* pList);
extern IMPORT char listMaxChar(LIST* pList);
extern IMPORT long listSumChar(LIST* pList);
extern IMPORT int listCompareChar(const void *p1, const void *p2);
extern IMPORT int listCompareCharCaseInsensitive(const void *p1, const void *p2);
extern IMPORT int listCompareCharReversed(const void *p1, const void *p2);
extern IMPORT int listCompareCharCaseInsensitiveReversed(const void *p1, const void *p2);

extern IMPORT STATUS listAppendUChar(LIST** ppList, unsigned char value);
#define listPushUChar listAppendUChar
#define listEnqueueUChar listAppendUChar
extern IMPORT STATUS listInsertFirstUChar(LIST** ppList, unsigned char value);
#define listPrependUChar listInsertFirstUChar
extern IMPORT STATUS listInsertUChar(LIST** ppList, long n, unsigned char value);
extern IMPORT STATUS listInsertSortedUChar(LIST** ppList, unsigned char value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
extern IMPORT STATUS listChangeUChar(LIST* pList, long n, unsigned char value);
extern IMPORT BOOLEAN listContainsUChar(LIST* pList, unsigned char value);
extern IMPORT long listCountUChar(LIST* pList, unsigned char value);
extern IMPORT long listIndexUChar(LIST* pList, unsigned char value);
extern IMPORT LIST* listIndexAllUChar(LIST* pList, unsigned char value);
#define listFindUChar listIndexAllUChar
#define listSearchUChar listIndexAllUChar
extern IMPORT void listRemoveUChar(LIST** ppList, unsigned char value);
extern IMPORT void listRemoveAllUChar(LIST** ppList, unsigned char value);
extern IMPORT unsigned char listMinUChar(LIST* pList);
extern IMPORT unsigned char listMaxUChar(LIST* pList);
extern IMPORT unsigned long listSumUChar(LIST* pList);
extern IMPORT int listCompareUChar(const void *p1, const void *p2);
extern IMPORT int listCompareUCharCaseInsensitive(const void *p1, const void *p2);
extern IMPORT int listCompareUCharReversed(const void *p1, const void *p2);
extern IMPORT int listCompareUCharCaseInsensitiveReversed(const void *p1, const void *p2);

extern IMPORT STATUS listAppendShort(LIST** ppList, short value);
#define listPushShort listAppendShort
#define listEnqueueShort listAppendShort
extern IMPORT STATUS listInsertFirstShort(LIST** ppList, short value);
#define listPrependShort listInsertFirstShort
extern IMPORT STATUS listInsertShort(LIST** ppList, long n, short value);
extern IMPORT STATUS listInsertSortedShort(LIST** ppList, short value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
extern IMPORT STATUS listChangeShort(LIST* pList, long n, short value);
extern IMPORT BOOLEAN listContainsShort(LIST* pList, short value);
extern IMPORT long listCountShort(LIST* pList, short value);
extern IMPORT long listIndexShort(LIST* pList, short value);
extern IMPORT LIST* listIndexAllShort(LIST* pList, short value);
#define listFindShort listIndexAllShort
#define listSearchShort listIndexAllShort
extern IMPORT void listRemoveShort(LIST** ppList, short value);
extern IMPORT void listRemoveAllShort(LIST** ppList, short value);
extern IMPORT short listMinShort(LIST* pList);
extern IMPORT short listMaxShort(LIST* pList);
extern IMPORT long listSumShort(LIST* pList);
extern IMPORT int listCompareShort(const void *p1, const void *p2);
extern IMPORT int listCompareShortReversed(const void *p1, const void *p2);

extern IMPORT STATUS listAppendUShort(LIST** ppList, unsigned short value);
#define listPushUShort listAppendUShort
#define listEnqueueUShort listAppendUShort
extern IMPORT STATUS listInsertFirstUShort(LIST** ppList, unsigned short value);
#define listPrependUShort listInsertFirstUShort
extern IMPORT STATUS listInsertUShort(LIST** ppList, long n, unsigned short value);
extern IMPORT STATUS listInsertSortedUShort(LIST** ppList, unsigned short value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
extern IMPORT STATUS listChangeUShort(LIST* pList, long n, unsigned short value);
extern IMPORT BOOLEAN listContainsUShort(LIST* pList, unsigned short value);
extern IMPORT long listCountUShort(LIST* pList, unsigned short value);
extern IMPORT long listIndexUShort(LIST* pList, unsigned short value);
extern IMPORT LIST* listIndexAllUShort(LIST* pList, unsigned short value);
#define listFindUShort listIndexAllUShort
#define listSearchUShort listIndexAllUShort
extern IMPORT void listRemoveUShort(LIST** ppList, unsigned short value);
extern IMPORT void listRemoveAllUShort(LIST** ppList, unsigned short value);
extern IMPORT unsigned short listMinUShort(LIST* pList);
extern IMPORT unsigned short listMaxUShort(LIST* pList);
extern IMPORT unsigned long listSumUShort(LIST* pList);
extern IMPORT int listCompareUShort(const void *p1, const void *p2);
extern IMPORT int listCompareUShortReversed(const void *p1, const void *p2);

extern IMPORT STATUS listAppendInt(LIST** ppList, int value);
#define listPushInt listAppendInt
#define listEnqueueInt listAppendInt
extern IMPORT STATUS listInsertFirstInt(LIST** ppList, int value);
#define listPrependInt listInsertFirstInt
extern IMPORT STATUS listInsertInt(LIST** ppList, long n, int value);
extern IMPORT STATUS listInsertSortedInt(LIST** ppList, int value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
extern IMPORT STATUS listChangeInt(LIST* pList, long n, int value);
extern IMPORT BOOLEAN listContainsInt(LIST* pList, int value);
extern IMPORT long listCountInt(LIST* pList, int value);
extern IMPORT long listIndexInt(LIST* pList, int value);
extern IMPORT LIST* listIndexAllInt(LIST* pList, int value);
#define listFindInt listIndexAllInt
#define listSearchInt listIndexAllInt
extern IMPORT void listRemoveInt(LIST** ppList, int value);
extern IMPORT void listRemoveAllInt(LIST** ppList, int value);
extern IMPORT int listMinInt(LIST* pList);
extern IMPORT int listMaxInt(LIST* pList);
extern IMPORT long listSumInt(LIST* pList);
extern IMPORT int listCompareInt(const void *p1, const void *p2);
extern IMPORT int listCompareIntReversed(const void *p1, const void *p2);

extern IMPORT STATUS listAppendUInt(LIST** ppList, unsigned int value);
#define listPushUInt listAppendUInt
#define listEnqueueUInt listAppendUInt
extern IMPORT STATUS listInsertFirstUInt(LIST** ppList, unsigned int value);
#define listPrependUInt listInsertFirstUInt
extern IMPORT STATUS listInsertUInt(LIST** ppList, long n, unsigned int value);
extern IMPORT STATUS listInsertSortedUInt(LIST** ppList, unsigned int value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
extern IMPORT STATUS listChangeUInt(LIST* pList, long n, unsigned int value);
extern IMPORT BOOLEAN listContainsUInt(LIST* pList, unsigned int value);
extern IMPORT long listCountUInt(LIST* pList, unsigned int value);
extern IMPORT long listIndexUInt(LIST* pList, unsigned int value);
extern IMPORT LIST* listIndexAllUInt(LIST* pList, unsigned int value);
#define listFindUInt listIndexAllUInt
#define listSearchUInt listIndexAllUInt
extern IMPORT void listRemoveUInt(LIST** ppList, unsigned int value);
extern IMPORT void listRemoveAllUInt(LIST** ppList, unsigned int value);
extern IMPORT unsigned int listMinUInt(LIST* pList);
extern IMPORT unsigned int listMaxUInt(LIST* pList);
extern IMPORT unsigned long listSumUInt(LIST* pList);
extern IMPORT int listCompareUInt(const void *p1, const void *p2);
extern IMPORT int listCompareUIntReversed(const void *p1, const void *p2);

extern IMPORT STATUS listAppendLong(LIST** ppList, long value);
#define listPushLong listAppendLong
#define listEnqueueLong listAppendLong
extern IMPORT STATUS listInsertFirstLong(LIST** ppList, long value);
#define listPrependLong listInsertFirstLong
extern IMPORT STATUS listInsertLong(LIST** ppList, long n, long value);
extern IMPORT STATUS listInsertSortedLong(LIST** ppList, long value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
extern IMPORT STATUS listChangeLong(LIST* pList, long n, long value);
extern IMPORT BOOLEAN listContainsLong(LIST* pList, long value);
extern IMPORT long listCountLong(LIST* pList, long value);
extern IMPORT long listIndexLong(LIST* pList, long value);
extern IMPORT LIST* listIndexAllLong(LIST* pList, long value);
#define listFindLong listIndexAllLong
#define listSearchLong listIndexAllLong
extern IMPORT void listRemoveLong(LIST** ppList, long value);
extern IMPORT void listRemoveAllLong(LIST** ppList, long value);
extern IMPORT long listMinLong(LIST* pList);
extern IMPORT long listMaxLong(LIST* pList);
extern IMPORT long long listSumLong(LIST* pList);
extern IMPORT int listCompareLong(const void *p1, const void *p2);
extern IMPORT int listCompareLongReversed(const void *p1, const void *p2);

extern IMPORT STATUS listAppendULong(LIST** ppList, unsigned long value);
#define listPushULong listAppendULong
#define listEnqueueULong listAppendULong
extern IMPORT STATUS listInsertFirstULong(LIST** ppList, unsigned long value);
#define listPrependULong listInsertFirstULong
extern IMPORT STATUS listInsertULong(LIST** ppList, long n, unsigned long value);
extern IMPORT STATUS listInsertSortedULong(LIST** ppList, unsigned long value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
extern IMPORT STATUS listChangeULong(LIST* pList, long n, unsigned long value);
extern IMPORT BOOLEAN listContainsULong(LIST* pList, unsigned long value);
extern IMPORT long listCountULong(LIST* pList, unsigned long value);
extern IMPORT long listIndexULong(LIST* pList, unsigned long value);
extern IMPORT LIST* listIndexAllULong(LIST* pList, unsigned long value);
#define listFindULong listIndexAllULong
#define listSearchULong listIndexAllULong
extern IMPORT void listRemoveULong(LIST** ppList, unsigned long value);
extern IMPORT void listRemoveAllULong(LIST** ppList, unsigned long value);
extern IMPORT unsigned long listMinULong(LIST* pList);
extern IMPORT unsigned long listMaxULong(LIST* pList);
extern IMPORT unsigned long long listSumULong(LIST* pList);
extern IMPORT int listCompareULong(const void *p1, const void *p2);
extern IMPORT int listCompareULongReversed(const void *p1, const void *p2);

extern IMPORT STATUS listAppendLongLong(LIST** ppList, long long value);
#define listPushLongLong listAppendLongLong
#define listEnqueueLongLong listAppendLongLong
extern IMPORT STATUS listInsertFirstLongLong(LIST** ppList, long long value);
#define listPrependLongLong listInsertFirstLongLong
extern IMPORT STATUS listInsertLongLong(LIST** ppList, long n, long long value);
extern IMPORT STATUS listInsertSortedLongLong(LIST** ppList, long long value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
extern IMPORT STATUS listChangeLongLong(LIST* pList, long n, long long value);
extern IMPORT BOOLEAN listContainsLongLong(LIST* pList, long long value);
extern IMPORT long listCountLongLong(LIST* pList, long long value);
extern IMPORT long listIndexLongLong(LIST* pList, long long value);
extern IMPORT LIST* listIndexAllLongLong(LIST* pList, long long value);
#define listFindLongLong listIndexAllLongLong
#define listSearchLongLong listIndexAllLongLong
extern IMPORT void listRemoveLongLong(LIST** ppList, long long value);
extern IMPORT void listRemoveAllLongLong(LIST** ppList, long long value);
extern IMPORT long long listMinLongLong(LIST* pList);
extern IMPORT long long listMaxLongLong(LIST* pList);
extern IMPORT long long listSumLongLong(LIST* pList);
extern IMPORT int listCompareLongLong(const void *p1, const void *p2);
extern IMPORT int listCompareLongLongReversed(const void *p1, const void *p2);

extern IMPORT STATUS listAppendULongLong(LIST** ppList, unsigned long long value);
#define listPushULongLong listAppendULongLong
#define listEnqueueULongLong listAppendULongLong
extern IMPORT STATUS listInsertFirstULongLong(LIST** ppList, unsigned long long value);
#define listPrependULongLong listInsertFirstULongLong
extern IMPORT STATUS listInsertULongLong(LIST** ppList, long n, unsigned long long value);
extern IMPORT STATUS listInsertSortedULongLong(LIST** ppList, unsigned long long value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
extern IMPORT STATUS listChangeULongLong(LIST* pList, long n, unsigned long long value);
extern IMPORT BOOLEAN listContainsULongLong(LIST* pList, unsigned long long value);
extern IMPORT long listCountULongLong(LIST* pList, unsigned long long value);
extern IMPORT long listIndexULongLong(LIST* pList, unsigned long long value);
extern IMPORT LIST* listIndexAllULongLong(LIST* pList, unsigned long long value);
#define listFindULongLong listIndexAllULongLong
#define listSearchULongLong listIndexAllULongLong
extern IMPORT void listRemoveULongLong(LIST** ppList, unsigned long long value);
extern IMPORT void listRemoveAllULongLong(LIST** ppList, unsigned long long value);
extern IMPORT unsigned long long listMinULongLong(LIST* pList);
extern IMPORT unsigned long long listMaxULongLong(LIST* pList);
extern IMPORT unsigned long long listSumULongLong(LIST* pList);
extern IMPORT int listCompareULongLong(const void *p1, const void *p2);
extern IMPORT int listCompareULongLongReversed(const void *p1, const void *p2);

extern IMPORT STATUS listAppendFloat(LIST** ppList, float value);
#define listPushFloat listAppendFloat
#define listEnqueueFloat listAppendFloat
extern IMPORT STATUS listInsertFirstFloat(LIST** ppList, float value);
#define listPrependFloat listInsertFirstFloat
extern IMPORT STATUS listInsertFloat(LIST** ppList, long n, float value);
extern IMPORT STATUS listInsertSortedFloat(LIST** ppList, float value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
extern IMPORT STATUS listChangeFloat(LIST* pList, long n, float value);
extern IMPORT BOOLEAN listContainsFloat(LIST* pList, float value);
extern IMPORT long listCountFloat(LIST* pList, float value);
extern IMPORT long listIndexFloat(LIST* pList, float value);
extern IMPORT LIST* listIndexAllFloat(LIST* pList, float value);
#define listFindFloat listIndexAllFloat
#define listSearchFloat listIndexAllFloat
extern IMPORT void listRemoveFloat(LIST** ppList, float value);
extern IMPORT void listRemoveAllFloat(LIST** ppList, float value);
extern IMPORT float listMinFloat(LIST* pList);
extern IMPORT float listMaxFloat(LIST* pList);
extern IMPORT double listSumFloat(LIST* pList);
extern IMPORT int listCompareFloat(const void *p1, const void *p2);
extern IMPORT int listCompareFloatReversed(const void *p1, const void *p2);

extern IMPORT STATUS listAppendDouble(LIST** ppList, double value);
#define listPushDouble listAppendDouble
#define listEnqueueDouble listAppendDouble
extern IMPORT STATUS listInsertFirstDouble(LIST** ppList, double value);
#define listPrependDouble listInsertFirstDouble
extern IMPORT STATUS listInsertDouble(LIST** ppList, long n, double value);
extern IMPORT STATUS listInsertSortedDouble(LIST** ppList, double value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
extern IMPORT STATUS listChangeDouble(LIST* pList, long n, double value);
extern IMPORT BOOLEAN listContainsDouble(LIST* pList, double value);
extern IMPORT long listCountDouble(LIST* pList, double value);
extern IMPORT long listIndexDouble(LIST* pList, double value);
extern IMPORT LIST* listIndexAllDouble(LIST* pList, double value);
#define listFindDouble listIndexAllDouble
#define listSearchDouble listIndexAllDouble
extern IMPORT void listRemoveDouble(LIST** ppList, double value);
extern IMPORT void listRemoveAllDouble(LIST** ppList, double value);
extern IMPORT double listMinDouble(LIST* pList);
extern IMPORT double listMaxDouble(LIST* pList);
extern IMPORT long double listSumDouble(LIST* pList);
extern IMPORT int listCompareDouble(const void *p1, const void *p2);
extern IMPORT int listCompareDoubleReversed(const void *p1, const void *p2);

extern IMPORT STATUS listAppendLongDouble(LIST** ppList, long double value);
#define listPushLongDouble listAppendLongDouble
#define listEnqueueLongDouble listAppendLongDouble
extern IMPORT STATUS listInsertFirstLongDouble(LIST** ppList, long double value);
#define listPrependLongDouble listInsertFirstLongDouble
extern IMPORT STATUS listInsertLongDouble(LIST** ppList, long n, long double value);
extern IMPORT STATUS listInsertSortedLongDouble(LIST** ppList, long double value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
extern IMPORT STATUS listChangeLongDouble(LIST* pList, long n, long double value);
extern IMPORT BOOLEAN listContainsLongDouble(LIST* pList, long double value);
extern IMPORT long listCountLongDouble(LIST* pList, long double value);
extern IMPORT long listIndexLongDouble(LIST* pList, long double value);
extern IMPORT LIST* listIndexAllLongDouble(LIST* pList, long double value);
#define listFindLongDouble listIndexAllLongDouble
#define listSearchLongDouble listIndexAllLongDouble
extern IMPORT void listRemoveLongDouble(LIST** ppList, long double value);
extern IMPORT void listRemoveAllLongDouble(LIST** ppList, long double value);
extern IMPORT long double listMinLongDouble(LIST* pList);
extern IMPORT long double listMaxLongDouble(LIST* pList);
extern IMPORT long double listSumLongDouble(LIST* pList);
extern IMPORT int listCompareLongDouble(const void *p1, const void *p2);
extern IMPORT int listCompareLongDoubleReversed(const void *p1, const void *p2);

extern IMPORT STATUS listAppendString(LIST** ppList, STRING value);
#define listPushString listAppendString
#define listEnqueueString listAppendString
extern IMPORT STATUS listInsertFirstString(LIST** ppList, STRING value);
#define listPrependString listInsertFirstString
extern IMPORT STATUS listInsertString(LIST** ppList, long n, STRING value);
extern IMPORT STATUS listInsertSortedString(LIST** ppList, STRING value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates);
extern IMPORT STATUS listChangeString(LIST* pList, long n, STRING value);
extern IMPORT BOOLEAN listContainsString(LIST* pList, STRING value);
extern IMPORT long listCountString(LIST* pList, STRING value);
extern IMPORT long listIndexString(LIST* pList, STRING value);
extern IMPORT LIST* listIndexAllString(LIST* pList, STRING value);
#define listFindString listIndexAllString
#define listSearchString listIndexAllString
extern IMPORT void listRemoveString(LIST** ppList, STRING value);
extern IMPORT void listRemoveAllString(LIST** ppList, STRING value);
extern IMPORT int listCompareString(const void *p1, const void *p2);
extern IMPORT int listCompareStringReversed(const void *p1, const void *p2);
extern IMPORT int listCompareStringCaseInsensitive(const void *p1, const void *p2);
extern IMPORT int listCompareStringCaseInsensitiveReversed(const void *p1, const void *p2);

#endif // PYLISTS4C_H
