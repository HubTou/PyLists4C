// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <string.h>

#include <pylists4c.h>
#include "global.h"

/******************************************************************************/
// FUNCTION: listCreateElement()
//     Creates an unlinked LIST element
// PARAMETERS:
//     pValue: A pointer to the new value
//     type: The ETYPE of that value
//     size: The size in bytes of that value
// RETURN VALUE:
//     A pointer to the new element
/******************************************************************************/
EXPORT LIST* listCreateElement(void* pValue, ETYPE type, size_t size)
{
    LIST* pElement = NULL;

    if ((pElement = malloc(sizeof(LIST))) == NULL)
    {
        if (listFatalMallocErrors)
        {
            if (listDebugMessages)
                fprintf(stderr, "CRITICAL: malloc(%zu) failed\n", sizeof(LIST));
            exit(FAILURE);
        }
        else
        {
            if (listDebugMessages)
                fprintf(stderr, "ERROR: malloc(%zu) failed\n", sizeof(LIST));
            return NULL;
        }
    }

    if ((pElement -> pValue = malloc(size)) == NULL)
    {
        free(pElement);
        if (listFatalMallocErrors)
        {
            if (listDebugMessages)
                fprintf(stderr, "CRITICAL: malloc(%zu) failed\n", size);
            exit(FAILURE);
        }
        else
        {
            if (listDebugMessages)
                fprintf(stderr, "ERROR: malloc(%zu) failed\n", size);
            return NULL;
        }
    }

    if (type == ETYPE_LIST)
        pElement -> pValue = listCopy(pValue);
    else if (pValue != NULL)
    {
        if (type != ETYPE_STRING)
            memcpy(pElement -> pValue, pValue, size);
        else
        {
            memset(pElement -> pValue, 0, size);
#if ! (defined(_WIN32) || defined(_WIN64) )
            strncpy(pElement -> pValue, pValue, size - 1);
#else
            strncpy_s(pElement -> pValue, size, pValue, size - 1);
#endif
        }
    }
    else
        memset(pElement -> pValue, 0, size);
    pElement -> size = size;
    pElement -> type = type;
    pElement -> pPrevious = NULL;
    pElement -> pNext = NULL;

    listAllocatedMemory += sizeof(LIST) + size;

    return pElement;
}

