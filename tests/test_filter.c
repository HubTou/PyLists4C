#include <string.h>

#include <pylists4c.h>

BOOLEAN onlyOddNumbers(LIST_ELEMENT element)
{
    switch (element -> type)
    {
        case ETYPE_CHAR: return *((char*) element -> pValue) % 2;
        case ETYPE_U_CHAR: return *((unsigned char*) element -> pValue) % 2;
        case ETYPE_SHORT: return *((short*) element -> pValue) % 2;
        case ETYPE_U_SHORT: return *((unsigned short*) element -> pValue) % 2;
        case ETYPE_INT: return *((int*) element -> pValue) % 2;
        case ETYPE_U_INT: return *((unsigned int*) element -> pValue) % 2;
        case ETYPE_LONG: return *((long*) element -> pValue) % 2;
        case ETYPE_U_LONG: return *((unsigned long*) element -> pValue) % 2;
        case ETYPE_LONG_LONG: return *((long long*) element -> pValue) % 2;
        case ETYPE_U_LONG_LONG: return *((unsigned long long*) element -> pValue) % 2;
        default: return FALSE;
    }
}

BOOLEAN noEInStrings(LIST_ELEMENT element)
{
    if (element -> type == ETYPE_STRING)
        if (strchr(element -> pValue, 'e') || strchr(element -> pValue, 'E'))
            return FALSE;

    return TRUE;
}

int main()
{
    LIST* pList = NULL;
    LIST* pFilteredList = NULL;

    printf("Filtering even numbers:\n");
    pList = list("1, 2, 3, 4, 5, 6, 7, 8, 9, 10");
    listPrint(pList);
    pFilteredList = listFilter(pList, onlyOddNumbers);
    listPrint(pFilteredList);
    listClear(&pList);
    listClear(&pFilteredList);

    printf("\nFiltering strings containing the E letter:\n");
    pList = list("'la', 'disparition', 'est', 'un', 'livre', 'fameux', 'de', 'Georges', 'Perec'");
    listPrint(pList);
    pFilteredList = listFilter(pList, noEInStrings);
    listPrint(pFilteredList);
    listClear(&pList);
    listClear(&pFilteredList);

    printf("\nAllocated memory: %lu\n", listGetAllocatedMemory());

    return 0;
}

