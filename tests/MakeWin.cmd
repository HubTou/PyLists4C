@ECHO off

REM Checking requirements
where clang.exe >nul 2>nul
IF %ERRORLEVEL% EQU 0 (
    SET CC=clang
) ELSE (
    ECHO.
    ECHO FATAL ERROR!
    ECHO The LLVM Clang C compiler is required
    ECHO Grab and install the latest LLVM-x.y.z-win64.exe version at:
    ECHO   https://github.com/llvm/llvm-project/releases
    ECHO.
    EXIT /B 1
)

SET CFLAGS=-O3 -Wall -Wextra -pipe -I..
ECHO.
ECHO Compiling the test programs:
ECHO.
@ECHO on
%CC% %CFLAGS% -c test_append.c -o test_append.o
%CC% test_append.o -L.. -lpylists4c -o test_append.exe
%CC% %CFLAGS% -c test_changeSlice.c -o test_changeSlice.o
%CC% test_changeSlice.o -L.. -lpylists4c -o test_changeSlice.exe
%CC% %CFLAGS% -c test_comprehension.c -o test_comprehension.o
%CC% test_comprehension.o -L.. -lpylists4c -o test_comprehension.exe
%CC% %CFLAGS% -c test_delSlice.c -o test_delSlice.o
%CC% test_delSlice.o -L.. -lpylists4c -o test_delSlice.exe
%CC% %CFLAGS% -c test_filter.c -o test_filter.o
%CC% test_filter.o -L.. -lpylists4c -o test_filter.exe
%CC% %CFLAGS% -c test_fromArray.c -o test_fromArray.o
%CC% test_fromArray.o -L.. -lpylists4c -o test_fromArray.exe
%CC% %CFLAGS% -c test_fromTable.c -o test_fromTable.o
%CC% test_fromTable.o -L.. -lpylists4c -o test_fromTable.exe
%CC% %CFLAGS% -c test_insert.c -o test_insert.o
%CC% test_insert.o -L.. -lpylists4c -o test_insert.exe
%CC% %CFLAGS% -c test_insertList.c -o test_insertList.o
%CC% test_insertList.o -L.. -lpylists4c -o test_insertList.exe
%CC% %CFLAGS% -c test_insertSorted.c -o test_insertSorted.o
%CC% test_insertSorted.o -L.. -lpylists4c -o test_insertSorted.exe
%CC% %CFLAGS% -c test_iterator.c -o test_iterator.o
%CC% test_iterator.o -L.. -lpylists4c -o test_iterator.exe
%CC% %CFLAGS% -c test_list.c -o test_list.o
%CC% test_list.o -L.. -lpylists4c -o test_list.exe
%CC% %CFLAGS% -c test_min_max_sum.c -o test_min_max_sum.o
%CC% test_min_max_sum.o -L.. -lpylists4c -o test_min_max_sum.exe
%CC% %CFLAGS% -c test_qsort.c -o test_qsort.o
%CC% test_qsort.o -L.. -lpylists4c -o test_qsort.exe
%CC% %CFLAGS% -c test_removeDuplicates.c -o test_removeDuplicates.o
%CC% test_removeDuplicates.o -L.. -lpylists4c -o test_removeDuplicates.exe
%CC% %CFLAGS% -c test_reverse.c -o test_reverse.o
%CC% test_reverse.o -L.. -lpylists4c -o test_reverse.exe
%CC% %CFLAGS% -c test_slice.c -o test_slice.o
%CC% test_slice.o -L.. -lpylists4c -o test_slice.exe
%CC% %CFLAGS% -c test_sort.c -o test_sort.o
%CC% test_sort.o -L.. -lpylists4c -o test_sort.exe
%CC% %CFLAGS% -c test_split.c -o test_split.o
%CC% test_split.o -L.. -lpylists4c -o test_split.exe
%CC% %CFLAGS% -c test_stats.c -o test_stats.o
%CC% test_stats.o -L.. -lpylists4c -o test_stats.exe
%CC% %CFLAGS% -c test_str.c -o test_str.o
%CC% test_str.o -L.. -lpylists4c -o test_str.exe
%CC% %CFLAGS% -c test_toArray.c -o test_toArray.o
%CC% test_toArray.o -L.. -lpylists4c -o test_toArray.exe
%CC% %CFLAGS% -c test_value.c -o test_value.o
%CC% test_value.o -L.. -lpylists4c -o test_value.exe

@ECHO.
@ECHO.
@ECHO Copying the DLL here so you can use the test programs:
copy ..\pylists4c.dll .
@ECHO.
@dir *.exe
@ECHO.

