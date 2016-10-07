/***************************************************************************
*  $MCI Módulo de implementação: PEC  Peca
*
*  Arquivo gerado:              Peca.c
*  Letras identificadoras:      PEC
*
*  Autores: Felipe Viberti,Luis Claudio e Victor Nogueira
*
*  $HA Histórico de evolução:
*     Versão  Autores                                           Data          Observações
*     1       Felipe Viberti,Luis Claudio e Victor Nogueira   02/out/2016  início desenvolvimento
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "peca.h"


/***********************************************************************
*
*  $TC Tipo de dados: MOV Movimento da Peca
*
*
***********************************************************************/
typedef struct movimento{
    int x;
    int y;
}Movimento;

/***********************************************************************
*
*  $TC Tipo de dados: Peca Peca
*
*
***********************************************************************/
 typedef struct peca {
        char id;  // string identificadora da peça
        char cor; //cor da peça
	    int qtdMov; //quantidade de movimentos da peça
	    int movParaTras; // Bool para ver se a peça move para trás ou não
        Movimento *movPeca; //Vetor da struct movimento contendo todos os movimentos que a peça pode fazer
 }Peca;


 /*****  Código das funções exportadas pelo módulo  *****/

 /***************************************************************************
*
*  Função: PEC  &Criar peca
*  ****/
PEC_tpCondRet PEC_CriaPeca(Peca **novo,char id,char cor) {
          *novo = (Peca *) malloc(sizeof(Peca));
          if(*novo == NULL) {
            return PEC_CondRetFaltouMemoria;
          }
		  (*novo)->id = id;
    
		  (*novo)->cor = cor;
          return PEC_CondRetOK; 
   }/* Fim função: PEC  &Criar peca */

 /***************************************************************************
*
*  Função: PEC  &Ensina Movimentos Pecas Conhecidas
*  ****/
PEC_tpCondRet PEC_EnsinaMovimentosPecasConhecidas(Peca **novo)
{
	int i = 1,j = 1,k;
	switch((*novo)->id)
	{
	case 'T':
		(*novo)->movPeca = (Movimento*)malloc(sizeof(Movimento)*14);
		(*novo)->qtdMov = 14;
		(*novo)->movParaTras = 1;
		if((*novo)->movPeca == NULL)
		{
			return PEC_CondRetFaltouMemoria;
		}
		for(i=1;i<8;i++)
		{
			(*novo)->movPeca[i].x = i;
			(*novo)->movPeca[i].y = 0;
		}
		for(j=1;j<8;j++)
		{
			(*novo)->movPeca[i].x = 0;
			(*novo)->movPeca[i].y = j;
			i++;
		}
	break;
	case 'C':
		(*novo)->movPeca = (Movimento*)malloc(sizeof(Movimento)*2);
		(*novo)->qtdMov = 2;
		(*novo)->movParaTras = 1;
		if((*novo)->movPeca == NULL)
		{
		return PEC_CondRetFaltouMemoria;
		}
		(*novo)->movPeca[0].x = 2;
		(*novo)->movPeca[0].y = 1;
		(*novo)->movPeca[1].x = 1;
		(*novo)->movPeca[1].y = 2;
		break;
	case 'B':
		(*novo)->movPeca = (Movimento*)malloc(sizeof(Movimento)*7);
		(*novo)->qtdMov = 7;
		(*novo)->movParaTras = 1;
		if((*novo)->movPeca == NULL)
		{
		return PEC_CondRetFaltouMemoria;
		}
		i = 1;
		for(k=1;k<8;k++)
		{
			(*novo)->movPeca[k].x = i;
			(*novo)->movPeca[k].y = i;
		}
		break;
	case 'P':
		(*novo)->movPeca = (Movimento*)malloc(sizeof(Movimento)*2);
		(*novo)->qtdMov = 2;
		(*novo)->movParaTras = 0;
		if((*novo)->movPeca == NULL)
		{
		return PEC_CondRetFaltouMemoria;
		}
		(*novo)->movPeca[0].x = 1;
		(*novo)->movPeca[0].y = 0;
		(*novo)->movPeca[1].x = 1;
		(*novo)->movPeca[1].y = 1;
		break;
	case 'D':
		(*novo)->movPeca = (Movimento*)malloc(sizeof(Movimento)*21);
		(*novo)->qtdMov = 21;
		(*novo)->movParaTras = 1;
		if((*novo)->movPeca == NULL)
		{
		return PEC_CondRetFaltouMemoria;
		}
		for(i=1;i<8;i++)
		{
			(*novo)->movPeca[i].x = i;
			(*novo)->movPeca[i].y = 0;
		}
		for(j=1;j<8;j++)
		{
			(*novo)->movPeca[i].x = 0;
			(*novo)->movPeca[i].y = j;
			i++;
		}
		j=1;
		for(k=1;k<8;k++)
		{
			(*novo)->movPeca[i].x = j;
			(*novo)->movPeca[i].y = j;
		}
		break;
	case 'R':
		(*novo)->movPeca = (Movimento*)malloc(sizeof(Movimento)*3);
		(*novo)->qtdMov = 3;
		(*novo)->movParaTras = 1;	
		if((*novo)->movPeca == NULL)
		{
		return PEC_CondRetFaltouMemoria;
		}
		(*novo)->movPeca[0].x = 1;
		(*novo)->movPeca[0].y = 0;
		(*novo)->movPeca[1].x = 1;
		(*novo)->movPeca[1].y = 1;
		(*novo)->movPeca[2].x = 0;
		(*novo)->movPeca[2].y = 1;
		break;

	default:
	return PEC_CondRetNaoAchouPeca;
	}
	return PEC_CondRetOK;
} /* Fim função: PEC  &Ensina Movimentos Pecas Conhecidas */
 /***************************************************************************
*
*  Função: PEC  &Ensina Movimentos Pecas Desconhecidas
*  ****/
PEC_tpCondRet PEC_EnsinaMovimentosPecasDesconhecidas(Peca **novo)
{
	char idLido,corLido;
	int x,y,i,j;
	FILE *fp;
	int qtdMov;
	if ((fp=fopen("PecasNovas.txt","r"))==NULL)
			{
			 printf("Error! opening file");
			exit(1);         
			}
			i = 0;
		while(fscanf(fp,"%c %c",&idLido,&corLido) == 2)
		{
			if ((idLido == (*novo)->id) && (corLido == (*novo)->cor))
			{
				while(fscanf(fp,"%d  %d",&x,&y) == 2)
				i++;
			}
			else
			{
				while(fscanf(fp,"%d  %d",&x,&y) == 2);
			}
		}
		printf("%d\n",i);
		(*novo)->movPeca = (Movimento*)malloc(sizeof(Movimento)*i);
		if ((*novo)->movPeca  == NULL)
		{
			return PEC_CondRetFaltouMemoria;
		}
		i = 0;
		fclose(fp);
		if ((fp=fopen("PecasNovas.txt","r"))==NULL)
			{
			 printf("Error! opening file");
			exit(1);         
			}
		while(fscanf(fp,"%c %c",&idLido,&corLido) == 2)
		{
			if ((idLido == (*novo)->id) && (corLido == (*novo)->cor))
			{
					while(fscanf(fp,"%d %d",&x,&y) == 2)
					{
					printf("%d %d",x,y);
					printf("\n");
					(*novo)->movPeca[i].x = x;
					(*novo)->movPeca[i].y = y;
					i++;
					}
			}
			else
			{
				while(fscanf(fp,"%d %d",&x,&y) == 2);
			}
		}
		(*novo)->qtdMov = i;
		fclose(fp);
		printf("\n\n\n");
		for(j=0;j<i;j++)
		{
			printf("%d %d",(*novo)->movPeca[j].x,(*novo)->movPeca[j].y);
			printf("\n");
		}
	return PEC_CondRetOK;
}/* Fim função: PEC  &Ensina Movimentos Pecas Desconhecidas */



 /***************************************************************************
*
*  Função: PEC  &Libera Peca
*  ****/
PEC_tpCondRet PEC_LiberaPeca(Peca *peca) {
         free(peca);
		 return PEC_CondRetOK;
   }/* Fim função: PEC  &Libera Peca */


