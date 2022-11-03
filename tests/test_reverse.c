#include <pylists4c.h>

int main()
{
    LIST* pList = NULL;
    LIST* pReversedList = NULL;

    listSetFatalMallocErrors(TRUE);

    printf("listReversed() test:\n");
    printf("====================\n");

    pList = list("0, 2, 4, 6, 8, 10");
    printf("pList=");
    listPrint(pList);

    pReversedList = listReversed(pList);
    printf("pReversedList=");
    listPrint(pReversedList);

    printf("pList=");
    listPrint(pList);

    printf("\nlistReverse() test:\n");
    printf("===================\n");

    listReverse(&pList);
    printf("pList=");
    listPrint(pList);

    listClear(&pList);
    listClear(&pReversedList);
    printf("\nAllocated memory: %lu\n", listGetAllocatedMemory());

    return 0;
}

