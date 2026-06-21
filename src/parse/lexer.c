#include <ctype.h>
#include <string.h>

#include "argument.h"

char *parse_word(char **cursor, quote_type_t *quote)
{
    char *start;
    char delimiter = '\0';

    if (quote)
        *quote = QUOTE_NONE;

    if (**cursor == '\'')
    {
        delimiter = '\'';
        
        if (quote)
            *quote = QUOTE_SINGLE;

        (*cursor)++;
    }
    else if (**cursor == '"')
    {
        delimiter = '"';

        if (quote)
            *quote = QUOTE_DOUBLE;
        
        (*cursor)++;
    }

    start = *cursor;

    if (delimiter)
    {
        while (**cursor && **cursor != delimiter) 
            (*cursor)++;
    }
    else {
        while (**cursor &&
               !isspace((unsigned char)**cursor) &&
               **cursor != '<' && 
               **cursor != '>')
        {
            (*cursor)++;
        }
    }
    
    if (**cursor)
    {
        **cursor = '\0';    
        (*cursor)++;
    }

    return strdup(start);
}

