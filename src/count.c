// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <string.h>

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listCount()
//     Returns the number of elements with the specified value
// PARAMETERS:
//     pList: A pointer to a LIST
//     pValue: A pointer to the searched value
//     type: The ETYPE of that value
//     size: The size in bytes of that value
// RETURN VALUE:
//     A value giving the number of occurrences
/******************************************************************************/
EXPORT long listCount(LIST* pList, void* pValue, ETYPE type, size_t size)
{
    long count = 0;
    LIST* pElement = pList;

    for (; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == type)
        {
            if (type == ETYPE_LIST)
            {
                if (listAreEqual(pElement -> pValue, pValue, FALSE))
                    count++;
            }
            else if (type == ETYPE_NULL)
                count++;
            else if (! memcmp(pElement -> pValue, pValue, size))
                count++;
        }

    return count;
}

