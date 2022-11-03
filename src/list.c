// PyLists4C - Python-style lists for the C language
// License: 3-clause BSD (see https://opensource.org/licenses/BSD-3-Clause)
// Author: Hubert Tournier

#include <ctype.h>
#include <string.h>

#include <pylists4c.h>
#include "global.h"

typedef enum
{
    STATE_BEFORE = 0,
    STATE_IN_INTEGER = 10,
    STATE_IN_INTEGER_DONE = 11,
    STATE_IN_FLOAT = 20,
    STATE_IN_FLOAT_DONE = 21,
    STATE_IN_SQ_STRING = 30,
    STATE_IN_DQ_STRING = 31,
    STATE_IN_STRING_DONE = 32,
    STATE_IN_LIST = 40,
    STATE_IN_LIST_IN_SQ_STRING = 41,
    STATE_IN_LIST_IN_DQ_STRING = 42,
    STATE_IN_LIST_DONE = 43,
    STATE_IN_GARBAGE = 50
} STATE;

// The character to be used as separator
// (i.e.: not a digit, space, '.', '-', '\'', '"', '[', ']', '\\')
char listSeparator = ',';

/******************************************************************************/
// FUNCTION: list()
//     Creates a LIST from a Python-style LIST declaration string
// PARAMETERS:
//     string: A string describing the LIST contents:
//             - list of digits are converted as long
//             - list of digits dot digits are converted as double
//             - single or double quoted strings are converted as STRING
//             - brackets enclosed strings are converted as LIST
// RETURN VALUE:
//     A pointer to the first element of the new LIST
// CAVEATS:
//     Exponents are not (yet) supported for decimal numbers
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
    int i = 0;
    STATE state = STATE_BEFORE;
    BOOLEAN backslash = FALSE;
    int depth = 0;
    int j = 0;
    char *buffer;

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
    while (i < length)
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
                if (listAppend(&pList, "", ETYPE_STRING, 1) == FAILURE)
                {
                    free(buffer);
                    listClear(&pList);
                    return NULL;
                }
                state = STATE_BEFORE;
            }
            else
                state = STATE_IN_GARBAGE;
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
            else if (string[i] == listSeparator)
            {
                long value;

                buffer[j] = 0;
                value = atol(buffer);

                if (listAppend(&pList, &value, ETYPE_LONG, sizeof(value)) == FAILURE)
                {
                    free(buffer);
                    listClear(&pList);
                    return NULL;
                }
                state = STATE_BEFORE;
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
                long value;

                buffer[j] = 0;
                value = atol(buffer);

                if (listAppend(&pList, &value, ETYPE_LONG, sizeof(value)) == FAILURE)
                {
                    free(buffer);
                    listClear(&pList);
                    return NULL;
                }
                state = STATE_BEFORE;
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
            else if (string[i] == listSeparator)
            {
                double value;

                buffer[j] = 0;
                value = atof(buffer);

                if (listAppend(&pList, &value, ETYPE_DOUBLE, sizeof(value)) == FAILURE)
                {
                    free(buffer);
                    listClear(&pList);
                    return NULL;
                }
                state = STATE_BEFORE;
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
                double value;

                buffer[j] = 0;
                value = atof(buffer);

                if (listAppend(&pList, &value, ETYPE_DOUBLE, sizeof(value)) == FAILURE)
                {
                    free(buffer);
                    listClear(&pList);
                    return NULL;
                }
                state = STATE_BEFORE;
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

                if (listAppend(&pList, buffer, ETYPE_STRING, strlen(buffer) + 1) == FAILURE)
                {
                    free(buffer);
                    listClear(&pList);
                    return NULL;
                }
                state = STATE_BEFORE;
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
            }
            else if (string[i] == ' ')
            {
            }
            else
                state = STATE_IN_GARBAGE;
        }

        /******************************************************************************/
        else if (state == STATE_IN_GARBAGE)
        {
            if (string[i] == listSeparator)
            {
                if (listAppend(&pList, "", ETYPE_STRING, 1) == FAILURE)
                {
                    free(buffer);
                    listClear(&pList);
                    return NULL;
                }
                state = STATE_BEFORE;
            }
        }

        i++;
    }

    if (state == STATE_IN_INTEGER || state == STATE_IN_INTEGER_DONE)
    {
        long value;

        buffer[j] = 0;
        value = atol(buffer);

        if (listAppend(&pList, &value, ETYPE_LONG, sizeof(value)) == FAILURE)
        {
            free(buffer);
            listClear(&pList);
            return NULL;
        }
    }
    else if (state == STATE_IN_FLOAT || state == STATE_IN_FLOAT_DONE)
    {
        double value;

        buffer[j] = 0;
        value = atof(buffer);

        if (listAppend(&pList, &value, ETYPE_DOUBLE, sizeof(value)) == FAILURE)
        {
            free(buffer);
            listClear(&pList);
            return NULL;
        }
    }
    else if (state == STATE_IN_STRING_DONE)
    {
        buffer[j] = 0;

        if (listAppend(&pList, buffer, ETYPE_STRING, strlen(buffer) + 1) == FAILURE)
        {
            free(buffer);
            listClear(&pList);
            return NULL;
        }
    }
    else if (state == STATE_IN_LIST_DONE)
    {
        LIST* pSubList = NULL;

        buffer[j] = 0;
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
        if (listAppend(&pList, "", ETYPE_STRING, 1) == FAILURE)
        {
            free(buffer);
            listClear(&pList);
            return NULL;
        }
    }

    return pList;
}

