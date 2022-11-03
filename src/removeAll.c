// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listRemoveAll()
//     Removes all the items with the specified value
// PARAMETERS:
//     ppList: A pointer to a pointer to a LIST
//     pValue: A pointer to the value to be removed
//     type: The ETYPE of that value
//     size: The size in bytes of that value
/******************************************************************************/
EXPORT void listRemoveAll(LIST** ppList, void* pValue, ETYPE type, size_t size)
{
    long index;

    while ((index = listIndex(*ppList, pValue, type, size) >= 0))
        listDelNth(ppList, index);
}

