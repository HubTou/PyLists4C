// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listPopNth()
// ALIAS: listPop()
//     Removes the element at the specified position and returns it
//     (you'll have to free it after use with listClear())
// PARAMETERS:
//     ppList: A pointer to a pointer to a LIST
//     n: the Nth element to be removed (numbered from 0)
// RETURN VALUE:
//     A pointer to the element that was popped from the list
/******************************************************************************/
EXPORT LIST* listPopNth(LIST** ppList, long n)
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
                (*ppList) -> pPrevious = NULL;
                pNthElement -> pNext = NULL;
            }
        }
        // Another element
        else
        {
            pNthElement -> pPrevious -> pNext = pNthElement -> pNext;
            // But not the last one
            if (pNthElement -> pNext != NULL)
            {
                pNthElement -> pNext -> pPrevious = pNthElement -> pPrevious;
                pNthElement -> pNext = NULL;
            }
            pNthElement -> pPrevious = NULL;
        }
    }

    return pNthElement;
}

