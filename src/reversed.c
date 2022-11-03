// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listReversed()
//     Returns a reversed copy of a LIST
// PARAMETERS:
//     pList: A pointer to a LIST
// RETURN VALUE:
//     A pointer to the reversed copy of the LIST
/******************************************************************************/
EXPORT LIST* listReversed(LIST* pList)
{
    LIST* pReversedList = NULL;
    LIST* pElement = NULL;

    for (pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (listInsertFirst(&pReversedList, pElement -> pValue, pElement -> type, pElement -> size) == FAILURE)
        {
            listClear(&pReversedList);
            return NULL;
        }

    return pReversedList;
}

