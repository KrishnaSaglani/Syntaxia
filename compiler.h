// compiler.h will contain all prototypes that we will be needing 
// This way we wont have to include all prototypes separately

#ifndef SYNTAXIA_H
#define SYNTAXIA_H
// if syntaxia.h is not already defined...then define this SYNTAXIA_H macro



#include <stdio.h>
#include <stdbool.h>

// Now lets define the various types of tokens
enum{
    TOKEN_TYPE_IDENTIFIER,
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_SYMBOL,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_COMMENT,
    TOKEN_TYPE_NEWLINE
};

//Every token has two values: type and value
struct token
{
    int type;
    int flags;

    union 
    {
        char cval;
        const char* sval;
        unsigned int inum;
        unsigned long lnum;
        unsigned long long llnum;
        void* any;
    };
    //Basically, in union there is a shared space for all elements...and only one of the elements can occupy it
    // Since the types can only be one of the above, hence this is an apt data structure to use here

    bool whitespace;
    // Tells us if there is a whitespace between current and next token
    // For ex. * a for token * means whitespace set wrt token a

    const char* between_brackets;
    // Useful for debugging....Basically points to first char at start of current bracket structure
    // Ex:  for (Hello), even if we are currently at o, it will point to H
};

// Now, each token will also have a position won't it?
struct pos
{
    int line;
    int col;
    const char* filename;
    // We are dealing with tokens from multiple files...like stdio.h, test.c, vector.h etc
};

//This here is the whole PROCESS of lexical analysis stored in a stuct
struct lex_process
{
    struct pos pos;
    struct vector * token_vector;
    // stores lots of tokens
    struct compile_process * compiler;
    // Points to the compiler process that this lexer is a part of

};

enum 
{
    COMPILER_FILE_COMPILED_OK,
    COMPILER_FAILED_WITH_ERRORS
};


//This basically is the ENTIRE process of compilation stored in a struct
struct compile_process
{
    //flags wrt how this file should be compiled
    int flags;

    struct compile_process_input_file
    {
        FILE * fp;
        const char* abs_path;

    }cfile;
    // This was the input file

    FILE * ofile;
    // This was the output file
};


int compile_file(const char* filename, const char* out_filename, int flags);
struct compile_process * compile_process_create(const char* filename, const char* filename_out, int flags);




#endif

// Basically,
// This file serves as a declaration file for compile_file(), 
// allowing multiple source files to use it.
