#include <pylists4c.h>

int main()
{
    LIST* pList = NULL;
    LIST_ITERATOR i;
    LIST_ELEMENT e;

    pList = list("1, 2, 3, 4, 5");
    listPrint(pList);

    i = listSetIterator(pList); 
    while ((e = listNext(&i)) != NULL)
        printf("%ld\n", listValueLong(e));

    listClear(&pList);
    printf("\nAllocated memory: %lu\n", listGetAllocatedMemory());

    return 0;
}

