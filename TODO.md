![alt text](https://github.com/HubTou/PyLists4C/blob/main/logo/pylists4c-logo.png "PyLists4C: Python-style lists for the C language")
# PyLists4C: Python-style lists for the C language

## Missing till Release 1.0
* listChangeRange(n, m)
  * listDelRange(n, m)
  * listInsertList(n)

## Generic needs
* Operating systems packages
  * FreeBSD
  * RaspberryPiOS
  * Ubuntu & Debian (I use these in Windows Subsystem for Linux 2)
  * Windows binary distribution?
  * ...

* Documentation translation

## For future releases
* src/list.c
  * exponents support
  * type indicators (ex: int:5, float:0.5)
  * STRUCTs declaration
    * Declared in list() with braces. For example: (subtype, int:x, int:y)

* listFromFile() / list[Readlines](https://docs.python.org/3/library/io.html?highlight=readlines#io.IOBase.readlines)()
* listToFile() / list[Writelines](https://docs.python.org/3/library/io.html?highlight=writelines#io.IOBase.writelines)()
  * Loading & Writing from/to an ASCII text file, line by line

* ETYPE support
  * STRUCT elements documentation: provide an example and a test program 
  * NULL elements support (already partial)
  * ARRAY elements support
    * Declared in list() with angle-brackets. For example: <int:1, 2, 3> (only the first element will need a type indicator if it's not supposed to be a long) 

## Maybe?
* Type conversion for [hybrid Python / C language programs](https://docs.python.org/3/extending/extending.html)?

* list{Contains, Count, Index, IndexAll}Values()
  * Regardless of ETYPE

* listSortedByMerge()
  * Cf. man 3 qsort
* Stable sort?
* Other sort algorithms?

* listForeach()
  * Calls a user-defined function for each element
    * Really useful?

* src/filter.c
  * listComprehension()
    * Better Python emulation?

* Tree data structures functions
  * Which ones?

## Possible other projects
* DICT elements
  * pydicts4c library!
    * Declared with curly braces. For example: {\'key1\': value1, \'key2\': value2}

* STRINGS elements?
  * pystrings4c library?
    * What could be missing in C that is available in Python?

* ARRAY library?
