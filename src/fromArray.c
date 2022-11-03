// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <string.h>

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listFromArray()
//     Converts an ARRAY into a LIST
// PARAMETERS:
//     pArray: A pointer to an ARRAY
// RETURN CODE:
//     A pointer to an allocated ARRAY
/******************************************************************************/
EXPORT LIST* listFromArray(ARRAY* pArray)
{
    LIST* pList = NULL;
    long i;

    for (i = 0; i < pArray -> length; i++)
    {
        STATUS returnCode;

        switch (pArray -> type)
        {
            case ETYPE_CHAR: returnCode = listAppend(&pList, &(pArray -> u.pChar[i]), pArray -> type, pArray -> size); break;
            case ETYPE_U_CHAR: returnCode = listAppend(&pList, &(pArray -> u.pUChar[i]), pArray -> type, pArray -> size); break;
            case ETYPE_SHORT: returnCode = listAppend(&pList, &(pArray -> u.pShort[i]), pArray -> type, pArray -> size); break;
            case ETYPE_U_SHORT: returnCode = listAppend(&pList, &(pArray -> u.pUShort[i]), pArray -> type, pArray -> size); break;
            case ETYPE_INT: returnCode = listAppend(&pList, &(pArray -> u.pInt[i]), pArray -> type, pArray -> size); break;
            case ETYPE_U_INT: returnCode = listAppend(&pList, &(pArray -> u.pUInt[i]), pArray -> type, pArray -> size); break;
            case ETYPE_LONG: returnCode = listAppend(&pList, &(pArray -> u.pLong[i]), pArray -> type, pArray -> size); break;
            case ETYPE_U_LONG: returnCode = listAppend(&pList, &(pArray -> u.pULong[i]), pArray -> type, pArray -> size); break;
            case ETYPE_LONG_LONG: returnCode = listAppend(&pList, &(pArray -> u.pLongLong[i]), pArray -> type, pArray -> size); break;
            case ETYPE_U_LONG_LONG: returnCode = listAppend(&pList, &(pArray -> u.pULongLong[i]), pArray -> type, pArray -> size); break;
            case ETYPE_FLOAT: returnCode = listAppend(&pList, &(pArray -> u.pFloat[i]), pArray -> type, pArray -> size); break;
            case ETYPE_DOUBLE: returnCode = listAppend(&pList, &(pArray -> u.pDouble[i]), pArray -> type, pArray -> size); break;
            case ETYPE_LONG_DOUBLE: returnCode = listAppend(&pList, &(pArray -> u.pLongDouble[i]), pArray -> type, pArray -> size); break;
            case ETYPE_STRING: returnCode = listAppend(&pList, &(pArray -> u.ppString[i]), pArray -> type, strlen(pArray -> u.ppString[i]) + 1); break;
            case ETYPE_LIST: returnCode = listAppend(&pList, &(pArray -> u.ppList[i]), pArray -> type, pArray -> size); break;
            case ETYPE_STRUCT: returnCode = listAppend(&pList, &(pArray -> u.ppStruct[i]), pArray -> type, pArray -> size); break;
            default: returnCode = FAILURE;
        }

        if (returnCode == FAILURE)
        {
            listClear(&pList);
            return NULL;
        }
    }

    return pList;
}

/******************************************************************************/
// FUNCTION: listFromTable()
//     Converts a C language table into a LIST
// PARAMETERS:
//     pTable: A pointer to a C-language table
//     type: the ETYPE of elements of the table
//     size: the size in bytes of elements of the table
//     length: the number of elements of the table
// RETURN CODE:
//     A pointer to an allocated LIST
/******************************************************************************/
EXPORT LIST* listFromTable(void* pTable, ETYPE type, size_t size, long length)
{
    ARRAY array;

    array.type = type;
    array.size = size;
    array.length = length;
    array.u.pGeneric = pTable;

    return listFromArray(&array);
}

