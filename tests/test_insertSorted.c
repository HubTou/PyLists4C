#include <pylists4c.h>

int main()
{
    LIST* pList = NULL;
    long v;

    listSetFatalMallocErrors(TRUE);

    /************/
    pList = list("2, 4, 6, 8");
    listPrint(pList);

    printf("Insert 0\n");
    v = 0;
    listInsertSorted(&pList, &v, ETYPE_LONG, sizeof(v), FALSE, FALSE, FALSE);
    listPrint(pList);

    printf("Insert 5\n");
    v = 5;
    listInsertSorted(&pList, &v, ETYPE_LONG, sizeof(v), FALSE, FALSE, FALSE);
    listPrint(pList);

    printf("Insert 10\n");
    v = 10;
    listInsertSorted(&pList, &v, ETYPE_LONG, sizeof(v), FALSE, FALSE, FALSE);
    listPrint(pList);

    listClear(&pList);
    printf("\n");

    /************/
    pList = list("8, 6, 4, 2");
    listPrint(pList);

    printf("Insert 0 in reverse order\n");
    v = 0;
    listInsertSorted(&pList, &v, ETYPE_LONG, sizeof(v), TRUE, FALSE, FALSE);
    listPrint(pList);

    printf("Insert 5 in reverse order\n");
    v = 5;
    listInsertSorted(&pList, &v, ETYPE_LONG, sizeof(v), TRUE, FALSE, FALSE);
    listPrint(pList);

    printf("Insert 10 in reverse order\n");
    v = 10;
    listInsertSorted(&pList, &v, ETYPE_LONG, sizeof(v), TRUE, FALSE, FALSE);
    listPrint(pList);

    listClear(&pList);
    printf("\n");

    /************/
    pList = list("'B', 'D', 'F', 'b', 'd', 'f'");
    listPrint(pList);

    printf("Insert 'A'\n");
    listInsertSorted(&pList, "A", ETYPE_STRING, 2, FALSE, FALSE, FALSE);
    listPrint(pList);

    printf("Insert 'a'\n");
    listInsertSorted(&pList, "a", ETYPE_STRING, 2, FALSE, FALSE, FALSE);
    listPrint(pList);

    printf("Insert 'g'\n");
    listInsertSorted(&pList, "g", ETYPE_STRING, 2, FALSE, FALSE, FALSE);
    listPrint(pList);

    listClear(&pList);
    printf("\n");

    /************/
    pList = list("'B', 'd', 'F'");
    listPrint(pList);

    printf("Insert 'a' case insensitive\n");
    listInsertSorted(&pList, "a", ETYPE_STRING, 2, FALSE, TRUE, FALSE);
    listPrint(pList);

    printf("Insert 'E' case insensitive\n");
    listInsertSorted(&pList, "E", ETYPE_STRING, 2, FALSE, TRUE, FALSE);
    listPrint(pList);

    printf("Insert 'g' case insensitive\n");
    listInsertSorted(&pList, "g", ETYPE_STRING, 2, FALSE, TRUE, FALSE);
    listPrint(pList);

    listClear(&pList);
    printf("\n");

    /************/
    pList = list("4, 6, 8");
    listPrint(pList);

    printf("Insert 2 no duplicates\n");
    listInsertSortedLong(&pList, 2, FALSE, FALSE, TRUE);
    listPrint(pList);

    printf("Insert 6 no duplicates\n");
    listInsertSortedLong(&pList, 6, FALSE, FALSE, TRUE);
    listPrint(pList);

    printf("Insert 10 no duplicates\n");
    listInsertSortedLong(&pList, 10, FALSE, FALSE, TRUE);
    listPrint(pList);

    listClear(&pList);
    printf("\n");

    printf("Allocated memory: %lu\n", listGetAllocatedMemory());

    return 0;
}

