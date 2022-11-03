// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <limits.h>

#include <pylists4c.h>
#include "../global.h"

EXPORT STATUS listAppendUShort(LIST** ppList, unsigned short value)
{
    return listAppend(ppList, &value, ETYPE_U_SHORT, sizeof(value));
}

EXPORT STATUS listInsertFirstUShort(LIST** ppList, unsigned short value)
{
    return listInsertFirst(ppList, &value, ETYPE_U_SHORT, sizeof(value));
}

EXPORT STATUS listInsertUShort(LIST** ppList, long n, unsigned short value)
{
    return listInsert(ppList, n, &value, ETYPE_U_SHORT, sizeof(value));
}

EXPORT STATUS listInsertSortedUShort(LIST** ppList, unsigned short value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates)
{
    return listInsertSorted(ppList, &value, ETYPE_U_SHORT, sizeof(value), reversed, caseInsensitive, noDuplicates);
}

EXPORT STATUS listChangeUShort(LIST* pList, long n, unsigned short value)
{
    return listChange(pList, n, &value, ETYPE_U_SHORT, sizeof(value));
}

EXPORT BOOLEAN listContainsUShort(LIST* pList, unsigned short value)
{
    return listContains(pList, &value, ETYPE_U_SHORT, sizeof(value));
}

EXPORT long listCountUShort(LIST* pList, unsigned short value)
{
    return listCount(pList, &value, ETYPE_U_SHORT, sizeof(value));
}

EXPORT long listIndexUShort(LIST* pList, unsigned short value)
{
    return listIndex(pList, &value, ETYPE_U_SHORT, sizeof(value));
}

EXPORT LIST* listIndexAllUShort(LIST* pList, unsigned short value)
{
    return listIndexAll(pList, &value, ETYPE_U_SHORT, sizeof(value));
}

EXPORT void listRemoveUShort(LIST** ppList, unsigned short value)
{
    listRemove(ppList, &value, ETYPE_U_SHORT, sizeof(value));
}

EXPORT void listRemoveAllUShort(LIST** ppList, unsigned short value)
{
    listRemoveAll(ppList, &value, ETYPE_U_SHORT, sizeof(value));
}

EXPORT unsigned short listMinUShort(LIST* pList)
{
    unsigned short min = USHRT_MAX;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_U_SHORT)
            if (*((unsigned short*) pElement -> pValue) < min)
                min = *((unsigned short*) pElement -> pValue);

    return min;
}

EXPORT unsigned short listMaxUShort(LIST* pList)
{
    unsigned short max = 0;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_U_SHORT)
            if (*((unsigned short*) pElement -> pValue) > max)
                max = *((unsigned short*) pElement -> pValue);

    return max;
}

EXPORT unsigned long listSumUShort(LIST* pList)
{
    unsigned long sum = 0;

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_U_SHORT)
            sum += *((unsigned short*) pElement -> pValue);

    return sum;
}

