#include <stdio.h>
#include <stdlib.h>
#include "peca.h"



typedef struct peca {
        char *id;  // string identificadora da peça
        char *cor; //cor da peça
        int x; //quantidade de movimentos no eixo vertical
        int y; // quantidade de movimentos no eixo horizontal
   }Peca;  



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
          novo.x = 0;
          novo.y = 0;
          return TAB_CondRetOK; 
   }






void liberaPeca(Peca *peca) {
         free(peca->cor);
         free(peca->id);
         free(peca);
   }


