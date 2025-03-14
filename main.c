#include <stdio.h>
#include "helpers/vector.h"
#include "compiler.h"

int main()
{
    int res = compile_file("./test.c", "./test" , 0);

    if (res == COMPILER_FILE_COMPILED_OK) printf(" Compilation successful");
    else if (res== COMPILER_FAILED_WITH_ERRORS) printf ("Compilation came up with an Error");
    else printf("Unknown Response from Compiler");

    return 0;

}