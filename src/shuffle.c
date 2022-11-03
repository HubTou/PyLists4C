// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listShuffle()
//     Shuffles a LIST
// PARAMETERS:
//     ppList: A pointer to a pointer to a LIST
// RETURN CODE:
//     A STATUS code
/******************************************************************************/
EXPORT STATUS listShuffle(LIST** ppList)
{
    LIST* pShuffledList = NULL;

    if (*ppList != NULL)
    {
        pShuffledList = listShuffled(*ppList);
        if (pShuffledList == NULL)
            return FAILURE;

        listClear(ppList);
        *ppList = pShuffledList;
    }

    return SUCCESS;
}

