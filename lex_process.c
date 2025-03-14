#include "compiler.h"
#include <stdlib.h>
#include "helpers/vector.h"

// Now, this functions basically initialises 
struct lex_process * lex_process_create( struct compile_process* compiler, struct lex_process_functions *functions, void * private)
{
    // We are initialising, so we have to allocate memories to everything so it can actually process the content
    struct lex_process* process = calloc( 1, sizeof(struct lex_process));
    process->function = functions;
    process->token_vec = vector_create( sizeof (struct token)); 
    // There you go, even this is created...now whenever token is created, its added here

    process->compiler = compiler;
    process->private = private;

    process->pos.line = 1;
    process->pos.col = 1;

    return process;
}

// Now we also want to be able to free this lex_process

void lex_process_free( struct lex_process* process)
{
    vector_free(process->token_vec);
    free(process);

    // As we have done only two callocs here, one for token_vector and one for process struct itself...
    // WHich of course stores the pointer ot token_vector
}

void * lex_process_private(struct lex_process * process)
{
    return process->private;
    // Returns user's private data
}

struct vector * lex_process_tokens( struct lex_process * process)
{
    return process->token_vec;
    // returns the token created so far
}
