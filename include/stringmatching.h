#ifndef STRINGMATCHING_H
#define STRINGMATCHING_H

#include <string.h>
#include <stdio.h>  
#include <stdlib.h>

#define MAX_TEXT_SIZE 10000
#define MAX_PATTERN_SIZE 100
#define ALPHABET_SIZE 256

typedef struct funcArgs{
    char text[MAX_TEXT_SIZE];
    char pattern[MAX_PATTERN_SIZE];
}FuncArgs;


void* bruteforce(void *arg);


#endif