#include "RLEList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NULL_TERMINATOR '\0'
#define BASE_TEN 10
#define REQUIRED_START 3
#define OUT_OF_BOUNDS 2
#define SUCCESS 2
#define NULL_LIST 1

static int numberOfDigit(RLEList list);

struct RLEList_t{
    char letter;
    int numOfRepetition;
    struct RLEList_t* next;
};

RLEList RLEListCreate()
{
    RLEList list = malloc(sizeof(*list));
	if(!list) {
		return NULL;
	}
    list -> letter = NULL_TERMINATOR;
    list -> numOfRepetition = 0;
    list -> next = NULL;
	return list;
}

void RLEListDestroy(RLEList list){
    while(list) {
		RLEList toDelete = list;
		list = list -> next;
		free(toDelete);
	}
}

void updateList(RLEList newList, char value){
    newList -> numOfRepetition = 1;
    newList -> letter = value;
}

RLEListResult RLEListAppend(RLEList list, char value)
{
    if(list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }

	while(list -> next != NULL){
        list = list -> next;
    }
    if (value == list -> letter){
        list -> numOfRepetition ++;
        return RLE_LIST_SUCCESS;
    }

    else{
        RLEList newList = RLEListCreate();
        updateList(newList, value);
        list -> next = newList;
        return RLE_LIST_SUCCESS;
    }
    
}

int RLEListSize(RLEList list)
{
    int totalNumberOfLetters = 0;  
    if(list == NULL){
        return -1;
    }

    while(list != NULL){
        totalNumberOfLetters = totalNumberOfLetters + list -> numOfRepetition ;
        list = list -> next; 
    }
    return totalNumberOfLetters;
}
int removeInputTest(RLEList list, int index, int check){
    if(list == NULL){
        check = NULL_LIST;
    }
    if (index < 0 || index >= RLEListSize(list)){
        check = OUT_OF_BOUNDS;
    }
    return check;
}
int firstInstance(RLEList current, RLEList list, int test){
    if (current -> numOfRepetition <= 1){
        list = current -> next;
        free(current);
        if(list == NULL){
            test = NULL_LIST;
            return test;
        }
        test = SUCCESS;
    }
    else{
        current -> numOfRepetition--;
        test = SUCCESS;
    }
    return test;
}
RLEListResult RLEListRemove(RLEList list, int index)
{
    int test = removeInputTest(list, index, 0);
    if(test == NULL_LIST){
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(test == OUT_OF_BOUNDS) {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList current = list;
    RLEList previous = list;
    int totalNumberOccurrence = current -> numOfRepetition - 1 ;
    if(totalNumberOccurrence >= index){
        test = firstInstance(current, list, test);
        if(test == NULL_LIST){
            return RLE_LIST_NULL_ARGUMENT;
        }
        return RLE_LIST_SUCCESS;
    } 
    else{
        while (totalNumberOccurrence < index){
            previous = current;
            current = current -> next;
            totalNumberOccurrence = current -> numOfRepetition + totalNumberOccurrence ;
        }

        if (current->numOfRepetition <= 1){
            if(current -> next ==NULL){
                previous -> next =NULL;
                free(current);
                return RLE_LIST_SUCCESS;
            }
            previous -> next = current -> next;
            RLEList currentNext = current -> next;
            if(previous -> letter == currentNext -> letter){
                previous -> numOfRepetition = previous -> numOfRepetition + currentNext -> numOfRepetition;
                previous -> next = currentNext -> next;
                free(currentNext);
            }
            free(current);
        }
        else{
            current -> numOfRepetition--;
        }
    }
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if(list == NULL){
        if(result != NULL){
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
    if (index < 0 || index >= RLEListSize(list)){
        if(result != NULL){
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }
    
    int numberOfRepetition = list -> numOfRepetition - 1 ;
    if(numberOfRepetition >= index){
        if(result != NULL){
            *result = RLE_LIST_SUCCESS;
        }
        return list -> letter;
    }
    else{
        while (numberOfRepetition < index){
            list = list -> next;
            numberOfRepetition = list -> numOfRepetition + numberOfRepetition ;
        }
    }
    if(result != NULL){
        *result = RLE_LIST_SUCCESS;
    }
    return list -> letter;
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if(list == NULL){
        if(result != NULL){
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    int sizeOfString = numberOfDigit(list);
    char* str = malloc((sizeof(char))*sizeOfString);
    char* temp = malloc((sizeof(char))*sizeOfString);
    if (str == NULL || temp == NULL){
        free(str);
        free(temp);
        return NULL;
    }

    for(int i = 0;i < sizeOfString; i++){
        str[i] = NULL_TERMINATOR;
    }
    while (list != NULL) {
        sprintf(temp,"%c%d\n",list -> letter, list -> numOfRepetition);
        strcat(str,temp);
        list = list -> next;
    }
    if(result != NULL){
        *result = RLE_LIST_SUCCESS;
    }
    strcat(str,"\0");
    free(temp);
    return str;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if(list == NULL || map_function == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEList mapList = RLEListCreate();
    RLEListResult result;
    int sizeOfList = RLEListSize(list);

    for (int index = 0; index < sizeOfList ; index++){
        char letter = RLEListGet(list,index,&result);
        letter = map_function(letter);
        result = RLEListAppend(mapList,letter);
    }

   RLEListDestroy(list->next);
    list -> next = NULL;

    for(int index=0; index < sizeOfList ;index++) {
        result = RLEListAppend(list, RLEListGet(mapList,index,&result));
    }

    RLEListDestroy(mapList);
    return  RLE_LIST_SUCCESS;
}

static int numberOfDigit(RLEList list)
{
    int numberOfDigits = 0;
    while(list != NULL){
        int temp = list -> numOfRepetition;
        while ((temp / BASE_TEN) > 0){
            numberOfDigits++;
            temp = temp / BASE_TEN;
        }
        numberOfDigits = numberOfDigits + REQUIRED_START;
        list = list -> next;
    }
    numberOfDigits = numberOfDigits + 1; //+1 for \0
    return numberOfDigits ; 
}