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
        printf("%ld\n", *((long*) e -> pValue));

    printf("---\n");

    i = listSetIterator(listGetLast(pList)); 
    while ((e = listPrevious(&i)) != NULL)
        printf("%ld\n", *((long*) e -> pValue));

    listClear(&pList);
    printf("\nAllocated memory: %lu\n", listGetAllocatedMemory());

    return 0;
}

