#include <pylists4c.h>

int main()
{
    LIST* pList = NULL;
    LIST* pList2 = NULL;

    listSetFatalMallocErrors(TRUE);

    pList2 = list("0, 1");
    listPrint(pList);
    printf("listInsertList(0, [0, 1])\n");
    listInsertList(&pList, 0, pList2);
    listPrint(pList);
    listClear(&pList);
    listClear(&pList2);
    printf("\n");

    pList = list("2, 5");
    pList2 = list("0, 1");
    listPrint(pList);
    printf("listInsertList(0, [0, 1])\n");
    listInsertList(&pList, 0, pList2);
    listPrint(pList);
    listClear(&pList);
    listClear(&pList2);
    printf("\n");

    pList = list("2, 5");
    pList2 = list("3, 4");
    listPrint(pList);
    printf("listInsertList(1, [3, 4])\n");
    listInsertList(&pList, 1, pList2);
    listPrint(pList);
    listClear(&pList);
    listClear(&pList2);
    printf("\n");

    pList = list("2, 5");
    pList2 = list("6, 7");
    listPrint(pList);
    printf("listInsertList(2, [6, 7])\n");
    listInsertList(&pList, 2, pList2);
    listPrint(pList);
    listClear(&pList);
    listClear(&pList2);
    printf("\n");

    pList = list("2, 5");
    pList2 = list("9, 10");
    listPrint(pList);
    printf("listInsertList(3, [9, 10])\n");
    listInsertList(&pList, 3, pList2);
    listPrint(pList);
    listClear(&pList);
    listClear(&pList2);

    printf("\nAllocated memory: %lu\n", listGetAllocatedMemory());

    return 0;
}

