// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <string.h>

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listIndexAll()
// ALIAS: listFind()
// ALIAS: listSearch()
//     Returns a LIST of all the indexes of the elements with the specified value
// PARAMETERS:
//     pList: A pointer to a LIST
//     pValue: A pointer to the searched value
//     type: The ETYPE of that value
//     size: The size in bytes of that value
// RETURN VALUE:
//     A LIST of indexes
/******************************************************************************/
EXPORT LIST* listIndexAll(LIST* pList, void* pValue, ETYPE type, size_t size)
{
    LIST* pIndexes = NULL;
    LIST* pElement = pList;

    for (long i = 0; pElement != NULL; pElement = pElement -> pNext, i++)
        if (pElement -> type == type)
        {
            if (type == ETYPE_LIST)
            {
                if (listAreEqual(pElement -> pValue, pValue, FALSE))
                    if (listAppendLong(&pIndexes, i) == FAILURE)
                    {
                        listClear(&pIndexes);
                        return NULL;
                    }
            }
            else if (type == ETYPE_STRUCT)
            {
                if (pElement -> size == size && ! memcmp(pElement -> pValue, pValue, size))
                    if (listAppendLong(&pIndexes, i) == FAILURE)
                    {
                        listClear(&pIndexes);
                        return NULL;
                    }
            }
            else if (type == ETYPE_NULL || ! memcmp(pElement -> pValue, pValue, size))
                if (listAppendLong(&pIndexes, i) == FAILURE)
                {
                    listClear(&pIndexes);
                    return NULL;
                }
        }

    return pIndexes;
}

