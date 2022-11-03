// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <string.h>

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listIndex()
//     Returns the index of the first element with the specified value
// PARAMETERS:
//     pList: A pointer to a LIST
//     pValue: A pointer to the searched value
//     type: The ETYPE of that value
//     size: The size in bytes of that value
// RETURN VALUE:
//     A 0+ value to indicate the index, or -1 if the value wasn't found
/******************************************************************************/
EXPORT long listIndex(LIST* pList, void* pValue, ETYPE type, size_t size)
{
    LIST* pElement = pList;

    for (long i = 0; pElement != NULL; pElement = pElement -> pNext, i++)
        if (pElement -> type == type)
        {
            if (type == ETYPE_LIST)
            {
                if (listAreEqual(pElement -> pValue, pValue, FALSE))
                    return i;
            }
            else if (type == ETYPE_STRUCT)
            {
                if (pElement -> size == size && ! memcmp(pElement -> pValue, pValue, size))
                    return i;
            }
            else if (! memcmp(pElement -> pValue, pValue, size))
                return i;
        }

    return -1;
}

