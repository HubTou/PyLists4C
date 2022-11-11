// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <string.h>

#include <pylists4c.h>
#include "global.h"

/******************************************************************************/
// FUNCTION: listChange()
//     Changes the value of the element at the Nth position of a LIST
// PARAMETERS:
//     pList: A pointer to a LIST
//     n: The Nth element where to do the change
//     pValue: A pointer to the new value
//     type: The ETYPE of that value
//     size: The size in bytes of that value
// RETURN VALUE:
//     A STATUS code
/******************************************************************************/
EXPORT STATUS listChange(LIST* pList, long n, void* pValue, ETYPE type, size_t size)
{
    LIST* pElement = listGet(pList, n);
    void* newValue = NULL;

    if (pElement == NULL)
        return FAILURE;

    // Allocate new space
    if (size && (newValue = malloc(size)) == NULL)
    {
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
            return FAILURE;
        }
    }

    // Free the previous value
    if (pElement -> type == ETYPE_LIST)
        listClear((LIST **) &(pElement -> pValue));
    else if (pElement -> type != ETYPE_NULL)
        free(pElement -> pValue);

    listAllocatedMemory -= pElement -> size;

    // Fill the new value
    if (type == ETYPE_LIST)
        newValue = listCopy(pValue);
    else if (pValue != NULL)
    {
        if (type != ETYPE_STRING)
            memcpy(newValue, pValue, size);
        else
        {
            memset(newValue, 0, size);
#if ! (defined(_WIN32) || defined(_WIN64) )
            strncpy(newValue, pValue, size - 1);
#else
            strncpy_s(newValue, size, pValue, size - 1);
#endif
        }
    }
    else if (size)
        memset(newValue, 0, size);

    // Modify the element
    pElement -> pValue = newValue;
    pElement -> size = size;
    pElement -> type = type;

    listAllocatedMemory += size;

    return SUCCESS;
}

