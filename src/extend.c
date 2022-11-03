// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listExtend()
//     Adds a copy of the elements of the second LIST to the end of the first one
// PARAMETERS:
//     ppList1: A pointer to a pointer to the first LIST
//     pList2: A pointer to the second LIST
/******************************************************************************/
EXPORT void listExtend(LIST** ppList1, LIST* pList2)
{
    LIST* pEndList1 = listGetLast(*ppList1);
    LIST* pCopyList2 = listCopy(pList2);

    if (*ppList1 == NULL)
        *ppList1 = pCopyList2;
    else
    {
        pEndList1 -> pNext = pCopyList2;
        pCopyList2 -> pPrevious = pEndList1;
    }
}

