// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listInsertList()
//     Inserts a copy of the elements of a LIST at the Nth position of another LIST
// PARAMETERS:
//     ppTarget: A pointer to a pointer to the target LIST
//     n: The Nth element where to do the insert
//     pSource: A pointer to the source LIST
/******************************************************************************/
EXPORT void listInsertList(LIST** ppTarget, long n, LIST* pSource)
{
    LIST* pElements = NULL;
    LIST* pPosition = NULL;
    LIST* pTail = NULL;

    if (pSource == NULL)
        // Empty source: nothing to do
        return;

    pElements = listCopy(pSource);

    if (*ppTarget == NULL)
    {
        // Empty target: the source copy becomes the list
        *ppTarget = pElements;
        return;
    }

    pPosition = listGet(*ppTarget, n);

    if (pPosition == NULL)
    {
        // Insert at the end of the target list
        pTail = listGetLast(*ppTarget);
        pTail -> pNext = pElements;
        pElements -> pPrevious = pTail;
    }
    else
    {
        pTail = listGetLast(pElements);

        if (pPosition -> pPrevious == NULL)
        {
            // Insert at the start of the target list
            pTail -> pNext = pPosition;
            pPosition -> pPrevious = pTail;
            *ppTarget = pElements;
        }
        else
        {
            // Insert inside the target list
            pPosition -> pPrevious -> pNext = pElements;
            pElements -> pPrevious = pPosition -> pPrevious;
            pTail -> pNext = pPosition;
            pPosition -> pPrevious = pTail;
        }
    }
}

