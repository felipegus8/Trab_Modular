//
//  main.c
//  modular4
//
//  Created by Roberto Nogueira on 6/12/16.
//  Copyright © 2016 Roberto Nogueira. All rights reserved.
//

#include <stdio.h>
#include "tabuleiro.h"

LIS_tppLista pLista;
pCasa cas;

int main(int argc, const char * argv[]) {
    char cor,id;
#ifdef _DEBUG
    printf("to em debug\n");
#endif
    TAB_CriaLL((LIS_tppLista *)&pLista);
    //Imprime(pLista);
    TAB_InserirPeca(pLista, 0, 0, 'B', 'R');
    TAB_ObterPeca(pLista, 0, 0, &cor, &id);
    //TAB_DestruirTabuleiro(pLista);
    
    //Imprime(pLista);
    printf("%c e %c\n",cor,id);
    return 0;
}
