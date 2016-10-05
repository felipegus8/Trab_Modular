#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include "Tabuleiro.h"
#include "Peca.h"
#include "Casa.h"

//Felipe e Luis, não consegui pensar em nenhuma maneira criativa de representar a movimentação da peça
    
   //Casa tabuleiro[8][8];
   //char idListaPeca[4] = "PeLI";
   //LIS_tppLista listaPecas;


   void destruirValor(void *pValor);

   void criarListaPecas();
   
            
   return TAB_CondRetOK;
   }
   
   criaTabuleiro();
   criaListaPecas();    

   
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



   TAB_tpCondRet inserirPeca(Casa tabuleiro[8][8],int x, char y,char cor,char id) {
        int yi = (int)(y - 'A');
        x--;
        if(x>7 || x<0 || yi>7 || yi<0) {
            return TAB_CondRetCoordenadaNExiste; 
        }
        Peca *novo;
        //strcpy(peca->cor,cor);
        //strcpy(peca->id,id);
        //tabuleiro[x][yi]->elemento = (Peca *) malloc(sizeof(Peca));
        criaPeca((Peca *)tabuleiro[x][yi]->elemento,id,cor);
        return TAB_CondRetOK:
   }

   TAB_tpCondRet ObterListaAmeacantes(int x, char y,LIS_tppLista **listaAmeacantes) {
          int yi = (int)(y - 'A');
           x--;
          if(x>7 || x<0 || yi>7 || yi<0) {
             return TAB_CondRetCoordenadaNExiste; 
          }
          *listaAmeacantes = tabuleiro[x,yi]->ameacantes;
          return TAB_CondRetOK;
   }
   
   TAB_tpCondRet ObterListaAmeacados(int x, char y,LIS_tppLista **listaAmeacados) {
          int yi = (int)(y - 'A');
           x--;
          if(x>7 || x<0 || yi>7 || yi<0) {
             return TAB_CondRetCoordenadaNExiste; 
          }
          *listaAmeacados = tabuleiro[x,yi]->ameacados;
          return TAB_CondRetOK;
   }

   TAB_tpCondRet obterPeca(int x, char y, char *cor, char *id) {
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
          strcpy(cor,peca->cor); 
          strcpy(id,peca->id);
   }

   TAB_tpCondRet RetirarPeca(int x,char y) {
          Peca *peca;
          int y = (int)(y - 'A');
          x--;
          if(x>7 || x<0 || yi>7 || yi<0) {
             return TAB_CondRetCoordenadaNExiste; 
          }
          if(peca == NULL) {
             return TAB_CondRetCasaVazia;
          }
          free(peca->cor);
          free(peca->id);
          peca = NULL;
   }

   TAB_tpCondRet MoverPeca(int xo,char yo,int xd,char yd) {
          char cor;
          char id;
          void *elemento;
          Peca *peca;
          LIS_tpCondRet ret;
          obterpeca(x0,y0,&cor,&id);
          obterno(lista,elemento);
          peca = (Peca *)elemento;
          while(strcmp(peca->id,id) != 0) {
                if(obterno(lista,peca) == LIS_CondRetFimLista) {
                     return TAB_CondRetNaoAchouPeca;
                }
                
              irProx(listaPecas);
          }
          
   }
  

   TAB_tpCondRet DestruirTabuleiro() {
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

   TAB_tpCondRet criaTabuleiro() {
   
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
              LIS_CriarLista(idListaAmeacados,DestruirValor,tabuleiro[i][j]->ameacados);
              LIS_CriarLista(idListaAmeacantes,DestruirValor,tabuleiro[i][j]->ameacantes);
              //criaPeca(tabuleiro[i][j]->peca);
              idListaAmeacadosY++;
              idListaAmeacantesY++;
              j++;
         }
         idListaAmeacadosX++;
         idListaAmeacantesX++;
         i++;
    }
       
   
   /*
   TAB_tpCondRet criaPeca (char *id,int movimentoX,int movimentoY) {
       void *elemento;
       inserirNo(listaPecas,elemento);
       elemento = (Peca *) malloc(sizeof(Peca));
       if(elemento == NULL) {
             return TAB_CondRetFaltouMemoria;
       }
       elemento->id = (char *) malloc(sizeof(char));
       strcpy(elemento->id,id);
       elemento->x = movimentoX;
       elemento->y = movimentoY;
   }
   */
   void criaListaPecas() {
            LIS_CriarLista(idListaPeca,DestruirValor,listaPecas);
   }

 
   void destruirValor(void *pValor) {
        free(pValor);
   }


  TAB_tpCondRet verificaMovimentoValido(Casa tabuleiro[8][8],Peca *movida,Movimento *movPeca)
  {

  }
