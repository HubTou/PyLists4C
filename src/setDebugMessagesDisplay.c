// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

BOOLEAN listDebugMessages = TRUE;

/******************************************************************************/
// FUNCTION: listSetDebugMessagesDisplay()
//     Sets whether or not to print debugging messages to stderr
// PARAMETERS:
//     display: A BOOLEAN with the desired state
/******************************************************************************/
EXPORT void listSetDebugMessagesDisplay(BOOLEAN display)
{
    listDebugMessages = display;
}

