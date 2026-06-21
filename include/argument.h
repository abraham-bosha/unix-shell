#ifndef ARGUMENT_H
#define ARGUMENT_H

typedef enum quote_type
{
    QUOTE_NONE,
    QUOTE_SINGLE,
    QUOTE_DOUBLE
} quote_type_t;

typedef struct argument
{
    char *value;
    quote_type_t quote;
} argument_t;

#endif
