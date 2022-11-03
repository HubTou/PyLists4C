// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listJoin()
//     Moves the elements of the second LIST to the end of the first one
// PARAMETERS:
//     ppList1: A pointer to a pointer to the first LIST
//     ppList2: A pointer to a pointer to the second LIST
/******************************************************************************/
EXPORT void listJoin(LIST** ppList1, LIST** ppList2)
{
    LIST* pEndList1 = listGetLast(*ppList1);

    if (*ppList1 == NULL)
        *ppList1 = *ppList2;
    else
    {
        pEndList1 -> pNext = *ppList2;
        (*ppList2) -> pPrevious = pEndList1;
    }
    *ppList2 = NULL;
}

