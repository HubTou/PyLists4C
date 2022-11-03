#include <string.h>

#include <pylists4c.h>

int main()
{
    LIST* pList = NULL;

    static char* lastManOnTheMoon = "Gene Cernan";
    long year = 1972;

    listSetFatalMallocErrors(TRUE);

    // Append into an empty list:
    listAppend(&pList, lastManOnTheMoon, ETYPE_STRING, strlen(lastManOnTheMoon) + 1);
    listAppend(&pList, &year, ETYPE_LONG, sizeof(long));
    listPrint(pList);
    listClear(&pList);

    // Append into an non empty list:
    pList = list("'Harrison Schmitt', 1972");
    listAppend(&pList, lastManOnTheMoon, ETYPE_STRING, strlen(lastManOnTheMoon) + 1);
    listAppend(&pList, &year, ETYPE_LONG, sizeof(long));
    listPrint(pList);
    listClear(&pList);

    printf("\nAllocated memory: %lu\n", listGetAllocatedMemory());

    return 0;
}

