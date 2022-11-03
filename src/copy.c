// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listCopy()
//     Returns a copy of the LIST (a full/deep copy as we don't want multiple
//     references to the same values)
// PARAMETERS:
//     pList: A pointer to a LIST
// RETURN VALUE:
//     A pointer to the copy of the LIST
/******************************************************************************/
EXPORT LIST* listCopy(LIST* pList)
{
    LIST* pListCopy = NULL;

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (listAppend(&pListCopy, pElement -> pValue, pElement -> type, pElement -> size) == FAILURE)
        {
            listClear(&pListCopy);
            return NULL;
        }

    return pListCopy;
}

