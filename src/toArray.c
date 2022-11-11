// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <string.h>

#include <pylists4c.h>
#include "global.h"

/******************************************************************************/
// FUNCTION: listToArray()
//     Converts a LIST into an ARRAY
//     (you'll have to free it after use with listFreeArray())
// PARAMETERS:
//     pList: A pointer to a LIST
// RETURN CODE:
//     A pointer to an allocated ARRAY
// CAVEATS:
//     Only works on homogeneous LISTs of non ETYPE_NULL elements
/******************************************************************************/
EXPORT ARRAY* listToArray(LIST* pList)
{
    ARRAY* pArray;
    LIST_STATS stats;
    size_t elementSize, totalSize;
    long i;
    LIST* pElement;

    if (pList == NULL)
        return NULL;

    listStats(pList, &stats);
    if (stats.isHomogeneous == FALSE || stats.homogeneousType == ETYPE_NULL)
        return NULL;

    if ((pArray = malloc(sizeof(ARRAY))) == NULL)
    {
        if (listFatalMallocErrors)
        {
            if (listDebugMessages)
                fprintf(stderr, "CRITICAL: malloc(%zu) failed\n", sizeof(ARRAY));
            exit(FAILURE);
        }
        else
        {
            if (listDebugMessages)
                fprintf(stderr, "ERROR: malloc(%zu) failed\n", sizeof(ARRAY));
            return NULL;
        }
    }

    if (stats.homogeneousType == ETYPE_STRING)
    {
        // we need to allocate a first layer of pointers to strings plus the space for the strings themselves
        elementSize = stats.largestString + 1;
        totalSize = (sizeof(char*) + elementSize) * stats.length;
    }
    else if (stats.homogeneousType == ETYPE_LIST)
    {
        // we'll only allocate a first layer of pointer to LISTs
        elementSize = sizeof(LIST*); // TODO
        totalSize = sizeof(LIST*) * stats.length;
    }
    else if (stats.homogeneousType == ETYPE_STRUCT)
    {
        // we need to allocate a first layer of pointers to STRUCTs plus the space for the STRUCTs themselves
        elementSize = stats.largestStruct;
        totalSize = (sizeof(void*) + elementSize) * stats.length;
    }
    else
    {
        // we'll only allocate the space of the elements themselves (them being of known types)
        elementSize = stats.homogeneousSize;
        totalSize = elementSize * stats.length;
    }

    if ((pArray -> u.pGeneric = malloc(totalSize)) == NULL)
    {
        if (listFatalMallocErrors)
        {
            if (listDebugMessages)
                fprintf(stderr, "CRITICAL: malloc(%zu) failed\n", totalSize);
            free(pArray);
            exit(FAILURE);
        }
        else
        {
            if (listDebugMessages)
                fprintf(stderr, "ERROR: malloc(%zu) failed\n", totalSize);
            free(pArray);
            return NULL;
        }
    }

    // for STRINGs and STRUCTs, we need to initialize the first layer of pointers
    if (stats.homogeneousType == ETYPE_STRING || stats.homogeneousType == ETYPE_STRUCT)
    {
        long j;
        char** ppAddress = pArray -> u.pGeneric;

        for (j = 0; j < stats.length; j++)
            ppAddress[j] = pArray -> u.pGeneric + (sizeof(char*) * stats.length) + (elementSize * j);
    }

    pArray -> type = pList -> type;
    pArray -> size = elementSize;
    pArray -> length = stats.length;

    for (pElement = pList, i = 0; pElement != NULL; pElement = pElement -> pNext, i++)
    {
        switch (pElement -> type)
        {
            case ETYPE_CHAR: pArray -> u.pChar[i] = *((char*) pElement -> pValue); break;
            case ETYPE_U_CHAR: pArray -> u.pUChar[i] = *((unsigned char*) pElement -> pValue); break;
            case ETYPE_SHORT: pArray -> u.pShort[i] = *((short*) pElement -> pValue); break;
            case ETYPE_U_SHORT: pArray -> u.pUShort[i] = *((unsigned short*) pElement -> pValue); break;
            case ETYPE_INT: pArray -> u.pInt[i] = *((int*) pElement -> pValue); break;
            case ETYPE_U_INT: pArray -> u.pUInt[i] = *((unsigned int*) pElement -> pValue); break;
            case ETYPE_LONG: pArray -> u.pLong[i] = *((long*) pElement -> pValue); break;
            case ETYPE_U_LONG: pArray -> u.pULong[i] = *((unsigned long*) pElement -> pValue); break;
            case ETYPE_LONG_LONG: pArray -> u.pLongLong[i] = *((long long*) pElement -> pValue); break;
            case ETYPE_U_LONG_LONG: pArray -> u.pULongLong[i] = *((unsigned long long*) pElement -> pValue); break;
            case ETYPE_FLOAT: pArray -> u.pFloat[i] = *((float*) pElement -> pValue); break;
            case ETYPE_DOUBLE: pArray -> u.pDouble[i] = *((double*) pElement -> pValue); break;
            case ETYPE_LONG_DOUBLE: pArray -> u.pLongDouble[i] = *((long double*) pElement -> pValue); break;
            case ETYPE_STRING:
#if ! (defined(_WIN32) || defined(_WIN64) )
                strcpy(pArray -> u.ppString[i], (char*) pElement -> pValue);
#else
                strcpy_s(pArray -> u.ppString[i], pArray -> size, (char*) pElement -> pValue);
#endif
                break;
            case ETYPE_LIST: pArray -> u.ppList[i] = listCopy(pElement -> pValue); break;
            case ETYPE_STRUCT: memcpy(pArray -> u.ppStruct[i], pElement -> pValue, pElement -> size); break;
            default: ; // discarded...
        }
    }

    listAllocatedMemory += sizeof(ARRAY) + totalSize;

    return pArray;
}

/******************************************************************************/
// FUNCTION: listFreeArray()
//     Frees the memory allocated to an ARRAY
// PARAMETERS:
//     ppArray: a pointer to a pointer to an ARRAY
/******************************************************************************/
EXPORT void listFreeArray(ARRAY** ppArray)
{
    if ((*ppArray) -> type == ETYPE_STRING)
        listAllocatedMemory -= (sizeof(ARRAY) + ((*ppArray) -> length * (sizeof(char*) + (*ppArray) -> size)));
    else if ((*ppArray) -> type == ETYPE_STRUCT)
        listAllocatedMemory -= (sizeof(ARRAY) + ((*ppArray) -> length * (sizeof(void*) +(*ppArray) -> size)));
    else
        listAllocatedMemory -= (sizeof(ARRAY) + ((*ppArray) -> length * (*ppArray) -> size));

    if ((*ppArray) -> type != ETYPE_LIST)
        free((*ppArray) -> u.pGeneric);
    else
        for (long i = 0; i < (*ppArray) -> length; i++)
            listClear(&((*ppArray) -> u.ppList[i]));

    free(*ppArray);
    *ppArray = NULL;
}

