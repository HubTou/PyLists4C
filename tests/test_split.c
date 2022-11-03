#include <pylists4c.h>

int main()
{
    LIST* pList = NULL;
    LIST* pList2 = NULL;

    pList = list("1, 2, 3, 4");
    listPrint(pList);
    printf("Split at position 2:\n");
    pList2 = listSplit(&pList, 2);
    listPrint(pList);
    listPrint(pList2);
    listClear(&pList);
    listClear(&pList2);
    printf("\n");

    pList = list("1, 2, 3, 4");
    listPrint(pList);
    printf("Split at position 0:\n");
    pList2 = listSplit(&pList, 0);
    listPrint(pList);
    listPrint(pList2);
    listClear(&pList);
    listClear(&pList2);
    printf("\n");

    pList = list("1, 2, 3, 4");
    listPrint(pList);
    printf("Split at position 7:\n");
    pList2 = listSplit(&pList, 7);
    listPrint(pList);
    listPrint(pList2);
    listClear(&pList);
    listClear(&pList2);
    printf("\n");

    pList = list("1, 2, 3, 4");
    listPrint(pList);
    printf("Halve odd list:\n");
    pList2 = listHalve(pList);
    listPrint(pList);
    listPrint(pList2);
    listClear(&pList);
    listClear(&pList2);
    printf("\n");

    pList = list("1, 2, 3, 4, 5");
    listPrint(pList);
    printf("Halve even list:\n");
    pList2 = listHalve(pList);
    listPrint(pList);
    listPrint(pList2);
    listClear(&pList);
    listClear(&pList2);
    printf("\n");

    printf("Allocated memory: %lu\n", listGetAllocatedMemory());

    return 0;
}

