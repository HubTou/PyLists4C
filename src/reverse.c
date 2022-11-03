// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listReverse()
//     Reverses the order of a LIST
// PARAMETERS:
//     ppList: A pointer to a pointer of a LIST
/******************************************************************************/
EXPORT void listReverse(LIST** ppList)
{
    LIST* pLastElement = NULL;
    LIST* pElement;

    // We permute next and previous pointers, so next element will be the previous one!
    for (pElement = *ppList; pElement != NULL; pLastElement = pElement, pElement = pElement -> pPrevious)
    {
        LIST* pCopy = NULL;

        pCopy = pElement -> pNext;
        pElement -> pNext = pElement -> pPrevious;
        pElement -> pPrevious = pCopy;
    }

    // And finally set the LIST pointer to its last element
    *ppList = pLastElement;
}

