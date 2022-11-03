// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <limits.h>
#include <string.h>

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listStatsPrint()
//     Prints statistics about a LIST to stdout
// PARAMETERS:
//     stats: a LIST_STATS structure to print
//     name: the name of your LIST variable or NULL
/******************************************************************************/
EXPORT void listStatsPrint(LIST_STATS stats, STRING name)
{
    if (name == NULL)
        printf("list:\n");
    else
        printf("%s:\n", name);
        
    printf("  length=%ld\n", stats.length);
    if (stats.nullCount)
        printf("    nullCount=%ld\n", stats.nullCount);
    if (stats.charCount)
        printf("    charCount=%ld\n", stats.charCount);
    if (stats.uCharCount)
        printf("    uCharCount=%ld\n", stats.uCharCount);
    if (stats.shortCount)
        printf("    shortCount=%ld\n", stats.shortCount);
    if (stats.uShortCount)
        printf("    uShortCount=%ld\n", stats.uShortCount);
    if (stats.intCount)
        printf("    intCount=%ld\n", stats.intCount);
    if (stats.uIntCount)
        printf("    uIntCount=%ld\n", stats.uIntCount);
    if (stats.longCount)
        printf("    longCount=%ld\n", stats.longCount);
    if (stats.uLongCount)
        printf("    uLongCount=%ld\n", stats.uLongCount);
    if (stats.longLongCount)
        printf("    longLongCount=%ld\n", stats.longLongCount);
    if (stats.uLongLongCount)
        printf("    uLongLongCount=%ld\n", stats.uLongLongCount);
    if (stats.floatCount)
        printf("    floatCount=%ld\n", stats.floatCount);
    if (stats.doubleCount)
        printf("    doubleCount=%ld\n", stats.doubleCount);
    if (stats.longDoubleCount)
        printf("    longDoubleCount=%ld\n", stats.longDoubleCount);
    if (stats.stringCount)
    {
        printf("    stringCount=%ld\n", stats.stringCount);
        printf("      smallestString=%lu + 1\n", stats.smallestString);
        printf("      largestString=%lu + 1\n", stats.largestString);
    }
    if (stats.arrayCount)
    {
        printf("    arrayCount=%ld\n", stats.arrayCount);
        printf("      shortestArray=%ld\n", stats.shortestArray);
        printf("      longestArray=%ld\n", stats.longestArray);
    }
    if (stats.listCount)
    {
        printf("    listCount=%ld\n", stats.listCount);
        printf("      shortestList=%ld\n", stats.shortestList);
        printf("      longestList=%ld\n", stats.longestList);
    }
    if (stats.dictCount)
    {
        printf("    dictCount=%ld\n", stats.dictCount);
        printf("      shortestDict=%ld\n", stats.shortestDict);
        printf("      longestDict=%ld\n", stats.longestDict);
    }
    if (stats.structCount)
    {
        printf("    structCount=%ld\n", stats.structCount);
        printf("      smallestStruct=%lu\n", stats.smallestStruct);
        printf("      largestStruct=%lu\n", stats.largestStruct);
    }
    if (stats.unknownCount)
        printf("    unknownCount=%ld\n", stats.unknownCount);
    printf("  isHomogeneous=%s\n", (stats.isHomogeneous)?"TRUE":"FALSE");
    if (stats.isHomogeneous)
    {
        printf("    homogeneousType=");
        switch (stats.homogeneousType)
        {
            case ETYPE_CHAR: printf("CHAR\n"); break;
            case ETYPE_U_CHAR: printf("U_CHAR\n"); break;
            case ETYPE_SHORT: printf("SHORT\n"); break;
            case ETYPE_U_SHORT: printf("U_SHORT\n"); break;
            case ETYPE_INT: printf("INT\n"); break;
            case ETYPE_U_INT: printf("U_INT\n"); break;
            case ETYPE_LONG: printf("LONG\n"); break;
            case ETYPE_U_LONG: printf("U_LONG\n"); break;
            case ETYPE_LONG_LONG: printf("LONG_LONG\n"); break;
            case ETYPE_U_LONG_LONG: printf("U_LONG_LONG\n"); break;
            case ETYPE_FLOAT: printf("FLOAT\n"); break;
            case ETYPE_DOUBLE: printf("DOUBLE\n"); break;
            case ETYPE_LONG_DOUBLE: printf("LONG_DOUBLE\n"); break;
            case ETYPE_STRING: printf("STRING\n"); break;
            case ETYPE_LIST: printf("LIST\n"); break;
            case ETYPE_STRUCT: printf("STRUCT\n"); break;
            default: printf("unknown!\n"); break;
        }
        printf("    homogeneousSize=%zu\n", stats.homogeneousSize);
    }
    printf("  pLastElement=@%p\n", stats.pLastElement);
    printf("  memoryUsed=%lu\n", stats.memoryUsed);
}

