// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listValueXXX()
//     Returns the element value in the requested type
// PARAMETERS:
//     element: A LIST_ELEMENT of a LIST
// RETURN VALUE:
//     The element value in the requested type 
/******************************************************************************/
EXPORT char listValueChar(LIST_ELEMENT element)
{
    return *((char*) element -> pValue);
}

EXPORT unsigned char listValueUChar(LIST_ELEMENT element)
{
    return *((unsigned char*) element -> pValue);
}

EXPORT short listValueShort(LIST_ELEMENT element)
{
    return *((short*) element -> pValue);
}

EXPORT unsigned short listValueUShort(LIST_ELEMENT element)
{
    return *((unsigned short*) element -> pValue);
}

EXPORT int listValueInt(LIST_ELEMENT element)
{
    return *((int*) element -> pValue);
}

EXPORT unsigned int listValueUInt(LIST_ELEMENT element)
{
    return *((unsigned int*) element -> pValue);
}

EXPORT long listValueLong(LIST_ELEMENT element)
{
    return *((long*) element -> pValue);
}

EXPORT unsigned long listValueULong(LIST_ELEMENT element)
{
    return *((unsigned long*) element -> pValue);
}

EXPORT long long listValueLongLong(LIST_ELEMENT element)
{
    return *((long long*) element -> pValue);
}

EXPORT unsigned long long listValueULongLong(LIST_ELEMENT element)
{
    return *((unsigned long long*) element -> pValue);
}

EXPORT float listValueFloat(LIST_ELEMENT element)
{
    return *((float*) element -> pValue);
}

EXPORT double listValueDouble(LIST_ELEMENT element)
{
    return *((double*) element -> pValue);
}

EXPORT long double listValueLongDouble(LIST_ELEMENT element)
{
    return *((long double*) element -> pValue);
}

EXPORT STRING listValueString(LIST_ELEMENT element)
{
    return (STRING) element -> pValue;
}

