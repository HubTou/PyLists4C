// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <limits.h>

#include <pylists4c.h>
#include "../global.h"

EXPORT STATUS listAppendLongLong(LIST** ppList, long long value)
{
    return listAppend(ppList, &value, ETYPE_LONG_LONG, sizeof(value));
}

EXPORT STATUS listInsertFirstLongLong(LIST** ppList, long long value)
{
    return listInsertFirst(ppList, &value, ETYPE_LONG_LONG, sizeof(value));
}

EXPORT STATUS listInsertLongLong(LIST** ppList, long n, long long value)
{
    return listInsert(ppList, n, &value, ETYPE_LONG_LONG, sizeof(value));
}

EXPORT STATUS listInsertSortedLongLong(LIST** ppList, long long value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates)
{
    return listInsertSorted(ppList, &value, ETYPE_LONG_LONG, sizeof(value), reversed, caseInsensitive, noDuplicates);
}

EXPORT STATUS listChangeLongLong(LIST* pList, long n, long long value)
{
    return listChange(pList, n, &value, ETYPE_LONG_LONG, sizeof(value));
}

EXPORT BOOLEAN listContainsLongLong(LIST* pList, long long value)
{
    return listContains(pList, &value, ETYPE_LONG_LONG, sizeof(value));
}

EXPORT long listCountLongLong(LIST* pList, long long value)
{
    return listCount(pList, &value, ETYPE_LONG_LONG, sizeof(value));
}

EXPORT long listIndexLongLong(LIST* pList, long long value)
{
    return listIndex(pList, &value, ETYPE_LONG_LONG, sizeof(value));
}

EXPORT LIST* listIndexAllLongLong(LIST* pList, long long value)
{
    return listIndexAll(pList, &value, ETYPE_LONG_LONG, sizeof(value));
}

EXPORT void listRemoveLongLong(LIST** ppList, long long value)
{
    listRemove(ppList, &value, ETYPE_LONG_LONG, sizeof(value));
}

EXPORT void listRemoveAllLongLong(LIST** ppList, long long value)
{
    listRemoveAll(ppList, &value, ETYPE_LONG_LONG, sizeof(value));
}

EXPORT long long listMinLongLong(LIST* pList)
{
    long long min = LLONG_MAX;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_LONG_LONG)
            if (*((long long*) pElement -> pValue) < min)
                min = *((long long*) pElement -> pValue);

    return min;
}

EXPORT long long listMaxLongLong(LIST* pList)
{
    long long max = LLONG_MIN;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_LONG_LONG)
            if (*((long long*) pElement -> pValue) > max)
                max = *((long long*) pElement -> pValue);

    return max;
}

EXPORT long long listSumLongLong(LIST* pList)
{
    long long sum = 0;

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_LONG_LONG)
            sum += *((long long*) pElement -> pValue);

    return sum;
}

