#include "parseCommand.hpp"

ParseResult parse_command(InputBuffer *input_buffer, Statement *statement){
  if (strncmp(input_buffer->buffer, "send", 4) == 0) return parse_send_file(input_buffer, statement);

  return PARSE_UNRECOGNIZED_STATEMENT;
}

ParseResult parse_send_file(InputBuffer *input_buffer, Statement *statement){
    statement->type = STATEMENT_SEND_FILE;
    statement->reciever = strtok(input_buffer->buffer, " ");
    statement->filename = strtok(NULL, " ");
     
    if (statement->reciever == NULL || statement->filename == NULL) return PARSE_SYNTAX_ERROR;
    return PARSE_SUCCESS;
}
