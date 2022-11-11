// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <ctype.h>
#include <string.h>
#if ! (defined(_WIN32) || defined(_WIN64) )
# include <strings.h>
#endif

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listAreEqual()
//     Tests if two LISTs contain the same values
// PARAMETERS:
//     pList1: A pointer to the first LIST
//     pList2: A pointer to the second LIST
//     caseInsensitive: A BOOLEAN indicating is to be done without regard to case
// RETURN VALUE:
//     A BOOLEAN giving the answer
/******************************************************************************/
EXPORT BOOLEAN listAreEqual(LIST* pList1, LIST* pList2, BOOLEAN caseInsensitive)
{
    for (; pList1 != NULL && pList2 != NULL; pList1 = pList1 -> pNext, pList2 = pList2 -> pNext)
    {
        if (pList1 -> type != pList2 -> type)
            return FALSE;

        if (pList1 -> type == ETYPE_NULL)
            return TRUE;

        if (pList1 -> type == ETYPE_STRING || pList1 -> type == ETYPE_STRUCT)
        {
            if (pList1 -> size != pList2 -> size)
                return FALSE;
        }

        if (pList1 -> type == ETYPE_LIST)
        {
            if (listAreEqual(pList1 -> pValue, pList2 -> pValue, caseInsensitive) == FALSE)
                return FALSE;
        }
        else if (caseInsensitive == FALSE || ! (pList1 -> type == ETYPE_CHAR || pList1 -> type == ETYPE_U_CHAR || pList1 -> type == ETYPE_STRING))
        {
            if (memcmp(pList1 -> pValue, pList2 -> pValue, pList1 -> size))
                return FALSE;
        }
        else if (pList1 -> type == ETYPE_CHAR)
        {
            if (tolower(*((char*) pList1 -> pValue)) != tolower(*((char*) pList2 -> pValue)))
                return FALSE;
        }
        else if (pList1 -> type == ETYPE_U_CHAR)
        {
            if (tolower(*((unsigned char*) pList1 -> pValue)) != tolower(*((unsigned char*) pList2 -> pValue)))
                return FALSE;
        }
        else // if (pList1 -> type == ETYPE_STRING)
        {
            if (strcasecmp(pList1 -> pValue, pList2 -> pValue) != 0)
                return FALSE;
        }
    }

    return (pList1 != NULL || pList2 != NULL);
}

