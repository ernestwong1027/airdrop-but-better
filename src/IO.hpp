#ifndef IO_H
#define IO_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

typedef enum {
    EXECUTE_SUCCESS,
    EXECUTE_INVALID_FILE,
} ExecuteResult;

typedef enum {
    PARSE_SUCCESS,
    PARSE_SYNTAX_ERROR,
    PARSE_UNRECOGNIZED_STATEMENT,
    PARSE_NEGATIVE_ID,
    PARSE_STRING_TOO_LONG,
} ParseResult;

typedef struct {
    char *buffer;
    size_t buffer_length;
    ssize_t text_length;
} InputBuffer;

InputBuffer *new_input_buffer();

void prompt_read();

void createFile(void *ptr, size_t size);

void print_parse_error(ParseResult result);

void print_execute_error(ExecuteResult result);

void read_input(InputBuffer *input_buffer);

void close_buffer(InputBuffer *input_buffer);

#endif