#ifndef EXECUTE_COMMAND_H
#define EXECUTE_COMMAND_H
#include "parseCommand.hpp"

ExecuteResult execute_statement(InputBuffer *input_buffer, Statement *statement);

ExecuteResult execute_send_file(InputBuffer *input_buffer, Statement *statement);

#endif