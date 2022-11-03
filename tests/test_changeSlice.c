#include <pylists4c.h>

int main()
{
    LIST* pList = NULL;
    LIST* pList2 = NULL;

    listSetFatalMallocErrors(TRUE);

    pList = list("'apple', 'banana', 'cherry', 'orange', 'kiwi', 'mango'");
    pList2 = list("'blackcurrant', 'watermelon'");
    listPrint(pList);
    printf("listChangeSlice(1, 3, ['blackcurrant', 'watermelon'])\n");
    listChangeSlice(&pList, 1, 3, pList2);
    listPrint(pList);
    listClear(&pList);
    listClear(&pList2);

    printf("\nAllocated memory: %lu\n", listGetAllocatedMemory());

    return 0;
}

