#ifndef PARSE_COMMAND_H
#define PARSE_COMMAND_H

#include "IO.hpp"


typedef enum
{
    STATEMENT_SEND_FILE
} StatementType;


typedef struct{
    StatementType type;
    char * filename;
    char * reciever;
} Statement;

ParseResult parse_command(InputBuffer *input_buffer, Statement *statement);

ParseResult parse_send_file(InputBuffer *input_buffer, Statement *statement);


#endif