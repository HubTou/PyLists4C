// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>
#include "global.h"

/******************************************************************************/
// FUNCTION: listPrint()
//     Prints a Python-style LIST representation to stdout
// PARAMETERS:
//     pList: A pointer to a LIST
/******************************************************************************/
EXPORT void listPrint(LIST* pList)
{
    LIST* pElement = pList;
    long i = 0;

    printf("[");
    while (pElement != NULL)
    {
        char* pCharacter;
        char* string = NULL;

        if (i)
            printf(", ");
        switch (pElement -> type)
        {
            case ETYPE_NULL: printf("NULL"); break;
            case ETYPE_CHAR: printf("%c", *((char*) pElement -> pValue)); break;
            case ETYPE_U_CHAR: printf("%c", *((unsigned char*) pElement -> pValue)); break;
            case ETYPE_SHORT: printf("%hd", *((short*) pElement -> pValue)); break;
            case ETYPE_U_SHORT: printf("%hu", *((unsigned short*) pElement -> pValue)); break;
            case ETYPE_INT: printf("%d", *((int*) pElement -> pValue)); break;
            case ETYPE_U_INT: printf("%u", *((unsigned int*) pElement -> pValue)); break;
            case ETYPE_LONG: printf("%ld", *((long*) pElement -> pValue)); break;
            case ETYPE_U_LONG: printf("%lu", *((unsigned long*) pElement -> pValue)); break;
            case ETYPE_LONG_LONG: printf("%lld", *((long long*) pElement -> pValue)); break;
            case ETYPE_U_LONG_LONG: printf("%llu", *((unsigned long long*) pElement -> pValue)); break;
            case ETYPE_FLOAT: printf("%f", *((float*) pElement -> pValue)); break;
            case ETYPE_DOUBLE: printf("%lf", *((double*) pElement -> pValue)); break;
            case ETYPE_LONG_DOUBLE: printf("%Lf", *((long double*) pElement -> pValue)); break;
            case ETYPE_STRING:
                printf("'");
                for (pCharacter = (char*) pElement -> pValue; *pCharacter != 0; pCharacter++)
                {
                    if (*pCharacter == '\'' || *pCharacter == '\\')
                        printf("\\");
                    printf("%c", *pCharacter);
                }        
                printf("'");
                break;
            case ETYPE_LIST: string = listStr(pElement -> pValue); printf("%s", string); listFreeStr(&string); break;
            case ETYPE_STRUCT: listPrintStruct(pElement -> pValue, pElement -> size); break;
            default: printf("@%p", pElement -> pValue);
        }
        i++;
        pElement = pElement -> pNext;
    }
    printf("]\n");
}

