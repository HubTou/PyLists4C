// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listFilter()
//     Returns a filtered copy of the LIST according to a user defined function
//     telling if an LIST_ELEMENT should be included or not
// PARAMETERS:
//     pList: A pointer to a LIST
//     pMyInclusionFunction: A pointer to a user defined function returning TRUE if a given LIST_ELEMENT should be included
// RETURN VALUE:
//     A pointer to the filtered copy of the LIST
/******************************************************************************/
EXPORT LIST* listFilter(LIST* pList, BOOLEAN (*pMyInclusionFunction)(LIST_ELEMENT element))
{
    LIST* pFilteredList = NULL;
    LIST_ITERATOR i = pList;
    LIST_ELEMENT element;

    while ((element = listNext(&i)) != NULL)
        if (pMyInclusionFunction(element))
            if (listAppend(&pFilteredList, element -> pValue, element -> type, element -> size) == FAILURE)
            {
                listClear(&pFilteredList);
                return NULL;
            }

    return pFilteredList;
}

