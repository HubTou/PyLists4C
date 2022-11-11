#include <pylists4c.h>

int main()
{
    LIST* pList = NULL;

    printf("Testing list(\"1, +1, -1, 1.2, +1.2, -1.2, 2e3, 2e+3, 2e-3, +3e4, +3e+4, +3e-4, -4e5, -4e+5, -4e-5, 5e8, 5e+8, 5e-8\"):\n");
    pList = list("1, +1, -1, 1.2, +1.2, -1.2, 2e3, 2e+3, 2e-3, +3e4, +3e+4, +3e-4, -4e5, -4e+5, -4e-5, 5e8, 5e+8, 5e-8");
    listDebug(pList, "pList");
    listClear(&pList);
    printf("\n");

    printf("Allocated memory: %lu\n", listGetAllocatedMemory());

    return 0;
}

