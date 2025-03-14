
#include <stdio.h>
#include  <stdlib.h>
#include "compiler.h"

struct compile_process * compile_process_create(const char* filename, const char* filename_out, int flags)
{
    FILE* file = fopen(filename, "r");
    if(!file)
    {
        return NULL;
    }

    FILE* out_file = NULL;
    if(filename_out)
    {
        out_file = fopen(filename_out, "w");
        if(!out_file)
        {
            return NULL;
        }
    }
    //You don't always want to pass out an exe file...you simply wanna show it on terminal
    // When filename_out not provided this is what you do

    // Now, finally allocating some memory for this struct compile_process located in compiler.h
    struct compile_process* process = calloc(1, sizeof(struct compile_process));
    process->flags = flags;
    process->ofile = out_file;
    process->cfile.fp = file;

    return process;
    
}


// This process takes in the current lex_process and returns the next character
// of course, it needs some specifiers...such as which compile process is going on
// i.e. which input and output file is being considered
char compiler_process_next_char( struct lex_process * lex_process)
{
    struct compile_process * compiler = lex_process->compiler;
    // hence we have created this compiler process called compiler that performs 
    // These activities like getting next char etc. that the lexer and other things can use
    compiler->pos.col += 1;
    char c = getc(compiler->cfile.fp);
    // this also moves fp ahead by one step


    if(c== '\n')
    {
        compiler->pos.line += 1;
        compiler->pos.col = 1;
    }

    return c; 
}



char compiler_process_peek_char (struct lex_process * lex_process)
// We always pass the pointer to lex_process as thats how we pass dynamically varying structures
{
    struct compile_process * compiler = lex_process->compiler;
    char c = getc(compiler->cfile.fp);
    // no need to check for '\n' as we are simply peeking

    ungetc(c, compiler->cfile.fp);
    // puts c back on and basically resets fp...so that we are back to where we were

    return c;
}

void compile_process_push_char (struct lex_process *lex_process, char c)
{
    struct compile_process * compiler = lex_process->compiler;
    // This is the compile operation being discussed.
    // The compiler process is what keeps track of the file and fp also as we go compiling

    ungetc(c, compiler->cfile.fp);
    
}
// Basically pushes c back into the filestream being parsed