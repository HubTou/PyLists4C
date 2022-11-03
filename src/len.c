// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listLen()
//     Returns the number of elements in a LIST
// PARAMETERS:
//     pList: A pointer to a LIST
// RETURN VALUE:
//     The number of elements in the LIST
/******************************************************************************/
EXPORT long listLen(LIST* pList)
{
    long length = 0;
    LIST* pElement = pList;

    if (pList == NULL)
        return 0;
    length++;

    while (pElement -> pNext != NULL)
    {
        pElement = pElement -> pNext;
        length++;
    }

    return length;
}

