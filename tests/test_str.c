#include <pylists4c.h>

int main()
{
    LIST* pList = NULL;
    char* string = NULL;

    pList = list("1, 2, 3");
    string = listStr(pList);
    printf("%s\n", string);
    listFreeStr(&string);
    listClear(&pList);
    printf("Allocated memory: %lu\n\n", listGetAllocatedMemory());

    pList = list("\"abc\", \"def\", \"ghi\"");
    string = listStr(pList);
    printf("%s\n", string);
    listFreeStr(&string);
    listClear(&pList);
    printf("Allocated memory: %lu\n\n", listGetAllocatedMemory());

    pList = list("123, 456.789, 'abc', \"def\", ['r', 3, 'd', 5]");
    string = listStr(pList);
    printf("%s\n", string);
    listFreeStr(&string);
    listClear(&pList);
    printf("Allocated memory: %lu\n\n", listGetAllocatedMemory());

    pList = list("[1, 2], [3, 4], [5, 6]");
    string = listStr(pList);
    printf("%s\n", string);
    listFreeStr(&string);
    listClear(&pList);
    printf("Allocated memory: %lu\n\n", listGetAllocatedMemory());

    pList = list("\"a'b\", 'c\\d'");
    string = listStr(pList);
    printf("%s\n", string);
    listFreeStr(&string);
    listClear(&pList);
    printf("Allocated memory: %lu\n\n", listGetAllocatedMemory());

    return 0;
}

