// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listGetLast()
//     Returns the last LIST_ELEMENT of a LIST
// PARAMETERS:
//     pList: A pointer to a LIST
// RETURN VALUE:
//     A pointer to the last element of the LIST
/******************************************************************************/
EXPORT LIST_ELEMENT listGetLast(LIST* pList)
{
    if (pList != NULL)
        while (pList -> pNext != NULL)
            pList = pList -> pNext;

    return pList;
}

