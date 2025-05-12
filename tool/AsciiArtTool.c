#include "AsciiArtTool.h"
#include "RLEList.h"
#include <stdlib.h>

RLEList asciiArtRead(FILE* in_stream)
{
    RLEList newList = RLEListCreate();
    if(newList == NULL){
        return NULL;
    }
    
    char value = fgetc(in_stream);
    while(value != EOF){
      RLEListAppend(newList,value);
      value = fgetc(in_stream);
    }

    return newList;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    if(out_stream == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }

    int sizeOfList = RLEListSize(list);

    RLEListResult result; 
    for(int index = 0 ; index < sizeOfList; index++){
        char letter = RLEListGet(list, index , &result);
        fputc(letter ,out_stream);
    }
    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if(out_stream == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }

   RLEListResult result; 
   char* encoded = RLEListExportToString(list,&result);
   if(encoded == NULL){
       return RLE_LIST_NULL_ARGUMENT;
   }
   fprintf(out_stream,"%s",encoded);
   free(encoded);
   
   return RLE_LIST_SUCCESS;
}
