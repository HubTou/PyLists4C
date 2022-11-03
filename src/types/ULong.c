// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <limits.h>

#include <pylists4c.h>
#include "../global.h"

EXPORT STATUS listAppendULong(LIST** ppList, unsigned long value)
{
    return listAppend(ppList, &value, ETYPE_U_LONG, sizeof(value));
}

EXPORT STATUS listInsertFirstULong(LIST** ppList, unsigned long value)
{
    return listInsertFirst(ppList, &value, ETYPE_U_LONG, sizeof(value));
}

EXPORT STATUS listInsertULong(LIST** ppList, long n, unsigned long value)
{
    return listInsert(ppList, n, &value, ETYPE_U_LONG, sizeof(value));
}

EXPORT STATUS listInsertSortedULong(LIST** ppList, unsigned long value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates)
{
    return listInsertSorted(ppList, &value, ETYPE_U_LONG, sizeof(value), reversed, caseInsensitive, noDuplicates);
}

EXPORT STATUS listChangeULong(LIST* pList, long n, unsigned long value)
{
    return listChange(pList, n, &value, ETYPE_U_LONG, sizeof(value));
}

EXPORT BOOLEAN listContainsULong(LIST* pList, unsigned long value)
{
    return listContains(pList, &value, ETYPE_U_LONG, sizeof(value));
}

EXPORT long listCountULong(LIST* pList, unsigned long value)
{
    return listCount(pList, &value, ETYPE_U_LONG, sizeof(value));
}

EXPORT long listIndexULong(LIST* pList, unsigned long value)
{
    return listIndex(pList, &value, ETYPE_U_LONG, sizeof(value));
}

EXPORT LIST* listIndexAllULong(LIST* pList, unsigned long value)
{
    return listIndexAll(pList, &value, ETYPE_U_LONG, sizeof(value));
}

EXPORT void listRemoveULong(LIST** ppList, unsigned long value)
{
    listRemove(ppList, &value, ETYPE_U_LONG, sizeof(value));
}

EXPORT void listRemoveAllULong(LIST** ppList, unsigned long value)
{
    listRemoveAll(ppList, &value, ETYPE_U_LONG, sizeof(value));
}

EXPORT unsigned long listMinULong(LIST* pList)
{
    unsigned long min = ULONG_MAX;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_U_LONG)
            if (*((unsigned long*) pElement -> pValue) < min)
                min = *((unsigned long*) pElement -> pValue);

    return min;
}

EXPORT unsigned long listMaxULong(LIST* pList)
{
    unsigned long max = 0;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_U_LONG)
            if (*((unsigned long*) pElement -> pValue) > max)
                max = *((unsigned long*) pElement -> pValue);

    return max;
}

EXPORT unsigned long long listSumULong(LIST* pList)
{
    unsigned long long sum = 0;

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_U_LONG)
            sum += *((unsigned long*) pElement -> pValue);

    return sum;
}

