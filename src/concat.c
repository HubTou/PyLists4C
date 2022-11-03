// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listConcat()
//     Returns a new LIST with the concatenation of the elements of LIST1 and LIST2
// PARAMETERS:
//     pList1: A pointer to the first LIST
//     pList2: A pointer to the second LIST
// RETURN VALUE:
//     A pointer to the first element of the new LIST
/******************************************************************************/
EXPORT LIST* listConcat(LIST* pList1, LIST* pList2)
{
    LIST* pCopyList1 = listCopy(pList1);
    LIST* pEndList1 = listGetLast(pCopyList1);
    LIST* pCopyList2 = listCopy(pList2);

    if (pCopyList1 == NULL)
        return pCopyList2;

    pEndList1 -> pNext = pCopyList2;
    pCopyList2 -> pPrevious = pEndList1;

    return pCopyList1;
}

