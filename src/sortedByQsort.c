// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>
#include "global.h"

/******************************************************************************/
// FUNCTION: listSortedByQsort()
//     Returns a sorted copy of a LIST, using an Quicksort algorithm
// PARAMETERS:
//     pList: A pointer to a LIST
//     reversed: A BOOLEAN indicating the sort order
//     caseInsensitive: A BOOLEAN specifying how to handle char and STRING
//     noDuplicates: A BOOLEAN indicating if duplicate values are discarded
// RETURN VALUE:
//     A pointer to the sorted copy of the LIST
/******************************************************************************/
EXPORT LIST* listSortedByQsort(LIST* pList, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates)
{
    LIST* pSortedList = NULL;
    ARRAY* pArray;

    if ((pArray = listToArray(pList)) == NULL)
        // If the LIST is not homogeneous, we return immediately
        return NULL;

    if (reversed)
    {
        switch (pArray -> type)
        {
            case ETYPE_CHAR:
                if (caseInsensitive)
                    qsort(pArray -> u.pChar, pArray -> length, pArray -> size, listCompareCharCaseInsensitiveReversed);
                else
                    qsort(pArray -> u.pChar, pArray -> length, pArray -> size, listCompareCharReversed);
                break;
            case ETYPE_U_CHAR:
                if (caseInsensitive)
                    qsort(pArray -> u.pUChar, pArray -> length, pArray -> size, listCompareUCharCaseInsensitiveReversed);
                else
                    qsort(pArray -> u.pUChar, pArray -> length, pArray -> size, listCompareUCharReversed);
                break;
            case ETYPE_SHORT: qsort(pArray -> u.pShort, pArray -> length, pArray -> size, listCompareShortReversed); break;
            case ETYPE_U_SHORT: qsort(pArray -> u.pUShort, pArray -> length, pArray -> size, listCompareUShortReversed); break;
            case ETYPE_INT: qsort(pArray -> u.pInt, pArray -> length, pArray -> size, listCompareIntReversed); break;
            case ETYPE_U_INT: qsort(pArray -> u.pUInt, pArray -> length, pArray -> size, listCompareUIntReversed); break;
            case ETYPE_LONG: qsort(pArray -> u.pLong, pArray -> length, pArray -> size, listCompareLongReversed); break;
            case ETYPE_U_LONG: qsort(pArray -> u.pULong, pArray -> length, pArray -> size, listCompareULongReversed); break;
            case ETYPE_LONG_LONG: qsort(pArray -> u.pLongLong, pArray -> length, pArray -> size, listCompareLongLongReversed); break;
            case ETYPE_U_LONG_LONG: qsort(pArray -> u.pULongLong, pArray -> length, pArray -> size, listCompareULongLongReversed); break;
            case ETYPE_FLOAT: qsort(pArray -> u.pFloat, pArray -> length, pArray -> size, listCompareFloatReversed); break;
            case ETYPE_DOUBLE: qsort(pArray -> u.pDouble, pArray -> length, pArray -> size, listCompareDoubleReversed); break;
            case ETYPE_LONG_DOUBLE: qsort(pArray -> u.pLongDouble, pArray -> length, pArray -> size, listCompareLongDoubleReversed); break;
            case ETYPE_STRING:
                if (caseInsensitive)
                    qsort(pArray -> u.ppString, pArray -> length, pArray -> size, listCompareStringCaseInsensitiveReversed);
                else
                    qsort(pArray -> u.ppString, pArray -> length, pArray -> size, listCompareStringReversed);
                break;
            case ETYPE_LIST: /* We don't know how to sort LISTs! */ break;
            case ETYPE_STRUCT:
                listStructSize = pArray -> size;
                qsort(pArray -> u.ppStruct, pArray -> length, pArray -> size, listCompareStructReversed);
                break;
            default: break;
        }
    }
    else
    {
        switch (pArray -> type)
        {
            case ETYPE_CHAR:
                if (caseInsensitive)
                    qsort(pArray -> u.pChar, pArray -> length, pArray -> size, listCompareCharCaseInsensitive);
                else
                    qsort(pArray -> u.pChar, pArray -> length, pArray -> size, listCompareChar);
                break;
            case ETYPE_U_CHAR:
                if (caseInsensitive)
                    qsort(pArray -> u.pUChar, pArray -> length, pArray -> size, listCompareUCharCaseInsensitive);
                else
                    qsort(pArray -> u.pUChar, pArray -> length, pArray -> size, listCompareUChar);
                break;
            case ETYPE_SHORT: qsort(pArray -> u.pShort, pArray -> length, pArray -> size, listCompareShort); break;
            case ETYPE_U_SHORT: qsort(pArray -> u.pUShort, pArray -> length, pArray -> size, listCompareUShort); break;
            case ETYPE_INT: qsort(pArray -> u.pInt, pArray -> length, pArray -> size, listCompareInt); break;
            case ETYPE_U_INT: qsort(pArray -> u.pUInt, pArray -> length, pArray -> size, listCompareUInt); break;
            case ETYPE_LONG: qsort(pArray -> u.pLong, pArray -> length, pArray -> size, listCompareLong); break;
            case ETYPE_U_LONG: qsort(pArray -> u.pULong, pArray -> length, pArray -> size, listCompareULong); break;
            case ETYPE_LONG_LONG: qsort(pArray -> u.pLongLong, pArray -> length, pArray -> size, listCompareLongLong); break;
            case ETYPE_U_LONG_LONG: qsort(pArray -> u.pULongLong, pArray -> length, pArray -> size, listCompareULongLong); break;
            case ETYPE_FLOAT: qsort(pArray -> u.pFloat, pArray -> length, pArray -> size, listCompareFloat); break;
            case ETYPE_DOUBLE: qsort(pArray -> u.pDouble, pArray -> length, pArray -> size, listCompareDouble); break;
            case ETYPE_LONG_DOUBLE: qsort(pArray -> u.pLongDouble, pArray -> length, pArray -> size, listCompareLongDouble); break;
            case ETYPE_STRING:
                if (caseInsensitive)
                    qsort(pArray -> u.ppString, pArray -> length, pArray -> size, listCompareStringCaseInsensitive);
                else
                    qsort(pArray -> u.ppString, pArray -> length, pArray -> size, listCompareString);
                break;
            case ETYPE_LIST: /* We don't know how to sort LISTs! */ break;
            case ETYPE_STRUCT:
                listStructSize = pArray -> size;
                qsort(pArray -> u.ppStruct, pArray -> length, pArray -> size, listCompareStruct);
                break;
            default: break;
        }
    }
    pSortedList = listFromArray(pArray);

    if (noDuplicates)
        listRemoveDuplicates(pSortedList);

    return pSortedList;
}

