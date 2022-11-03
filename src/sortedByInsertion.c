// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listSortedByInsertion()
//     Returns a sorted copy of a LIST, using an insertion sort algorithm
// PARAMETERS:
//     pList: A pointer to a LIST
//     reversed: A BOOLEAN indicating the sort order
//     caseInsensitive: A BOOLEAN specifying how to handle char and STRING
//     noDuplicates: A BOOLEAN indicating if duplicate values are discarded
// RETURN VALUE:
//     A pointer to the sorted copy of the LIST
/******************************************************************************/
EXPORT LIST* listSortedByInsertion(LIST* pList, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates)
{
    LIST* pSortedList = NULL;
    LIST* pElement = NULL;

    for (pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (listInsertSorted(&pSortedList, pElement -> pValue, pElement -> type, pElement -> size, reversed, caseInsensitive, noDuplicates) == FAILURE)
        {
            listClear(&pSortedList);
            return NULL;
        }

    return pSortedList;
}

