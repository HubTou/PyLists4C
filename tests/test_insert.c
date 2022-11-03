#include <pylists4c.h>

int main()
{
    LIST* pList = NULL;
    long v;

    listSetFatalMallocErrors(TRUE);

    pList = list("2, 4, 6, 8");
    listPrint(pList);

    printf("\nInsert 0 at pos 0\n");
    v = 0;
    listInsert(&pList, 0, &v, ETYPE_LONG, sizeof(v));
    listPrint(pList);

    printf("\nInsert 5 at pos 3\n");
    v = 5;
    listInsert(&pList, 3, &v, ETYPE_LONG, sizeof(v));
    listPrint(pList);

    printf("\nInsert 7 at pos 5\n");
    v = 7;
    listInsert(&pList, 5, &v, ETYPE_LONG, sizeof(v));
    listPrint(pList);

    printf("\nInsert 20 at pos 20\n");
    v = 20;
    listInsert(&pList, 20, &v, ETYPE_LONG, sizeof(v));
    listPrint(pList);

    listClear(&pList);
    printf("\nAllocated memory: %lu\n", listGetAllocatedMemory());

    return 0;
}

