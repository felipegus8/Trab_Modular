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

typedef struct TAG_tabuleiro {
	Casa tab[8][8];
}Tabuleiro;

//typedef Tabuleiro * ptTabuleiro;
char idListaPecas[5] = "PeLi"; //identificação da lista de peças
LIS_tppLista listaPecas;
LIS_tpCondRet  retLis = LIS_CondRetOK;
LIS_tpCondRet retLis2 = LIS_CondRetOK;
PEC_tpCondRet retPeca = PEC_CondRetOK;

/***** Protótipos das funções encapuladas no módulo *****/
void destruirValor(void *pValor); //função de destruição de valor
TAB_tpCondRet criarListaPecas();
TAB_tpCondRet TAB_VerificaSeCome(ptTabuleiro tabu,int xo,int yo,int xd,int yd,char corRecebida,char idRecebido);
/*****  Código das funções exportadas pelo módulo  *****/  

/***************************************************************************
*
*  Função: TAB  &Criar Tabuleiro
*  ****/
   TAB_tpCondRet TAB_CriaTabuleiro(ptTabuleiro *tabu,int TamLinhas, int TamColunas) {
	int i,j;
    ptTabuleiro novo = (Tabuleiro *) malloc(sizeof(Tabuleiro));
    char a[] = "amd";
    char b[] = "amn";
    char cor,id;
	criarListaPecas();
	
    if(novo == NULL) {
        printf("bayblade\n");
        exit(-1);
    }


    for(i=0;i<8;i++) {
        for(j=0;j<8;j++) {
            PEC_CriaPeca((Peca **)&(novo->tab[i][j].elemento),'V','V');
			LIS_CriarLista((LIS_tppLista *)&(novo->tab[i][j].ameacados),a,destruirValor);
			LIS_CriarLista((LIS_tppLista *)&(novo->tab[i][j].ameacados),a,destruirValor);
			PEC_RetornaCor((Peca *)(novo->tab[i][j].elemento),&cor);
			PEC_RetornaId((Peca *)(novo->tab[i][j].elemento),&id);
			printf("cor: %c e id: %c",cor,id);
        }
    }
    *tabu = novo;
	 return TAB_CondRetOK;
 }



 /***************************************************************************
*
*  Função: TAB  &Inserir Peca
*  ****/
   TAB_tpCondRet TAB_InserirPeca(ptTabuleiro tabuleiro,int x, int yi,char cor,char id) {
        //int yi = (int)(y - 'A');
	    char corObtida,idObtida;
       LIS_InserirNo(listaPecas, (void *)&(tabuleiro->tab[x][yi].elemento));
		printf("Criou a lista\n");
        if(x>7 || x<0 || yi>7 || yi<0) {
            return TAB_CondRetCoordenadaNExiste; 
        }
		
        retPeca = PEC_CriaPeca((Peca **)&(tabuleiro->tab[x][yi].elemento),id,cor);//cria peça novo
		printf("criou peça\n");
        if(retPeca == PEC_CondRetFaltouMemoria) {
            return TAB_CondRetFaltouMemoria;
        }
		printf("%d e %d\n",x,yi);
		//printf("cor obtida: %c e id obtida: %c\n",corObtida,idObtida);
		retLis = LIS_InserirNo(listaPecas,(LIS_tppLista )(tabuleiro->tab[x][yi].elemento)); //insere peça nova na lista
        retPeca = PEC_EnsinaMovimentosPecasConhecidas((Peca **)&(tabuleiro->tab[x][yi].elemento)); //obtem o movimento da peça caso esta for "conhecida"
		printf("Chegou aqui");
        if(retPeca == PEC_CondRetFaltouMemoria) {
            return TAB_CondRetOK;
        }
        if(retPeca == PEC_CondRetNaoAchouPeca) { //caso insere o movimento
             retPeca = PEC_EnsinaMovimentosPecasDesconhecidas((Peca **)&(tabuleiro->tab[x][yi].elemento));
             if(retPeca == PEC_CondRetFaltouMemoria) {
                return TAB_CondRetFaltouMemoria;
             }
        }
        return TAB_CondRetOK;
	
   }/* Fim função: TAB  &Inserir Peca*/
/***************************************************************************
*
*  Função: TAB  &Obter Lista Ameaçantes
*  ****/
   TAB_tpCondRet TAB_ObterListaAmeacantes(Casa *tabuleiro,int x, int yi,LIS_tppLista *listaAmeacantes) {
           
          if(x>7 || x<0 || yi>7 || yi<0) {
             return TAB_CondRetCoordenadaNExiste; 
          }
          *listaAmeacantes = tabuleiro[x * 8 + yi].ameacantes;
          if(listaAmeacantes == NULL) {
              return TAB_CondRetListaAmeacantesNaoExiste;
          }
          
          return TAB_CondRetOK;
   }/* Fim função: TAB  &Obter Lista Ameaçantes */
   /***************************************************************************
*
*  Função: TAB  &Obter Lista Ameaçados
*  ****/
   TAB_tpCondRet TAB_ObterListaAmeacados(Casa *tabuleiro,int x, int yi,LIS_tppLista *listaAmeacados) {
          //int yi = (int)(y - 'A');
           
          if(x>7 || x<0 || yi>7 || yi<0) {
             return TAB_CondRetCoordenadaNExiste; 
          }
          *listaAmeacados = tabuleiro[x * 8 + yi].ameacados;
          if(listaAmeacados == NULL) {
              return TAB_CondRetListaAmeacadosNaoExiste;
          }
          return TAB_CondRetOK;
   }/* Fim função: TAB  &Obter Lista Ameaçados */
/***************************************************************************
*
*  Função: TAB  &Obter Peca
*  ****/
   TAB_tpCondRet TAB_ObterPeca(ptTabuleiro tabu,int x, int y, char *cor, char *id) {
	 char corObtida,idObtido;


      printf("Chegou aqui peca\n");
          if(x>7 || x<0 || y>7 || y < 0) {
			  printf("deu blade aqui\n");
             return TAB_CondRetCoordenadaNExiste; 
          }

	 PEC_RetornaCor((Peca *)(tabu->tab[x][y].elemento),&corObtida);
			PEC_RetornaId((Peca *)(tabu->tab[x][y].elemento),&idObtido);
			printf("linha: %d e coluna: %d\n",x,y);
			printf("cor: %c e id: %c\n",cor,id);

	 *cor = corObtida;
	 *id = idObtido;
   }/* Fim função: TAB  &Obter Peca */
/***************************************************************************
*
*  Função: TAB  &Retirar Peca
*  ****/
   TAB_tpCondRet TAB_RetirarPeca(ptTabuleiro tabu,int x,int y) {
		char corObtida,idObtido;
		
		 if(x>7 || x<0 || y>7 || y<0) {
             return TAB_CondRetCoordenadaNExiste; 
          }


		 PEC_RetornaCor((Peca *)(tabu->tab[x][y].elemento),&corObtida);
		 PEC_RetornaId((Peca *)(tabu->tab[x][y].elemento),&idObtido);
		 
		 if(corObtida== 'V' &&  idObtido== 'V') {
             return TAB_CondRetCasaVazia;
          }
		 PEC_EliminarPeca((Peca *)(tabu->tab[x][y].elemento));
          return TAB_CondRetOK;
}/* Fim função: TAB  &Retirar Peca */
    



/***************************************************************************
    
*
*  Função: TAB  &Mover Peça
*  ****/
   TAB_tpCondRet TAB_MoverPeca(Casa *tabuleiro,int xo,int yi,int xd,int yi2) {
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
          TAB_ObterPeca((Casa *)tabuleiro,xo,yi,&cor,&id);
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
				PEC_RetornaXMovimento(peca,i,&xRet);
				PEC_RetornaYMovimento(peca,i,&yRet);
                if(abs(movX) == xRet && abs(movY) == yRet) {
                        if(movX<0 || movY <0) {
                              if(moveParaTras == 1) {
                                  TAB_VerificaSeCome((Casa*)tabuleiro,xd, yi2,cor);
                                   return TAB_CondRetOK;
                              } else {
                                   TAB_VerificaSeCome((Casa*)tabuleiro,xd, yi2,cor);
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
   TAB_tpCondRet TAB_DestruirTabuleiro(Casa *tabuleiro) {
          int i=0,j=0;
          while(i<8) {
               while(i<8) {
                   if(tabuleiro[i*8 + j].elemento != NULL) {
                     LIS_DestroiLista(tabuleiro[i * 8 + j].ameacados);
                     LIS_DestroiLista(tabuleiro[i * 8 + j].ameacantes);
                     PEC_LiberaPeca((Peca*)tabuleiro[i * 8 + j].elemento);
                   }
               }
          }
        return TAB_CondRetOK;
   }/* Fim função: TAB  &Destruir Tabuleiro*/



/***************************************************************************


/*****  Código das funções encapsuladas no módulo  *****/

TAB_tpCondRet criarListaPecas() {
    retLis = LIS_CriarLista(&listaPecas,idListaPecas,destruirValor);
    if(retLis == LIS_CondRetOK) {
        return TAB_CondRetOK;
    }
    return TAB_CondRetFaltouMemoria;
}
/***************************************************************************
 *
*  Função: TAB  &Verifica Se Come Peca
*  ****/

TAB_tpCondRet TAB_VerificaSeCome(ptTabuleiro tabu,int xo,int yo,int xd,int yd,char corRecebida,char idRecebido) {
	char corObtida,idObtido;
	  
        TAB_ObterPeca(tabu,xd,yd,&corObtida,&idObtido);
	  
	 if(corRecebida != corObtida) {
	      TAB_RetirarPeca(tabu,xd,yd);
	      TAB_RetirarPeca(tabu,xo,yo);
	      TAB_InserirPeca(tabu,xd,yd,corRecebida,idRecebido);
	      return TAB_CondRetComeu;
	 } 
	 if(idObtido == 'V' && corObtida == 'V') {
              TAB_RetirarPeca(tabu,xo,yo);
	      TAB_InserirPeca(tabu,xd,yd,corRecebida,idRecebido);
	      return TAB_CondRetOK;
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
