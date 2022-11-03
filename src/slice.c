// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listSlice(n, m)
// FUNCTION: listSliceFrom(n)
// FUNCTION: listSliceTo(m)
//     Returns a copy of a slice (ie. [n:m]) of a LIST
// PARAMETERS:
//     pList: A pointer to a LIST
//     n: The included lower bound of the slice (numbered from 0 or -len(pList))
//     m: The excluded upper bound of the slice (numbered from len(pList) or 0)
// RETURN VALUE:
//     A pointer to the sliced LIST
/******************************************************************************/
INTERNAL LIST* listSliceCommon(LIST* pList, long n, long m)
{
    LIST* pSlice = NULL;
    LIST* pElement = NULL;

    // Empty slice!
    if (n >= m)
        return NULL;

    // Copy slice
    pElement = listGet(pList, n);
    for (long i = n; i < m && pElement != NULL; pElement = pElement -> pNext, i++)
        if (listAppend(&pSlice, pElement -> pValue, pElement -> type, pElement -> size) == FAILURE)
        {
            listClear(&pList);
            return NULL;
        }

    return pSlice;
}

// list[n:m]
EXPORT LIST* listSlice(LIST* pList, long n, long m)
{
    return listSliceCommon(pList, n, m);
}

// list[n:]
EXPORT LIST* listSliceFrom(LIST* pList, long n)
{
    long m;

    // Handling missing indice
    if (n < 0)
        m = 0;
    else
        m = listLen(pList);

    return listSliceCommon(pList, n, m);
}

// list[:m]
EXPORT LIST* listSliceTo(LIST* pList, long m)
{
    long n;

    // Handling missing indice
    if (m < 0)
        n = -1 * listLen(pList);
    else
        n = 0;

    return listSliceCommon(pList, n, m);
}

