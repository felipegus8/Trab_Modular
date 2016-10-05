#include <stdio.h>
#include <stdlib.h>
#include "peca.h"
typedef struct movimento{
    int x;
    int y;
}Movimento;

 typedef struct peca {
        char id;  // string identificadora da peça
        char cor; //cor da peça
	int qtdMov; //quantidade de movimentos da peça
	int movParaTras; // Bool para ver se a peça move para trás ou não
        Movimento *movPeca; //Vetor da struct movimento contendo todos os movimentos que a peça pode fazer
 }Peca;



PEC_tpCondRet criaPeca(Peca **novo,char id,char cor) {
          *novo = (Peca *) malloc(sizeof(Peca));
          if(*novo == NULL) {
            return PEC_CondRetFaltouMemoria;
          }
		  *novo->id = id;
    
		  *novo->cor = cor;
          return PEC_CondRetOK; 
   }
PEC_tpCondRet alocaMovimento(Peca **novo,int i)
{
	*novo->movPeca = (Movimento*)malloc(sizeof(Movimento)*i);
	return PEC_CondRetOK;
}

PEC_tpCondRet recebeX(int x,Peca **novo,int i)
{
	*novo->movPeca[i].x = x;
	return PEC_CondRetOK;
}
PEC_tpCondRet recebeY(int y,Peca **novo,int i)
{
	*novo->movPeca[i].y = y;
	return PEC_CondRetOK;
}
PEC_tpCondRet retornaMovimento(Peca **novo)
{
	
}
PEC_tpCondRet ensinaMovimentosPecasConhecidas(Peca **novo)
{
	int i = 1,j = 1,k;
	switch(*novo->id)
	{
	case 'T':
		*novo->movPeca = (Movimento*)malloc(sizeof(Movimento)*14);
		*novo->qtdMov = 14;
		*novo->movParaTras = 1;
		if(novo->movPeca == NULL)
		{
			return PEC_CondRetFaltouMemoria;
		}
		for(i=1;i<8;i++)
		{
			*novo->movPeca[i].x = i;
			*novo->movPeca[i].y = 0;
		}
		for(j=1;j<8;j++)
		{
			*novo->movPeca[i].x = 0;
			*novo->movPeca[i].y = j;
			i++;
		}
	break;
	case 'C':
		*novo->movPeca = (Movimento*)malloc(sizeof(Movimento)*2);
		*novo->qtdMov = 2;
		*novo->movParaTras = 1;
		if(*novo->movPeca == NULL)
		{
		return PEC_CondRetFaltouMemoria;
		}
		*novo->movPeca[0].x = 2;
		*novo->movPeca[0].y = 1;
		*novo->movPeca[1].x = 1;
		*novo->movPeca[1].y = 2;
		break;
	case 'B':
		*novo->movPeca = (Movimento*)malloc(sizeof(Movimento)*7);
		*novo->qtdMov = 7;
		*novo->movParaTras = 1;
		if(novo->movPeca == NULL)
		{
		return PEC_CondRetFaltouMemoria;
		}
		i = 1;
		for(k=1;k<8;k++)
		{
			*novo->movPeca[k].x = i;
			*novo->movPeca[k].y = i;
		}
		break;
	case 'P':
		*novo->movPeca = (Movimento*)malloc(sizeof(Movimento)*2);
		*novo->qtdMov = 2;
		*novo->movParaTras = 0;
		if(*novo->movPeca == NULL)
		{
		return PEC_CondRetFaltouMemoria;
		}
		*novo->movPeca[0].x = 1;
		*novo->movPeca[0].y = 0;
		*novo->movPeca[1].x = 1;
		*novo->movPeca[1].y = 1;
		break;
	case 'D':
		*novo->movPeca = (Movimento*)malloc(sizeof(Movimento)*21);
		*novo->qtdMov = 21;
		*novo->movParaTras = 1;
		if(*novo->movPeca == NULL)
		{
		return PEC_CondRetFaltouMemoria;
		}
		for(i=1;i<8;i++)
		{
			*novo->movPeca[i].x = i;
			*novo->movPeca[i].y = 0;
		}
		for(j=1;j<8;j++)
		{
			*novo->movPeca[i].x = 0;
			*novo->movPeca[i].y = j;
			i++;
		}
		j=1;
		for(k=1;k<8;k++)
		{
			*novo->movPeca[i].x = j;
			*novo->movPeca[i].y = j;
		}
		break;
	case 'R':
		*novo->movPeca = (Movimento*)malloc(sizeof(Movimento)*3);
		*novo->qtdMov = 3;
		*novo->movParaTras = 1;	
		if(*novo->movPeca == NULL)
		{
		return PEC_CondRetFaltouMemoria;
		}
		*novo->movPeca[0].x = 1;
		*novo->movPeca[0].y = 0;
		*novo->movPeca[1].x = 1;
		*novo->movPeca[1].y = 1;
		*novo->movPeca[2].x = 0;
		*novo->movPeca[2].y = 1;
		break;

	default:
	return PEC_CondRetNaoAchouPeca;
	}
	return PEC_CondRetOK;
}

PEC_tpCondRet ensinaMovimentosPecasDesconhecidas(Peca **novo,Movimento *movPecaNova)
{
	*novo->movPeca = (Movimento*)malloc(sizeof(Movimento));
	if(*novo->movPeca == NULL)
	{
		return PEC_CondRetFaltouMemoria;
	}
	*novo->movPeca = movPecaNova;
	return PEC_CondRetOK;
}




PEC_tpCondRet liberaPeca(Peca *peca) {
         free(peca);
		 return PEC_CondRetOK;
   }


