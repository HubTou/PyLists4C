// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

EXPORT STATUS listAppendNull(LIST** ppList)
{
    return listAppend(ppList, NULL, ETYPE_NULL, 0);
}

EXPORT STATUS listInsertFirstNull(LIST** ppList)
{
    return listInsertFirst(ppList, NULL, ETYPE_NULL, 0);
}

EXPORT STATUS listInsertNull(LIST** ppList, long n)
{
    return listInsert(ppList, n, NULL, ETYPE_NULL, 0);
}

EXPORT STATUS listInsertSortedNull(LIST** ppList, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates)
{
    return listInsertSorted(ppList, NULL, ETYPE_NULL, 0, reversed, caseInsensitive, noDuplicates);
}

EXPORT STATUS listChangeNull(LIST* pList, long n)
{
    return listChange(pList, n, NULL, ETYPE_NULL, 0);
}

EXPORT BOOLEAN listContainsNull(LIST* pList)
{
    return listContains(pList, NULL, ETYPE_NULL, 0);
}

EXPORT long listCountNull(LIST* pList)
{
    return listCount(pList, NULL, ETYPE_NULL, 0);
}

EXPORT long listIndexNull(LIST* pList)
{
    return listIndex(pList, NULL, ETYPE_NULL, 0);
}

EXPORT LIST* listIndexAllNull(LIST* pList)
{
    return listIndexAll(pList, NULL, ETYPE_NULL, 0);
}

EXPORT void listRemoveNull(LIST** ppList)
{
    listRemove(ppList, NULL, ETYPE_NULL, 0);
}

EXPORT void listRemoveAllNull(LIST** ppList)
{
    listRemoveAll(ppList, NULL, ETYPE_NULL, 0);
}

