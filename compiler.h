// compiler.h will contain all prototypes that we will be needing 
// This way we wont have to include all prototypes separately

#ifndef SYNTAXIA_H
#define SYNTAXIA_H
// if syntaxia.h is not already defined...then define this SYNTAXIA_H macro



#include <stdio.h>
#include <stdbool.h>

enum{
    LEXICAL_ANALYSIS_ALL_OK, 
    LEXICAL_ANALYSIS_INPUT_ERROR
};
// Always use enumerations for such flags and definitions

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


struct lex_process;

typedef char (*LEX_PROCESS_NEXT_CHAR) (struct lex_process* process);
// This is a functoin
// Basically, lex_process struct moves throughout the c code token by token
// And simply uses these functons one by one to process and keep moving ahead...
// Basically the lex_process structure inherits these functoins defined in below structure to 
// process the string. This particular function simply reads the next char and returns it YAY

// But the cool thing is...these aren't functoins...these are functoin pointers, hence they can be 
// contained inside structs also. This is how we have inheritence in c...and it allows for very 
// nice abstractions
typedef char (*LEX_PROCESS_PEEK_CHAR) (struct lex_process * process);
typedef void (*LEX_PROCESS_PUSH_CHAR) (struct lex_process * process, char ch);
// The last one basically pushes a character to say a buffer or smth. We'll see soon.


struct lex_process_functions
{
    LEX_PROCESS_NEXT_CHAR next_char;
    LEX_PROCESS_PEEK_CHAR peek_char;
    LEX_PROCESS_PUSH_CHAR push_char;
};
// don't forget typedef was present earlier, so we have renamed the functions here easily
// Also, don't forget that these are function pointers not functions    
// These will basically point to the three functions created in cprocess, and can even point to 
// other even more efficient functions if required. How useful it is to use function pointers!

//This here is the whole PROCESS of lexical analysis stored in a stuct
struct lex_process
{
    struct pos pos; 
    struct vector * token_vec;
    // stores lots of tokens
    struct compile_process * compiler;
    // Points to the compiler process that this lexer is a part of

    int current_expression_count;
    // Basically, ([a]) for a this will be 2...as its inside 2 brackets

    struct buffer* parenthesis_buffer;
    struct lex_process_functions* function; 
    // The functoin currently being employed


    // Points to data that the lexer doesn't understand but the user
    // only can understand
    void * private;
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

    struct pos pos;
    // This too moves ahead as a whole structure right with the lexer

    struct compile_process_input_file
    {
        FILE * fp;
        const char* abs_path;

    }cfile;
    // This was the input file

    FILE * ofile;
    // This was the output file
};

// Prototype for compiler.c
int compile_file(const char* filename, const char* out_filename, int flags);
// Prototype for cprocess.c
struct compile_process * compile_process_create(const char* filename, const char* filename_out, int flags);

// more Prototypes for cprocess.c
char compiler_process_next_char( struct lex_process * lex_process);
char compiler_process_peek_char (struct lex_process * lex_process);
void compile_process_push_char (struct lex_process *lex_process, char c);


// Prototypes for lex_process.c
struct lex_process * lex_process_create( struct compile_process* compiler, struct lex_process_functions *functions, void * private);
void lex_process_free( struct lex_process* process);
void * lex_process_private(struct lex_process * process);
struct vector * lex_process_tokens( struct lex_process * process);


int lex(struct lex_process * process);


#endif

// Basically,
// This file serves as a declaration file for compile_file(), 
// allowing multiple source files to use it.
