#include <stdio.h>
#include <stdlib.h>
#include "lib/cpu_t.h"

//-----------------------------------------------------------------------------------------------------

enum EXITS
{
    FOPEN_ERR =  -1
};

//-----------------------------------------------------------------------------------------------------

int main()
{
    FILE *fin;

    if((fin = fopen("/Users/andreyandriyaynen/CLionProjects/assembler/cmake-build-debug/output.txt", "r")) == nullptr)
        return FOPEN_ERR;
    long  filesize;
    char * arr = text_reading(fin, &filesize);
    fclose(fin);

    cpu_t theCPU;
    cpu_exec( &theCPU, arr );

    cpu_load( &theCPU );

    cpu_dtor( &theCPU );

    return 0;
}

//-----------------------------------------------------------------------------------------------------

char * text_reading(FILE *file, long * FileSize)
{
    fseek(file, 0, SEEK_END);
    *FileSize = ftell(file);
    rewind(file);
    char * buffer = (char *) calloc(*FileSize, sizeof(char));
    fread(buffer, sizeof(char *), *FileSize, file);

    return buffer;
}