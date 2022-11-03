// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

// Pointer to the default sort algorithm:
LIST* (*listSortedAlgorithm)(LIST* pList, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates) = listSortedByInsertion;

/******************************************************************************/
// FUNCTION: listSorted()
//     Returns a sorted copy of a LIST
// PARAMETERS:
//     pList: A pointer to a LIST
//     reversed: A BOOLEAN indicating the sort order
//     caseInsensitive: A BOOLEAN specifying how to handle char and STRING
//     noDuplicates: A BOOLEAN indicating if duplicate values are discarded
// RETURN VALUE:
//     A pointer to the sorted copy of the LIST
/******************************************************************************/
EXPORT LIST* listSorted(LIST* pList, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates)
{
    return listSortedAlgorithm(pList, reversed, caseInsensitive, noDuplicates);
}

/******************************************************************************/
// FUNCTION: listSetDefaultSort()
//     Sets the default sorting algorithm
// PARAMETERS:
//     defaultSortAlgorithm: A pointer to the function to use by default
/******************************************************************************/
EXPORT void listSetDefaultSort(LIST* (*defaultSortAlgorithm)(LIST* pList, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates))
{
    listSortedAlgorithm = defaultSortAlgorithm;
}

