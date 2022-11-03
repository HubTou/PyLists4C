// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <string.h>

#include <pylists4c.h>
#include "global.h"

#define BUFFER_SIZE 8192

STATUS listAddStringPart(LIST**, size_t*, char*);

/******************************************************************************/
// FUNCTION: listStr()
// ALIAS: listAscii()
// ALIAS: listRepr()
//     Returns a pointer to a string containing a Python-style LIST
//     representation
// PARAMETERS:
//     pList: A pointer to a LIST
// RETURN CODE:
//     A pointer to an allocated string
/******************************************************************************/
EXPORT STRING listStr(LIST* pList)
{
    char* fullString = NULL;
    size_t fullLength = 0;
    LIST* pStringParts = NULL;

    long n = 0;
    LIST* pElement = pList;

    if (listAddStringPart(&pStringParts, &fullLength, "[") == FAILURE)
        return NULL;

    while (pElement != NULL)
    {
        char buffer[BUFFER_SIZE];
        STRING string = NULL;
        STRING stringPart = NULL;
        BOOLEAN freeRequested = FALSE;
        int i, j;

        if (n)
            if (listAddStringPart(&pStringParts, &fullLength, ", ") == FAILURE)
                return NULL;

        switch (pElement -> type)
        {
            case ETYPE_NULL: sprintf(buffer, "NULL"); stringPart = buffer; break;
            case ETYPE_CHAR: sprintf(buffer, "%c", *((char*) pElement -> pValue)); stringPart = buffer; break;
            case ETYPE_U_CHAR: sprintf(buffer, "%c", *((unsigned char*) pElement -> pValue)); stringPart = buffer; break;
            case ETYPE_SHORT: sprintf(buffer, "%hd", *((short*) pElement -> pValue)); stringPart = buffer; break;
            case ETYPE_U_SHORT: sprintf(buffer, "%hu", *((unsigned short*) pElement -> pValue)); stringPart = buffer; break;
            case ETYPE_INT: sprintf(buffer, "%d", *((int*) pElement -> pValue)); stringPart = buffer; break;
            case ETYPE_U_INT: sprintf(buffer, "%u", *((unsigned int*) pElement -> pValue)); stringPart = buffer; break;
            case ETYPE_LONG: sprintf(buffer, "%ld", *((long*) pElement -> pValue)); stringPart = buffer; break;
            case ETYPE_U_LONG: sprintf(buffer, "%lu", *((unsigned long*) pElement -> pValue)); stringPart = buffer; break;
            case ETYPE_LONG_LONG: sprintf(buffer, "%lld", *((long long*) pElement -> pValue)); stringPart = buffer; break;
            case ETYPE_U_LONG_LONG: sprintf(buffer, "%llu", *((unsigned long long*) pElement -> pValue)); stringPart = buffer; break;
            case ETYPE_FLOAT: sprintf(buffer, "%f", *((float*) pElement -> pValue)); stringPart = buffer; break;
            case ETYPE_DOUBLE: sprintf(buffer, "%lf", *((double*) pElement -> pValue)); stringPart = buffer; break;
            case ETYPE_LONG_DOUBLE: sprintf(buffer, "%Lf", *((long double*) pElement -> pValue)); stringPart = buffer; break;
            case ETYPE_STRING:
                i = 0;
                string = (char*) pElement -> pValue;
                j = 0;
                buffer[j++] = '\'';
                while (string[i])
                {
                    for (; string[i] && j < BUFFER_SIZE - 2; i++, j++)
                    {
                        if (string[i] == '\\' || string[i] == '\'')
                            buffer[j++] = '\\';
                        buffer[j] = string[i];
                    }
                    if (j == BUFFER_SIZE - 2)
                    {
                        buffer[j] = 0;
                        stringPart = buffer;
                        if (listAddStringPart(&pStringParts, &fullLength, stringPart) == FAILURE)
                            return NULL;

                        j = 0;
                        stringPart = NULL;
                    }
                }
                buffer[j++] = '\'';
                buffer[j++] = 0;
                stringPart = buffer;
                break;
            case ETYPE_LIST: stringPart = listStr(pElement -> pValue); freeRequested = TRUE; break;
            case ETYPE_STRUCT: listStringStruct(buffer, pElement -> pValue, pElement -> size); stringPart = buffer; break;
            default: sprintf(buffer, "@%p", pElement -> pValue); stringPart = buffer;
        }
        if (listAddStringPart(&pStringParts, &fullLength, stringPart) == FAILURE)
            return NULL;
        if (freeRequested)
            listFreeStr(&stringPart);

        n++;
        pElement = pElement -> pNext;
    }
    if (listAddStringPart(&pStringParts, &fullLength, "]") == FAILURE)
        return NULL;

    // now we allocate a persistent continuous space to store the resulting string
    if ((fullString = malloc(fullLength + 1)) == NULL)
    {
        if (listFatalMallocErrors)
        {
            if (listDebugMessages)
                fprintf(stderr, "CRITICAL: malloc(%zu) failed\n", fullLength + 1);
            listClear(&pStringParts);
            exit(FAILURE);
        }
        else
        {
            if (listDebugMessages)
                fprintf(stderr, "ERROR: malloc(%zu) failed\n", fullLength + 1);
            listClear(&pStringParts);
            return NULL;
        }
    }
    listAllocatedMemory += (fullLength + 1); 
    fullString[0] = 0;
    for (pElement = pStringParts; pElement != NULL; pElement = pElement -> pNext)
#if ! (defined(_WIN32) || defined(_WIN64) )
        strcat(fullString, (char*) (pElement -> pValue));
#else
        strcat_s(fullString, fullLength + 1, (char*) (pElement -> pValue));
#endif
    listClear(&pStringParts);

    return fullString;
}

/******************************************************************************/
INTERNAL STATUS listAddStringPart(LIST** ppStringParts, size_t* pFullLength, char* stringPart)
{
    LIST* pCurrentPart = NULL;
    size_t currentPartLength;
    size_t stringPartLength;

    pCurrentPart = listGetLast(*ppStringParts);
    if (pCurrentPart != NULL)
        currentPartLength = strlen(pCurrentPart -> pValue);
    else
        currentPartLength = BUFFER_SIZE;

    stringPartLength = strlen(stringPart);

    if (currentPartLength + stringPartLength < BUFFER_SIZE)
    {
        // there is enough space to store the string part
#if ! (defined(_WIN32) || defined(_WIN64) )
        strcat(pCurrentPart -> pValue, stringPart);
#else
        strcat_s(pCurrentPart -> pValue, BUFFER_SIZE, stringPart);
#endif
    }
    else
    {
        size_t cellSize;

        if (stringPartLength > BUFFER_SIZE)
            cellSize = stringPartLength + 1;
        else
            cellSize = BUFFER_SIZE;

        // there isn't enough space to store the string part
        if ((listAppend(ppStringParts, stringPart, ETYPE_STRING, cellSize)) == FAILURE)
        {
            listClear(ppStringParts);
            *pFullLength = 0;
            return FAILURE;
        }
    }
    *pFullLength += stringPartLength;

    return SUCCESS;
}

/******************************************************************************/
// FUNCTION: listFreeStr()
//     Frees the memory allocated to a Python-style LIST representation
// PARAMETERS:
//     pString: A pointer to a STRING (which will be resetted to NULL)
/******************************************************************************/
EXPORT void listFreeStr(STRING* pString)
{
    size_t stringLength = strlen(*pString);

    free(*pString);
    *pString = NULL;
    listAllocatedMemory -= (stringLength + 1); 
}

