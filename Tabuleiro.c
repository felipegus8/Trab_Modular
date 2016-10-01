#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include "Tabuleiro.h"


typedef struct tagElemLista {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

   } tpElemLista ;


typedef struct LIS_tagLista {

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* Número de elementos da lista */
               
         char idLista[4];
              /*  String que identifica a lista */
         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

   } LIS_tppLista ;
   
   
   
   
   typedef struct casa {
         LIS_tppLista *ameacados;
         /* ponteiro para a cabeça da lista que contém as peças ameaçadas pela peça da casa */
         LIS_tppLista *amecantes;
         /* ponteiro para a cabeça da lista que contém as peças que ameaçam a peça da casa */
         Peca *peca;
         /*ponteiro para a estrutura da peça contida na casa */
   } Casa;

   void destruirValor(void *pValor);
   
   TAB_tpCondRet criaTabuleiro(Casa **tabuleiro,char idListaAmeacados[4],char idListaAmeacantes[4]) {
   
    int i = 0,j=0;
    tabuleiro = malloc(sizeof(Casa) * 64);
    if(tabuleiro == NULL) {
         return -1;
    }        
    
    while(i<8) {
         while(j<8) {
              LIS_CriarLista(idListaAmeacados,DestruirValor,tabuleiro[i][j]->ameacados);
              LIS_CriarLista(idListaAmeacantes,DestruirValor,tabuleiro[i][j]->ameacantes);
              tabuleiro[i][j]->peca = NULL;
              j++;
         }
         i++;
    }
            
   return LIS_CondRetOK;
   }

   
   void destruirValor(void *pValor) {
        free(pValor);
   }

