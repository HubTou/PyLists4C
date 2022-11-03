#include <pylists4c.h>

int main()
{
    LIST* pList;
    ARRAY* pArray;

    listSetFatalMallocErrors(TRUE);

    pList = list("0, 1, 2, 3, 4, 5, 6, 7, 8, 9");
    printf("pList=");
    listPrint(pList);
    printf("Allocated memory: %lu\n", listGetAllocatedMemory());

    pArray = listToArray(pList);
    for (int i = 0; i < pArray -> length; i++)
        printf("pArray[%d]=%ld\n", i, pArray -> u.pLong[i]);
    printf("Allocated memory: %lu\n", listGetAllocatedMemory());
    listFreeArray(&pArray);
    printf("Allocated memory after freeing pArray: %lu\n", listGetAllocatedMemory());
    listClear(&pList);
    printf("Allocated memory after freeing pList: %lu\n\n", listGetAllocatedMemory());


    pList = list("'Ken', 'Dennis', 'Brian', 'bill', 'kirk', 'richard', 'linus', 'guido'");
    printf("pList=");
    listPrint(pList);
    printf("Allocated memory: %lu\n", listGetAllocatedMemory());

    pArray = listToArray(pList);
    for (int i = 0; i < pArray -> length; i++)
        printf("pArray[%d]=%s\n", i, pArray -> u.ppString[i]);
    printf("Allocated memory: %lu\n", listGetAllocatedMemory());
    listFreeArray(&pArray);
    printf("Allocated memory after freeing pArray: %lu\n", listGetAllocatedMemory());
    listClear(&pList);
    printf("Allocated memory after freeing pList: %lu\n", listGetAllocatedMemory());

    return 0;
}

