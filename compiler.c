#include "compiler.h"

struct lex_process_functions compiler_lex_functions =
{
    .next_char = compiler_process_next_char,
    .peek_char = compiler_process_peek_char,
    .push_char = compile_process_push_char
};
//Assigned all function pointers to respective identifiers

int compile_file(const char* filename, const char* out_filename, int flags)
{
    //Now for the actual implementation of all the functions created so far
    struct compile_process* process = compile_process_create(filename, out_filename, flags);
    if(!process)
    {
        return COMPILER_FAILED_WITH_ERRORS;
    }

    //Lexical Analysis:
    struct lex_process * lex_process = lex_process_create(process, &compiler_lex_functions, NULL);
    if(!lex_process)
    {
        return COMPILER_FAILED_WITH_ERRORS;
    }
    // Now process created...which is simply a structure that moves across the file and gathers tokens
    // Time for the ACTUAL lexing:
    if(lex(lex_process) != LEXICAL_ANALYSIS_ALL_OK)
    {
        return COMPILER_FAILED_WITH_ERRORS;
    }

    // Parsing:
    
    // Code Generation:


    return COMPILER_FILE_COMPILED_OK;
}