#include <pylists4c.h>

int main()
{
    LIST* pList = NULL;

    listSetFatalMallocErrors(TRUE);

    pList = list("31, 13, 47, 19, 3, 41, 17, 5, 11, 29, 43, 23, 2, 7, 37");
    listPrint(pList);

    printf("min=%ld\n", listMinLong(pList));
    printf("max=%ld\n", listMaxLong(pList));
    printf("sum=%lld\n", listSumLong(pList));

    listClear(&pList);
    printf("\nAllocated memory: %lu\n", listGetAllocatedMemory());

    return 0;
}
