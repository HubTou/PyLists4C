// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>
#include "global.h"

/******************************************************************************/
// FUNCTION: listDelSlice(n, m)
//     Removes the elements at the specified slice
// PARAMETERS:
//     ppList: A pointer to a pointer to a LIST
//     n: The included lower bound of the slice (numbered from 0 or -len(pList))
//     m: The excluded upper bound of the slice (numbered from len(pList) or 0)
/******************************************************************************/
EXPORT void listDelSlice(LIST** ppList, long n, long m)
{
    LIST* pSubListToDelete = NULL;

    // Empty slice!
    if (n >= m)
    {
        if (listDebugMessages)
            fprintf(stderr, "WARNING: slice [%ld:%ld] is invalid\n", n, m);
        return;
    }

    pSubListToDelete = listGet(*ppList, n);
    
    if (pSubListToDelete != NULL)
    {
        LIST_ITERATOR i = pSubListToDelete;
        LIST_ELEMENT e = NULL;

        for (long j = m - n; j > 0; j--)
            if ((e = listNext(&i)) == NULL)
                break;

        // Does the sublist includes the head of the list?
        if (pSubListToDelete -> pPrevious == NULL)
        {
            // We change the head of the list
            *ppList = i;

            // Does the sublist NOT includes the tail of the list?
            if (i != NULL)
            {
                // The sublist is cut to its last element
                i -> pPrevious -> pNext = NULL;

                // The predecessor of the first element after the sublist is set
                i -> pPrevious = NULL;
            }
        }
        else
        {
            // The successor to the last element before the sublist is set to the first one after:
            pSubListToDelete -> pPrevious -> pNext = i;

            // Does the sublist NOT includes the tail of the list?
            if (i != NULL)
            {
                // The sublist is cut to its last element
                i -> pPrevious -> pNext = NULL;

                // The predecessor of the first element after the sublist is set
                i -> pPrevious = pSubListToDelete -> pPrevious;
            }
        }

        // The sublist has no predecessor
        pSubListToDelete -> pPrevious = NULL;

        // The sublist is finally deleted in one shot
        listClear(&pSubListToDelete);
    }
}

