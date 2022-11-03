#include <pylists4c.h>

int main()
{
    LIST* pList = NULL;
    LIST* pSlice = NULL;

    listSetFatalMallocErrors(TRUE);

    pList = list("0, 1, 2, 3, 4, 5, 6, 7, 8, 9");
    printf("list=");
    listPrint(pList);

    pSlice = listSlice(pList, 1, 9);
    printf("list[1:9]=");
    listPrint(pSlice);
    listClear(&pSlice);

    pSlice = listSliceTo(pList, 5);
    printf("list[:5]=");
    listPrint(pSlice);
    listClear(&pSlice);

    pSlice = listSliceFrom(pList, 5);
    printf("list[5:]=");
    listPrint(pSlice);
    listClear(&pSlice);

    pSlice = listSlice(pList, -9, -1);
    printf("list[-9:-1]=");
    listPrint(pSlice);
    listClear(&pSlice);

    pSlice = listSliceTo(pList, -5);
    printf("list[:-5]=");
    listPrint(pSlice);
    listClear(&pSlice);

    pSlice = listSliceFrom(pList, -5);
    printf("list[-5:]=");
    listPrint(pSlice);
    listClear(&pSlice);

    listClear(&pList);
    printf("\nAllocated memory: %lu\n", listGetAllocatedMemory());

    return 0;
}

