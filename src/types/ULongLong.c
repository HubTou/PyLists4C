// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <limits.h>

#include <pylists4c.h>
#include "../global.h"

EXPORT STATUS listAppendULongLong(LIST** ppList, unsigned long long value)
{
    return listAppend(ppList, &value, ETYPE_U_LONG_LONG, sizeof(value));
}

EXPORT STATUS listInsertFirstULongLong(LIST** ppList, unsigned long long value)
{
    return listInsertFirst(ppList, &value, ETYPE_U_LONG_LONG, sizeof(value));
}

EXPORT STATUS listInsertULongLong(LIST** ppList, long n, unsigned long long value)
{
    return listInsert(ppList, n, &value, ETYPE_U_LONG_LONG, sizeof(value));
}

EXPORT STATUS listInsertSortedULongLong(LIST** ppList, unsigned long long value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates)
{
    return listInsertSorted(ppList, &value, ETYPE_U_LONG_LONG, sizeof(value), reversed, caseInsensitive, noDuplicates);
}

EXPORT STATUS listChangeULongLong(LIST* pList, long n, unsigned long long value)
{
    return listChange(pList, n, &value, ETYPE_U_LONG_LONG, sizeof(value));
}

EXPORT BOOLEAN listContainsULongLong(LIST* pList, unsigned long long value)
{
    return listContains(pList, &value, ETYPE_U_LONG_LONG, sizeof(value));
}

EXPORT long listCountULongLong(LIST* pList, unsigned long long value)
{
    return listCount(pList, &value, ETYPE_U_LONG_LONG, sizeof(value));
}

EXPORT long listIndexULongLong(LIST* pList, unsigned long long value)
{
    return listIndex(pList, &value, ETYPE_U_LONG_LONG, sizeof(value));
}

EXPORT LIST* listIndexAllULongLong(LIST* pList, unsigned long long value)
{
    return listIndexAll(pList, &value, ETYPE_U_LONG_LONG, sizeof(value));
}

EXPORT void listRemoveULongLong(LIST** ppList, unsigned long long value)
{
    listRemove(ppList, &value, ETYPE_U_LONG_LONG, sizeof(value));
}

EXPORT void listRemoveAllULongLong(LIST** ppList, unsigned long long value)
{
    listRemoveAll(ppList, &value, ETYPE_U_LONG_LONG, sizeof(value));
}

EXPORT unsigned long long listMinULongLong(LIST* pList)
{
    unsigned long long min = ULLONG_MAX;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_U_LONG_LONG)
            if (*((unsigned long long*) pElement -> pValue) < min)
                min = *((unsigned long long*) pElement -> pValue);

    return min;
}

EXPORT unsigned long long listMaxULongLong(LIST* pList)
{
    unsigned long long max = 0;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_U_LONG_LONG)
            if (*((unsigned long long*) pElement -> pValue) > max)
                max = *((unsigned long long*) pElement -> pValue);

    return max;
}

EXPORT unsigned long long listSumULongLong(LIST* pList)
{
    unsigned long long sum = 0;

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_U_LONG_LONG)
            sum += *((unsigned long long*) pElement -> pValue);

    return sum;
}

