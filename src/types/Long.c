// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <limits.h>

#include <pylists4c.h>
#include "../global.h"

EXPORT STATUS listAppendLong(LIST** ppList, long value)
{
    return listAppend(ppList, &value, ETYPE_LONG, sizeof(value));
}

EXPORT STATUS listInsertFirstLong(LIST** ppList, long value)
{
    return listInsertFirst(ppList, &value, ETYPE_LONG, sizeof(value));
}

EXPORT STATUS listInsertLong(LIST** ppList, long n, long value)
{
    return listInsert(ppList, n, &value, ETYPE_LONG, sizeof(value));
}

EXPORT STATUS listInsertSortedLong(LIST** ppList, long value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates)
{
    return listInsertSorted(ppList, &value, ETYPE_LONG, sizeof(value), reversed, caseInsensitive, noDuplicates);
}

EXPORT STATUS listChangeLong(LIST* pList, long n, long value)
{
    return listChange(pList, n, &value, ETYPE_LONG, sizeof(value));
}

EXPORT BOOLEAN listContainsLong(LIST* pList, long value)
{
    return listContains(pList, &value, ETYPE_LONG, sizeof(value));
}

EXPORT long listCountLong(LIST* pList, long value)
{
    return listCount(pList, &value, ETYPE_LONG, sizeof(value));
}

EXPORT long listIndexLong(LIST* pList, long value)
{
    return listIndex(pList, &value, ETYPE_LONG, sizeof(value));
}

EXPORT LIST* listIndexAllLong(LIST* pList, long value)
{
    return listIndexAll(pList, &value, ETYPE_LONG, sizeof(value));
}

EXPORT void listRemoveLong(LIST** ppList, long value)
{
    listRemove(ppList, &value, ETYPE_LONG, sizeof(value));
}

EXPORT void listRemoveAllLong(LIST** ppList, long value)
{
    listRemoveAll(ppList, &value, ETYPE_LONG, sizeof(value));
}

EXPORT long listMinLong(LIST* pList)
{
    long min = LONG_MAX;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_LONG)
            if (*((long*) pElement -> pValue) < min)
                min = *((long*) pElement -> pValue);

    return min;
}

EXPORT long listMaxLong(LIST* pList)
{
    long max = LONG_MIN;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_LONG)
            if (*((long*) pElement -> pValue) > max)
                max = *((long*) pElement -> pValue);

    return max;
}

EXPORT long long listSumLong(LIST* pList)
{
    long long sum = 0;

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_LONG)
            sum += *((long*) pElement -> pValue);

    return sum;
}

