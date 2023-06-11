#include <stdio.h>
#include <stdlib.h>
#include "../include/tests.h"


int main(int argc, char **argv){
    Tests *tests = createTests(argv[1]);

    execTests(tests, 1);
    
    // Libera a memoria 
    freeTests(tests);
}