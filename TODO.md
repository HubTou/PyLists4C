![alt text](https://github.com/HubTou/PyLists4C/blob/main/logo/pylists4c-logo.png "PyLists4C: Python-style lists for the C language")
# PyLists4C: Python-style lists for the C language

## Missing till Release 1.0
* listSortedByQsort() (in Changing elements order)
  * 3 BOOLEAN parameters to take into account

* listRemoveDuplicates() (in Removing elements)

* listSplit() (in Working with LISTs)

* listHalve() (in Working with LISTs)

* src/str.c
  * 1 byte offset bug correction

* src/str.c src/print.c:
  * Single quote escaping

* src/Makefile
  * Installation
    * System
    * User
  * Shared Output library

* DOC.md
  * Installation procedure

## For future releases
* listChangeRange()
  * listDelRange()
  * listInsertRange()

* src/list.c
  * exponents support
  * type indicators (ex: int:5, float:0.5)

* src/list.c
  * STRUCTs declaration
    * Declared in list() with braces. For example: (subtype, int:x, int:y)

* Packages
  * FreeBSD
  * RaspberryPiOS

* ETYPE support
  * NULL elements support (already partial)
  * ARRAY elements support

## Maybe?
* list{Contains, Count, Index, IndexAll}Values()
  * Regardless of ETYPE

* listSortedByMerge()
  * Cf. man 3 qsort

* Stable sort?

* listForeach()
  * Calls a user-defined function for each element
    * Really useful?

*  src/filter.c
  * listComprehension()
    * Better Python emulation?

* Tree data structures functions
  * Which ones?

## Other projects
* DICT elements
  * pydicts4c library!
    * Declared with curly braces. For example: {'': value}

* STRINGS elements
  * pystrings4c library?
    * What"s missing in C?

* ARRAY library?
