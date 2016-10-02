#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include "Tabuleiro.h"
    
   typedef struct peca {
        char *id;  // string identificadora da peça
        char *cor; //cor da peça
        int x; //quantidade de movimentos no eixo vertical
        int y; // quantidade de movimentos no eixo horizontal
   }Peca;   

   typedef struct casa {
         LIS_tppLista *ameacados;
         /* ponteiro para a cabeça da lista que contém as peças ameaçadas pela peça da casa */
         LIS_tppLista *amecantes;
         /* ponteiro para a cabeça da lista que contém as peças que ameaçam a peça da casa */
         Peca *peca;
         /*ponteiro para a estrutura da peça contida na casa */
   } Casa;
    
   Casa tabuleiro[8][8];
   char idListaPeca[4] = "PeLI";
   LIS_tppLista listaPecas;


   void destruirValor(void *pValor);

   TAB_tpCondRet obterValorPeca(char *id,int movimentoX, int movimentoY) {
            
   
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
              tabuleiro[i][j]->peca = NULL;
              idListaAmeacadosY++;
              idListaAmeacantesY++;
              j++;
         }
         idListaAmeacadosX++;
         idListaAmeacantesX++;
         i++;
    }
            
   return TAB_CondRetOK;
   }

   void criaListaPecas() {
            
            LIS_CriarLista(idListaPeca,DestruirValor,listaPecas);
   
   }
   
   criaTabuleiro(tabuleiro);
   criaListaPecas();    

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

   TAB_tpCondRet inserirPeca(int x, char y,char *cor,char *id) {
        int y = (int)(y - 'A');
        x--;
        if(x>7 || x<0 || y>7 || y<0) {
            return TAB_CondRetCoordenadaNExiste; 
        }
        Peca *novo= (Peca *) malloc(sizeof(Peca));
        if(novo == NULL) {
            return TAB_CondRetFaltouMemoria;
        }
        
        strcpy(peca->cor,cor);
        strcpy(peca->id,id);
        tabuleiro[x][y]->peca = novo;
        return TAB_CondRetOK:
   }

   TAB_tpCondRet ObterListaAmeacantes(int x, char y,LIS_tppLista listaAmeacantes) {
          int y = (int)(y - 'A');
           x--;
          if(x>7 || x<0 || y>7 || y<0) {
             return TAB_CondRetCoordenadaNExiste; 
          }
          listaAmeacantes = tabuleiro[x,y]->ameacantes;
          return TAB_CondRetOK;
   }
   
   TAB_tpCondRet ObterListaAmeacados(int x, char y,LIS_tppLista listaAmeacados) {
          int y = (int)(y - 'A');
           x--;
          if(x>7 || x<0 || y>7 || y<0) {
             return TAB_CondRetCoordenadaNExiste; 
          }
          listaAmeacados = tabuleiro[x,y]->ameacados;
          return TAB_CondRetOK;
   }

   TAB_tpCondRet obterPeca(int x, char y, char *cor, char *id) {
          Peca *peca;
          int y = (int)(y - 'A');
          x--;
          if(x>7 || x<0 || y>7 || y<0) {
             return TAB_CondRetCoordenadaNExiste; 
          }
          peca = tabuleiro[x][y]->peca;
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
          if(x>7 || x<0 || y>7 || y<0) {
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
  

   void liberaPeca(Peca *peca) {
         free(peca->cor);
         free(peca->id);
         free(peca);
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

   void destruirValor(void *pValor) {
        free(pValor);
   }



