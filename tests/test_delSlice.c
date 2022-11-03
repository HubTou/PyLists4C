#include <pylists4c.h>

int main()
{
    LIST* pList = NULL;

    listSetFatalMallocErrors(TRUE);

    pList = list("0, 1, 2, 3");
    listPrint(pList);
    printf("listDelSlice(0, 2)\n");
    listDelSlice(&pList, 0, 2);
    listPrint(pList);
    listClear(&pList);
    printf("\n");

    pList = list("0, 1, 2, 3");
    listPrint(pList);
    printf("listDelSlice(1, 3)\n");
    listDelSlice(&pList, 1, 3);
    listPrint(pList);
    listClear(&pList);
    printf("\n");

    pList = list("0, 1, 2, 3");
    listPrint(pList);
    printf("listDelSlice(2, 4)\n");
    listDelSlice(&pList, 2, 4);
    listPrint(pList);
    listClear(&pList);
    printf("\n");

    pList = list("0, 1, 2, 3");
    listPrint(pList);
    printf("listDelSlice(-4, -2)\n");
    listDelSlice(&pList, -4, -2);
    listPrint(pList);
    listClear(&pList);
    printf("\n");

    pList = list("0, 1, 2, 3");
    listPrint(pList);
    printf("listDelSlice(-3, -1)\n");
    listDelSlice(&pList, -3, -1);
    listPrint(pList);
    listClear(&pList);
    printf("\n");

    pList = list("0, 1, 2, 3");
    listPrint(pList);
    printf("listDelSlice(-2, 0)\n");
    listDelSlice(&pList, -2, 0);
    listPrint(pList);
    listClear(&pList);

    printf("\nAllocated memory: %lu\n", listGetAllocatedMemory());

    return 0;
}

