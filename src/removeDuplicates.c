// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <string.h>

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listRemoveDuplicates()
//     Removes adjacent duplicate items in a sorted LIST
// PARAMETERS:
//     pList: A pointer to a LIST
/******************************************************************************/
EXPORT void listRemoveDuplicates(LIST* pList)
{
    ETYPE lastType = ETYPE_UNDEFINED;
    size_t lastSize = 0;
    void* lastValue = NULL;
    LIST* pLastElement = NULL;
    LIST* pDuplicates = NULL;

    for (; pList != NULL; pList = pList -> pNext)
    {
        if (pList -> type != lastType)
        {
            lastType = pList -> type;
            lastSize = pList -> size;
            lastValue = pList -> pValue;
            if (pDuplicates != NULL)
            {
                pLastElement -> pNext = pList;
                pList -> pPrevious -> pNext = NULL;
                pList -> pPrevious = pLastElement;
                listClear(&pDuplicates);
                // pDuplicates is NULL after that
            }
        }
        else if (pList -> size != lastSize)
        {
            lastSize = pList -> size;
            lastValue = pList -> pValue;
            if (pDuplicates != NULL)
            {
                pLastElement -> pNext = pList;
                pList -> pPrevious -> pNext = NULL;
                pList -> pPrevious = pLastElement;
                listClear(&pDuplicates);
                // pDuplicates is NULL after that
            }
        }
        else if ((pList -> type == ETYPE_LIST && listAreEqual(pList -> pValue, lastValue, FALSE)) || ! memcmp(pList -> pValue, lastValue, lastSize))
        {
            if (pDuplicates == NULL)
            {
                // A duplicate
                pLastElement = pList -> pPrevious;
                pDuplicates = pList;
                pDuplicates -> pPrevious = NULL;
            }
            // else
                // Another duplicate
        }
        else
        {
            lastValue = pList -> pValue;
            if (pDuplicates != NULL)
            {
                pLastElement -> pNext = pList;
                pList -> pPrevious -> pNext = NULL;
                pList -> pPrevious = pLastElement;
                listClear(&pDuplicates);
                // pDuplicates is NULL after that
            }
        }
    }

    if (pDuplicates != NULL)
    {
        pLastElement -> pNext = NULL;
        listClear(&pDuplicates);
    }
}

