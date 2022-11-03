// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

#ifndef PYLISTS4C_GLOBAL_H
#define PYLISTS4C_GLOBAL_H
/******************************************************************************/
// Library "private" global variables
/******************************************************************************/

// Default STRUCT handling functions (cf. struct.c):
extern size_t listStructSize; // No default
extern int (*listCompareStruct)(const void* pStruct1, const void* pStruct2); // Default is listCompareStructByMemcmp
extern void (*listStringStruct)(STRING buffer, void* pStruct, size_t size); // Default is listStringStructByDefault
extern void (*listPrintStruct)(void* pStruct, size_t size); // Default is listPrintStructByDefault
extern void (*listDebugStruct)(void* pStruct, size_t size); // Default is listDebugStructByDefault

// Printing debugging messages state (cf. setDebugMessages.c):
extern BOOLEAN listDebugMessages; // Default is TRUE
 
// Fatal malloc errors state (cf. setFatalMallocErrors.c):
extern BOOLEAN listFatalMallocErrors; // Default is FALSE

// Default sorting algorithm (cf. sorted.c):
extern LIST* (*listSortedAlgorithm)(LIST* pList, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates); // Default is listSortedByInsertion

// Allocated memory in bytes (cf. getAllocatedMemory.c):
extern unsigned long listAllocatedMemory; // Default is 0

// Separator used in Python-style list declaration strings (cf. list.c):
extern char listSeparator; // Default is ','

#endif // PYLISTS4C_GLOBAL_H
