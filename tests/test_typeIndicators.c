#include <pylists4c.h>

int main()
{
    LIST* pList = NULL;

    printf("Testing list(\"char:-12, short:-34, int:-56, long:-78, longlong:-90, uchar:12, ushort:34, uint:56, ulong:78, ulonglong:90\"):\n");
    pList = list("char:-12, short:-34, int:-56, long:-78, longlong:-90, uchar:12, ushort:34, uint:56, ulong:78, ulonglong:90");
    listPrint(pList);
    listDebug(pList, "pList");
    listClear(&pList);
    printf("\n");

    printf("Testing list(\"float:1.23, double:4.56, longdouble:7.89\"):\n");
    pList = list("float:1.23, double:4.56, longdouble:7.89");
    listPrint(pList);
    listDebug(pList, "pList");
    listClear(&pList);
    printf("\n");

    printf("Testing list(\"null, char:'C', uchar:'U', 'string'\"):\n");
    pList = list("null, char:'C', uchar:'U', 'string'");
    listPrint(pList);
    listDebug(pList, "pList");
    listClear(&pList);
    printf("\n");

    printf("Testing list(\"c:-12, hd:-34, hi:-34, d:-56, i:-56, ld:-78, li:-78, lld:-90, lli:-90, hu:34, u:56, lu:78, llu:90\"):\n");
    pList = list("c:-12, hd:-34, hi:-34, d:-56, i:-56, ld:-78, li:-78, lld:-90, lli:-90, hu:34, u:56, lu:78, llu:90");
    listDebug(pList, "pList");
    listClear(&pList);
    printf("\n");

    printf("Testing list(\"f:1.23, lf:4.56, Lf:7.89\"):\n");
    pList = list("f:1.23, lf:4.56, Lf:7.89");
    listDebug(pList, "pList");
    listClear(&pList);
    printf("\n");

    printf("Testing list(\"f:12, lf:34, Lf:56\"):\n");
    pList = list("f:12, lf:34, Lf:56");
    listDebug(pList, "pList");
    listClear(&pList);
    printf("\n");

    printf("Testing list(\"c:'C'\"):\n");
    pList = list("c:'C'");
    listDebug(pList, "pList");
    listClear(&pList);
    printf("\n");

    printf("Testing list(\"c:-128, c:127, uchar:255, hi:-32768, hi:32767, hu:65535, i:-2147483648, i:2147483647, u:4294967295\"):\n");
    pList = list("c:-128, c:127, uchar:255, hi:-32768, hi:32767, hu:65535, i:-2147483648, i:2147483647, u:4294967295");
    listPrint(pList);
    listClear(&pList);
    printf("\n");

    printf("Testing list(\"li:-9223372036854775808, li:9223372036854775807, lu:18446744073709551615\"):\n");
    pList = list("li:-9223372036854775808, li:9223372036854775807, lu:18446744073709551615");
    listPrint(pList);
    listClear(&pList);
    printf("\n");

    printf("Testing list(\"f:1.17549435E-38, f:3.40282347E+38, lf:2.2250738585072014E-308, lf:1.7976931348623157E+308, Lf:3.3621031431120935063E-4932, Lf:1.1897314953572317650E+4932\"):\n");
    pList = list("f:1.17549435E-38, f:3.40282347E+38, lf:2.2250738585072014E-308, lf:1.7976931348623157E+308, Lf:3.3621031431120935063E-4932, Lf:1.1897314953572317650E+4932");
    listPrint(pList);
    listClear(&pList);
    printf("\n");

    printf("Testing list(\"c:-129, c:128, uchar:-1, uchar:256, hi:-32769, hi:32768, hu:-1, hu:65536, i:-2147483649, i:2147483648, u:-1, u:4294967296\"):\n");
    pList = list("c:-129, c:128, uchar:-1, uchar:256, hi:-32769, hi:32768,  hu:-1, hu:65536, i:-2147483649, i:2147483648, u:-1, u:4294967296");
    listPrint(pList);
    listClear(&pList);
    printf("\n");

    printf("Testing list(\"li:-9223372036854775809, li:9223372036854775808, lu:-1, lu:18446744073709551616\"):\n");
    pList = list("li:-9223372036854775809, li:9223372036854775808, lu:-1, lu:18446744073709551616");
    listPrint(pList);
    listClear(&pList);
    printf("\n");

    printf("Testing list(\"f:1.17549435E-39, f:3.40282347E+39, lf:2.2250738585072014E-309, lf:1.7976931348623157E+309, Lf:3.3621031431120935063E-4933, Lf:1.1897314953572317650E+4933\"):\n");
    pList = list("f:1.17549435E-39, f:3.40282347E+39, lf:2.2250738585072014E-309, lf:1.7976931348623157E+309, Lf:3.3621031431120935063E-4933, Lf:1.1897314953572317650E+4933");
    listPrint(pList);
    listClear(&pList);
    printf("\n");

    printf("Allocated memory: %lu\n", listGetAllocatedMemory());

    return 0;
}

