// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listInsert()
//     Inserts an element at the Nth position of a LIST
// PARAMETERS:
//     ppList: A pointer to a pointer to a LIST
//     n: The Nth element where to do the insert
//     pValue: A pointer to the new value
//     type: The ETYPE of that value
//     size: The size in bytes of that value
// RETURN VALUE:
//     A STATUS code
/******************************************************************************/
EXPORT STATUS listInsert(LIST** ppList, long n, void* pValue, ETYPE type, size_t size)
{
    LIST* pElement = NULL;

    if ((pElement = listCreateElement(pValue, type, size)) == NULL)
        return FAILURE;

    if (*ppList == NULL)
        *ppList = pElement;
    else
    {
        LIST* pTarget = NULL;

        // Insertion at the indicated place
        pTarget = listGet(*ppList, n);
        if (pTarget != NULL)
        {
            if (pTarget -> pPrevious != NULL)
            {
                pTarget -> pPrevious -> pNext = pElement;
                pElement -> pPrevious = pTarget -> pPrevious;
            }
            // Insertion at the start of the LIST
            else
                *ppList = pElement;
            pElement -> pNext = pTarget;
            pTarget -> pPrevious = pElement;
        }

        // Insertion at the end of the LIST
        else
        {
            pTarget = listGetLast(*ppList);

            pTarget -> pNext = pElement;
            pElement -> pPrevious = pTarget;
        }
    }

    return SUCCESS;
}

