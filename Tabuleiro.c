#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include "Tabuleiro.h"
    
   
   typedef struct casa {
         LIS_tppLista *ameacados;
         /* ponteiro para a cabeça da lista que contém as peças ameaçadas pela peça da casa */
         LIS_tppLista *amecantes;
         /* ponteiro para a cabeça da lista que contém as peças que ameaçam a peça da casa */
         Peca *peca;
         /*ponteiro para a estrutura da peça contida na casa */
   } Casa;

   void destruirValor(void *pValor);
   
   TAB_tpCondRet criaTabuleiro(Casa **tabuleiro) {
   
    int i = 0,j=0;
    char a = 'A';
    char b = 'B';
    char idListaAmeacadosX = '0';//linha da casa onde reside a lista ameacados
    char idListaAmeacadosY; //coluna da casa onde reside a lista ameacados
    char idListaAmeacantesX = '0';//linha da casa onde reside a lista ameacantes
    char idListaAmeacadosY;//coluna da casa onde reside a lista ameacantes
    char idListaAmeacantes[4];
    char idListaAmecantes[4];
    tabuleiro = malloc(sizeof(Casa) * 64);
    if(tabuleiro == NULL) {
         return TAB_CondRetFaltouMemoria;
    }        
    
    while(i<8) {
             idListaAmeacadosY = 'A';
             idListaAmeacantesY = 'A';
         while(j<8) {
              strcpy(idListaAmeacados,idListaAmeacadosX);
              strcat(idLIstaAmeacados,idListaAmeacadosY);
              strcat(idListaAmeacados,a);
              //as 3 linhas acima fazem com que a string identificadora da lista fique da forma "linhaColunaA"
              strcpy(idListaAmeacantes,idListaAmeacantesX);
              strcat(idLIstaAmeacantes,idListaAmeacantesY);
              strcat(idListaAmeacantes,b);
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

   
   void destruirValor(void *pValor) {
        free(pValor);
   }

