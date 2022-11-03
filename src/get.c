// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listGet()
//     Returns the Nth LIST_ELEMENT of a LIST
// PARAMETERS:
//     pList: A pointer to a LIST
//     n: the Nth element seeked (numbered from 0)
// RETURN VALUE:
//     A pointer to the Nth element of the LIST or NULL if n is greater than the
//     length of the LIST
/******************************************************************************/
EXPORT LIST_ELEMENT listGet(LIST* pList, long n)
{
    LIST* pElement;

    if (n >= 0)
    {
        pElement = pList;
        for (long i = 0; i < n && pElement != NULL; i++)
            pElement = pElement -> pNext;
    }
    else
    {
        pElement = listGetLast(pList);
        for (long i = -1; i > n && pElement != NULL; i--)
            pElement = pElement -> pPrevious;
    }

    return pElement;
}

