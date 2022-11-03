// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listComprehension()
// ALIAS: listForEach()
//     Returns a new LIST according to a user defined function producing 0-N
//     elements for each LIST_ELEMENT
// PARAMETERS:
//     pList: A pointer to a LIST
//     pMyListComprehensionFunction: A pointer to a user defined function
//                                   returning a 0-N elements LIST given a
//                                   LIST_ELEMENT
// RETURN VALUE:
//     A pointer to the new LIST
/******************************************************************************/
EXPORT LIST* listComprehension(LIST* pList, LIST* (*pMyListComprehensionFunction)(LIST_ELEMENT element))
{
    LIST* pNewList = NULL;
    LIST* pNewListTail = NULL;

    LIST_ITERATOR i = pList;
    LIST_ELEMENT element;

    while ((element = listNext(&i)) != NULL)
    {
        LIST* pSubList = pMyListComprehensionFunction(element);

        // If the list comprehension function has returned something
        if (pSubList != NULL)
        {
            LIST* pSubListTail = listGetLast(pSubList);

            // If the new LIST was empty, we now have a head
            if (pNewList == NULL)
                pNewList = pSubList;
            // Else we append the sub LIST to the new LIST
            else
            {
                pNewListTail -> pNext = pSubList;
                pSubList -> pPrevious = pNewListTail;
            }

            // And we now have a new tail
            pNewListTail = pSubListTail;
        }
    }

    return pNewList;
}

