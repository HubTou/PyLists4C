// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <string.h>

#include <pylists4c.h>

EXPORT STATUS listAppendString(LIST** ppList, STRING value)
{
    return listAppend(ppList, &value, ETYPE_STRING, strlen(value) + 1);
}

EXPORT STATUS listInsertFirstString(LIST** ppList, STRING value)
{
    return listInsertFirst(ppList, &value, ETYPE_STRING, strlen(value) + 1);
}

EXPORT STATUS listInsertString(LIST** ppList, long n, STRING value)
{
    return listInsert(ppList, n, &value, ETYPE_STRING, strlen(value) + 1);
}

EXPORT STATUS listInsertSortedString(LIST** ppList, STRING value, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates)
{
    return listInsertSorted(ppList, &value, ETYPE_STRING, strlen(value) + 1, reversed, caseInsensitive, noDuplicates);
}

EXPORT STATUS listChangeString(LIST* pList, long n, STRING value)
{
    return listChange(pList, n, &value, ETYPE_STRING, strlen(value) + 1);
}

EXPORT BOOLEAN listContainsString(LIST* pList, STRING value)
{
    return listContains(pList, &value, ETYPE_STRING, strlen(value) + 1);
}

EXPORT long listCountString(LIST* pList, STRING value)
{
    return listCount(pList, &value, ETYPE_STRING, strlen(value) + 1);
}

EXPORT long listIndexString(LIST* pList, STRING value)
{
    return listIndex(pList, &value, ETYPE_STRING, strlen(value) + 1);
}

EXPORT LIST* listIndexAllString(LIST* pList, STRING value)
{
    return listIndexAll(pList, &value, ETYPE_STRING, strlen(value) + 1);
}

EXPORT void listRemoveString(LIST** ppList, STRING value)
{
    listRemove(ppList, &value, ETYPE_STRING, strlen(value) + 1);
}

EXPORT void listRemoveAllString(LIST** ppList, STRING value)
{
    listRemoveAll(ppList, &value, ETYPE_STRING, strlen(value) + 1);
}

