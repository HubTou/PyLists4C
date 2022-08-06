![alt text](https://github.com/HubTou/PyLists4C/blob/main/logo/pylists4c-logo.png "PyLists4C: Python-style lists for the C language")
# PyLists4C: Python-style lists for the C language
## Data structures
### LIST type
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
Lists should only be allocated through the library's functions.

If you want to declare a LIST variable, just use:
```C
LIST* MyList = NULL;
```

### ETYPE type
TODO

## Base functions
TODO
