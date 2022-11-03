// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listAppend()
// ALIAS: listPush()
// ALIAS: listEnqueue()
//     Adds an element at the end of a LIST
// PARAMETERS:
//     ppList: a pointer to a pointer to a LIST
//     pValue: a pointer to the new value
//     type: the ETYPE of that value
//     size: the size in bytes of that value
// RETURN VALUE:
//     A STATUS code
/******************************************************************************/
EXPORT STATUS listAppend(LIST** ppList, void* pValue, ETYPE type, size_t size)
{
    LIST* pElement = NULL;

    if ((pElement = listCreateElement(pValue, type, size)) == NULL)
        return FAILURE;

    if (*ppList == NULL)
        *ppList = pElement;
    else
    {
        LIST* pEnd = listGetLast(*ppList);

        pEnd -> pNext = pElement;
        pElement -> pPrevious = pEnd;
    }

    return SUCCESS;
}

