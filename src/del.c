// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>
#include "global.h"

/******************************************************************************/
// FUNCTION: listDelNth()
// ALIAS: listDelFirst()
// ALIAS: listDelLast()
//     Removes the element at the specified position
// PARAMETERS:
//     ppList: A pointer to a pointer to a LIST
//     n: the Nth element to be removed (numbered from 0)
/******************************************************************************/
EXPORT void listDelNth(LIST** ppList, long n)
{
    LIST* pNthElement = listGet(*ppList, n);

    if (pNthElement != NULL)
    {
        if (pNthElement -> pPrevious == NULL)
        {
            // First and only element
            if (pNthElement -> pNext == NULL)
                *ppList = NULL;
            // First element
            else
            {
                *ppList = pNthElement -> pNext;
                pNthElement -> pNext -> pPrevious = NULL;
            }
        }
        // Another element
        else
        {
            pNthElement -> pPrevious -> pNext = pNthElement -> pNext;
            if (pNthElement -> pNext != NULL)
                pNthElement -> pNext -> pPrevious = pNthElement -> pPrevious;
        }

        if (pNthElement -> type == ETYPE_LIST)
            listClear((LIST **) &(pNthElement -> pValue));
        else
            free(pNthElement -> pValue);
        free(pNthElement);

        listAllocatedMemory -= sizeof(LIST) + pNthElement -> size;
    }
}

