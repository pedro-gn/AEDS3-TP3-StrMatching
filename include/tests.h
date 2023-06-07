#ifndef TESTS_H
#define TESTS_H

#define MAX_TEXT_SIZE 10000
#define MAX_PATTERN_SIZE 100
#include <stdio.h>
#include <stdlib.h>

// Contem todos os textos e o padrao e a quantidade de testes
// Os indices dos vetores texts e patterns são correspondentes, ou seja, o padrao do texts[0] corresponde ao pattern[0]
typedef struct tests{
    int ntests;
    char **texts;
    char **patterns;

}Tests;

Tests *createTests(char *fileName);
void freeTests(Tests *tests);
void execTests(Tests *tests, int strmatchAlgo);
#endif