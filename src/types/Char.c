// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <limits.h>

#include <pylists4c.h>
#include "../global.h"

EXPORT STATUS listAppendChar(LIST** ppList, char value)
{
    return listAppend(ppList, &value, ETYPE_CHAR, sizeof(value));
}

EXPORT STATUS listInsertFirstChar(LIST** ppList, char value)
{
    return listInsertFirst(ppList, &value, ETYPE_CHAR, sizeof(value));
}

EXPORT STATUS listInsertChar(LIST** ppList, long n, char value)
{
    return listInsert(ppList, n, &value, ETYPE_CHAR, sizeof(value));
}

EXPORT STATUS listInsertSortedChar(LIST** ppList, char value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates)
{
    return listInsertSorted(ppList, &value, ETYPE_CHAR, sizeof(value), reversed, caseInsensitive, noDuplicates);
}

EXPORT STATUS listChangeChar(LIST* pList, long n, char value)
{
    return listChange(pList, n, &value, ETYPE_CHAR, sizeof(value));
}

EXPORT BOOLEAN listContainsChar(LIST* pList, char value)
{
    return listContains(pList, &value, ETYPE_CHAR, sizeof(value));
}

EXPORT long listCountChar(LIST* pList, char value)
{
    return listCount(pList, &value, ETYPE_CHAR, sizeof(value));
}

EXPORT long listIndexChar(LIST* pList, char value)
{
    return listIndex(pList, &value, ETYPE_CHAR, sizeof(value));
}

EXPORT LIST* listIndexAllChar(LIST* pList, char value)
{
    return listIndexAll(pList, &value, ETYPE_CHAR, sizeof(value));
}

EXPORT void listRemoveChar(LIST** ppList, char value)
{
    listRemove(ppList, &value, ETYPE_CHAR, sizeof(value));
}

EXPORT void listRemoveAllChar(LIST** ppList, char value)
{
    listRemoveAll(ppList, &value, ETYPE_CHAR, sizeof(value));
}

EXPORT char listMinChar(LIST* pList)
{
    char min = CHAR_MAX;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_CHAR)
            if (*((char*) pElement -> pValue) < min)
                min = *((char*) pElement -> pValue);

    return min;
}

EXPORT char listMaxChar(LIST* pList)
{
    char max = CHAR_MIN;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_CHAR)
            if (*((char*) pElement -> pValue) > max)
                max = *((char*) pElement -> pValue);

    return max;
}

EXPORT long listSumChar(LIST* pList)
{
    long sum = 0;

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_CHAR)
            sum += *((char*) pElement -> pValue);

    return sum;
}

