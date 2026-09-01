#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  
#include <stdbool.h>

int main(){
    FILE *fptr;
    char dataOneLine[16];
    bool endReached = false;
    int ch;
    int hexnum=0;
    int bytesCount=0;
    char asciistr[6]=("ASCII");
    char hexastr[12] = ("Hexadecimal");

    //randomfile.txt topuriaFucked.png
    fptr = fopen("randomfile.txt", "rb");
    if(fptr ==NULL){
        printf("The file failed to open");
    }

    else{
        printf("The file is opened\n");
        printf("Offset %15s %42s\n",hexastr, asciistr);

        while (endReached==false){ 
            bytesCount = 0;

            for(int i = 0; i < 16; i++){
                if((ch =  fgetc(fptr))!= EOF){
                    dataOneLine[i] = ch;
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


    return 0;
}