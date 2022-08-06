![alt text](https://github.com/HubTou/PyLists4C/blob/main/logo/pylists4c-logo.png "PyLists4C: Python-style lists for the C language")
# PyLists4C: Python-style lists for the C language
## Glossary and conventions
* A **LIST** is an instance of linked list this library provides.
* An **element** is a node of a LIST.
* A **value** is the payload of an element of a LIST.
* An **homogeneous LIST** is a special kind of LIST where all values are of the same type.
* Pointers variable names are prefixed with a **p** character. Pointers to pointers with **pp** and so on.

## Data structures
### LIST type
The main data structure of this library is defined like this:
```C
// Double-linked variable content linked list cell:
typedef struct list
{
    void* pValue;

    ETYPE type;
    size_t size;

    struct list* pPrevious;
    struct list* pNext;
} LIST;
```
Design notes:
* In order to mix different types of *values* in a same LIST, we need a **type** variable to keep track of the kind of *value* a peculiar *element* will carry.
* As we want to use some custom types beyond standard C language types, we introduce the **ETYPE** type to be able to use:
  * STRINGs (C language NUL terminated character arrays),
  * sub-LISTs,
  * and user defined, self contained (that is to say, without pointers) STRUCTs.
  * We might add Python-style dictionaries (DICTs) in the future.
  * With Python-style lists, you can implement many other data types with sub LISTS (all kind of trees, for example).
* As the size of user defined STRUCTs is unknown (and furthermore can be of variable size inside a same LIST) and STRINGS can be allocated to larger character arrays than their current content, we need a **size** variable to keep track of the space allocated to store the *value*.
  * If you use multiple kind of STRUCTs in the same LIST, it is advised to start each of these STRUCTs with a fixed length field indicating its sub type.
* As we want an *element* to have the same memory size, we use pointers for all *values*, not just STRINGs, LISTs and STRUCTS. Thus we need a **pValue** variable to point to the *value* of each *element*.

If you want to declare an empty LIST, just use:
```C
LIST* MyList = NULL;
```

LISTs should only be allocated through the library's functions, so don't use static LIST objects (eg: LIST MyList).

### ETYPE type
It's defined like this:
```C
// Element TYPEs:
typedef enum
{
    ETYPE_UNDEFINED = -1,
    ETYPE_CHAR = 1,
    ETYPE_U_CHAR = 2,
    ETYPE_SHORT = 3,
    ETYPE_U_SHORT = 4,
    ETYPE_INT = 5,
    ETYPE_U_INT = 6,
    ETYPE_LONG = 7,
    ETYPE_U_LONG = 8,
    ETYPE_LONG_LONG = 9,
    ETYPE_U_LONG_LONG = 10,
    ETYPE_FLOAT = 21,
    ETYPE_DOUBLE = 22,
    ETYPE_LONG_DOUBLE = 23,
    // C-style strings:
    // (ie. 0 terminated character array)
    ETYPE_STRING = 31,
    // Sub-LISTs:
    ETYPE_LIST = 32,
    // Python-style dictionaries for C (maybe one day :-))
//  ETYPE_DICT = 33,
    // Self-contained structures without pointers:
    // (it would be a good practice to have a starting sub-TYPE field
    // if you want to have non homogeneous STRUCTs)
    ETYPE_STRUCT = 34
} ETYPE;
```
Design notels:
* ETYPE_UNDEFINED is meant for internal use.
* ETYPE_DICT is a placeholder for a possible complementary library for Python-style dictionaries.

We provide convenience functions for each standard C language types, so you don't have to pass values by address, provide the *type* and *size* parameters, or cast variables to specific types.

## Base functions
TODO
