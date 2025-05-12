#ifndef HW1_ASCIARTTOOL_H
#define HW1_ASCIARTTOOL_H

#include <stdio.h>
#include <stdbool.h>

#include "RLEList.h"
RLEList asciiArtRead(FILE* in_stream); //The function reads the given file and compresses it using the RLE method.
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);
//The function writes an image that is represented by a list of type istRLEL to a file.
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);
//The function writes the image to the file in a compressed form.

#endif //HW1_ASCIARTTOOL_H