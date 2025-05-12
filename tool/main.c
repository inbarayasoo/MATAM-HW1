#include "AsciiArtTool.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SOURCE 2
#define TARGET 3
#define FLAG_POSITION 1
#define NUMBER_OF_ARGUMENTS 4
#define STRING_SIZE 3
#define SPACE ' '
#define AT '@'
#define FLAG_E "-e"
#define FLAG_I "-i"

char replaceCharacter(char character);

int main(int argc, char** argv){
    if (argc < NUMBER_OF_ARGUMENTS) {
        return 0;
    }

    FILE* inStream = fopen(argv[SOURCE], "r");
    if (!inStream) {
        return 0;
    }
    FILE* outStream  = fopen(argv[TARGET], "w");
    if (!outStream) { 
        fclose(inStream); 
        return 0;
    }
    RLEList list = NULL;   
    list = asciiArtRead(inStream); 
    char flagE[STRING_SIZE] = FLAG_E;
    char flagI[STRING_SIZE] = FLAG_I;
    if(strcmp(flagE , argv[FLAG_POSITION]) == 0){
        asciiArtPrintEncoded(list,outStream); 
    }
    else if (strcmp(flagI , argv[FLAG_POSITION]) == 0){
         RLEListMap(list, replaceCharacter);
         asciiArtPrint(list,outStream);
    }
    fclose(inStream);
    fclose(outStream);
    RLEListDestroy(list);
    return 0;
}

char replaceCharacter(char character)
{
    if(character == SPACE){
        return AT;
    }
    if(character == AT){
        return SPACE;
    }
    return character;
}