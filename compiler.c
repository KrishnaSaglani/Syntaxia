#include "compiler.h"

int compile_file(const char* filename, const char* out_filename, int flags)
{
    //Now for the actual implementation of all the functions created so far
    struct compile_process* process = compile_process_create(filename, out_filename, flags);
    if(!process)
    {
        return COMPILER_FAILED_WITH_ERRORS;
    }

    //Lexical Analysis:

    // Parsing:

    // Code Generation:


    return COMPILER_FILE_COMPILED_OK;
}