// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <limits.h>
#include <string.h>

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listStats()
//     Fills statistics about a LIST in one walkthrough
// PARAMETERS:
//     pList: A pointer to a LIST
//     pStats: The address of a LIST_STATS structure to fill
/******************************************************************************/
EXPORT void listStats(LIST* pList, LIST_STATS* pStats)
{
    LIST* pElement;

    memset(pStats, 0, sizeof(LIST_STATS));
    pStats -> smallestString = ULONG_MAX;
    pStats -> smallestStruct = ULONG_MAX;
    pStats -> shortestArray = LONG_MAX;
    pStats -> shortestList = LONG_MAX;
    pStats -> shortestDict = LONG_MAX;
    pStats -> isHomogeneous = TRUE;
    pStats -> homogeneousType = ETYPE_UNDEFINED;

    for (pElement = pList; pElement != NULL; pElement = pElement -> pNext)
    {
        size_t length;
        LIST_STATS subListStats;

        pStats -> length++;

        switch (pElement -> type)
        {
            case ETYPE_NULL: pStats -> nullCount++; break;
            case ETYPE_CHAR: pStats -> charCount++; break;
            case ETYPE_U_CHAR: pStats -> uCharCount++; break;
            case ETYPE_SHORT: pStats -> shortCount++; break;
            case ETYPE_U_SHORT: pStats -> uShortCount++; break;
            case ETYPE_INT: pStats -> intCount++; break;
            case ETYPE_U_INT: pStats -> uIntCount++; break;
            case ETYPE_LONG: pStats -> longCount++; break;
            case ETYPE_U_LONG: pStats -> uLongCount++; break;
            case ETYPE_LONG_LONG: pStats -> longLongCount++; break;
            case ETYPE_U_LONG_LONG: pStats -> uLongLongCount++; break;
            case ETYPE_FLOAT: pStats -> floatCount++; break;
            case ETYPE_DOUBLE: pStats -> doubleCount++; break;
            case ETYPE_LONG_DOUBLE: pStats -> longDoubleCount++; break;
            case ETYPE_STRING:
                pStats -> stringCount++;
                length = strlen(pElement -> pValue);
                if (length < pStats -> smallestString)
                    pStats -> smallestString = length;
                if (length > pStats -> largestString)
                    pStats -> largestString = length;
                break;
            case ETYPE_ARRAY:
                pStats -> arrayCount++;
                if (((ARRAY*) (pElement -> pValue)) -> length < pStats -> shortestArray)
                    pStats -> shortestArray = ((ARRAY*) (pElement -> pValue)) -> length;
                if (((ARRAY*) (pElement -> pValue)) -> length > pStats -> longestArray)
                    pStats -> longestArray = ((ARRAY*) (pElement -> pValue)) -> length;
                break;
            case ETYPE_LIST:
                pStats -> listCount++;
                listStats(pElement -> pValue, &subListStats);
                if (subListStats.length < pStats -> shortestList)
                    pStats -> shortestList = subListStats.length;
                if (subListStats.length > pStats -> longestList)
                    pStats -> longestList = subListStats.length;
                break;
            case ETYPE_DICT:
                pStats -> dictCount++;
                // We'll need to compute shortest/longest DICTs if we implement them
                break;
            case ETYPE_STRUCT:
                pStats -> structCount++;
                if (pElement -> size < pStats -> smallestStruct)
                    pStats -> smallestStruct = pElement -> size;
                if (pElement -> size > pStats -> largestStruct)
                    pStats -> largestStruct = pElement -> size;
                break;
            default: pStats -> unknownCount++;
        }

        if (pStats -> homogeneousType == ETYPE_UNDEFINED)
        {
            pStats -> homogeneousType = pElement -> type;
            pStats -> homogeneousSize = pElement -> size;
        }
        else if (pStats -> homogeneousType != pElement -> type)
            pStats -> isHomogeneous = FALSE;
        else if (pStats -> homogeneousType == ETYPE_STRUCT && pStats -> homogeneousSize != pElement -> size)
            pStats -> isHomogeneous = FALSE;

        pStats -> pLastElement = pElement;

        pStats -> memoryUsed += sizeof(LIST) + pElement -> size;
        if (pElement -> type == ETYPE_LIST)
            pStats -> memoryUsed += subListStats.memoryUsed;
        // There'll be something to do for ETYPE_ARRAY and ETYPE_DICT if we implement them
    }

    if (! pStats -> stringCount)
        pStats -> smallestString = 0;
    if (! pStats -> structCount)
        pStats -> smallestStruct = 0;
    if (! pStats -> arrayCount)
        pStats -> shortestArray = 0;
    if (! pStats -> listCount)
        pStats -> shortestList = 0;
    if (! pStats -> dictCount)
        pStats -> shortestDict = 0;
}

