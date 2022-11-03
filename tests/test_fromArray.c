#include <pylists4c.h>

int main()
{
    long longsArray[] = {8, 1, 3, 0, 2, 6, 4, 9, 5, 0, 7};
    long longsArrayLength = 11;
    ARRAY array;
    LIST* pList;

    array.type = ETYPE_LONG;
    array.size = sizeof(long);
    array.length = longsArrayLength;
    array.u.pLong = longsArray;
    for (long i = 0; i < longsArrayLength; i++)
        printf("array.u.pLong[%ld]=%ld\n", i, array.u.pLong[i]);

    listSetFatalMallocErrors(TRUE);

    pList = listFromArray(&array);
    printf("pList=");
    listPrint(pList);
    printf("Allocated memory: %lu\n", listGetAllocatedMemory());
    listClear(&pList);
    printf("Allocated memory after freeing pList: %lu\n\n", listGetAllocatedMemory());

    return 0;
}

