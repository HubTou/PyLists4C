// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <float.h>

#include <pylists4c.h>
#include "../global.h"

EXPORT STATUS listAppendDouble(LIST** ppList, double value)
{
    return listAppend(ppList, &value, ETYPE_DOUBLE, sizeof(value));
}

EXPORT STATUS listInsertFirstDouble(LIST** ppList, double value)
{
    return listInsertFirst(ppList, &value, ETYPE_DOUBLE, sizeof(value));
}

EXPORT STATUS listInsertDouble(LIST** ppList, long n, double value)
{
    return listInsert(ppList, n, &value, ETYPE_DOUBLE, sizeof(value));
}

EXPORT STATUS listInsertSortedDouble(LIST** ppList, double value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates)
{
    return listInsertSorted(ppList, &value, ETYPE_DOUBLE, sizeof(value), reversed, caseInsensitive, noDuplicates);
}

EXPORT STATUS listChangeDouble(LIST* pList, long n, double value)
{
    return listChange(pList, n, &value, ETYPE_DOUBLE, sizeof(value));
}

EXPORT BOOLEAN listContainsDouble(LIST* pList, double value)
{
    return listContains(pList, &value, ETYPE_DOUBLE, sizeof(value));
}

EXPORT long listCountDouble(LIST* pList, double value)
{
    return listCount(pList, &value, ETYPE_DOUBLE, sizeof(value));
}

EXPORT long listIndexDouble(LIST* pList, double value)
{
    return listIndex(pList, &value, ETYPE_DOUBLE, sizeof(value));
}

EXPORT LIST* listIndexAllDouble(LIST* pList, double value)
{
    return listIndexAll(pList, &value, ETYPE_DOUBLE, sizeof(value));
}

EXPORT void listRemoveDouble(LIST** ppList, double value)
{
    listRemove(ppList, &value, ETYPE_DOUBLE, sizeof(value));
}

EXPORT void listRemoveAllDouble(LIST** ppList, double value)
{
    listRemoveAll(ppList, &value, ETYPE_DOUBLE, sizeof(value));
}

EXPORT double listMinDouble(LIST* pList)
{
    double min = DBL_MAX;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_DOUBLE)
            if (*((double*) pElement -> pValue) < min)
                min = *((double*) pElement -> pValue);

    return min;
}

EXPORT double listMaxDouble(LIST* pList)
{
    double max = DBL_MIN;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_DOUBLE)
            if (*((double*) pElement -> pValue) > max)
                max = *((double*) pElement -> pValue);

    return max;
}

EXPORT long double listSumDouble(LIST* pList)
{
   long double sum = 0;

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_DOUBLE)
            sum += *((double*) pElement -> pValue);

    return sum;
}

