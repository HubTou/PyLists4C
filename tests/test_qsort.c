#include <pylists4c.h>

int longCompare(const void *p1, const void *p2)
{
    long left = *((long*) p1);
    long right = *((long*) p2);

    return ((left > right) - (left < right));
}

int main()
{
    LIST* pList;
    ARRAY* pArray;
    LIST* pSortedList;

    listSetFatalMallocErrors(TRUE);

    pList = list("8, 1, 3, 0, 2, 6, 4, 9, 5, 0, 7");
    printf("pList=");
    listPrint(pList);

    printf("\nConverting pList to pArray with listToArray()\n");
    pArray = listToArray(pList);
    for (int i = 0; i < pArray -> length; i++)
        printf("pArray[%d]=%ld\n", i, pArray -> u.pLong[i]);

    printf("\nSorting pArray with qsort()\n");
    qsort(pArray -> u.pLong, pArray -> length, pArray -> size, longCompare);
    for (int i = 0; i < pArray -> length; i++)
        printf("pArray[%d]=%ld\n", i, pArray -> u.pLong[i]);

    printf("\nConverting pArray to pList with listFromArray()\n");
    pSortedList = listFromArray(pArray);
    printf("pSortedList=");
    listPrint(pSortedList);

    listClear(&pList);
    listFreeArray(&pArray);
    listClear(&pSortedList);

    printf("\nAllocated memory: %lu\n", listGetAllocatedMemory());

    return 0;
}

