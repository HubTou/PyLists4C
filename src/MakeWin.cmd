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
@ECHO on
%CC% %CFLAGS% -c append.c -o append.o
@IF %ERRORLEVEL% NEQ 0 (
    ECHO.
    ECHO FATAL ERROR!
    ECHO The Windows SDK and Universal C Runtime are required
    ECHO Grab and install the latest Microsoft Visual Studio Community edition at:
    ECHO   https://visualstudio.microsoft.com/
    ECHO Click on the "Individual components" tab
    ECHO Go in the "SDK, libraries and frameworks" section
    ECHO and at a minimum select:
    ECHO   "Windows Universal C Runtime"
    ECHO   the latest SDK for your Windows version
    ECHO And in the "Compilers, generation tools and runtimes" section select:
    ECHO   the latest build tools version for x64/x86 architectures
    ECHO   "MSVC v143 - VS 2022 C++ x64/x86 Build Tools -last version-" for example
    ECHO Then in your Windows Terminal go to:
    ECHO   INSTALL_DIR\Visual Studio\Common7\Tools
    ECHO And run:
    ECHO   .\VsMSBuildCmd.bat
    ECHO.
    EXIT /B 1
)

%CC% %CFLAGS% -c areEqual.c -o areEqual.o
%CC% %CFLAGS% -c change.c -o change.o
%CC% %CFLAGS% -c changeSlice.c -o changeSlice.o
%CC% %CFLAGS% -c clear.c -o clear.o
%CC% %CFLAGS% -c compareValues.c -o compareValues.o
%CC% %CFLAGS% -c comprehension.c -o comprehension.o
%CC% %CFLAGS% -c concat.c -o concat.o
%CC% %CFLAGS% -c contains.c -o contains.o
%CC% %CFLAGS% -c copy.c -o copy.o
%CC% %CFLAGS% -c count.c -o count.o
%CC% %CFLAGS% -c createElement.c -o createElement.o
%CC% %CFLAGS% -c debug.c -o debug.o
%CC% %CFLAGS% -c del.c -o del.o
%CC% %CFLAGS% -c delSlice.c -o delSlice.o
%CC% %CFLAGS% -c extend.c -o extend.o
%CC% %CFLAGS% -c filter.c -o filter.o
%CC% %CFLAGS% -c fromArray.c -o fromArray.o
%CC% %CFLAGS% -c get.c -o get.o
%CC% %CFLAGS% -c getAllocatedMemory.c -o getAllocatedMemory.o
%CC% %CFLAGS% -c getLast.c -o getLast.o
%CC% %CFLAGS% -c index.c -o index.o
%CC% %CFLAGS% -c indexAll.c -o indexAll.o
%CC% %CFLAGS% -c insert.c -o insert.o
%CC% %CFLAGS% -c insertFirst.c -o insertFirst.o
%CC% %CFLAGS% -c insertList.c -o insertList.o
%CC% %CFLAGS% -c insertSorted.c -o insertSorted.o
%CC% %CFLAGS% -c iterator.c -o iterator.o
%CC% %CFLAGS% -c join.c -o join.o
%CC% %CFLAGS% -c len.c -o len.o
%CC% %CFLAGS% -c list.c -o list.o
%CC% %CFLAGS% -c pop.c -o pop.o
%CC% %CFLAGS% -c print.c -o print.o
%CC% %CFLAGS% -c remove.c -o remove.o
%CC% %CFLAGS% -c removeAll.c -o removeAll.o
%CC% %CFLAGS% -c removeDuplicates.c -o removeDuplicates.o
%CC% %CFLAGS% -c reverse.c -o reverse.o
%CC% %CFLAGS% -c reversed.c -o reversed.o
%CC% %CFLAGS% -c setDebugMessagesDisplay.c -o setDebugMessagesDisplay.o
%CC% %CFLAGS% -c setFatalMallocErrors.c -o setFatalMallocErrors.o
%CC% %CFLAGS% -c shuffle.c -o shuffle.o
%CC% %CFLAGS% -c shuffled.c -o shuffled.o
%CC% %CFLAGS% -c slice.c -o slice.o
%CC% %CFLAGS% -c sort.c -o sort.o
%CC% %CFLAGS% -c sorted.c -o sorted.o
%CC% %CFLAGS% -c sortedByInsertion.c -o sortedByInsertion.o
%CC% %CFLAGS% -c sortedByQsort.c -o sortedByQsort.o
%CC% %CFLAGS% -c split.c -o split.o
%CC% %CFLAGS% -c stats.c -o stats.o
%CC% %CFLAGS% -c statsPrint.c -o statsPrint.o
%CC% %CFLAGS% -c str.c -o str.o
%CC% %CFLAGS% -c toArray.c -o toArray.o
%CC% %CFLAGS% -c value.c -o value.o
%CC% %CFLAGS% -c types/Char.c -o types/Char.o
%CC% %CFLAGS% -c types/UChar.c -o types/UChar.o
%CC% %CFLAGS% -c types/Short.c -o types/Short.o
%CC% %CFLAGS% -c types/UShort.c -o types/UShort.o
%CC% %CFLAGS% -c types/Int.c -o types/Int.o
%CC% %CFLAGS% -c types/UInt.c -o types/UInt.o
%CC% %CFLAGS% -c types/Long.c -o types/Long.o
%CC% %CFLAGS% -c types/ULong.c -o types/ULong.o
%CC% %CFLAGS% -c types/LongLong.c -o types/LongLong.o
%CC% %CFLAGS% -c types/ULongLong.c -o types/ULongLong.o
%CC% %CFLAGS% -c types/Float.c -o types/Float.o
%CC% %CFLAGS% -c types/Double.c -o types/Double.o
%CC% %CFLAGS% -c types/LongDouble.c -o types/LongDouble.o
%CC% %CFLAGS% -c types/String.c -o types/String.o
%CC% %CFLAGS% -c types/Struct.c -o types/Struct.o

@ECHO.
@ECHO.
@ECHO Building the Dynamic Link Library:
%CC% --shared append.o areEqual.o change.o changeSlice.o clear.o compareValues.o comprehension.o concat.o contains.o copy.o count.o createElement.o debug.o del.o delSlice.o extend.o filter.o fromArray.o get.o getAllocatedMemory.o getLast.o index.o indexAll.o insert.o insertFirst.o insertList.o insertSorted.o iterator.o join.o len.o list.o pop.o print.o remove.o removeAll.o removeDuplicates.o reverse.o reversed.o setDebugMessagesDisplay.o setFatalMallocErrors.o shuffle.o shuffled.o slice.o sort.o sorted.o sortedByInsertion.o sortedByQsort.o split.o stats.o statsPrint.o str.o toArray.o value.o types/Char.o types/UChar.o types/Short.o types/UShort.o types/Int.o types/UInt.o types/Long.o types/ULong.o types/LongLong.o types/ULongLong.o types/Float.o types/Double.o types/LongDouble.o types/String.o types/Struct.o -o ../pylists4c.dll >nul
@ECHO.
@dir ..\pylists4c.*
@ECHO.

