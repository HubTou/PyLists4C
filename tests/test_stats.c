#include <pylists4c.h>

int main()
{
    LIST* pList = NULL;
    LIST_STATS stats;

    pList = list("1, 2, 3");
    listPrint(pList);
    listStats(pList, &stats);
    listStatsPrint(stats, "pList");
    printf("Allocated memory: %lu\n", listGetAllocatedMemory());
    listClear(&pList);
    printf("\n");

    pList = list("\"abc\", \"def\", \"ghi\"");
    listPrint(pList);
    listStats(pList, &stats);
    listStatsPrint(stats, "pList");
    printf("Allocated memory: %lu\n", listGetAllocatedMemory());
    listClear(&pList);
    printf("\n");

    pList = list("123, 456.789, 'abc', \"def\", ['r', 2, 'd', 2]");
    listPrint(pList);
    listStats(pList, &stats);
    listStatsPrint(stats, "pList");
    printf("Allocated memory: %lu\n", listGetAllocatedMemory());
    listClear(&pList);
    printf("\n");

    pList = list(" 1, 2 , garbage, .3, 4.5.6, 'a\"b', \"c'd\", 'end'");
    listPrint(pList);
    listStats(pList, &stats);
    listStatsPrint(stats, "pList");
    printf("Allocated memory: %lu\n", listGetAllocatedMemory());
    listClear(&pList);
    printf("\n");

    pList = list("'nested', ['lists', ['are', ['possible']]]");
    listPrint(pList);
    listStats(pList, &stats);
    listStatsPrint(stats, "pList");
    printf("Allocated memory: %lu\n", listGetAllocatedMemory());
    listClear(&pList);
    printf("\n");

    pList = list("'empty lists too', []");
    listPrint(pList);
    listStats(pList, &stats);
    listStatsPrint(stats, "pList");
    printf("Allocated memory: %lu\n", listGetAllocatedMemory());
    listClear(&pList);
    printf("\n");

    printf("Allocated memory: %lu\n", listGetAllocatedMemory());

    return 0;
}

