#include "executeCommand.hpp"
#include "HuffmanEncoding.hpp"
//list recievers
//send reciever file_name
//^multiple file names



ExecuteResult execute_statement(InputBuffer *input_buffer, Statement *statement) {
    //
    switch (statement->type)
    {
    case (STATEMENT_SEND_FILE):
        return execute_send_file(input_buffer, statement);
    }
}

ExecuteResult execute_send_file(InputBuffer *input_buffer, Statement *statement){
    HuffmanEncoding h = HuffmanEncoding(statement->filename);
    h.encode();
    //TODO send file 
}