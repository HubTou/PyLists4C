#include <pylists4c.h>

LIST* onlyOddDigitsSquares(LIST_ELEMENT element)
{
    LIST* pSubList = NULL;

    if (element -> type == ETYPE_LONG)
    {
        long value = listValueLong(element);

        if (value % 2)
            (void) listAppendLong(&pSubList, value * value);
    }

    return pSubList;
}

int main()
{
    LIST* pDigits = list("0, 1, 2, 3, 4, 5, 6, 7, 8, 9");
    LIST* pOddDigitsSquares = NULL;

    printf("Let's try something like [x**2 for x in range(10) if x%%2]\n");
    listPrint(pDigits);
    pOddDigitsSquares = listComprehension(pDigits, onlyOddDigitsSquares);
    listPrint(pOddDigitsSquares);
    listClear(&pDigits);
    listClear(&pOddDigitsSquares);

    printf("\nAllocated memory: %lu\n", listGetAllocatedMemory());

    return 0;
}

