#include <pylists4c.h>

int main()
{
    LIST* pList = NULL;

    pList = list("1, 2, 2, 3, 3, 3, 4");
    listPrint(pList);
    listRemoveDuplicates(pList);
    listPrint(pList);
    listClear(&pList);
    printf("\n");

    pList = list("1, 2, 2, 3, 3, 3");
    listPrint(pList);
    listRemoveDuplicates(pList);
    listPrint(pList);
    listClear(&pList);
    printf("\n");

    pList = list("1, 2, 2, 3, 1, 4");
    listPrint(pList);
    listRemoveDuplicates(pList);
    listPrint(pList);
    listClear(&pList);
    printf("\n");

    printf("Allocated memory: %lu\n", listGetAllocatedMemory());

    return 0;
}

