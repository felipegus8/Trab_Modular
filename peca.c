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
	    int movParaTras; // Bool para ver se a peça move para trás ou não(0 ou 1).
        Movimento *movPeca; //Vetor da struct movimento contendo todos os movimentos que a peça pode fazer
 }Peca;


 /*****  Código das funções exportadas pelo módulo  *****/

 /***************************************************************************
*
*  Função: PEC  &Criar peca
*  ****/
//AE: Recebe um ponteiro de ponteiro da struct peca, uma identificação e uma cor
PEC_tpCondRet PEC_CriaPeca(Peca **novo,char id,char cor) {
	  Peca *novoCopia = NULL;
	
          *novoCopia = (Peca *) malloc(sizeof(Peca));
          if(*novoCopia == NULL) {
            return PEC_CondRetFaltouMemoria;
          }
		  *novoCopia->id = id;
    
		  *novoCopia->cor = cor;
	*novo = novoCopia;
          return PEC_CondRetOK; 
   }/* Fim função: PEC  &Criar peca */
//AS: Uma peça foi criada e iniciada com a identidade e cor recebida
 /***************************************************************************
*
*  Função: PEC  &Ensina Movimentos Pecas Conhecidas
*  ****/
//AE: Recebe uma peça já criada
PEC_tpCondRet PEC_EnsinaMovimentosPecasConhecidas(Peca **novo)
{
	int i = 0,j = 0,k = 0 ;
	//Em todos os casos do switch a variável moveParaTras será preenchida como 1(Verdadeiro) exceto no peão,que será 0.
	switch((*novo)->id)
	{
	case 'T':
		printf("\nEntrou na torre\n");
		(*novo)->movPeca = (Movimento*)malloc(sizeof(Movimento)*14);
		if((*novo)->movPeca == NULL)
		{
			return PEC_CondRetFaltouMemoria;
		}
		printf("Passou daqui");
		(*novo)->qtdMov = 14;
		(*novo)->movParaTras = 1;
		if((*novo)->movPeca == NULL)
		{
			return PEC_CondRetFaltouMemoria;
		}
		//Movimento na vertical da torre
		(*novo)->movPeca[i].x = 1;
		(*novo)->movPeca[i].y = 0;
		for(i=1;i<7;i++)
		{
			(*novo)->movPeca[i].x = i+1;
			(*novo)->movPeca[i].y = 0;
		}
		//Movimento na horizontal da torre
		for(j=1;j<8;j++)
		{
			(*novo)->movPeca[i].x = 0;
			(*novo)->movPeca[i].y = j;
			i++;
		}
	break;
	case 'C':
		printf("\nEntrou no cavalo\n");
		(*novo)->movPeca = (Movimento*)malloc(sizeof(Movimento)*2);
		(*novo)->qtdMov = 2;
		(*novo)->movParaTras = 1;
		if((*novo)->movPeca == NULL)
		{
		return PEC_CondRetFaltouMemoria;
		}
		//Movimento do cavalo
		(*novo)->movPeca[0].x = 2;
		(*novo)->movPeca[0].y = 1;
		(*novo)->movPeca[1].x = 1;
		(*novo)->movPeca[1].y = 2;
		break;
	case 'B':
		printf("\nEntrou no bispo\n");
		(*novo)->movPeca = (Movimento*)malloc(sizeof(Movimento)*7);
		printf("Passou");
		(*novo)->qtdMov = 7;
		(*novo)->movParaTras = 1;
		if((*novo)->movPeca == NULL)
		{
		return PEC_CondRetFaltouMemoria;
		}
		i = 2;
		printf("Chegou aqui");
		//Movimento do bispo(diagonais)
		(*novo)->movPeca[0].x = 1;
		(*novo)->movPeca[0].y = 1;
		for(k=1;k<7;k++)
		{
			(*novo)->movPeca[k].x = i;
			(*novo)->movPeca[k].y = i;
			i++;
		}
		break;
	case 'P':
		printf("\nEntrou no peao\n");
		(*novo)->movPeca = (Movimento*)malloc(sizeof(Movimento)*2);
		(*novo)->qtdMov = 2;
		(*novo)->movParaTras = 0;
		if((*novo)->movPeca == NULL)
		{
		return PEC_CondRetFaltouMemoria;
		}
		//Movimento do peão.Aqui não se considera o fato dele poder se mover duas casas para frente na primeira jogada.
		(*novo)->movPeca[0].x = 1;
		(*novo)->movPeca[0].y = 0;
		(*novo)->movPeca[1].x = 1;
		(*novo)->movPeca[1].y = 1;
		break;
	case 'D':
		printf("\nEntrou na rainha\n");
		(*novo)->movPeca = (Movimento*)malloc(sizeof(Movimento)*21);
		(*novo)->qtdMov = 21;
		(*novo)->movParaTras = 1;
		if((*novo)->movPeca == NULL)
		{
		return PEC_CondRetFaltouMemoria;
		}
		//Movimento na vertical da rainha
		(*novo)->movPeca[i].x = 1;
		(*novo)->movPeca[i].y = 0;
		for(i=1;i<7;i++)
		{
			(*novo)->movPeca[i].x = i + 1;
			(*novo)->movPeca[i].y = 0;
		}
		//Movimento na horizontal da rainha
		for(j=1;j<8;j++)
		{
			(*novo)->movPeca[i].x = 0;
			(*novo)->movPeca[i].y = j;
			i++;
		}
		j=1;
		//Movimento na diagonal da rainha
		for(k=1;k<8;k++)
		{
			(*novo)->movPeca[i].x = j;
			(*novo)->movPeca[i].y = j;
		}
		break;
	case 'R':
		printf("\nEntrou no rei\n");
		(*novo)->movPeca = (Movimento*)malloc(sizeof(Movimento)*3);
		(*novo)->qtdMov = 3;
		(*novo)->movParaTras = 1;	
		if((*novo)->movPeca == NULL)
		{
		return PEC_CondRetFaltouMemoria;
		}
		//Movimento do rei
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
//AS: A peça recebida aprende o movimento respectivo a sua identidade
*  Função: PEC  &Ensina Movimentos Pecas Desconhecidas
*  ****/
//AE: Recebe uma peça já criada
PEC_tpCondRet PEC_EnsinaMovimentosPecasDesconhecidas(Peca **novo)
{
	char idLido,corLido;
	int x,y,i,j;
	FILE *fp;
	//O arquivo PecasNovas.txt contem todas as peças novas que podem ser usadas no jogo.Para criar uma nova peça,o usuário deve escrever nesse arquivo,seguindo o formato lá apresentado.
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
//AS: A peca aprendeu o movimeno de acordo com suas especificações no documento txt


 /***************************************************************************
*
*  Função: PEC  &Libera Peca
*  ****/
//AE: Recebe uma peça já criada
PEC_tpCondRet PEC_LiberaPeca(Peca *peca) {
         free(peca);
		 return PEC_CondRetOK;
   }/* Fim função: PEC  &Libera Peca */
//AS: A peca recebida foi liberada
/***************************************************************************
*
*  Função: PEC  &Retorna Id
*  ****/
//AE: Recebe uma peça já criada e um ponteiro para a identificação requisitada
PEC_tpCondRet PEC_RetornaId(Peca *peca,char *id)
{
	*id = peca->id;
	return PEC_CondRetOK;
}/* Fim função: PEC  &Retorna Id */
//AS: O ponterio recebido foi apontado para identificação da peça
/***************************************************************************
*
*  Função: PEC  &Retorna Cor
*  ****/
//AE: Recebe uma peça já criada e um ponteiro para a cor da peca
PEC_tpCondRet PEC_RetornaCor(Peca *peca,char *cor)
{
	*cor = peca->cor;
	return PEC_CondRetOK;
}/* Fim função: PEC  &Retorna Cor */
//AS: O ponterio recebido foi apontado para a cor da peça
/***************************************************************************
*
*  Função: PEC  &Retorna Qtd_Mov
*  ****/
//AE: Recebe uma peça já criada e um ponteiro para a quantidade de movimentos da peca
PEC_tpCondRet PEC_RetornaQtd_Mov(Peca *peca,int *qtdMov)
{
	*qtdMov = peca->qtdMov;
	return PEC_CondRetOK;
}/* Fim função: PEC  &Retorna Qtd_Mov */
//AS: O ponterio recebido foi apontado para a quantidade de movimento da peça
/***************************************************************************
*
*  Função: PEC  &Retorna Move Para Tras
*  ****/
//AE: Recebe uma peça já criada e um ponteiro para os de movimentos para tras da peca
PEC_tpCondRet PEC_RetornaMoveParaTras(Peca *peca,int *moveParaTras)
{
	*moveParaTras = peca->movParaTras;
	//Move Para Tras sempre será 0 ou 1.
	return PEC_CondRetOK;
}/* Fim função: PEC  &Retorna Move Para Tras */
//AS: O ponterio recebido foi apontado para os de movimentos para tras da peça

/***************************************************************************
*
*  Função: PEC  &Retorna X Movimento
*  ****/
//AE: Recebe uma peça já criada, a posição do vetor movPeca e ponteiro que pegará o contudo da posição do vetor movPeca
PEC_tpCondRet PEC_RetornaXMovimento(Peca *peca,int i,int *x)
{
	*x = peca->movPeca[i].x;
	return PEC_CondRetOK;
}/* Fim função: PEC  &Retorna X Movimento */
//AS: O ponteiro aponta agora para a posicão desejado do vetor movPeça
/***************************************************************************
*
*  Função: PEC  &Retorna Y Movimento
*  ****/
//AE: Recebe uma peça já criada, a posição do vetor movPeca e ponteiro que pegará o contudo da posição do vetor movPeca
PEC_tpCondRet PEC_RetornaYMovimento(Peca *peca,int i,int *y)
{
	*y = peca->movPeca[i].y;
	return PEC_CondRetOK;
}/* Fim função: PEC  &Retorna Y Movimento */
//AS: O ponteiro aponta agora para a posicão desejado do vetor movPeça

/***************************************************************************
*
*  Função: PEC  &Eliminar Peca
*  ****/
//AE: Recebe uma peça já criada
PEC_tpCondRet PEC_EliminarPeca(Peca *peca)
{
	peca->id = 'V';
	peca->cor = 'V';
	return PEC_CondRetOK;
}/* Fim função: PEC  &Eliminar Peca */
//AS: A peça recebida foi eliminada do programa

 /********** Fim do módulo de implementação: PEC  Peca **********/
