// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listInsertFirst()
// ALIAS: listPrepend()
//     Adds an element at the start of a LIST
// PARAMETERS:
//     ppList: A pointer to a pointer to a LIST
//     pValue: A pointer to the new value
//     type: The ETYPE of that value
//     size: The size in bytes of that value
// RETURN VALUE:
//     A STATUS code
/******************************************************************************/
EXPORT STATUS listInsertFirst(LIST** ppList, void* pValue, ETYPE type, size_t size)
{
    LIST* pElement = NULL;

    if ((pElement = listCreateElement(pValue, type, size)) == NULL)
        return FAILURE;

    if (*ppList != NULL)
    {
        pElement -> pNext = *ppList;
        (*ppList) -> pPrevious = pElement;
    }
    *ppList = pElement;

    return SUCCESS;
}

