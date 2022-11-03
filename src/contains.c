// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <string.h>

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listContains()
//     Tests if a value appears in a LIST
// PARAMETERS:
//     pList: A pointer to a LIST
//     pValue: A pointer to the searched value
//     type: The ETYPE of that value
//     size: The size in bytes of that value
// RETURN VALUE:
//     A BOOLEAN giving the answer
// CAVEATS:
//     The value tested has to be of the same type, and for STRUCTs to be of
//     the same size (i.e.: int 2 is different form long 2).
/******************************************************************************/
EXPORT BOOLEAN listContains(LIST* pList, void* pValue, ETYPE type, size_t size)
{
    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == type)
        {
            if (type == ETYPE_LIST)
            {
                if (listAreEqual(pElement -> pValue, pValue, FALSE))
                    return TRUE;
            }
            else if (type == ETYPE_STRUCT)
            {
                if (pElement -> size == size && ! memcmp(pElement -> pValue, pValue, size))
                    return TRUE;
            }
            else if (! memcmp(pElement -> pValue, pValue, size))
                return TRUE;
        }

    return FALSE;
}

