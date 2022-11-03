// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <limits.h>

#include <pylists4c.h>
#include "../global.h"

EXPORT STATUS listAppendInt(LIST** ppList, int value)
{
    return listAppend(ppList, &value, ETYPE_INT, sizeof(value));
}

EXPORT STATUS listInsertFirstInt(LIST** ppList, int value)
{
    return listInsertFirst(ppList, &value, ETYPE_INT, sizeof(value));
}

EXPORT STATUS listInsertInt(LIST** ppList, long n, int value)
{
    return listInsert(ppList, n, &value, ETYPE_INT, sizeof(value));
}

EXPORT STATUS listInsertSortedInt(LIST** ppList, int value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates)
{
    return listInsertSorted(ppList, &value, ETYPE_INT, sizeof(value), reversed, caseInsensitive, noDuplicates);
}

EXPORT STATUS listChangeInt(LIST* pList, long n, int value)
{
    return listChange(pList, n, &value, ETYPE_INT, sizeof(value));
}

EXPORT BOOLEAN listContainsInt(LIST* pList, int value)
{
    return listContains(pList, &value, ETYPE_INT, sizeof(value));
}

EXPORT long listCountInt(LIST* pList, int value)
{
    return listCount(pList, &value, ETYPE_INT, sizeof(value));
}

EXPORT long listIndexInt(LIST* pList, int value)
{
    return listIndex(pList, &value, ETYPE_INT, sizeof(value));
}

EXPORT LIST* listIndexAllInt(LIST* pList, int value)
{
    return listIndexAll(pList, &value, ETYPE_INT, sizeof(value));
}

EXPORT void listRemoveInt(LIST** ppList, int value)
{
    listRemove(ppList, &value, ETYPE_INT, sizeof(value));
}

EXPORT void listRemoveAllInt(LIST** ppList, int value)
{
    listRemoveAll(ppList, &value, ETYPE_INT, sizeof(value));
}

EXPORT int listMinInt(LIST* pList)
{
    int min = INT_MAX;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_INT)
            if (*((int*) pElement -> pValue) < min)
                min = *((int*) pElement -> pValue);

    return min;
}

EXPORT int listMaxInt(LIST* pList)
{
    int max = INT_MIN;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_INT)
            if (*((int*) pElement -> pValue) > max)
                max = *((int*) pElement -> pValue);

    return max;
}

EXPORT long listSumInt(LIST* pList)
{
    long sum = 0;

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_INT)
            sum += *((int*) pElement -> pValue);

    return sum;
}

