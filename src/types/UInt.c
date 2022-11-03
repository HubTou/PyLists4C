// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <limits.h>

#include <pylists4c.h>
#include "../global.h"

EXPORT STATUS listAppendUInt(LIST** ppList, unsigned int value)
{
    return listAppend(ppList, &value, ETYPE_U_INT, sizeof(value));
}

EXPORT STATUS listInsertFirstUInt(LIST** ppList, unsigned int value)
{
    return listInsertFirst(ppList, &value, ETYPE_U_INT, sizeof(value));
}

EXPORT STATUS listInsertUInt(LIST** ppList, long n, unsigned int value)
{
    return listInsert(ppList, n, &value, ETYPE_U_INT, sizeof(value));
}

EXPORT STATUS listInsertSortedUInt(LIST** ppList, unsigned int value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates)
{
    return listInsertSorted(ppList, &value, ETYPE_U_INT, sizeof(value), reversed, caseInsensitive, noDuplicates);
}

EXPORT STATUS listChangeUInt(LIST* pList, long n, unsigned int value)
{
    return listChange(pList, n, &value, ETYPE_U_INT, sizeof(value));
}

EXPORT BOOLEAN listContainsUInt(LIST* pList, unsigned int value)
{
    return listContains(pList, &value, ETYPE_U_INT, sizeof(value));
}

EXPORT long listCountUInt(LIST* pList, unsigned int value)
{
    return listCount(pList, &value, ETYPE_U_INT, sizeof(value));
}

EXPORT long listIndexUInt(LIST* pList, unsigned int value)
{
    return listIndex(pList, &value, ETYPE_U_INT, sizeof(value));
}

EXPORT LIST* listIndexAllUInt(LIST* pList, unsigned int value)
{
    return listIndexAll(pList, &value, ETYPE_U_INT, sizeof(value));
}

EXPORT void listRemoveUInt(LIST** ppList, unsigned int value)
{
    listRemove(ppList, &value, ETYPE_U_INT, sizeof(value));
}

EXPORT void listRemoveAllUInt(LIST** ppList, unsigned int value)
{
    listRemoveAll(ppList, &value, ETYPE_U_INT, sizeof(value));
}

EXPORT unsigned int listMinUInt(LIST* pList)
{
    unsigned int min = UINT_MAX;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_U_INT)
            if (*((unsigned int*) pElement -> pValue) < min)
                min = *((unsigned int*) pElement -> pValue);

    return min;
}

EXPORT unsigned int listMaxUInt(LIST* pList)
{
    unsigned int max = 0;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_U_INT)
            if (*((unsigned int*) pElement -> pValue) > max)
                max = *((unsigned int*) pElement -> pValue);

    return max;
}

EXPORT unsigned long listSumUInt(LIST* pList)
{
    unsigned long sum = 0;

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_U_INT)
            sum += *((unsigned int*) pElement -> pValue);

    return sum;
}

