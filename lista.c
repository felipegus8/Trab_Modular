#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include "Lista.h"


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

/***** Protótipos das funções encapuladas no módulo *****/

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista pLista );


/***************************************************************************
*
*  Função: LIS  &Criar lista
*  ****/

   LIS_tppLista LIS_CriarLista(char idLista[4]
             void   ( * ExcluirValor ) ( void * pDado ))
   {

      LIS_tppLista * pLista = NULL ;

      pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tppLista )) ;
      if ( pLista == NULL )
      {
         return NULL ;
      } /* if */

      LimparCabeca( pLista ) ;

      pLista->ExcluirValor = ExcluirValor;
      
      pLista->idLista = (char *) malloc(sizeof(char) * strlen(idLista));
      
      strcpy(pLista->idLista, idLista);

      return pLista ;

   } /* Fim função: LIS  &Criar lista */
   
   
/***************************************************************************
*
*  Função: LIS  &Obter Id Lista
*  ****/
   
   char *obterIdLista(LIS_tppLista lista) {
            if(lista == NULL) {
                     return NULL;
            }
             return lista->idLista;
   } 

/***************************************************************************
*
*  Função: LIS  &Inserir nó na lista
*  ****/

  int inserirNo(LIS_tppLista lista, char *elemento) {
           tpElemLista *novo;
           tpElemLista *aux;
           #ifdef _DEBUG
           assert( pLista != NULL ) ;
           #endif
           
           novo =  (tpElemLista *) malloc(sizeof(tpElemLista));
           if(novo == NULL) {
                   // printf("falta de memória para inserir novo elemento na lista\n");
                    return 6;
           }
           
           tpElemLista->pValor = (char *) malloc(sizeof(char) * strlen(elemento));
           if(tpElemLista->pValor) {
                    // printf("falta de memória para inserir novo elemento na lista\n");
                    return 6;
           }
           strcpy(tpElemLista->pValor, elemento);
           aux = lista->pElemCorr->pProx;
           novo->pAnt = lista->pElemCorr;
           if(aux != NULL) {
                    novo->pProx = aux;
                    lista->pElemCorr->prox = novo;
                    aux->ant = novo;
           } else {
                    novo->pProx = NULL;
           }
           return 0;
  }


/*
char *obterIdLista(LIS_tppLista pLista) {
   #ifdef _DEBUG
   assert(plista != NULL) 
    #endif
    if(pLista == NULL) {
        return NULL;
    }
    return pLista->idLista;
   }

*/
