// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <pylists4c.h>

/******************************************************************************/
// FUNCTION: listSetIterator()
//     Defines a LIST_ITERATOR from a LIST_ELEMENT of a LIST
// PARAMETERS:
//     element: an element of a LIST
// RETURN VALUE:
//     
// CAVEATS:
//     It's quicker to write:
//         LIST_ITERATOR i = listGet(0);
//     or
//         LIST_ITERATOR i = listGet(-1);
//     but the whole idea is to make something readable...
/******************************************************************************/
EXPORT LIST_ITERATOR listSetIterator(LIST_ELEMENT element)
{
    return element;
}

/******************************************************************************/
// FUNCTION: listNext()
//     Returns the next LIST_ELEMENT of a LIST starting from a LIST_ITERATOR
// PARAMETERS:
//     pIterator: an iterator of a LIST
// RETURN VALUE:
//     The next LIST_ELEMENT or NULL if there are no more elements
/******************************************************************************/
EXPORT LIST_ELEMENT listNext(LIST_ITERATOR* pIterator)
{
    LIST_ELEMENT element;

    if (*pIterator == NULL)
        return NULL;

    element = *pIterator;
    *pIterator = (*pIterator) -> pNext;

    return element;
}

/******************************************************************************/
// FUNCTION: listPrevious()
//     Returns the previous LIST_ELEMENT of a LIST starting from a LIST_ITERATOR
// PARAMETERS:
//     pIterator: an iterator of a LIST
// RETURN VALUE:
//     The previous LIST_ELEMENT or NULL if there are no more elements
/******************************************************************************/
EXPORT LIST_ELEMENT listPrevious(LIST_ITERATOR* pIterator)
{
    LIST_ELEMENT element;

    if (*pIterator == NULL)
        return NULL;

    element = *pIterator;
    *pIterator = (*pIterator) -> pPrevious;

    return element;
}

