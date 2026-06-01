#include <ctype.h>

char *parse_word(char **cursor)
{
    char *word = *cursor;

    while (**cursor && !isspace((unsigned char)**cursor) && **cursor != '<' && **cursor != '>') 
        (*cursor)++;
    
    if (**cursor)
    {
        **cursor = '\0';    
        (*cursor)++;
    }

    return word;
}

