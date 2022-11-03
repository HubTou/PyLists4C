// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

BOOLEAN listFatalMallocErrors = FALSE;

/******************************************************************************/
// FUNCTION: listSetFatalMallocErrors()
//     Sets whether memory allocation errors are fatal or not
// PARAMETERS:
//     fatal: A BOOLEAN with the desired state
/******************************************************************************/
EXPORT void listSetFatalMallocErrors(BOOLEAN fatal)
{
    listFatalMallocErrors = fatal;
}

