// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <float.h>

#include <pylists4c.h>
#include "../global.h"

EXPORT STATUS listAppendLongDouble(LIST** ppList, long double value)
{
    return listAppend(ppList, &value, ETYPE_LONG_DOUBLE, sizeof(value));
}

EXPORT STATUS listInsertFirstLongDouble(LIST** ppList, long double value)
{
    return listInsertFirst(ppList, &value, ETYPE_LONG_DOUBLE, sizeof(value));
}

EXPORT STATUS listInsertLongDouble(LIST** ppList, long n, long double value)
{
    return listInsert(ppList, n, &value, ETYPE_LONG_DOUBLE, sizeof(value));
}

EXPORT STATUS listInsertSortedLongDouble(LIST** ppList, long double value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates)
{
    return listInsertSorted(ppList, &value, ETYPE_LONG_DOUBLE, sizeof(value), reversed, caseInsensitive, noDuplicates);
}

EXPORT STATUS listChangeLongDouble(LIST* pList, long n, long double value)
{
    return listChange(pList, n, &value, ETYPE_LONG_DOUBLE, sizeof(value));
}

EXPORT BOOLEAN listContainsLongDouble(LIST* pList, long double value)
{
    return listContains(pList, &value, ETYPE_LONG_DOUBLE, sizeof(value));
}

EXPORT long listCountLongDouble(LIST* pList, long double value)
{
    return listCount(pList, &value, ETYPE_LONG_DOUBLE, sizeof(value));
}

EXPORT long listIndexLongDouble(LIST* pList, long double value)
{
    return listIndex(pList, &value, ETYPE_LONG_DOUBLE, sizeof(value));
}

EXPORT LIST* listIndexAllLongDouble(LIST* pList, long double value)
{
    return listIndexAll(pList, &value, ETYPE_LONG_DOUBLE, sizeof(value));
}

EXPORT void listRemoveLongDouble(LIST** ppList, long double value)
{
    listRemove(ppList, &value, ETYPE_LONG_DOUBLE, sizeof(value));
}

EXPORT void listRemoveAllLongDouble(LIST** ppList, long double value)
{
    listRemoveAll(ppList, &value, ETYPE_LONG_DOUBLE, sizeof(value));
}

EXPORT long double listMinLongDouble(LIST* pList)
{
    long double min = LDBL_MAX;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_LONG_DOUBLE)
            if (*((long double*) pElement -> pValue) < min)
                min = *((long double*) pElement -> pValue);

    return min;
}

EXPORT long double listMaxLongDouble(LIST* pList)
{
    long double max = LDBL_MIN;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_LONG_DOUBLE)
            if (*((long double*) pElement -> pValue) > max)
                max = *((long double*) pElement -> pValue);

    return max;
}

EXPORT long double listSumLongDouble(LIST* pList)
{
    long double sum = 0;

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_LONG_DOUBLE)
            sum += *((long double*) pElement -> pValue);

    return sum;
}

