#include <pylists4c.h>

int main()
{
    LIST* pList = NULL;

    pList = list("1, 2, 3");
    listPrint(pList);
    listClear(&pList);
    printf("\n");

    pList = list("\"abc\", \"def\", \"ghi\"");
    listPrint(pList);
    listClear(&pList);
    printf("\n");

    pList = list("123, 456.789, -987, 'abc', \"def\", ['r', 2, 'd', 2]");
    listPrint(pList);
    printf("\n");
    listDebug(pList, "pList");
    listClear(&pList);
    printf("\n");

    pList = list(" 1, 2 , garbage, .3, 4.5.6, 'a\"b', \"c'd\", 'e\\f', 'end'");
    listPrint(pList);
    printf("\n");
    listDebug(pList, "pList");
    listClear(&pList);
    printf("\n");

    pList = list("'nested', ['lists', ['are', ['possible']]]");
    listPrint(pList);
    printf("\n");
    listDebug(pList, "pList");
    listClear(&pList);
    printf("\n");

    pList = list("'empty lists too', []");
    listPrint(pList);
    printf("\n");
    listDebug(pList, "pList");
    listClear(&pList);

    printf("\nAllocated memory: %lu\n", listGetAllocatedMemory());

    return 0;
}

