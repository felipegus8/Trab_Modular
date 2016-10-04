#include <stdio.h>
#include <stdlib.h>
#include "peca.h"



typedef struct peca {
        char *id;  // string identificadora da peça
        char *cor; //cor da peça
        int x; //quantidade de movimentos no eixo vertical
        int y; // quantidade de movimentos no eixo horizontal
   }Peca;  
