// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <string.h>

#include <pylists4c.h>

size_t listStructSize;
int (*listCompareStruct)(const void* pStruct1, const void* pStruct2) = listCompareStructByMemcmp;
void (*listStringStruct)(STRING buffer, void* pStruct, size_t size) = listStringStructByDefault;
void (*listPrintStruct)(void* pStruct, size_t size) = listPrintStructByDefault;
void (*listDebugStruct)(void* pStruct, size_t size) = listDebugStructByDefault;

/******************************************************************************/
// FUNCTION: listSetStructSize()
//     Sets the size of a STRUCT you want to compare
// PARAMETERS:
//     size: The size of the STRUCT in bytes
// CAVEATS:
//     This is an horrible kludge! Because we sometimes use standard C *sort()
//     functions that take comparison functions with 2 parameters, we hide the
//     third argument of memcmp() in a global variable
/******************************************************************************/
EXPORT void listSetStructSize(size_t size)
{
    listStructSize = size;
}

/******************************************************************************/
// FUNCTION: listCompareStructByMemcmp()
//     Default handling of STRUCTs comparison
// PARAMETERS:
//     p1: A pointer to the first STRUCT
//     p2: A pointer to the second STRUCT
// RETURN VALUE:
//     The result of the comparison: -1 meaning before, 0 equal and +1 after
/******************************************************************************/
EXPORT int listCompareStructByMemcmp(const void *p1, const void *p2)
{
    return memcmp(p1, p2, listStructSize);
}

/******************************************************************************/
// FUNCTION: listCompareStructReversed()
//     Compare STRUCTs elements in reverse order
// PARAMETERS:
//     p1: A pointer to the first STRUCT
//     p2: A pointer to the second STRUCT
// RETURN VALUE:
//     The result of the comparison: -1 meaning after, 0 equal and +1 before
/******************************************************************************/
EXPORT int listCompareStructReversed(const void *p1, const void *p2)
{
    return -1 * listCompareStruct(p1, p2);
}

/******************************************************************************/
// FUNCTION: listXXXStructByDefault()
//     Default handling of STRUCTs {stringing, printing, debugging}
// PARAMETERS:
//     pStruct: A pointer to a STRUCT
//     size: The size of the STRUCT in bytes
/******************************************************************************/
EXPORT void listStringStructByDefault(STRING buffer, void* pStruct, size_t size)
{
    char hexa[4];

    buffer[0] = 0;
    for (size_t i = 0; i < size; i++)
    {
        sprintf(hexa, "%02X ", *(((char*) pStruct) + i));
#if ! (defined(_WIN32) || defined(_WIN64) )
        strcat(buffer, hexa);
#else
        strcat_s(buffer, 4, hexa);
#endif
    }
}

EXPORT void listPrintStructByDefault(void* pStruct, size_t size)
{
    for (size_t i = 0; i < size; i++)
        printf("%02X ", *(((char*) pStruct) + i));
}

EXPORT void listDebugStructByDefault(void* pStruct, size_t size)
{
    for (size_t i = 0; i < size; i++)
        fprintf(stderr, "%02X ", *(((char*) pStruct) + i));
}

/******************************************************************************/
// FUNCTION: listSetStructXXX()
//     Sets the function to be used to {compare, print, debug} STRUCTs
// PARAMETERS:
//     listStructXXX: A pointer to a user-defined function
/******************************************************************************/
EXPORT void listSetStructComparator(int (*listStructComparator)(const void* pStruct1, const void* pStruct2))
{
    listCompareStruct = listStructComparator;
}

EXPORT void listSetStructStringer(void (*listStructStringer)(STRING buffer, void* pStruct, size_t size))
{
    listStringStruct = listStructStringer;
}

EXPORT void listSetStructPrinter(void (*listStructPrinter)(void* pStruct, size_t size))
{
    listPrintStruct = listStructPrinter;
}

EXPORT void listSetStructDebugger(void (*listStructDebugger)(void* pStruct, size_t size))
{
    listDebugStruct = listStructDebugger;
}

