#include <stdio.h>
#include <stdlib.h>
#include "peca.h"


 struct peca {
        char *id;  // string identificadora da peça
        char *cor; //cor da peça
        Movimento *movPeca;
 };

struct movimento{
    int x;
    int y;
};

TAB_tpCondRet criaPeca(Peca *novo) {
          novo = (Peca *) malloc(sizeof(Peca));
          if(novo == NULL) {
            return TAB_CondRetFaltouMemoria;
          }
          novo->id = (char *) sizeof(char);
          if(novo->id == NULL) {
            return TAB_CondRetFaltouMemoria;
          }
          *(novo->id) = 'V';
          novo->cor = (char *) sizeof(char);
          if(novo->cor == NULL) {
            return TAB_CondRetFaltouMemoria;
          }
          *(novo->cor) = 'V';
          return TAB_CondRetOK; 
   }






void liberaPeca(Peca *peca) {
         free(peca->cor);
         free(peca->id);
         free(peca);
   }


