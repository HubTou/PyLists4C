// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listSplit(n)
//     Cuts a LIST in two parts and returns a pointer to the second part
// PARAMETERS:
//     ppList: A pointer to a pointer to a LIST
//     n: The index of the first element of the second part of the LIST
// RETURN VALUE:
//     A pointer to the second part of the LIST
/******************************************************************************/
EXPORT LIST* listSplit(LIST** ppList, long n)
{
    LIST* pPart2 = NULL;

    if (*ppList == NULL)
        return NULL;

    if (n == 0)
    {
        pPart2 = *ppList;
        *ppList = NULL;
    }
    else
    {
        LIST* pFirstElement = listGet(*ppList, n);

        if (pFirstElement != NULL)
        {
            pFirstElement -> pPrevious -> pNext = NULL;
            pFirstElement -> pPrevious = NULL;
            pPart2 = pFirstElement;
        }
        // else
            // n is beyond *ppList end
    }

    return pPart2;
}

/******************************************************************************/
// FUNCTION: listHalve()
//     Cuts a LIST in two and returns a pointer to the second half
// PARAMETERS:
//     pList: A pointer to a LIST
// RETURN VALUE:
//     A pointer to the second half of the LIST
/******************************************************************************/
EXPORT LIST* listHalve(LIST* pList)
{
    long length = listLen(pList);
    long n = (length / 2) + (length % 2);

    return listSplit(&pList, n);
}

