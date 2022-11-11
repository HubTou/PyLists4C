// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

#include <pylists4c.h>
#include "global.h"

typedef enum
{
    STATE_BEFORE = 0,
    STATE_IN_INTEGER = 10,
    STATE_IN_INTEGER_DONE = 11,
    STATE_IN_FLOAT = 20,
    STATE_IN_FLOAT_EXPONENT = 21,
    STATE_IN_FLOAT_DONE = 22,
    STATE_IN_SQ_STRING = 30,
    STATE_IN_DQ_STRING = 31,
    STATE_IN_STRING_DONE = 32,
    STATE_IN_LIST = 40,
    STATE_IN_LIST_IN_SQ_STRING = 41,
    STATE_IN_LIST_IN_DQ_STRING = 42,
    STATE_IN_LIST_DONE = 43,
    STATE_IN_TYPE = 50,
    STATE_IN_GARBAGE = 60
} STATE;

// The character to be used as separator
// (i.e.: not a digit, space, '.', '-', '\'', '"', '[', ']', '\\')
char listSeparator = ',';

INTERNAL STATUS appendInteger(LIST** ppList, STRING buffer, ETYPE indicator, STATE* pState, int* pI);
INTERNAL STATUS appendDecimal(LIST** ppList, STRING buffer, ETYPE indicator, STATE* pState, int* pI);
INTERNAL STATUS appendCharacters(LIST** ppList, STRING buffer, ETYPE indicator, STATE* pState, int* pI);

/******************************************************************************/
// FUNCTION: list()
//     Creates a LIST from a Python-style LIST declaration string
// PARAMETERS:
//     string: A string describing the LIST contents:
//             - list of digits are converted as long
//             - list of digits dot digits are converted as double
//             - single or double quoted strings are converted as STRING
//             - brackets enclosed strings are converted as LIST
//             - type indicators and exponent notation are also available
// RETURN VALUE:
//     A pointer to the first element of the new LIST
// EXISTENTIAL QUESTIONS:
//     Requiring brackets in the declaration string would be like saying we are
//     already manipulating a LIST (Python uses braces, but because of syntax
//     requirements). On the other hand, doing so would ease going from str()
//     to list()
/******************************************************************************/
EXPORT LIST* list(STRING string)
{
    LIST* pList = NULL;
    int length = strlen(string);
    int i;
    STATE state = STATE_BEFORE;
    BOOLEAN backslash = FALSE;
    int depth = 0;
    int j = 0;
    char *buffer;
    ETYPE indicator = ETYPE_UNDEFINED;

    // Allocate a buffer for string parsing (doubling length in case of full backslash-escaping)
    if ((buffer = malloc((2 * length) + 1)) == NULL)
    {
        if (listFatalMallocErrors)
        {
            if (listDebugMessages)
                fprintf(stderr, "CRITICAL: malloc(%d) failed\n", (2 * length) + 1);
            exit(FAILURE);
        }
        else
        {
            if (listDebugMessages)
                fprintf(stderr, "ERROR: malloc(%d) failed\n", (2 * length) + 1);
            return NULL;
        }
    }

    // String parsing
    for (i = 0; i < length; i++)
    {
        /******************************************************************************/
        if (state == STATE_BEFORE)
        {
            if (isdigit(string[i]) || string[i] == '-')
            {
                state = STATE_IN_INTEGER;
                buffer[0] = string[i];
                j = 1;
            }
            else if (string[i] == '+')
            {
                state = STATE_IN_INTEGER;
                j = 0;
            }
            else if (string[i] == '\'')
            {
                state = STATE_IN_SQ_STRING;
                backslash = FALSE;
                j = 0;
            }
            else if (string[i] == '"')
            {
                state = STATE_IN_DQ_STRING;
                backslash = FALSE;
                j = 0;
            }
            else if (string[i] == '[')
            {
                state = STATE_IN_LIST;
                depth = 1;
                j = 0;
            }
            else if (string[i] == ' ')
            {
            }
            else if (string[i] == listSeparator)
            {
                if (listAppend(&pList, NULL, ETYPE_NULL, 0) == FAILURE)
                {
                    free(buffer);
                    listClear(&pList);
                    return NULL;
                }
                state = STATE_BEFORE;
            }
            else
            {
                state = STATE_IN_TYPE;
                i--;
                j = 0;
            }
        }

        /******************************************************************************/
        else if (state == STATE_IN_INTEGER)
        {
            if (isdigit(string[i]))
            {
                buffer[j] = string[i];
                j++;
            }
            else if (string[i] == '.')
            {
                state = STATE_IN_FLOAT;
                buffer[j] = string[i];
                j++;
            }
            else if (isdigit(string[i - 1]) && (string[i] == 'e' || string[i] == 'E'))
            {
                state = STATE_IN_FLOAT_EXPONENT;
                buffer[j] = string[i];
                j++;
            }
            else if (string[i] == listSeparator)
            {
                state = STATE_IN_INTEGER_DONE;
                i--;
            }
            else if (string[i] == ' ')
                state = STATE_IN_INTEGER_DONE;
            else
                state = STATE_IN_GARBAGE;
        }

        /******************************************************************************/
        else if (state == STATE_IN_INTEGER_DONE)
        {
            if (string[i] == listSeparator)
            {
                buffer[j] = 0;
                if (appendInteger(&pList, buffer, indicator, &state, &i) == FAILURE)
                    return NULL;
                indicator = ETYPE_UNDEFINED;
            }
            else if (string[i] == ' ')
            {
            }
            else
                state = STATE_IN_GARBAGE;
        }

        /******************************************************************************/
        else if (state == STATE_IN_FLOAT)
        {
            if (isdigit(string[i]))
            {
                buffer[j] = string[i];
                j++;
            }
            else if (isdigit(string[i - 1]) && (string[i] == 'e' || string[i] == 'E'))
            {
                state = STATE_IN_FLOAT_EXPONENT;
                buffer[j] = string[i];
                j++;
            }
            else if (string[i] == listSeparator)
            {
                state = STATE_IN_FLOAT_DONE;
                i--;
            }
            else if (string[i] == ' ')
                state = STATE_IN_FLOAT_DONE;
            else
                state = STATE_IN_GARBAGE;
        }

        /******************************************************************************/
        else if (state == STATE_IN_FLOAT_EXPONENT)
        {
            if (isdigit(string[i]))
            {
                buffer[j] = string[i];
                j++;
            }
            else if ((string[i - 1] == 'e' || string[i - 1] == 'E') && (string[i] == '+' || string[i] == '-'))
            {
                buffer[j] = string[i];
                j++;
            }
            else if (isdigit(string[i - 1]) && string[i] == listSeparator)
            {
                state = STATE_IN_FLOAT_DONE;
                i--;
            }
            else if (string[i] == listSeparator)
            {
                state = STATE_IN_GARBAGE;
                i--;
            }
            else if (string[i] == ' ')
                state = STATE_IN_FLOAT_DONE;
            else
                state = STATE_IN_GARBAGE;
        }

        /******************************************************************************/
        else if (state == STATE_IN_FLOAT_DONE)
        {
            if (string[i] == listSeparator)
            {
                buffer[j] = 0;
                if (appendDecimal(&pList, buffer, indicator, &state, &i) == FAILURE)
                    return NULL;
                indicator = ETYPE_UNDEFINED;
            }
            else if (string[i] == ' ')
            {
            }
            else
                state = STATE_IN_GARBAGE;
        }

        /******************************************************************************/
        else if (state == STATE_IN_SQ_STRING)
        {
            if (string[i] == '\\')
            {
                if (backslash == TRUE)
                {
                    buffer[j] = string[i];
                    j++;
                    backslash = FALSE;
                }
                else
                    backslash = TRUE;
            }
            else if (string[i] == '\'')
            {
                if (backslash == TRUE)
                {
                    buffer[j] = string[i];
                    j++;
                    backslash = FALSE;
                }
                else
                    state = STATE_IN_STRING_DONE;
            }
            else
            {
                if (backslash == TRUE)
                {
                    buffer[j] = '\\';
                    j++;
                    backslash = FALSE;
                }
                buffer[j] = string[i];
                j++;
            }
        }

        /******************************************************************************/
        else if (state == STATE_IN_DQ_STRING)
        {
            if (string[i] == '\\')
            {
                if (backslash == TRUE)
                {
                    buffer[j] = string[i];
                    j++;
                    backslash = FALSE;
                }
                else
                    backslash = TRUE;
            }
            else if (string[i] == '"')
            {
                if (backslash == TRUE)
                {
                    buffer[j] = string[i];
                    j++;
                    backslash = FALSE;
                }
                else
                    state = STATE_IN_STRING_DONE;
            }
            else
            {
                if (backslash == TRUE)
                {
                    buffer[j] = '\\';
                    j++;
                    backslash = FALSE;
                }
                buffer[j] = string[i];
                j++;
            }
        }

        /******************************************************************************/
        else if (state == STATE_IN_STRING_DONE)
        {
            if (string[i] == listSeparator)
            {
                buffer[j] = 0;
                if (appendCharacters(&pList, buffer, indicator, &state, &i) == FAILURE)
                    return NULL;
                indicator = ETYPE_UNDEFINED;
            }
            else if (string[i] == ' ')
            {
            }
            else
                state = STATE_IN_GARBAGE;
        }

        /******************************************************************************/
        else if (state == STATE_IN_LIST)
        {
            if (string[i] == ']')
            {
                depth--;
                if (depth)
                {
                    buffer[j] = string[i];
                    j++;
                }
                else
                    state = STATE_IN_LIST_DONE;
            }
            else if (string[i] == '[')
            {
                depth++;
                buffer[j] = string[i];
                j++;
            }
            else if (string[i] == '\'')
            {
                state = STATE_IN_LIST_IN_SQ_STRING;
                buffer[j] = string[i];
                j++;
            }
            else if (string[i] == '"')
            {
                state = STATE_IN_LIST_IN_DQ_STRING;
                buffer[j] = string[i];
                j++;
            }
            else
            {
                buffer[j] = string[i];
                j++;
            }
        }

        /******************************************************************************/
        else if (state == STATE_IN_LIST_IN_SQ_STRING)
        {
            if (string[i] == '\'')
                state = STATE_IN_LIST;

            buffer[j] = string[i];
            j++;
        }

        /******************************************************************************/
        else if (state == STATE_IN_LIST_IN_DQ_STRING)
        {
            if (string[i] == '"')
                state = STATE_IN_LIST;

            buffer[j] = string[i];
            j++;
        }

        /******************************************************************************/
        else if (state == STATE_IN_LIST_DONE)
        {
            if (string[i] == listSeparator)
            {
                LIST* pSubList = NULL;

                buffer[j] = 0;
                if (j)
                    pSubList = list(buffer);
                else
                    pSubList = NULL;

                if (listAppend(&pList, pSubList, ETYPE_LIST, sizeof(pSubList)) == FAILURE)
                {
                    free(buffer);
                    listClear(&pList);
                    return NULL;
                }

                listClear(&pSubList);

                state = STATE_BEFORE;
                indicator = ETYPE_UNDEFINED;
            }
            else if (string[i] == ' ')
            {
            }
            else
                state = STATE_IN_GARBAGE;
        }

        /******************************************************************************/
        else if (state == STATE_IN_TYPE)
        {
            if (isalnum(string[i]))
            {
                buffer[j] = string[i];
                j++;
            }
            else if (string[i] == ':')
            {
                buffer[j] = 0;

                if (! strcmp(buffer, "char") || ! strcmp(buffer, "c"))
                {
                    indicator = ETYPE_CHAR;
                    state = STATE_BEFORE;
                }
                else if (! strcmp(buffer, "uchar"))
                {
                    indicator = ETYPE_U_CHAR;
                    state = STATE_BEFORE;
                }
                else if (! strcmp(buffer, "short") || ! strcmp(buffer, "hd") || ! strcmp(buffer, "hi"))
                {
                    indicator = ETYPE_SHORT;
                    state = STATE_BEFORE;
                }
                else if (! strcmp(buffer, "ushort") || ! strcmp(buffer, "hu"))
                {
                    indicator = ETYPE_U_SHORT;
                    state = STATE_BEFORE;
                }
                else if (! strcmp(buffer, "int") || ! strcmp(buffer, "d") || ! strcmp(buffer, "i"))
                {
                    indicator = ETYPE_INT;
                    state = STATE_BEFORE;
                }
                else if (! strcmp(buffer, "uint") || ! strcmp(buffer, "u"))
                {
                    indicator = ETYPE_U_INT;
                    state = STATE_BEFORE;
                }
                else if (! strcmp(buffer, "long") || ! strcmp(buffer, "ld") || ! strcmp(buffer, "li"))
                {
                    indicator = ETYPE_LONG;
                    state = STATE_BEFORE;
                }
                else if (! strcmp(buffer, "ulong") || ! strcmp(buffer, "lu"))
                {
                    indicator = ETYPE_U_LONG;
                    state = STATE_BEFORE;
                }
                else if (! strcmp(buffer, "longlong") || ! strcmp(buffer, "lld") || ! strcmp(buffer, "lli"))
                {
                    indicator = ETYPE_LONG_LONG;
                    state = STATE_BEFORE;
                }
                else if (! strcmp(buffer, "ulonglong") || ! strcmp(buffer, "llu"))
                {
                    indicator = ETYPE_U_LONG_LONG;
                    state = STATE_BEFORE;
                }
                else if (! strcmp(buffer, "float") || ! strcmp(buffer, "f"))
                {
                    indicator = ETYPE_FLOAT;
                    state = STATE_BEFORE;
                }
                else if (! strcmp(buffer, "double") || ! strcmp(buffer, "lf"))
                {
                    indicator = ETYPE_DOUBLE;
                    state = STATE_BEFORE;
                }
                else if (! strcmp(buffer, "longdouble") || ! strcmp(buffer, "Lf"))
                {
                    indicator = ETYPE_LONG_DOUBLE;
                    state = STATE_BEFORE;
                }
                else
                {
                    state = STATE_IN_GARBAGE;
                }
            }
            else if (string[i] == listSeparator)
            {
                state = STATE_IN_GARBAGE;
                i--;
            }
            else
                state = STATE_IN_GARBAGE;
        }

        /******************************************************************************/
        else if (state == STATE_IN_GARBAGE)
        {
            if (string[i] == listSeparator)
            {
                if (listAppend(&pList, NULL, ETYPE_NULL, 0) == FAILURE)
                {
                    free(buffer);
                    listClear(&pList);
                    return NULL;
                }
                state = STATE_BEFORE;
                indicator = ETYPE_UNDEFINED;
            }
        }
    }

    buffer[j] = 0;
    if (state == STATE_IN_INTEGER || state == STATE_IN_INTEGER_DONE)
    {
        if (appendInteger(&pList, buffer, indicator, &state, &i) == FAILURE)
            return NULL;
    }
    else if (state == STATE_IN_FLOAT || state == STATE_IN_FLOAT_EXPONENT || state == STATE_IN_FLOAT_DONE)
    {
        if (appendDecimal(&pList, buffer, indicator, &state, &i) == FAILURE)
            return NULL;
    }
    else if (state == STATE_IN_STRING_DONE)
    {
        if (appendCharacters(&pList, buffer, indicator, &state, &i) == FAILURE)
            return NULL;
    }
    else if (state == STATE_IN_LIST_DONE)
    {
        LIST* pSubList = NULL;

        pSubList = list(buffer);

        if (listAppend(&pList, pSubList, ETYPE_LIST, sizeof(pSubList)) == FAILURE)
        {
            free(buffer);
            listClear(&pList);
            return NULL;
        }

        listClear(&pSubList);
    }
    else if (state != STATE_BEFORE)
    {
        if (listAppend(&pList, NULL, ETYPE_NULL, 0) == FAILURE)
        {
            free(buffer);
            listClear(&pList);
            return NULL;
        }
        state =  STATE_BEFORE;
    }

    // last minute garbage?
    if (state == STATE_IN_GARBAGE)
    {
        if (listAppend(&pList, NULL, ETYPE_NULL, 0) == FAILURE)
        {
            free(buffer);
            listClear(&pList);
            return NULL;
        }
    }

    return pList;
}

STATUS appendInteger(LIST** ppList, STRING buffer, ETYPE indicator, STATE* pState, int* pI)
{
    if (indicator == ETYPE_UNDEFINED || indicator == ETYPE_LONG)
    {
        long value = strtol(buffer, (char**) NULL, 10);

        if (errno == ERANGE || errno == EINVAL)
        {
            *pState = STATE_IN_GARBAGE;
            (*pI)--;
        }
        else if (listAppend(ppList, &value, ETYPE_LONG, sizeof(value)) == FAILURE)
        {
            free(buffer);
            listClear(ppList);
            return FAILURE;
        }
        else
            *pState = STATE_BEFORE;
    }
    else if (indicator == ETYPE_CHAR)
    {
        long longValue = strtol(buffer, (char**) NULL, 10);
        char value;

        if (longValue < CHAR_MIN || longValue > CHAR_MAX)
            errno = ERANGE;
        else
            value = (char) longValue;

        if (errno == ERANGE)
        {
            *pState = STATE_IN_GARBAGE;
            (*pI)--;
        }
        else if (listAppend(ppList, &value, ETYPE_CHAR, sizeof(value)) == FAILURE)
        {
            free(buffer);
            listClear(ppList);
            return FAILURE;
        }
        else
            *pState = STATE_BEFORE;
    }
    else if (indicator == ETYPE_U_CHAR)
    {
        long longValue = strtol(buffer, (char**) NULL, 10);
        unsigned char value;

        if (longValue < 0 || longValue > UCHAR_MAX)
            errno = ERANGE;
        else
            value = (unsigned char) longValue;

        if (errno == ERANGE)
        {
            *pState = STATE_IN_GARBAGE;
            (*pI)--;
        }
        else if (listAppend(ppList, &value, ETYPE_U_CHAR, sizeof(value)) == FAILURE)
        {
            free(buffer);
            listClear(ppList);
            return FAILURE;
        }
        else
            *pState = STATE_BEFORE;
    }
    else if (indicator == ETYPE_SHORT)
    {
        long longValue = strtol(buffer, (char**) NULL, 10);
        short value;

        if (longValue < SHRT_MIN || longValue > SHRT_MAX)
            errno = ERANGE;
        else
            value = (short) longValue;

        if (errno == ERANGE)
        {
            *pState = STATE_IN_GARBAGE;
            (*pI)--;
        }
        else if (listAppend(ppList, &value, ETYPE_SHORT, sizeof(value)) == FAILURE)
        {
            free(buffer);
            listClear(ppList);
            return FAILURE;
        }
        else
            *pState = STATE_BEFORE;
    }
    else if (indicator == ETYPE_U_SHORT)
    {
        long longValue = strtol(buffer, (char**) NULL, 10);
        unsigned short value;

        if (longValue < 0 || longValue > USHRT_MAX)
            errno = ERANGE;
        else
            value = (unsigned short) longValue;

        if (errno == ERANGE)
        {
            *pState = STATE_IN_GARBAGE;
            (*pI)--;
        }
        else if (listAppend(ppList, &value, ETYPE_U_SHORT, sizeof(value)) == FAILURE)
        {
            free(buffer);
            listClear(ppList);
            return FAILURE;
        }
        else
            *pState = STATE_BEFORE;
    }
    else if (indicator == ETYPE_INT)
    {
        long longValue = strtol(buffer, (char**) NULL, 10);
        int value;

        if (longValue < INT_MIN || longValue > INT_MAX)
            errno = ERANGE;
        else
            value = (int) longValue;

        if (errno == ERANGE)
        {
            *pState = STATE_IN_GARBAGE;
            (*pI)--;
        }
        else if (listAppend(ppList, &value, ETYPE_INT, sizeof(value)) == FAILURE)
        {
            free(buffer);
            listClear(ppList);
            return FAILURE;
        }
        else
            *pState = STATE_BEFORE;
    }
    else if (indicator == ETYPE_U_INT)
    {
        long longValue = strtol(buffer, (char**) NULL, 10);
        unsigned int value;

        if (longValue < 0 || longValue > (long) UINT_MAX)
            errno = ERANGE;
        else
            value = (unsigned int) longValue;

        if (errno == ERANGE)
        {
            *pState = STATE_IN_GARBAGE;
            (*pI)--;
        }
        else if (listAppend(ppList, &value, ETYPE_U_INT, sizeof(value)) == FAILURE)
        {
            free(buffer);
            listClear(ppList);
            return FAILURE;
        }
        else
            *pState = STATE_BEFORE;
    }
    else if (indicator == ETYPE_U_LONG)
    {
        unsigned long value = strtoul(buffer, (char**) NULL, 10);

        // testing buffer[0] because strtoul("-1"...) is not invalid!
        if (errno == ERANGE || errno == EINVAL || buffer[0] == '-')
        {
            *pState = STATE_IN_GARBAGE;
            (*pI)--;
        }
        else if (listAppend(ppList, &value, ETYPE_U_LONG, sizeof(value)) == FAILURE)
        {
            free(buffer);
            listClear(ppList);
            return FAILURE;
        }
        else
            *pState = STATE_BEFORE;
    }
    else if (indicator == ETYPE_LONG_LONG)
    {
        long long value = strtoll(buffer, (char**) NULL, 10);

        if (errno == ERANGE || errno == EINVAL)
        {
            *pState = STATE_IN_GARBAGE;
            (*pI)--;
        }
        else if (listAppend(ppList, &value, ETYPE_LONG_LONG, sizeof(value)) == FAILURE)
        {
            free(buffer);
            listClear(ppList);
            return FAILURE;
        }
        else
            *pState = STATE_BEFORE;
    }
    else if (indicator == ETYPE_U_LONG_LONG)
    {
        unsigned long long value = strtoull(buffer, (char**) NULL, 10);

        // testing buffer[0] because strtoull("-1"...) is not invalid!
        if (errno == ERANGE || errno == EINVAL || buffer[0] == '-')
        {
            *pState = STATE_IN_GARBAGE;
            (*pI)--;
        }
        else if (listAppend(ppList, &value, ETYPE_U_LONG_LONG, sizeof(value)) == FAILURE)
        {
            free(buffer);
            listClear(ppList);
            return FAILURE;
        }
        else
            *pState = STATE_BEFORE;
    }
    else if (indicator == ETYPE_FLOAT || indicator == ETYPE_DOUBLE || indicator == ETYPE_LONG_DOUBLE)
    {
        if (appendDecimal(ppList, buffer, indicator, pState, pI) == FAILURE)
            return FAILURE;
    }
    else
    {
        *pState = STATE_IN_GARBAGE;
        (*pI)--;
    }

    errno = 0;
    return SUCCESS;
}

STATUS appendDecimal(LIST** ppList, STRING buffer, ETYPE indicator, STATE* pState, int* pI)
{
    if (indicator == ETYPE_UNDEFINED || indicator == ETYPE_DOUBLE)
    {
        double value = strtod(buffer, (char **) NULL);

        if (errno == ERANGE || errno == EINVAL)
        {
            *pState = STATE_IN_GARBAGE;
            (*pI)--;
        }
        else if (listAppend(ppList, &value, ETYPE_DOUBLE, sizeof(value)) == FAILURE)
        {
            free(buffer);
            listClear(ppList);
            return FAILURE;
        }
        else
            *pState = STATE_BEFORE;
    }
    else if (indicator == ETYPE_FLOAT)
    {
        float value = strtof(buffer, (char **) NULL);

        if (errno == ERANGE || errno == EINVAL)
        {
            *pState = STATE_IN_GARBAGE;
            (*pI)--;
        }
        else if (listAppend(ppList, &value, ETYPE_FLOAT, sizeof(value)) == FAILURE)
        {
            free(buffer);
            listClear(ppList);
            return FAILURE;
        }
        else
            *pState = STATE_BEFORE;
    }
    else if (indicator == ETYPE_LONG_DOUBLE)
    {
        long double value = strtold(buffer, (char **) NULL);

        if (errno == ERANGE || errno == EINVAL)
        {
            *pState = STATE_IN_GARBAGE;
            (*pI)--;
        }
        else if (listAppend(ppList, &value, ETYPE_LONG_DOUBLE, sizeof(value)) == FAILURE)
        {
            free(buffer);
            listClear(ppList);
            return FAILURE;
        }
        else
            *pState = STATE_BEFORE;
    }
    else
    {
        *pState = STATE_IN_GARBAGE;
        (*pI)--;
    }

    errno = 0;
    return SUCCESS;
}

STATUS appendCharacters(LIST** ppList, STRING buffer, ETYPE indicator, STATE* pState, int* pI)
{
    BOOLEAN rangeError = FALSE;

    if (indicator == ETYPE_UNDEFINED || indicator == ETYPE_STRING)
    {
        if (listAppend(ppList, buffer, ETYPE_STRING, strlen(buffer) + 1) == FAILURE)
        {
            free(buffer);
            listClear(ppList);
            return FAILURE;
        }
        *pState = STATE_BEFORE;
    }
    else if (indicator == ETYPE_CHAR)
    {
        char character;

        if (strlen(buffer) == 1)
            character = buffer[0];
        else
            rangeError = TRUE;

        if (rangeError)
        {
            *pState = STATE_IN_GARBAGE;
            (*pI)--;
        }
        else if (listAppend(ppList, &character, ETYPE_CHAR, sizeof(character)) == FAILURE)
        {
            free(buffer);
            listClear(ppList);
            return FAILURE;
        }
        else
            *pState = STATE_BEFORE;
    }
    else if (indicator == ETYPE_U_CHAR)
    {
        unsigned char character;

        if (strlen(buffer) == 1)
            character = (unsigned char) buffer[0];
        else
            rangeError = TRUE;

        if (rangeError)
        {
            *pState = STATE_IN_GARBAGE;
            (*pI)--;
        }
        else if (listAppend(ppList, &character, ETYPE_U_CHAR, sizeof(character)) == FAILURE)
        {
            free(buffer);
            listClear(ppList);
            return FAILURE;
        }
        else
            *pState = STATE_BEFORE;
    }
    else
    {
        *pState = STATE_IN_GARBAGE;
        (*pI)--;
    }

    return SUCCESS;
}

