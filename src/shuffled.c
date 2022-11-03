// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <time.h>

#include <pylists4c.h>

#if defined(_WIN32) || defined(_WIN64)
# define srandom srand
long random()
{
    return (long) ((((unsigned long) rand()) << 32) + (unsigned long) rand());
}
#endif

/******************************************************************************/
// FUNCTION: listShuffled()
//     Returns a shuffled copy of a LIST
// PARAMETERS:
//     pList: A pointer to a LIST
// RETURN VALUE:
//     A pointer to the first element of the new shuffled LIST
/******************************************************************************/
EXPORT LIST* listShuffled(LIST* pList)
{
    LIST* pShuffled = NULL;
    LIST* pUnshuffled = NULL;
    size_t count;

    pUnshuffled = listCopy(pList);
    count = listLen(pUnshuffled);

    if (count)
    {
        unsigned int seed;

        seed = (unsigned int) time(NULL);
        srandom(seed);
    
        while (count)
        {
            long n;
            LIST* pElement = NULL;
     
            // Randomly select one element
            n = random() % count;
    
            // Add it to the list of shuffled elements
            pElement = listGet(pUnshuffled, n);
            if (listAppend(&pShuffled, pElement -> pValue, pElement -> type, pElement -> size) == FAILURE)
            {
                listClear(&pShuffled);
                listClear(&pUnshuffled);

                return NULL;
            }
    
            // Remove it from the list of remaining elements
            listDelNth(&pUnshuffled, n);
            count--;
        }
    }

    return pShuffled;
}

