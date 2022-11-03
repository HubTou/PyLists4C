// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listClear()
// ALIAS: listDel()
// ALIAS: listFree()
//     Removes all the elements from the LIST
// PARAMETERS:
//     ppList: A pointer to a pointer to a LIST
/******************************************************************************/
EXPORT void listClear(LIST** ppList)
{
    while (*ppList != NULL)
        listDelFirst(ppList);
}

