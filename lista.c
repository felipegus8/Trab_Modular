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

   static tpElemLista * CriarElemento( LIS_tppLista lista ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista lista );

   static void EsvaziarLista(LIS_tppLista lista);
/***************************************************************************
*
*  Função: LIS  &Criar lista
*  ****/

   LIS_tpCondRet LIS_CriarLista(LIS_tpplista *lista,char idLista[4]
             void   ( * ExcluirValor ) ( void * pDado ), LIS_tppLista lista)
   {

      //LIS_tppLista * lista = NULL ;

      lista = ( LIS_tpLista * ) malloc( sizeof( LIS_tppLista)) ;
      if ( lista == NULL )
      {
         return LIS_CondRetFaltouMemoria ;
      } /* if */

      LimparCabeca( lista );

      lista->ExcluirValor = ExcluirValor;
      
      lista->idLista = (char *) malloc(sizeof(char) * strlen(idLista));
      
      strcpy(lista->idLista, idLista);

      return LIS_CondRetOK;

   } /* Fim função: LIS  &Criar lista */
   
   
/***************************************************************************
*
*  Função: LIS  &Obter Id Lista
*  ****/
   
   LIS_tpCondRet obterIdLista(LIS_tppLista *lista, char idLista[4]) {
            if(lista == NULL) {
                     return LIS_tpCondRetNaoAchou;
            }
            strcpy(idLista,lista->idLista);
            return LIS_tpCondRetOK;
   } 

/***************************************************************************
*
*  Função: LIS  &Inserir nó na lista
*  ****/

  LIS_tpCondRet inserirNo(LIS_tppLista lista, void *elemento) {
           tpElemLista *novo;
           tpElemLista *aux;
           #ifdef _DEBUG
           assert( lista != NULL ) ;
           #endif
           
           novo =  (tpElemLista *) malloc(sizeof(tpElemLista));
           if(novo == NULL) {
                   // printf("falta de memória para inserir novo elemento na lista\n");
                    return LIS_CondRetFaltouMemoria;
           }
           
           //tpElemLista->pValor = (char *) malloc(sizeof(char) * strlen(elemento));
           if(tpElemLista->pValor) {
                    // printf("falta de memória para inserir novo elemento na lista\n");
                    return LIS_CondRetFaltouMemoria;
           }
           //strcpy(tpElemLista->pValor, elemento);
           elemento = tpElemLista->pValor;
           aux = lista->pElemCorr->pProx;
           novo->pAnt = lista->pElemCorr;
           if(aux != NULL) {
                    novo->pProx = aux;
                    lista->pElemCorr->prox = novo;
                    aux->ant = novo;
           } else {
                    novo->pProx = NULL;
           }
           return LIS_CondRetOK;
  } 

  /***************************************************************************
*
*  Função: LIS  &Obter nó na Lista
*  ****/
   
   LIS_tpCondRet obterNo(LIS_tppLista lista, void *s) {
           #ifdef _DEBUG
           assert( lista != NULL ) ;
           #endif
           if(lista->pElemCorr == NULL) {
                    return LIS_CondRetListaVazia;
           }
           //strcpy(s, (char *)lista->pElemCorr->pValor);
           s = lista->pElemCorr->pValor;
           return LIS_CondRetOK;
   } 

   /***************************************************************************
*
*  Função: LIS  &Excluir nó corrente
*  ****/
   
   LIS_tpCondRet excluirNoCorrente(LIS_tppLista lista) {
           #ifdef _DEBUG
           assert(lista != NULL ) ;
           #endif
           
           tppElemLista * pElem;
           pElem = lista->pElemCorr;
           if(lista->pElemCorr == NULL) {
                    return LIS_CondRetListaVazia;
           }
           /* Desencadeia esquerda */

         if ( pElem->pAnt != NULL )
         {
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia direita */

         if ( pElem->pProx != NULL )
         {
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
            pLista->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( pLista , pElem ) ;

      return LIS_CondRetOK;
            
   }/* fim função: Lis &Excluir nó  */

   /***************************************************************************
*
*  Função: LIS  &Ir para o próximo nó
*  ****/
  
  LIS_tpCondRet irProx(LIS_tppLista lista) {
           #ifdef _DEBUG
           assert(lista != NULL ) ;
           #endif
           
           if(lista->pElemCorr == NULL) {
                    return LIS_CondRetListaVazia;
           } 
           
           if(lista->pElemCorr->pProx = NULL) {
                    return LIS_CondRetFimLista;
           }
           lista->pElemCorr = lista->pElemCorr->pProx;
           return LIS_CondRetOK;
  }/* fim função: Lis &Ir para o próximo nó

   /***************************************************************************
*
*  Função: LIS  &Ir para o nó anterior
*  ****/
   LIS_tpCondRet irAnt(LIS_tppLista lista) {
           #ifdef _DEBUG
           assert(lista != NULL ) ;
           #endif
           
           if(lista->pElemCorr == NULL) {
                    return LIS_CondRetListaVazia;
           } 
           
           if(lista->pElemCorr->pAnt = NULL) {
                    return LIS_CondRetFimLista;
           }
           lista->pElemCorr = lista->pElemCorr->pAnt;
           return LIS_CondRetOK;
  }/* fim função: Lis &Ir para o nó anterior */
   
     /***************************************************************************
*
*  Função: LIS  &Alterar nó corrente
*  ****/
   LIS_tpCondRet alterarNoCorrente(LIS_tppLista lista, void *novo) {
           if(lista != NULL ) {
                    return LIS_CondRetFimLista;
           }
           
           if(lista->pElemCorr == NULL) {
                    return LIS_CondRetListaVazia;
           }  
           
           //strcpy(lista->pElemCorr->pValor, novo);
           novo = lista->pElemCorr->pValor;
           return LIS_CondRetOK;
   }/* fim função: Lis &Alterar nó corrente */
    
        /***************************************************************************
*
*  Função: LIS  &Destruir lista
*  ****/
      LIS_tpCondRet destroiLista(LIS_tpp lista) {

          if(lista == NULL) {
                   return LIS_CondRetFimLista;
          } 

      EsvaziarLista( lista ) ;

      free( lista ) ;
      return LIS_CondRetOK;
   } /* Fim funÁ„o: LIS  &Destruir lista */

/***************************************************************************


/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaÁos apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   lista ,
                         tppElemLista  * pElem   )
   {

      if ( ( lista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
         lista->ExcluirValor( pElem->pValor ) ;
      } /* if */

      free( pElem ) ;

      lista->numElem-- ;

   } /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
*
***********************************************************************/

   tppElemLista * CriarElemento( LIS_tppLista lista ,
                                void *       pValor  )
   {

      tppElemLista * pElem ;

      pElem = ( tppElemLista * ) malloc( sizeof( tppElemLista )) ;
      if ( pElem == NULL )
      {
         return NULL ;
      } /* if */

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

      lista->numElem ++ ;

      return pElem ;

   } /* Fim função: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista lista )
   {

      lista->pOrigemLista = NULL ;
      lista->pFimLista = NULL ;
      lista->pElemCorr = NULL ;
      lista->numElem   = 0 ;

   } /* Fim função: LIS  -Limpar a cabeça da lista */

/***************************************************************************
*
*  Função: LIS  &Esvaziar lista
*  ****/

   void LIS_EsvaziarLista( LIS_tppLista lista ) {

      tppElemLista * pElem ;
      tppElemLista * pProx ;

      #ifdef _DEBUG
         assert( lista != NULL ) ;
      #endif

      pElem = lista->pOrigemLista;
      while ( pElem != NULL )
      {
         pProx = pElem->pProx ;
         LiberarElemento(lista , pElem ) ;
         pElem = pProx ;
      } /* while */

      LimparCabeca( pLista ) ;

   } /* Fim função: LIS  &Esvaziar lista */

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/
