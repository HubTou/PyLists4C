// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

unsigned long listAllocatedMemory = 0;

/******************************************************************************/
// FUNCTION: listGetAllocatedMemory()
//     Returns the quantity of allocated/unfreed memory used by this library
// RETURN VALUE:
//     An unsigned long value
/******************************************************************************/
EXPORT unsigned long listGetAllocatedMemory()
{
    return listAllocatedMemory;
}

