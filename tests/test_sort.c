#include <pylists4c.h>

int main()
{
    LIST* pList = NULL;
    LIST* pSortedList = NULL;

    listSetFatalMallocErrors(TRUE);

    printf("listSorted() test:\n");
    printf("==================\n");
    pList = list("8, 1, 3, 0, 2, 6, 4, 9, 5, 0, 7");
    printf("pList=");
    listPrint(pList);

    pSortedList = listSorted(pList, FALSE, FALSE, FALSE);
    printf("pSortedList=");
    listPrint(pSortedList);
    listClear(&pSortedList);

    pSortedList = listSorted(pList, TRUE, FALSE, FALSE);
    printf("pReverseSortedList=");
    listPrint(pSortedList);
    listClear(&pSortedList);

    pSortedList = listSorted(pList, FALSE, FALSE, TRUE);
    printf("pNoDupsSortedList=");
    listPrint(pSortedList);
    listClear(&pSortedList);

    printf("pList=");
    listPrint(pList);

    printf("\nlistSort() test:\n");
    printf("================\n");
    listSort(&pList, FALSE, FALSE, FALSE);
    printf("pList=");
    listPrint(pList);
    listClear(&pList);

    printf("\nStrings:\n");
    printf("========\n");
    pList = list("'Ken', 'Dennis', 'Brian', 'bill', 'kirk', 'richard', 'linus', 'guido'");
    printf("pList=");
    listPrint(pList);

    pSortedList = listSorted(pList, FALSE, TRUE, FALSE);
    printf("pSortedList=");
    listPrint(pSortedList);
    listClear(&pSortedList);
    listClear(&pList);

    printf("\nAnd now something not possible with Python:\n");
    printf("===========================================\n");
    pList = list("'Ken', 43, 'Dennis', 41, 'Brian', 42, 'bill', 54, 'kirk', 54, 'richard', 53, 'linus', 69, 'guido', 57");
    printf("pList=");
    listPrint(pList);

    pSortedList = listSorted(pList, FALSE, TRUE, FALSE);
    printf("pSortedList=");
    listPrint(pSortedList);
    listClear(&pSortedList);
    listClear(&pList);

    printf("\nAllocated memory: %lu\n", listGetAllocatedMemory());

    return 0;
}

