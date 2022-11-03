// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listChangeSlice()
//     Replaces the elements at the defined LIST slice with those from the second LIST
// PARAMETERS:
//     ppTarget: A pointer to a pointer to the target LIST
//     n: The included lower bound of the slice (numbered from 0 or -len(pList))
//     m: The excluded upper bound of the slice (numbered from len(pList) or 0)
//     pSource: A pointer to the source LIST
/******************************************************************************/
EXPORT void listChangeSlice(LIST** ppTarget, long n, long m, LIST* pSource)
{
    listDelSlice(ppTarget, n, m);
    listInsertList(ppTarget, n, pSource);
}

