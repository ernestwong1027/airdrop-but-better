#include "IO.hpp"

void prompt_read() { printf("AirdropButBetter - "); }


InputBuffer *new_input_buffer() {
    InputBuffer *input_buffer = (InputBuffer *)malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->text_length = 0;

    return input_buffer;
}

void createFile(void *ptr, size_t size) {
    //create file pointer
    int r = rand();
    char* filename_ = (char *)malloc(20*sizeof(char));
    sprintf(filename_,"%d",r);
    FILE* file = fopen(filename_, "wb+"); 
    fwrite(ptr, size, 1, file);    
}

void close_buffer(InputBuffer *input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

void read_input(InputBuffer *input_buffer) {
    ssize_t text_length = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin) - 1;

    if (text_length < 0)
    {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    input_buffer->text_length = text_length;
    input_buffer->buffer[text_length] = 0;
}

void indent(int indent_level){
    for(int i =0 ; i<indent_level; i++)
    {
        printf("    ");
    }
}