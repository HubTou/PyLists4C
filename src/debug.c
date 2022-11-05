// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>
#include "global.h"

#define MAX_NAME_SIZE 80
#define BUFFER_SIZE (MAX_NAME_SIZE + 22) // 22 = '[' + 19 digits 64 bits long + ']' + '\0'

/******************************************************************************/
// FUNCTION: listDebug()
//     Prints all LIST details to stderr
// PARAMETERS:
//     pList: A pointer to a LIST
//     name: the name of your LIST variable or NULL
/******************************************************************************/
EXPORT void listDebug(LIST* pList, STRING name)
{
    LIST* pElement = NULL;
    long i = 0;
    char subname[BUFFER_SIZE];
    char* pCharacter;

    pElement = pList;
    while (pElement != NULL)
    {
        if (name == NULL)
            fprintf(stderr, "list");
        else
            fprintf(stderr, "%s", name);
        fprintf(stderr, "[%ld] = address: @%p / contents: @%p <-- ", i, pElement, pElement -> pPrevious);
        switch (pElement -> type)
        {
            case ETYPE_NULL: fprintf(stderr, "(NULL, "); break;
            case ETYPE_CHAR: fprintf(stderr, "%c (%s, ", *((char*) pElement -> pValue), "char"); break;
            case ETYPE_U_CHAR: fprintf(stderr, "%c (%s, ", *((unsigned char*) pElement -> pValue), "unsigned char"); break;
            case ETYPE_SHORT: fprintf(stderr, "%hd (%s, ", *((short*) pElement -> pValue), "short"); break;
            case ETYPE_U_SHORT: fprintf(stderr, "%hu (%s, ", *((unsigned short*) pElement -> pValue), "unsigned short"); break;
            case ETYPE_INT: fprintf(stderr, "%d (%s, ", *((int*) pElement -> pValue), "int"); break;
            case ETYPE_U_INT: fprintf(stderr, "%u (%s, ", *((unsigned int*) pElement -> pValue), "unsigned int"); break;
            case ETYPE_LONG: fprintf(stderr, "%ld (%s, ", *((long*) pElement -> pValue), "long"); break;
            case ETYPE_U_LONG: fprintf(stderr, "%lu (%s, ", *((unsigned long*) pElement -> pValue), "unsigned long"); break;
            case ETYPE_LONG_LONG: fprintf(stderr, "%lld (%s, ", *((long long*) pElement -> pValue), "long long"); break;
            case ETYPE_U_LONG_LONG: fprintf(stderr, "%llu (%s, ", *((unsigned long long*) pElement -> pValue), "unsigned long long"); break;
            case ETYPE_FLOAT: fprintf(stderr, "%f (%s, ", *((float*) pElement -> pValue), "float"); break;
            case ETYPE_DOUBLE: fprintf(stderr, "%lf (%s, ", *((double*) pElement -> pValue), "double"); break;
            case ETYPE_LONG_DOUBLE: fprintf(stderr, "%Lf (%s, ", *((long double*) pElement -> pValue), "long double"); break;
            case ETYPE_STRING:
                fprintf(stderr, "'");
                for (pCharacter = (char*) pElement -> pValue; *pCharacter != 0; pCharacter++)
                {
                    if (*pCharacter == '\'' || *pCharacter == '\\')
                        fprintf(stderr, "\\");
                    fprintf(stderr, "%c", *pCharacter);
                }        
                fprintf(stderr, "' (STRING, ");
                break;
            case ETYPE_LIST:
                fprintf(stderr, "%s (%s, %zu byte%s) --> @%p\n", (pElement -> pValue)?"see below":"[]", "LIST*", pElement -> size, (pElement -> size > 1)?"s":"", pElement -> pNext);
                if (name == NULL)
                    snprintf(subname, BUFFER_SIZE, "list[%ld]", i);
                else
                    snprintf(subname, BUFFER_SIZE, "%.*s[%ld]", MAX_NAME_SIZE, name, i);
                listDebug(pElement -> pValue, subname);
                break;
            case ETYPE_STRUCT: listDebugStruct(pElement -> pValue, pElement -> size); break;
            default: fprintf(stderr, "@%p (%d, ", pElement -> pValue, pElement -> type);
        }
        if (pElement -> type != ETYPE_LIST)
            fprintf(stderr, "%zu byte%s) --> @%p\n", pElement -> size, (pElement -> size > 1)?"s":"", pElement -> pNext);
        i++;
        pElement = pElement -> pNext;
    }
}

