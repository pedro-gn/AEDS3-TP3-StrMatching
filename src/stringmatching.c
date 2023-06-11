#include "../include/stringmatching.h"

// Reverte a string
char *reverseString(char *string, int stringLenght){
    char *revString = malloc(sizeof(char)*stringLenght); 

    for(int i = stringLenght-1, j = 0; i >= 0; i--, j++){
        revString[j] = string[i];
    }

    revString[stringLenght] = '\0';

    return revString;
}


void* bruteforce(void *arg){
    FuncArgs *args = (FuncArgs*)arg;

    int textSize = strlen( args->text);
    int patternSize = strlen(args->pattern);
    char *revPattern = reverseString(args->pattern, patternSize);


    for( int i = 0; i < textSize + patternSize-1; i++){
        for( int j = i, k = 0 ; k < patternSize; j++, k++){

            if(j>=textSize){
                j = j - textSize;
            }

            if( args->text[j] == args->pattern[k] ){
                // Casou 1 caractere
                if(k == patternSize-1){
                    // Checa se casou todos caracteres 
                    free(revPattern);
                    free(args);
                    return (void*)i+1;
                }else{
                    continue;
                }
            }else{
                // Caso não case, para e move o padrao em 1 posição
                break;
            }
        }
    }

    // Faz o mesmo processo com a string invertida
    for( int i = 0; i < textSize + patternSize-1; i++){
        for( int j = i, k = 0 ; k < patternSize; j++, k++){

            if(j>=textSize){
                j = j - textSize;
            }

            if( args->text[j] == revPattern[k] ){
                // Casou 1 caractere
                if(k == patternSize-1){
                    // Checa se casou todos caracteres
                    free(revPattern); 
                    free(args);
                    return (void*)(i + patternSize);
                }else{
                    continue;
                }
            }else{
                // Caso não case, para e move o padrao em 1 posição
                break;
            }
        }
    }
    
    free(args);
    free(revPattern);
    return (void*)-1;
}

// Pre processamento que cria a tabela de deslocamento ou bad characteres
void preProcess(char *pattern, int patternLength, int *badCharTable) {
    int i;
    
    // Inicializa a tabela de caracteres ruins com o comprimento do padrão
    for (i = 0; i < ALPHABET_SIZE; i++) {
        badCharTable[i] = patternLength;
    }
    
    // Preenche a tabela com o deslocamento correto para cada caractere do padrão
    for (i = 0; i < patternLength - 1; i++) {
        badCharTable[(int)pattern[i]] = patternLength - 1 - i;
    }
}

void BMHSearch(void *arg) {
    FuncArgs *args = (FuncArgs*)arg;

    int textLength = strlen( args->text);
    int patternLength = strlen(args->pattern);
    char *revPattern = reverseString(args->pattern, patternLength);
    
    int badCharTable[ALPHABET_SIZE];

    preProcess(args->pattern, patternLength, badCharTable);
    
    int shift = 0;
    while (shift <= textLength - patternLength) {
        int j = patternLength - 1;
        
        // Enquanto os caracteres do padrão e do texto forem iguais
        while (j >= 0 && args->pattern[j] == args->text[shift + j]) {
            j--;
        }
        
        if (j < 0) {
            // O padrão foi encontrado
            printf("Padrão encontrado na posição %d\n", shift);
            
            // Realiza um deslocamento único após o padrão
            shift += badCharTable[(int)args->text[shift + patternLength]];
        } else {
            // Realiza um deslocamento com base na tabela de caracteres ruins
            shift += badCharTable[(int)args->text[shift + patternLength - 1]];
        }
    }
}