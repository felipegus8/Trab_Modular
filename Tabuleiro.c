/***************************************************************************
*  $MCI Módulo de implementação: TAB  Tabuleiro
*  Arquivo gerado:              Tabuleiro.c
*  Letras identificadoras:      TAB
*
*  Autores: Felipe Viberti,Luis Claudio e Victor Nogueira
*
*  $HA Histórico de evolução:
*     Versão  Autores                                           Data          Observações
*     1       Felipe Viberti,Luis Claudio e Victor Nogueira   27/set/2016  início desenvolvimento
*
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include "Tabuleiro.h"
/***********************************************************************
*
*  $TC Tipo de dados: TAB Casa do Tabuleiro
*
*
***********************************************************************/
typedef struct casa {
         LIS_tppLista ameacados;
         /* ponteiro para a cabeça da lista que contém as peças ameaçadas pela peça da casa */
         LIS_tppLista ameacantes;
         /* ponteiro para a cabeça da lista que contém as peças que ameaçam a peça da casa */
         void *elemento;
         /*ponteiro para o elemento contido na casa */
   } Casa;

typedef struct tabuleiro {
   Casa *tabuleiro[8][8];
   
}Tabuleiro;

//LUIS É VIADO!!!


char idListaPecas[5] = "PeLi"; //identificação da lista de peças
LIS_tppLista listaPecas;
LIS_tpCondRet  retLis = LIS_CondRetOK;
LIS_tpCondRet retLis2 = LIS_CondRetOK;
PEC_tpCondRet retPeca = PEC_CondRetOK;

/***** Protótipos das funções encapuladas no módulo *****/
void destruirValor(void *pValor); //função de destruição de valor
TAB_tpCondRet criarListaPecas();
TAB_tpCondRet TAB_VerificaSeCome(Casa *tabuleiro,int posicaoX, int posicaoY, char corRecebida);
/*****  Código das funções exportadas pelo módulo  *****/  

/***************************************************************************
*
*  Função: TAB  &Criar Tabuleiro
*  ****/
   TAB_tpCondRet TAB_CriaTabuleiro(ptTabuleiro tabuleiro) {
	   int i=0,j=0;
	   LIS_tppLista listaAmeacados;
	   LIS_tppLista listaAmeacantes; 
       
	  tabuleiro = NULL;
	  tabuleiro = (Tabuleiro *) malloc(sizeof(Tabuleiro));

	if(tabuleiro == NULL) {
	     return TAB_CondRetFaltouMemoria;
	} /*if */
	criarListaPecas();
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			PEC_CriaPeca((Peca**)(tabuleiro->*tabuleiro[i][j].elemento),'V','V');
			  listaAmeacados = tabuleiro->*tabuleiro[i][j].ameacados;
	          listaAmeacantes = tabuleiro->*tabuleiro[i][j].ameacantes;
	          retLis = LIS_CriarLista(&listaAmeacados,"Amd",destruirValor);
	          if(retLis == LIS_CondRetFaltouMemoria) {
                    return TAB_CondRetFaltouMemoria;
         }
              retLis2 = LIS_CriarLista(&listaAmeacantes,"Amn",destruirValor);
              if(retLis2 == LIS_CondRetFaltouMemoria) {
                    return TAB_CondRetFaltouMemoria;
            }
		}
	}
    /*
    int i = 0,j=0;
	LIS_tppLista listaAmeacados;
	LIS_tppLista listaAmeacantes;   
    char idListaAmeacadosX = '1';//linha da casa onde reside a lista ameacados
    char idListaAmeacadosY; //coluna da casa onde reside a lista ameacados
    char idListaAmeacantesX = '1';//linha da casa onde reside a lista ameacantes
    char idListaAmeacantesY;//coluna da casa onde reside a lista ameacantes
    char *idListaAmeacados = "Amd";
    char *idListaAmeacantes = "Amn";

    criarListaPecas();

    while(i<TamLinhas) {
             idListaAmeacadosY = 'A';
             idListaAmeacantesY = 'A';
         while(j<TamColunas) {
              //as 3 linhas acima fazem com que a string identificadora da lista ameacantes fique da forma "linhaColunaB
			  printf("declarei aqui a casa\n");
			  listaAmeacados = tabuleiro[i * TamLinhas + j].ameacados;
			  listaAmeacantes = tabuleiro[i * TamLinhas + j].ameacantes;
              retLis = LIS_CriarLista(&listaAmeacados,idListaAmeacados,destruirValor);
              if(retLis == LIS_CondRetFaltouMemoria) {
                    return TAB_CondRetFaltouMemoria;
              }
              retLis2 = LIS_CriarLista(&listaAmeacantes,idListaAmeacantes,destruirValor);
              if(retLis2 == LIS_CondRetFaltouMemoria) {
                    return TAB_CondRetFaltouMemoria;
              }
              PEC_CriaPeca((Peca **)&(tabuleiro[i * TamLinhas + j].elemento),'V','V');
              idListaAmeacadosY++;
              idListaAmeacantesY++;
              j++;
         }
         idListaAmeacadosX++;
         idListaAmeacantesX++;
         i++;
    }
    */
       return TAB_CondRetOK;
   }




 /***************************************************************************
*
*  Função: TAB  &Inserir Peca
*  ****/
   TAB_tpCondRet TAB_InserirPeca(ptTabuleiro pTabuleiro,int x, int y,char cor,char id) {
    x--;
    if(x>7 || x<0 || y>7 || y<0) {
        return TAB_CondRetCoordenadaNExiste;
    }
    retPeca = PEC_CriarPeca((Peca **)&(pTabuleiro->*tabuleiro[x][y]).elemento),id,cor);
    if(retPeca = PEC_CondRetFaltouMemoria) {
        return TAB_CondRetFaltouMemoria;
    }
    retLis = LIS_InserirNo(listaPecas,(Peca **)pTabuleiro->*tabuleiro.elemento);
    retPeca = PEC_EnsinaMovimentosPecasConhecidas((Peca **)pTabuleiro->*tabuleiro.elemento); //obtem o movimento da peça caso esta for "conhecida"
    printf("Chegou aqui");
    if(retPeca == PEC_CondRetFaltouMemoria) {
        return TAB_CondRetOK;
    }
    if(retPeca == PEC_CondRetNaoAchouPeca) { //caso insere o movimento
        retPeca = PEC_EnsinaMovimentosPecasDesconhecidas((Peca **)pTabuleiro->*tabuleiro[x][y].elemento);
        if(retPeca == PEC_CondRetFaltouMemoria) {
            return TAB_CondRetFaltouMemoria;
        }
    }
    return TAB_CondRetOK;

}

	   
	/*
		printf("Criou a lista\n");
        if(x>7 || x<0 || yi>7 || yi<0) {
            return TAB_CondRetCoordenadaNExiste; 
        }
		
        retPeca = PEC_CriaPeca((Peca **)&(tabuleiro[x * 8 + yi].elemento),id,cor);//cria peça novo
		printf("criou peça\n");
        if(retPeca == PEC_CondRetFaltouMemoria) {
            return TAB_CondRetFaltouMemoria;
        }
        retLis = LIS_InserirNo(listaPecas,tabuleiro[x * 8 + yi].elemento); //insere peça nova na lista
        retPeca = PEC_EnsinaMovimentosPecasConhecidas((Peca **)&tabuleiro[x * 8 + yi].elemento); //obtem o movimento da peça caso esta for "conhecida"
		printf("Chegou aqui");
        if(retPeca == PEC_CondRetFaltouMemoria) {
            return TAB_CondRetFaltouMemoria;
        }
        if(retPeca == PEC_CondRetNaoAchouPeca) { //caso insere o movimento
             retPeca = PEC_EnsinaMovimentosPecasDesconhecidas((Peca **)&tabuleiro[x * 8 + yi].elemento);
             if(retPeca == PEC_CondRetFaltouMemoria) {
                return TAB_CondRetFaltouMemoria;
             }
        }
        return TAB_CondRetOK;
	*/
   }/* Fim função: TAB  &Inserir Peca*/
/***************************************************************************
*
*  Função: TAB  &Obter Lista Ameaçantes
*  ****/
   TAB_tpCondRet TAB_ObterListaAmeacantes(ptTabuleiro tabuleiro,int x, int yi,LIS_tppLista *listaAmeacantes) {
           x--;
          if(x>7 || x<0 || yi>7 || yi<0) {
             return TAB_CondRetCoordenadaNExiste; 
          }
          *listaAmeacantes = tabuleiro->tabuleiro[x][yi].ameacantes;
          if(listaAmeacantes == NULL) {
              return TAB_CondRetListaAmeacantesNaoExiste;
          }
          
          return TAB_CondRetOK;
   }/* Fim função: TAB  &Obter Lista Ameaçantes */
   /***************************************************************************
*
*  Função: TAB  &Obter Lista Ameaçados
*  ****/
   TAB_tpCondRet TAB_ObterListaAmeacados(ptTabuleiro tabuleiro,int x, int yi,LIS_tppLista *listaAmeacados) {
          //int yi = (int)(y - 'A');
           x--;
          if(x>7 || x<0 || yi>7 || yi<0) {
             return TAB_CondRetCoordenadaNExiste; 
          }
          *listaAmeacados = tabuleiro->tabuleiro[x][yi].ameacados;
          if(listaAmeacados == NULL) {
              return TAB_CondRetListaAmeacadosNaoExiste;
          }
          return TAB_CondRetOK;
   }/* Fim função: TAB  &Obter Lista Ameaçados */
/***************************************************************************
*
*  Função: TAB  &Obter Peca
*  ****/
   TAB_tpCondRet TAB_ObterPeca(ptTabuleiro tabuleiro,int x, int y, char *cor, char *id) {
          Peca *peca;
		  char corPec,idPec;
		  printf("Chegou aqui");
          x--;
          if(x>7 || x<0 || y>7 || y < 0) {
             return TAB_CondRetCoordenadaNExiste; 
          }
          peca = (Peca *)(tabuleiro->tabuleiro[x][y].elemento);
		  PEC_RetornaCor(peca,&corPec);
		  PEC_RetornaId(peca,&idPec);
          if(corPec== 'V' &&  idPec== 'V') {
             return TAB_CondRetCasaVazia;
          }
       
          *cor = corPec;
          *id = idPec;
          return TAB_CondRetOK;
   }/* Fim função: TAB  &Obter Peca */
/***************************************************************************
*
*  Função: TAB  &Retirar Peca
*  ****/
   TAB_tpCondRet TAB_RetirarPeca(ptTabuleiro tabuleiro,int x,int y) {
          Peca *peca;
		  char corPec,idPec;
		  printf("\nRetirar");
          x--;
          if(x>7 || x<0 || y>7 || y<0) {
             return TAB_CondRetCoordenadaNExiste; 
          }
		  peca = (Peca *)(tabuleiro->*tabuleiro[x][yi].elemento);
          PEC_RetornaCor(peca,&corPec);
		  PEC_RetornaId(peca,&idPec);
          if(corPec== 'V' &&  idPec== 'V') {
             return TAB_CondRetCasaVazia;
          }
		 PEC_EliminarPeca(peca);
          return TAB_CondRetOK;
   }/* Fim função: TAB  &Retirar Peca */
    



/***************************************************************************
    
*
*  Função: TAB  &Mover Peça
*  ****/
   TAB_tpCondRet TAB_MoverPeca(ptTabuleiro tabuleiro,int xo,int yi,int xd,int yi2) {
          char cor;
          int i;
          char id;
		  char idPec;
          Peca *elemento;
          int movX,movY,xRet,yRet,moveParaTras;
          Peca *peca;
	      Peca *naLista;
		  int qtdMov;
		  //int yi = (int)(yo - 'A');
          //int yi2 = (int)(yd - 'A');
	  printf("Entrei no movimento\n");
          TAB_ObterPeca((Casa *)tabuleiro->*tabuleiro[xo][yi],xo,yi,&cor,&id);
	  printf("Passei da obter\n");
          LIS_ObterNo(listaPecas,(void **)&elemento);
	  printf("Obteve o nó\n");
          peca = (Peca *)elemento;
           xo--;
           if(xo>7 || xo<0 || yi>7 || yi<0) {
              return TAB_CondRetCoordenadaNExiste; 
           }
         
           xd--;
           if(xd>7 || xd<0 || yi2>7 || yi2<0) {
              return TAB_CondRetCoordenadaNExiste; 
           }
		    PEC_RetornaId(peca,&idPec);

          //procura na lista pelo id da peça e checa se o movimento está ok
          while(1) {
                if(LIS_ObterNo(listaPecas,(void **)&elemento) == LIS_CondRetFimLista) {
                     return TAB_CondRetNaoAchouPeca;
                }
                naLista = (Peca *) elemento;
		PEC_RetornaId(naLista, &id);
		if(idPec == id) {
		      break;
		}
              LIS_IrProx(listaPecas);
          }
		  PEC_RetornaQtd_Mov(peca,&qtdMov);
		  PEC_RetornaMoveParaTras(peca,&moveParaTras);
          for(i=0;i<qtdMov;i++) {
                movX = xd - xo;
                movY = yi2 - yi;
				printf("antes do to aqui\n");
				PEC_RetornaXMovimento(peca,i,&xRet);
				PEC_RetornaYMovimento(peca,i,&yRet);
				printf("ta aqui porra\n");
				printf("x: %d e y: %d\n",xRet,yRet);
                if(abs(movX) == xRet && abs(movY) == yRet) {
					printf("passei do abs\n");
                        if(movX<0 || movY <0) {
                              if(moveParaTras == 1) {
								  printf(" chegou movPraTras\n");
                                  TAB_VerificaSeCome((Casa*)tabuleiro->*tabuleiro[xd][yi2],xd, yi2,cor);
                                   return TAB_CondRetOK;
                              } else {
								  printf("else do chegou mov\n");
                                   TAB_VerificaSeCome((Casa*)tabuleiro->*tabuleiro[xd][yi2],xd, yi2,cor);
                                   return TAB_CondRetMovimentoIrregular;
                              }
                        }
                       return TAB_CondRetOK;
              }
          }
          return TAB_CondRetMovimentoIrregular;
   }/* Fim função: TAB  &Mover Peca*/
  
   /***************************************************************************
*
*  Função: TAB  &Destruir Tabuleiro
*  ****/
   TAB_tpCondRet TAB_DestruirTabuleiro(ptTabuleiro tabuleiro) {
          int i=0,j=0;
          while(i<8) {
               while(j<8) {
                   if(tabuleiro[i][j].elemento != NULL) {
                     LIS_DestroiLista(tabuleiro->tabuleiro[i][j].ameacados);
					 printf("Cheguei aqui\n");
                     LIS_DestroiLista(tabuleiro->tabuleiro[i][j].ameacantes);
                     PEC_LiberaPeca((Peca*)(tabuleiro->tabuleiro[i][j].elemento));
					 j++;
                   }
				   i++;
               }
          }
		  free(tabuleiro);
        return TAB_CondRetOK;
   }/* Fim função: TAB  &Destruir Tabuleiro*/



/***************************************************************************


/*****  Código das funções encapsuladas no módulo  *****/

TAB_tpCondRet criarListaPecas() {
    retLis = LIS_CriarLista(&listaPecas,idListaPecas,destruirValor);
    if(retLis = LIS_CondRetOK) {
        return TAB_CondRetOK;
    }
    return TAB_CondRetFaltouMemoria;
}

/***************************************************************************
 *
*  Função: TAB  &Verifica Se Come Peca
*  ****/

TAB_tpCondRet TAB_VerificaSeCome(Casa *tabuleiro,int posicaoX, int posicaoY, char corRecebida) {
    char cor,id;
	posicaoX++;
    TAB_ObterPeca(tabuleiro,posicaoX,posicaoY,&cor,&id);
	printf("passei pelo obter");
    if(cor != corRecebida) {
	TAB_RetirarPeca(tabuleiro,posicaoX,posicaoY);
        return TAB_CondRetComeu;
    }
    return TAB_CondRetCasaTemDono;
}

/***************************************************************************
*
*  Função: TAB  -Destruir Valor
*  ****/
   void destruirValor(void *pValor) {
        free(pValor);
   }/* Fim função: TAB  -Destruir Valor*/

 /********** Fim do módulo de implementação: TAB  Tabuleiro **********/
