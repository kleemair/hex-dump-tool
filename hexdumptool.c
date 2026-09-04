#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  
#include <stdbool.h>
#include <math.h>


int main(int argc, char *argv[]){
    FILE *fptr;
    char dataOneLine[16];
    bool endReached = false;
    int memory = 1;
    int ch;
    int filesize;
    int hexnum=0;
    int bytesCount=0;
    char asciistr[6]=("ASCII");
    char hexastr[12] = ("Hexadecimal");
    int *offsetSearchfound = malloc(memory * sizeof(int));
    if (offsetSearchfound == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    char *buffer;
    char bufferSearch[17];
    bool foundSome = false;
    bool mustsearch = false;

    //checking input
    if (argc == 1)
    {
        printf("No file passed.\n");
        return 1;
    }
    else if(argc > 2){
        if(strcmp(argv[2], "--search") != 0){
            printf("Error in input\n");
            return 1;
        }
        else if(argc == 3 && strcmp(argv[2], "--search") == 0){
            printf("Missing values to search");
            return 1;
        }
        else if(argc > 4){
            printf("Too many values passed");
            return 1;
        }
        else if(argc ==4 && strcmp(argv[2], "--search") == 0){
            mustsearch = true;
        }
    }

    fptr = fopen(argv[1], "rb");
    if(fptr ==NULL){
        printf("The file failed to open");
    }

    else{
        printf("The file is opened\n\n");
        printf("Offset %15s %42s\n",hexastr, asciistr);

        //fill buffer with file content
        fseek(fptr, 0L, SEEK_END);
        filesize = ftell(fptr);
        rewind(fptr);
        buffer = malloc(filesize+1);
        if (buffer == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        buffer[filesize] = '\0';
        fread(buffer, 1, filesize, fptr);

        //search 
        if(mustsearch == true){
            sprintf(bufferSearch, "%s", argv[3]);
            int searchLength = strlen(bufferSearch);
            for (int i = 0; i < filesize - searchLength+1; i++)
            {
                if(memcmp(buffer+i, bufferSearch, searchLength) == 0){
                    foundSome = true;
                    memory++;
                    int *temp = realloc(offsetSearchfound, memory* sizeof(int));
                    if (temp == NULL) {
                        printf("Memory reallocation failed\n");
                        free(offsetSearchfound);
                        return 1;
                    }
                    offsetSearchfound = temp;
                    offsetSearchfound[memory-2] = floor(i/16);  
                } 
            }
        }

        //read one line from file in bytes and print
        while (endReached==false){ 
            bytesCount = 0;

            for(int i = 0; i < 16; i++){
                if(hexnum + i < filesize){
                    dataOneLine[i] = buffer[i+hexnum];
                }
                else{
                    endReached = true;
                    break;
                }
                bytesCount= i+1;
                
            }
            
            //offset
            printf("%08x   ", hexnum);

            
            //hexadecimal 
            for(int i = 0; i< 16; i++){
                if (i < bytesCount){
                    printf("%02x ", (unsigned char)dataOneLine[i]);
                }
                else{
                    printf("   "); 
                }
            }
            
            printf("|");

            //ASCII 
            for(int i = 0; i< bytesCount; i++){
                if(isprint(dataOneLine[i])!= 0){
                    printf("%c", dataOneLine[i]);
                }
                else{
                    printf(".");
                }
            }
            printf("|\n");

           hexnum+=16;
        }
        fclose(fptr);
    }
    
    if(foundSome == false && mustsearch == true){
        printf("Search was not successful");
    }
    else if(foundSome == true && mustsearch == true){
        printf("\nFound \"%s\" %d %s:\n", bufferSearch, memory-1, (memory-1 == 1) ? "time" : "times");
        for (int i = 0; i < memory-1; i++)
        {
            printf("Number %d found at offset: %08x\n", i+1, offsetSearchfound[i]);
        }
    }

    free(buffer);
    free(offsetSearchfound);
    return 0;
}