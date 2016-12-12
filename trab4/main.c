//
//  main.c
//  modular4
//
//  Created by Roberto Nogueira on 6/12/16.
//  Copyright © 2016 Roberto Nogueira. All rights reserved.
//

#include <stdio.h>
#include "tabuleiro.h"

LIS_tppLista pLista,pCabeca;
pCasa cas;

int main(int argc, const char * argv[]) {
    char cor,id;
    int numErros = 0;
    TAB_CriaLL((LIS_tppLista *)&pLista);
    TAB_Deturpa(pLista, 7);
    TAB_VerificaTabuleiro(pLista, &numErros);
    TAB_DestruirTabuleiro(pLista);
    printf("%d\n",numErros);
    numErros = 0;
    TAB_CriaLL((LIS_tppLista *)&pLista);
    TAB_Deturpa(pLista, 4);
    TAB_VerificaTabuleiro(pLista, &numErros);
    printf("num erros: %d\n",numErros);
    TAB_DestruirTabuleiro(pLista);
    TAB_CriaLL((LIS_tppLista *)&pLista);
    TAB_Deturpa(pLista, 1);
    TAB_VerificaTabuleiro(pLista, &numErros);
    printf("num erros: %d\n",numErros);
    TAB_DestruirTabuleiro(pLista);
    
    
    return 0;
}
