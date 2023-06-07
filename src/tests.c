#include "../include/tests.h"

// Cria o estrutura testes com pelo nome do arquivo com os testes passado
Tests *createTests(char *fileName){

    Tests *tests;
    tests = (Tests *)malloc(sizeof(Tests));

    FILE *f = fopen(fileName, "r");

    fscanf(f," %d ", &tests->ntests);
    
    tests->texts = (char**)malloc(tests->ntests *  sizeof(char*));
    tests->patterns = (char**)malloc(tests->ntests *  sizeof(char*));

    for(int i = 0; i < tests->ntests; i++){
        tests->texts[i] = malloc(MAX_TEXT_SIZE * sizeof(char));
        tests->patterns[i] = malloc(MAX_PATTERN_SIZE * sizeof(char));
        fscanf(f, " %s %s ", tests->patterns[i], tests->texts[i]);
    }

    fclose(f);

    return tests;
}


// Libera a memoria dos textos e dos patterns 
void freeTests(Tests *tests){

    for(int i = 0; i < tests->ntests; i++){
        free(tests->patterns[i]);
        free(tests->texts[i]);
    }

    free(tests->patterns);
    free(tests->texts);
    free(tests);
}



void execTests(Tests *tests, int strmatchAlgo){
    
}