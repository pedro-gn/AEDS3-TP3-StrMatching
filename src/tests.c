#include "../include/tests.h"


// Cria o estrutura testes com pelo nome do arquivo com os testes passado
Tests *createTests(char *fileName){

    Tests *tests;
    tests = (Tests *)malloc(sizeof(Tests));

    tests->fileName = malloc(strlen(fileName) * sizeof(char));
    strcpy(tests->fileName,fileName);


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

void writeText(int **results, int nresults, char *fileName){
    char *name;
    FILE *f;

    name = strtok(fileName, ".");
    strcat(name, ".out");

    f = fopen(name, "w");
    
    for(int i = 0; i< nresults; i++){
        if(results[i] == -1){
            fprintf(f,"N\n");
        }else{
            fprintf(f,"S %d\n", results[i]);
        }
    }
    
    fclose(f);

}   

// Libera a memoria dos textos e dos patterns 
void freeTests(Tests *tests){

    for(int i = 0; i < tests->ntests; i++){
        free(tests->patterns[i]);
        free(tests->texts[i]);
    }

    free(tests->fileName);
    free(tests->patterns);
    free(tests->texts);
    free(tests);
}

// Executa os testes com o algoritmo escolhido 
void execTests(Tests *tests, int strmatchAlgo){

    pthread_t threads[tests->ntests]; //threads
    int *results[tests->ntests]; //resultados dos testes

    // Cria as threads
    for(int i = 0; i < tests->ntests; i++){

        // Prepara os argumentos para mandar para thread
        FuncArgs *args = malloc(sizeof(FuncArgs));
        strcpy(args->text, tests->texts[i]);
        strcpy(args->pattern, tests->patterns[i]);

        // Escolhe Qual Algoritmo Será usado
        switch (strmatchAlgo){
        case 1: 
            pthread_create(&threads[i], NULL, bruteforce, (void*)args);
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            printf("Algoritmo Invalido!!");
            free(args);
            break;
        }
    }

    // Aguarda o término das threads
    for (int i = 0; i < tests->ntests; i++) {
        pthread_join(threads[i], (void**)&results[i]);
   
    }


    writeText(results, tests->ntests, tests->fileName);
}