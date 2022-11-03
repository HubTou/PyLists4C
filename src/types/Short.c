// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <limits.h>

#include <pylists4c.h>
#include "../global.h"

EXPORT STATUS listAppendShort(LIST** ppList, short value)
{
    return listAppend(ppList, &value, ETYPE_SHORT, sizeof(value));
}

EXPORT STATUS listInsertFirstShort(LIST** ppList, short value)
{
    return listInsertFirst(ppList, &value, ETYPE_SHORT, sizeof(value));
}

EXPORT STATUS listInsertShort(LIST** ppList, long n, short value)
{
    return listInsert(ppList, n, &value, ETYPE_SHORT, sizeof(value));
}

EXPORT STATUS listInsertSortedShort(LIST** ppList, short value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates)
{
    return listInsertSorted(ppList, &value, ETYPE_SHORT, sizeof(value), reversed, caseInsensitive, noDuplicates);
}

EXPORT STATUS listChangeShort(LIST* pList, long n, short value)
{
    return listChange(pList, n, &value, ETYPE_SHORT, sizeof(value));
}

EXPORT BOOLEAN listContainsShort(LIST* pList, short value)
{
    return listContains(pList, &value, ETYPE_SHORT, sizeof(value));
}

EXPORT long listCountShort(LIST* pList, short value)
{
    return listCount(pList, &value, ETYPE_SHORT, sizeof(value));
}

EXPORT long listIndexShort(LIST* pList, short value)
{
    return listIndex(pList, &value, ETYPE_SHORT, sizeof(value));
}

EXPORT LIST* listIndexAllShort(LIST* pList, short value)
{
    return listIndexAll(pList, &value, ETYPE_SHORT, sizeof(value));
}

EXPORT void listRemoveShort(LIST** ppList, short value)
{
    listRemove(ppList, &value, ETYPE_SHORT, sizeof(value));
}

EXPORT void listRemoveAllShort(LIST** ppList, short value)
{
    listRemoveAll(ppList, &value, ETYPE_SHORT, sizeof(value));
}

EXPORT short listMinShort(LIST* pList)
{
    short min = SHRT_MAX;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_SHORT)
            if (*((short*) pElement -> pValue) < min)
                min = *((short*) pElement -> pValue);

    return min;
}

EXPORT short listMaxShort(LIST* pList)
{
    short max = SHRT_MIN;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_SHORT)
            if (*((short*) pElement -> pValue) > max)
                max = *((short*) pElement -> pValue);

    return max;
}

EXPORT long listSumShort(LIST* pList)
{
    long sum = 0;

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_SHORT)
            sum += *((short*) pElement -> pValue);

    return sum;
}

