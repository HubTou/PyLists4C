// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <float.h>

#include <pylists4c.h>
#include "../global.h"

EXPORT STATUS listAppendFloat(LIST** ppList, float value)
{
    return listAppend(ppList, &value, ETYPE_FLOAT, sizeof(value));
}

EXPORT STATUS listInsertFirstFloat(LIST** ppList, float value)
{
    return listInsertFirst(ppList, &value, ETYPE_FLOAT, sizeof(value));
}

EXPORT STATUS listInsertFloat(LIST** ppList, long n, float value)
{
    return listInsert(ppList, n, &value, ETYPE_FLOAT, sizeof(value));
}

EXPORT STATUS listInsertSortedFloat(LIST** ppList, float value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates)
{
    return listInsertSorted(ppList, &value, ETYPE_FLOAT, sizeof(value), reversed, caseInsensitive, noDuplicates);
}

EXPORT STATUS listChangeFloat(LIST* pList, long n, float value)
{
    return listChange(pList, n, &value, ETYPE_FLOAT, sizeof(value));
}

EXPORT BOOLEAN listContainsFloat(LIST* pList, float value)
{
    return listContains(pList, &value, ETYPE_FLOAT, sizeof(value));
}

EXPORT long listCountFloat(LIST* pList, float value)
{
    return listCount(pList, &value, ETYPE_FLOAT, sizeof(value));
}

EXPORT long listIndexFloat(LIST* pList, float value)
{
    return listIndex(pList, &value, ETYPE_FLOAT, sizeof(value));
}

EXPORT LIST* listIndexAllFloat(LIST* pList, float value)
{
    return listIndexAll(pList, &value, ETYPE_FLOAT, sizeof(value));
}

EXPORT void listRemoveFloat(LIST** ppList, float value)
{
    listRemove(ppList, &value, ETYPE_FLOAT, sizeof(value));
}

EXPORT void listRemoveAllFloat(LIST** ppList, float value)
{
    listRemoveAll(ppList, &value, ETYPE_FLOAT, sizeof(value));
}

EXPORT float listMinFloat(LIST* pList)
{
    float min = FLT_MAX;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_FLOAT)
            if (*((float*) pElement -> pValue) < min)
                min = *((float*) pElement -> pValue);

    return min;
}

EXPORT float listMaxFloat(LIST* pList)
{
    float max = FLT_MIN;

    if (listDebugMessages)
        if (pList == NULL)
            fprintf(stderr, "WARNING: Meaningless result as LIST is empty\n");

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_FLOAT)
            if (*((float*) pElement -> pValue) > max)
                max = *((float*) pElement -> pValue);

    return max;
}

EXPORT double listSumFloat(LIST* pList)
{
    double sum = 0;

    for (LIST* pElement = pList; pElement != NULL; pElement = pElement -> pNext)
        if (pElement -> type == ETYPE_FLOAT)
            sum += *((float*) pElement -> pValue);

    return sum;
}

