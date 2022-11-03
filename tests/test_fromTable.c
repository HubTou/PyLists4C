#include <pylists4c.h>

int main()
{
    long longsArray[] = {8, 1, 3, 0, 2, 6, 4, 9, 5, 0, 7};
    long longsArrayLength = 11;
    LIST* pList;

    for (long i = 0; i < longsArrayLength; i++)
        printf("longsArray[%ld]=%ld\n", i, longsArray[i]);

    listSetFatalMallocErrors(TRUE);

    pList = listFromTable(longsArray, ETYPE_LONG, sizeof(long), longsArrayLength);
    printf("pList=");
    listPrint(pList);
    printf("Allocated memory: %lu\n", listGetAllocatedMemory());
    listClear(&pList);
    printf("Allocated memory after freeing pList: %lu\n\n", listGetAllocatedMemory());

    return 0;
}

