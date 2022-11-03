// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <ctype.h>
#include <string.h>
#if ! (defined(_WIN32) || defined(_WIN64) )
# include <strings.h>
#endif

#include <pylists4c.h>
#include "global.h"

/******************************************************************************/
// FUNCTION: listInsertSorted()
//     Inserts an element in a sorted LIST
// PARAMETERS:
//     ppList: A pointer to a pointer to a LIST
//     pValue: A pointer to the new value
//     type: The ETYPE of that value
//     size: The size in bytes of that value
//     reversed: A BOOLEAN indicating the sort order
//     caseInsensitive: A BOOLEAN specifying how to handle char and STRING
//     noDuplicates: A BOOLEAN indicating if duplicate values are discarded
// RETURN VALUE:
//     A STATUS code
// CAVEATS:
//     Assumes LIST is already sorted
//     Groups values by ETYPE when LIST is not homogeneous
//     Doesn't fully sort sub LISTs (before and after being hard to define...)
//     but they are still added to the LIST.
/******************************************************************************/
EXPORT STATUS listInsertSorted(LIST** ppList, void* pValue, ETYPE type, size_t size, BOOLEAN reversed, BOOLEAN caseInsensitive, BOOLEAN noDuplicates)
{
    LIST* pNewElement = NULL;
    LIST* pElement = NULL;
    LIST* pPreviousElement = NULL;

    if ((pNewElement = listCreateElement(pValue, type, size)) == NULL)
        return FAILURE;

    if (*ppList == NULL)
    {
        *ppList = pNewElement;
        return SUCCESS;
    }
    
    for (pElement = *ppList, pPreviousElement = NULL; pElement != NULL; pPreviousElement = pElement, pElement = pElement -> pNext)
    {
        BOOLEAN foundPosition = FALSE;

        if (pElement -> type == type)
        {
            int comparison;

            switch (pElement -> type)
            {
                case ETYPE_SHORT:
                    if (*((short*) pValue) < *((short*) pElement -> pValue))
                    {
                        if (! reversed)
                            foundPosition = TRUE;
                    }
                    else if (*((short*) pValue) > *((short*) pElement -> pValue))
                    {
                        if (reversed)
                            foundPosition = TRUE;
                    }
                    else
                    {
                        if (noDuplicates)
                        {
                            listClear(&pNewElement);
                            return SUCCESS;
                        }
                        else
                            foundPosition = TRUE;
                    }
                    break;

                case ETYPE_U_SHORT:
                    if (*((unsigned short*) pValue) < *((unsigned short*) pElement -> pValue))
                    {
                        if (! reversed)
                            foundPosition = TRUE;
                    }
                    else if (*((unsigned short*) pValue) > *((unsigned short*) pElement -> pValue))
                    {
                        if (reversed)
                            foundPosition = TRUE;
                    }
                    else
                    {
                        if (noDuplicates)
                        {
                            listClear(&pNewElement);
                            return SUCCESS;
                        }
                        else
                            foundPosition = TRUE;
                    }
                    break;

                case ETYPE_INT:
                    if (*((int*) pValue) < *((int*) pElement -> pValue))
                    {
                        if (! reversed)
                            foundPosition = TRUE;
                    }
                    else if (*((int*) pValue) > *((int*) pElement -> pValue))
                    {
                        if (reversed)
                            foundPosition = TRUE;
                    }
                    else
                    {
                        if (noDuplicates)
                        {
                            listClear(&pNewElement);
                            return SUCCESS;
                        }
                        else
                            foundPosition = TRUE;
                    }
                    break;

                case ETYPE_U_INT:
                    if (*((unsigned int*) pValue) < *((unsigned int*) pElement -> pValue))
                    {
                        if (! reversed)
                            foundPosition = TRUE;
                    }
                    else if (*((unsigned int*) pValue) > *((unsigned int*) pElement -> pValue))
                    {
                        if (reversed)
                            foundPosition = TRUE;
                    }
                    else
                    {
                        if (noDuplicates)
                        {
                            listClear(&pNewElement);
                            return SUCCESS;
                        }
                        else
                            foundPosition = TRUE;
                    }
                    break;

                case ETYPE_LONG:
                    if (*((long*) pValue) < *((long*) pElement -> pValue))
                    {
                        if (! reversed)
                            foundPosition = TRUE;
                    }
                    else if (*((long*) pValue) > *((long*) pElement -> pValue))
                    {
                        if (reversed)
                            foundPosition = TRUE;
                    }
                    else
                    {
                        if (noDuplicates)
                        {
                            listClear(&pNewElement);
                            return SUCCESS;
                        }
                        else
                            foundPosition = TRUE;
                    }
                    break;

                case ETYPE_U_LONG:
                    if (*((unsigned long*) pValue) < *((unsigned long*) pElement -> pValue))
                    {
                        if (! reversed)
                            foundPosition = TRUE;
                    }
                    else if (*((unsigned long*) pValue) > *((unsigned long*) pElement -> pValue))
                    {
                        if (reversed)
                            foundPosition = TRUE;
                    }
                    else
                    {
                        if (noDuplicates)
                        {
                            listClear(&pNewElement);
                            return SUCCESS;
                        }
                        else
                            foundPosition = TRUE;
                    }
                    break;

                case ETYPE_LONG_LONG:
                    if (*((long long*) pValue) < *((long long*) pElement -> pValue))
                    {
                        if (! reversed)
                            foundPosition = TRUE;
                    }
                    else if (*((long long*) pValue) > *((long long*) pElement -> pValue))
                    {
                        if (reversed)
                            foundPosition = TRUE;
                    }
                    else
                    {
                        if (noDuplicates)
                        {
                            listClear(&pNewElement);
                            return SUCCESS;
                        }
                        else
                            foundPosition = TRUE;
                    }
                    break;

                case ETYPE_U_LONG_LONG:
                    if (*((unsigned long long*) pValue) < *((unsigned long long*) pElement -> pValue))
                    {
                        if (! reversed)
                            foundPosition = TRUE;
                    }
                    else if (*((unsigned long long*) pValue) > *((unsigned long long*) pElement -> pValue))
                    {
                        if (reversed)
                            foundPosition = TRUE;
                    }
                    else
                    {
                        if (noDuplicates)
                        {
                            listClear(&pNewElement);
                            return SUCCESS;
                        }
                        else
                            foundPosition = TRUE;
                    }
                    break;

                case ETYPE_FLOAT:
                    if (*((float*) pValue) < *((float*) pElement -> pValue))
                    {
                        if (! reversed)
                            foundPosition = TRUE;
                    }
                    else if (*((float*) pValue) > *((float*) pElement -> pValue))
                    {
                        if (reversed)
                            foundPosition = TRUE;
                    }
                    else
                    {
                        if (noDuplicates)
                        {
                            listClear(&pNewElement);
                            return SUCCESS;
                        }
                        else
                            foundPosition = TRUE;
                    }
                    break;

                case ETYPE_DOUBLE:
                    if (*((double*) pValue) < *((double*) pElement -> pValue))
                    {
                        if (! reversed)
                            foundPosition = TRUE;
                    }
                    else if (*((double*) pValue) > *((double*) pElement -> pValue))
                    {
                        if (reversed)
                            foundPosition = TRUE;
                    }
                    else
                    {
                        if (noDuplicates)
                        {
                            listClear(&pNewElement);
                            return SUCCESS;
                        }
                        else
                            foundPosition = TRUE;
                    }
                    break;

                case ETYPE_LONG_DOUBLE:
                    if (*((long double*) pValue) < *((long double*) pElement -> pValue))
                    {
                        if (! reversed)
                            foundPosition = TRUE;
                    }
                    else if (*((long double*) pValue) > *((long double*) pElement -> pValue))
                    {
                        if (reversed)
                            foundPosition = TRUE;
                    }
                    else
                    {
                        if (noDuplicates)
                        {
                            listClear(&pNewElement);
                            return SUCCESS;
                        }
                        else
                            foundPosition = TRUE;
                    }
                    break;

                case ETYPE_CHAR:
                    if (caseInsensitive)
                    {
                        if (tolower(*((char*) pValue)) < tolower(*((char*) pElement -> pValue)))
                        {
                            if (! reversed)
                                foundPosition = TRUE;
                        }
                        else if (tolower(*((char*) pValue)) > tolower(*((char*) pElement -> pValue)))
                        {
                            if (reversed)
                                foundPosition = TRUE;
                        }
                        else
                        {
                            if (noDuplicates)
                            {
                                listClear(&pNewElement);
                                return SUCCESS;
                            }
                            else
                                foundPosition = TRUE;
                        }
                    }
                    else
                    {
                        if (*((char*) pValue) < *((char*) pElement -> pValue))
                        {
                            if (! reversed)
                                foundPosition = TRUE;
                        }
                        else if (*((char*) pValue) > *((char*) pElement -> pValue))
                        {
                            if (reversed)
                                foundPosition = TRUE;
                        }
                        else
                        {
                            if (noDuplicates)
                            {
                                listClear(&pNewElement);
                                return SUCCESS;
                            }
                            else
                                foundPosition = TRUE;
                        }
                    }
                    break;

                case ETYPE_U_CHAR:
                    if (caseInsensitive)
                    {
                        if (tolower(*((unsigned char*) pValue)) < tolower(*((unsigned char*) pElement -> pValue)))
                        {
                            if (! reversed)
                                foundPosition = TRUE;
                        }
                        else if (tolower(*((unsigned char*) pValue)) > tolower(*((unsigned char*) pElement -> pValue)))
                        {
                            if (reversed)
                                foundPosition = TRUE;
                        }
                        else
                        {
                            if (noDuplicates)
                            {
                                listClear(&pNewElement);
                                return SUCCESS;
                            }
                            else
                                foundPosition = TRUE;
                        }
                    }
                    else
                    {
                        if (*((unsigned char*) pValue) < *((unsigned char*) pElement -> pValue))
                        {
                            if (! reversed)
                                foundPosition = TRUE;
                        }
                        else if (*((unsigned char*) pValue) > *((unsigned char*) pElement -> pValue))
                        {
                            if (reversed)
                                foundPosition = TRUE;
                        }
                        else
                        {
                            if (noDuplicates)
                            {
                                listClear(&pNewElement);
                                return SUCCESS;
                            }
                            else
                                foundPosition = TRUE;
                        }
                    }
                    break;

                case ETYPE_STRING:
                    if (caseInsensitive)
                        comparison = strcasecmp(pValue, pElement -> pValue);
                    else
                        comparison = strcmp(pValue, pElement -> pValue);

                    if (comparison < 0)
                    {
                        if (! reversed)
                            foundPosition = TRUE;
                    }
                    else if (comparison > 0)
                    {
                        if (reversed)
                            foundPosition = TRUE;
                    }
                    else
                    {
                        if (noDuplicates)
                        {
                            listClear(&pNewElement);
                            return SUCCESS;
                        }
                        else
                            foundPosition = TRUE;
                    }
                    break;

                case ETYPE_LIST:
                    comparison = (int) listAreEqual(pValue, pElement -> pValue, caseInsensitive);

                    if (comparison)
                    {
                        if (noDuplicates)
                        {
                            listClear(&pNewElement);
                            return SUCCESS;
                        }
                        else
                            foundPosition = TRUE;
                    }
                    break;

                case ETYPE_STRUCT:
                    listStructSize = pElement -> size;
                    comparison = listCompareStruct(pValue, pElement -> pValue);

                    if (comparison < 0)
                    {
                        if (! reversed)
                            foundPosition = TRUE;
                    }
                    else if (comparison > 0)
                    {
                        if (reversed)
                            foundPosition = TRUE;
                    }
                    else
                    {
                        if (noDuplicates)
                        {
                            listClear(&pNewElement);
                            return SUCCESS;
                        }
                        else
                            foundPosition = TRUE;
                    }
                    break;

               default:
                    break;
            }

        }
        else if (type < pElement -> type)
            foundPosition = TRUE;

        if (foundPosition)
        {
            if (pElement -> pPrevious == NULL)
            {
                // Insertion at the head of the list
                *ppList = pNewElement;
            }
            else
            {
                // Insertion in the list
                pNewElement -> pPrevious = pElement -> pPrevious;
                pNewElement -> pPrevious -> pNext = pNewElement;
            }
            pNewElement -> pNext = pElement;
            pElement -> pPrevious = pNewElement;

            return SUCCESS;
        }
    }

    // Insertion at the end of the list
    pPreviousElement -> pNext = pNewElement;
    pNewElement -> pPrevious = pPreviousElement;

    return SUCCESS;
}

