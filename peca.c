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

PEC_tpCondRet criaPeca(Peca *novo) {
          novo = (Peca *) malloc(sizeof(Peca));
          if(novo == NULL) {
            return PEC_CondRetFaltouMemoria;
          }
          novo->id = (char *) sizeof(char);
          if(novo->id == NULL) {
            return PEC_CondRetFaltouMemoria;
          }
          *(novo->id) = 'V';
          novo->cor = (char *) sizeof(char);
          if(novo->cor == NULL) {
            return PEC_CondRetFaltouMemoria;
          }
          *(novo->cor) = 'V';
          return PEC_CondRetOK; 
   }

PEC_tpCondRet ensinaMovimentosPecasconhecidas(Peca *novo)
{
	int i = 1,j = 1;
	switch(novo->id)
	{
	case "T":
		novo->movPeca = (Movimento*)malloc(sizeof(Movimento)*14);
		for(i=0;i<8;i++)
		{
			novo->movPeca->x = i;
			novo->movPeca->y = 0;
		}
		i = 1;
		for(j=0;j<8;j++)
		{
			novo->movPeca->x = 0;
			novo->movPeca->y = j;
		}
	}
}






void liberaPeca(Peca *peca) {
         free(peca->cor);
         free(peca->id);
         free(peca);
   }


