![alt text](https://github.com/HubTou/PyLists4C/blob/main/logo/pylists4c-logo.png "PyLists4C: Python-style lists for the C language")
# PyLists4C: Python-style lists for the C language

## Missing till Release 1.0
* [listChangeRange(n, m)](https://www.w3schools.com/python/trypython.asp?filename=demo_list_change_range)
  * listDelRange(n, m)
  * listInsertList(n)

* Replacing alias functions with macros?

## Generic needs
* Operating systems packages creation and maintenance
  * [FreeBSD](https://docs.freebsd.org/en/books/porters-handbook/book/)
  * RaspberryPiOS
  * [Ubuntu](https://packaging.ubuntu.com/html/packaging-new-software.html)
  * [Debian](https://www.debian.org/doc/manuals/maint-guide/)
  * [Windows package](https://learn.microsoft.com/en-us/windows/package-manager/package/repository)
  * Windows binary distribution?
  * ...

* [Documentation](DOC.md) translation

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
* Support for [hybrid Python / C language programs](https://docs.python.org/3/extending/extending.html) or [type conversion](https://docs.python.org/3/library/ctypes.html#module-ctypes)?

* list{Contains, Count, Index, IndexAll}Values()
  * Regardless of ETYPE

* listSortedByMerge()
  * Cf. [man 3 qsort](https://www.freebsd.org/cgi/man.cgi?query=qsort&sektion=3)
* Other [sorting algorithms](https://en.wikipedia.org/wiki/Sorting_algorithm)?

* listForeach()
  * Calls a user-defined function for each element
    * Really useful?

* src/filter.c
  * listComprehension()
    * Better emulation of Python's [list comprehension](https://docs.python.org/3/tutorial/datastructures.html#list-comprehensions)?

* [Tree](https://en.wikipedia.org/wiki/Tree_(data_structure)) data structures functions
  * Which ones?

## Possible other projects
* [DICT](https://www.w3schools.com/python/python_dictionaries.asp) elements
  * pydicts4c library!
    * Declared with curly braces. For example: {\'key1\': value1, \'key2\': value2}

* STRINGS elements?
  * pystrings4c library?
    * What could be missing in C that is [available in Python](https://www.w3schools.com/python/python_strings.asp)?

* ARRAY library?
