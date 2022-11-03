// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <limits.h>

#include <pylists4c.h>
#include "../global.h"

EXPORT STATUS listAppendUChar(LIST** ppList, unsigned char value)
{
    return listAppend(ppList, &value, ETYPE_U_CHAR, sizeof(value));
}

EXPORT STATUS listInsertFirstUChar(LIST** ppList, unsigned char value)
{
    return listInsertFirst(ppList, &value, ETYPE_U_CHAR, sizeof(value));
}

EXPORT STATUS listInsertUChar(LIST** ppList, long n, unsigned char value)
{
    return listInsert(ppList, n, &value, ETYPE_U_CHAR, sizeof(value));
}

EXPORT STATUS listInsertSortedUChar(LIST** ppList, unsigned char value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates)
{
    return listInsertSorted(ppList, &value, ETYPE_U_CHAR, sizeof(value), reversed, caseInsensitive, noDuplicates);
}

EXPORT STATUS listChangeUChar(LIST* pList, long n, unsigned char value)
{
    return listChange(pList, n, &value, ETYPE_U_CHAR, sizeof(value));
}

EXPORT BOOLEAN listContainsUChar(LIST* pList, unsigned char value)
{
    return listContains(pList, &value, ETYPE_U_CHAR, sizeof(value));
}

EXPORT long listCountUChar(LIST* pList, unsigned char value)
{
    return listCount(pList, &value, ETYPE_U_CHAR, sizeof(value));
}

EXPORT long listIndexUChar(LIST* pList, unsigned char value)
{
    return listIndex(pList, &value, ETYPE_U_CHAR, sizeof(value));
}

EXPORT LIST* listIndexAllUChar(LIST* pList, unsigned char value)
{
    return listIndexAll(pList, &value, ETYPE_U_CHAR, sizeof(value));
}

EXPORT void listRemoveUChar(LIST** ppList, unsigned char value)
{
    listRemove(ppList, &value, ETYPE_U_CHAR, sizeof(value));
}

EXPORT void listRemoveAllUChar(LIST** ppList, unsigned char value)
{
    listRemoveAll(ppList, &value, ETYPE_U_CHAR, sizeof(value));
}

EXPORT unsigned char listMinUChar(LIST* pList)
{
    unsigned char min = UCHAR_MAX;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_U_CHAR)
            if (*((unsigned char*) pElement -> pValue) < min)
                min = *((unsigned char*) pElement -> pValue);

    return min;
}

EXPORT unsigned char listMaxUChar(LIST* pList)
{
    unsigned char max = 0;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_U_CHAR)
            if (*((unsigned char*) pElement -> pValue) > max)
                max = *((unsigned char*) pElement -> pValue);

    return max;
}

EXPORT unsigned long listSumUChar(LIST* pList)
{
    unsigned long sum = 0;

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_U_CHAR)
            sum += *((unsigned char*) pElement -> pValue);

    return sum;
}

