![alt text](https://github.com/HubTou/PyLists4C/blob/main/logo/pylists4c-logo.png "PyLists4C: Python-style lists for the C language")
# PyLists4C: Python-style lists for the C language
## Glossary
* A **LIST** is an instance of linked list this library provides.
* An **element** is a node of a LIST.
* A **value** is the payload of an element of a LIST
* An **homogeneous LIST** is a special kind of LIST where all values are of the same type.

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
TODO

## Base functions
TODO
