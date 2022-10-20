![alt text](https://github.com/HubTou/PyLists4C/blob/main/logo/pylists4c-logo.png "PyLists4C: Python-style lists for the C language")
# PyLists4C: Python-style lists for the C language

## Missing till Release 1.0
* listChangeRange(n, m)
  * listDelRange(n, m)
  * listInsertList(n)

## For future releases
* src/list.c
  * exponents support
  * type indicators (ex: int:5, float:0.5)
  * STRUCTs declaration
    * Declared in list() with braces. For example: (subtype, int:x, int:y)

* Packages
  * FreeBSD
  * RaspberryPiOS
  * Ubuntu (I use this in Windows Subsystem for Linux 2)
  * Windows binary distribution?

* ETYPE support
  * STRUCT elements documentation: provide an example and a test program 
  * NULL elements support (already partial)
  * ARRAY elements support
    * Declared in list() with angle-brackets. For example: <int:1, 2, 3> (only the first element will need a type indicator if it's not supposed to be a long) 

## Maybe?
* list{Contains, Count, Index, IndexAll}Values()
  * Regardless of ETYPE

* listSortedByMerge()
  * Cf. man 3 qsort

* Stable sort?

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
    * Declared with curly braces. For example: {'': value}

* STRINGS elements?
  * pystrings4c library?
    * What could be missing in C?

* ARRAY library?
