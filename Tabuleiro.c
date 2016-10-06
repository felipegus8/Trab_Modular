#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include "Tabuleiro.h"
#include "Peca.h"
#include "Casa.h"


    
typedef struct casa {
         LIS_tppLista *ameacados;
         /* ponteiro para a cabeça da lista que contém as peças ameaçadas pela peça da casa */
         LIS_tppLista *amecantes;
         /* ponteiro para a cabeça da lista que contém as peças que ameaçam a peça da casa */
         void *elemento;
         /*ponteiro para o elemento contido na casa */
   } Casa;
char idListaPecas = "PeLi"; //identificação da lista de peças
LIS_tpCondRet = retLis;
PEC_tpCondRet = retPeca;
void destruirValor(void *pValor); //função de destruição de valor

LIS_CriarLista(&listaPecas,idListaPecas,destruirValor); //criação da lista de peças

   void destruirValor(void *pValor);

   LIS_tpp listaPecas;
   //void criarListaPecas();
   
            
   return TAB_CondRetOK;
   }
   
   criaTabuleiro();
   criaListaPecas();    

   /*
   GER_tpCondRet criaTabuleiro(Casa tabuleiro[8][8]) {
              int i = 0;
              int y = 0;
              tabuleiro = (Casa **) malloc(sizeof(Casa) * 64);
              while(i<8) {
                  while(j<8) {
                        //tabuleiro[i][j] = 
                  }
              }
   }
   */

   TAB_tpCondRet criaTabuleiro(Casa *tabuleiro[8][8]) {
   
    int i = 0,j=0;
    char a = 'A';
    char b = 'B';    
    char idListaAmeacadosX = '1';//linha da casa onde reside a lista ameacados
    char idListaAmeacadosY; //coluna da casa onde reside a lista ameacados
    char idListaAmeacantesX = '1';//linha da casa onde reside a lista ameacantes
    char idListaAmeacadosY;//coluna da casa onde reside a lista ameacantes
    char idListaAmeacantes[4];
    char idListaAmecantes[4];
    if(tabuleiro == NULL) {
         return TAB_CondRetFaltouMemoria;
    }        
    
    while(i<8) {
             idListaAmeacadosY = 'A';
             idListaAmeacantesY = 'A';
         while(j<8) {
              strcpy(idListaAmeacados,&idListaAmeacadosX);
              strcat(idLIstaAmeacados,&idListaAmeacadosY);
              strcat(idListaAmeacados,&a);
              //as 3 linhas acima fazem com que a string identificadora da lista fique da forma "linhaColunaA"
              strcpy(idListaAmeacantes,&idListaAmeacantesX);
              strcat(idLIstaAmeacantes,&idListaAmeacantesY);
              strcat(idListaAmeacantes,&b);
              //as 3 linhas acima fazem com que a string identificadora da lista fique da forma "linhaColunaB"    
              LIS_CriarLista(idListaAmeacados,DestruirValor,&tabuleiro[i][j]->ameacados);
              LIS_CriarLista(idListaAmeacantes,DestruirValor,&tabuleiro[i][j]->ameacantes);
              criaPeca((Peca **)&tabuleiro[i][j]->elem,'V','V');
              idListaAmeacadosY++;
              idListaAmeacantesY++;
              j++;
         }
         idListaAmeacadosX++;
         idListaAmeacantesX++;
         i++;
    }



   TAB_tpCondRet inserirPeca(Casa tabuleiro[8][8],int x, char y,char cor,char id) {
        int yi = (int)(y - 'A');
        x--;
        if(x>7 || x<0 || yi>7 || yi<0) {
            return TAB_CondRetCoordenadaNExiste; 
        }
        retPeca = criaPeca((Peca *)&tabuleiro[x][yi]->elemento,id,cor);//cria peça novo
        if(retPeca == LIS_tpCondRetFaltouMemoria) {
            return TAB_tpCondRetFaltouMemoria;
        }
        retLis = LIS_tpCondRet inserirNo(listaPecas,tabuleiro[x][yi]->elemento); //insere peça nova na lista
        
        return TAB_CondRetOK:
   }

   TAB_tpCondRet ObterListaAmeacantes(Casa tabuleiro[8][8],int x, char y,LIS_tppLista **listaAmeacantes) {
          int yi = (int)(y - 'A');
           x--;
          if(x>7 || x<0 || yi>7 || yi<0) {
             return TAB_CondRetCoordenadaNExiste; 
          }
          *listaAmeacantes = tabuleiro[x,yi]->ameacantes;
          return TAB_CondRetOK;
   }
   
   TAB_tpCondRet ObterListaAmeacados(Casa tabuleiro[8][8],int x, char y,LIS_tppLista **listaAmeacados) {
          int yi = (int)(y - 'A');
           x--;
          if(x>7 || x<0 || yi>7 || yi<0) {
             return TAB_CondRetCoordenadaNExiste; 
          }
          *listaAmeacados = tabuleiro[x,yi]->ameacados;
          return TAB_CondRetOK;
   }

   TAB_tpCondRet obterPeca(Casa tabuleiro[8][8],int x, char y, char cor, char id) {
          Peca *peca;
          int yi = (int)(y - 'A');
          x--;
          if(x>7 || x<0 || yi>7 || yi < 0) {
             return TAB_CondRetCoordenadaNExiste; 
          }
          peca = (Peca *)tabuleiro[x][yi]->elemento;
          if(peca == NULL) {
             return TAB_CondRetCasaVazia;
          }
          //strcpy(cor,peca->cor); 
          cor = peca->cor;
          id = peca->id;
   }

   TAB_tpCondRet RetirarPeca(Casa tabuleiro[8][8],int x,char y) {
          Peca *peca;
          int yi = (int)(y - 'A');
          x--;
          if(x>7 || x<0 || yi>7 || yi<0) {
             return TAB_CondRetCoordenadaNExiste; 
          }
          if(peca == NULL) {
             return TAB_CondRetCasaVazia;
          }
          peca = (Peca *)tabuleiro[x][yi]->elem;
          peca->id = 'V';
          peca->cor = 'V';
   }

   TAB_tpCondRet MoverPeca(Casa tabuleiro[8][8],int xo,char yo,int xd,char yd) {
          char cor;
          int i;
          char id;
          void *elemento;
          int movX,movY;
          Peca *peca;
          LIS_tpCondRet ret;
          obterpeca(xo,yo,&cor,&id);
          obterno(lista,elemento);
          peca = (Peca *)elemento;
          int yi = (int)(yo - 'A');
           xo--;
           if(xo>7 || xo<0 || yi>7 || yi<0) {
              return TAB_CondRetCoordenadaNExiste; 
           }
           int yi2 = (int)(yd - 'A');
           xd--;
           if(xd>7 || xd<0 || yi2>7 || yi2<0) {
              return TAB_CondRetCoordenadaNExiste; 
           }
          //procura na lista pelo id da peça e checa se o movimento está ok
          while(strcmp(peca->id,id) != 0) {
                if(obterno(lista,peca) == LIS_CondRetFimLista) {
                     return TAB_CondRetNaoAchouPeca;
                }
                
              irProx(listaPecas);
          }
          for(i=0;i<peca->qtdMov;i++) {
                movX = xd - xo;
                movY = yd - yo;
                if(abs(movX) == movPeca[i].x && abs(movY) == movPeca[i].y) {
                        if(movX<0 || movY <0) {
                              if(peca->movParaTras == 1) {
                                   //return movOK;
                              } else {
                                  //return movIrregular
                              }
                        }
                }
          }
          //return movIrregular
   }
  

   TAB_tpCondRet DestruirTabuleiro(Casa tabuleiro[8][8]) {
          int i=0,j=0;
          while(i<8) {
               while(i<8) {
                   if(tabuleiro[i][j] != NULL) {
                     destroiLista(tabuleiro[i][j]->ameacados);
                     destroiLista(tabuleiro[i][j]->ameacados);
                     liberarPeca(tabuleiro[i][j]->peca);
                   }
               }
          }
   
   }

   
    
   
   void criaListaPecas() {
            LIS_CriarLista(idListaPeca,DestruirValor,listaPecas);
   }

 
   void destruirValor(void *pValor) {
        free(pValor);
   }


  TAB_tpCondRet verificaMovimentoValido(Casa tabuleiro[8][8],Peca *movida,Movimento *movPeca)
  {

  }

