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
// FUNCTION: listCompareXXX()
//     Returns an integer less than, equal to, or greater than zero
//     if the first argument is considered to be respectively
//     less than, equal to, or greater than the second.
// PARAMETERS:
//     p1: A pointer to the first value
//     p2: A pointer to the second value
// RETURN VALUE:
//     An integer indicating the result of the comparison
/******************************************************************************/

EXPORT int listCompareChar(const void *p1, const void *p2)
{
    long left = *((char*) p1);
    long right = *((char*) p2);

    return ((left > right) - (left < right));
}

EXPORT int listCompareCharCaseInsensitive(const void *p1, const void *p2)
{
    long left = tolower(*((char*) p1));
    long right = tolower(*((char*) p2));

    return ((left > right) - (left < right));
}

EXPORT int listCompareUChar(const void *p1, const void *p2)
{
    long left = *((unsigned char*) p1);
    long right = *((unsigned char*) p2);

    return ((left > right) - (left < right));
}

EXPORT int listCompareUCharCaseInsensitive(const void *p1, const void *p2)
{
    long left = tolower(*((unsigned char*) p1));
    long right = tolower(*((unsigned char*) p2));

    return ((left > right) - (left < right));
}

EXPORT int listCompareShort(const void *p1, const void *p2)
{
    long left = *((short*) p1);
    long right = *((short*) p2);

    return ((left > right) - (left < right));
}

EXPORT int listCompareUShort(const void *p1, const void *p2)
{
    long left = *((unsigned short*) p1);
    long right = *((unsigned short*) p2);

    return ((left > right) - (left < right));
}

EXPORT int listCompareInt(const void *p1, const void *p2)
{
    long left = *((int*) p1);
    long right = *((int*) p2);

    return ((left > right) - (left < right));
}

EXPORT int listCompareUInt(const void *p1, const void *p2)
{
    long left = *((unsigned int*) p1);
    long right = *((unsigned int*) p2);

    return ((left > right) - (left < right));
}

EXPORT int listCompareLong(const void *p1, const void *p2)
{
    long left = *((long*) p1);
    long right = *((long*) p2);

    return ((left > right) - (left < right));
}

EXPORT int listCompareULong(const void *p1, const void *p2)
{
    long left = *((unsigned long*) p1);
    long right = *((unsigned long*) p2);

    return ((left > right) - (left < right));
}

EXPORT int listCompareLongLong(const void *p1, const void *p2)
{
    long left = *((long long*) p1);
    long right = *((long long*) p2);

    return ((left > right) - (left < right));
}

EXPORT int listCompareULongLong(const void *p1, const void *p2)
{
    long left = *((unsigned long long*) p1);
    long right = *((unsigned long long*) p2);

    return ((left > right) - (left < right));
}

EXPORT int listCompareFloat(const void *p1, const void *p2)
{
    long left = *((float*) p1);
    long right = *((float*) p2);

    return ((left > right) - (left < right));
}

EXPORT int listCompareDouble(const void *p1, const void *p2)
{
    long left = *((double*) p1);
    long right = *((double*) p2);

    return ((left > right) - (left < right));
}

EXPORT int listCompareLongDouble(const void *p1, const void *p2)
{
    long left = *((long double*) p1);
    long right = *((long double*) p2);

    return ((left > right) - (left < right));
}

EXPORT int listCompareString(const void *p1, const void *p2)
{
    return strcmp(p1, p2);
}

EXPORT int listCompareStringCaseInsensitive(const void *p1, const void *p2)
{
    return strcasecmp(p1, p2);
}

// There is no need for a listCompareList() function. We don't know how to sort LISTs!

// For STRUCTs see the code in struct.c

EXPORT int listCompareCharReversed(const void *p1, const void *p2)
{
    return -1 * listCompareChar(p1, p2);
}

EXPORT int listCompareCharCaseInsensitiveReversed(const void *p1, const void *p2)
{
    return -1 * listCompareCharCaseInsensitive(p1, p2);
}

EXPORT int listCompareUCharReversed(const void *p1, const void *p2)
{
    return -1 * listCompareUChar(p1, p2);
}

EXPORT int listCompareUCharCaseInsensitiveReversed(const void *p1, const void *p2)
{
    return -1 * listCompareUCharCaseInsensitive(p1, p2);
}

EXPORT int listCompareShortReversed(const void *p1, const void *p2)
{
    return -1 * listCompareShort(p1, p2);
}

EXPORT int listCompareUShortReversed(const void *p1, const void *p2)
{
    return -1 * listCompareUShort(p1, p2);
}

EXPORT int listCompareIntReversed(const void *p1, const void *p2)
{
    return -1 * listCompareInt(p1, p2);
}

EXPORT int listCompareUIntReversed(const void *p1, const void *p2)
{
    return -1 * listCompareUInt(p1, p2);
}

EXPORT int listCompareLongReversed(const void *p1, const void *p2)
{
    return -1 * listCompareLong(p1, p2);
}

EXPORT int listCompareULongReversed(const void *p1, const void *p2)
{
    return -1 * listCompareULong(p1, p2);
}

EXPORT int listCompareLongLongReversed(const void *p1, const void *p2)
{
    return -1 * listCompareLongLong(p1, p2);
}

EXPORT int listCompareULongLongReversed(const void *p1, const void *p2)
{
    return -1 * listCompareULongLong(p1, p2);
}

EXPORT int listCompareFloatReversed(const void *p1, const void *p2)
{
    return -1 * listCompareFloat(p1, p2);
}

EXPORT int listCompareDoubleReversed(const void *p1, const void *p2)
{
    return -1 * listCompareDouble(p1, p2);
}

EXPORT int listCompareLongDoubleReversed(const void *p1, const void *p2)
{
    return -1 * listCompareLongDouble(p1, p2);
}

EXPORT int listCompareStringReversed(const void *p1, const void *p2)
{
    return -1 * listCompareString(p1, p2);
}

EXPORT int listCompareStringCaseInsensitiveReversed(const void *p1, const void *p2)
{
    return -1 * listCompareStringCaseInsensitive(p1, p2);
}

