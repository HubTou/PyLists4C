// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listSort()
//     Sorts a LIST
// PARAMETERS:
//     ppList: A pointer to a pointer to a LIST
//     reversed: A BOOLEAN indicating the sort order
//     caseInsensitive: A BOOLEAN specifying how to handle char and STRING
//     noDuplicates: A BOOLEAN indicating if duplicate values are discarded
// RETURN CODE:
//     A STATUS code
/******************************************************************************/
EXPORT STATUS listSort(LIST** ppList, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates)
{
    LIST* pSortedList = NULL;

    if (*ppList != NULL)
    {
        pSortedList = listSorted(*ppList, reversed, caseInsensitive, noDuplicates);
        if (pSortedList == NULL)
            return FAILURE;

        listClear(ppList);
        *ppList = pSortedList;
    }

    return SUCCESS;
}

