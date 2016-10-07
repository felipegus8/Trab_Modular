/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista genérica duplamente encadeada.
*
*  Arquivo gerado:              Lista.c
*  Letras identificadoras:      LIS
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
#include "lista.h"

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/
typedef struct tagElemLista {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
*
*
***********************************************************************/
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

   } LIS_tpLista ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void LiberarElemento( LIS_tppLista   lista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista lista ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista lista );

   static void EsvaziarLista(LIS_tppLista lista);

   /*****  Código das funções exportadas pelo módulo  *****/
/***************************************************************************
*
*  Função: LIS  &Criar lista
*  ****/

   LIS_tpCondRet LIS_CriarLista(LIS_tppLista *lista,char idLista[4],
             void   ( * ExcluirValor ) ( void * pDado ))
   {

      //LIS_tppLista * lista = NULL ;

      lista = (LIS_tppLista *) malloc( sizeof( LIS_tppLista)) ;
      if ( (*lista) == NULL )
      {
         return LIS_CondRetFaltouMemoria ;
      } /* if */

      LimparCabeca( *lista );

      (*lista)->ExcluirValor = ExcluirValor;
      
      
      strcpy((*lista)->idLista, idLista);

      return LIS_CondRetOK;

   } /* Fim função: LIS  &Criar lista */
   
   
/***************************************************************************
*
*  Função: LIS  &Obter Id Lista
*  ****/
   
   LIS_tpCondRet LIS_ObterIdLista(LIS_tppLista lista, char idLista[4]) {
            if(lista == NULL) {
                     return LIS_CondRetNaoAchou;
            }
            strcpy(idLista,lista->idLista);
            return LIS_CondRetOK;
   } /* Fim função: LIS  &Obter Id Lista */

/***************************************************************************
*
*  Função: LIS  &Inserir nó na lista
*  ****/

  LIS_tpCondRet LIS_InserirNo(LIS_tppLista lista, void *elemento) {
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
           novo->pValor = elemento;
           aux = lista->pElemCorr->pProx;
           novo->pAnt = lista->pElemCorr;
           if(aux != NULL) {
                    novo->pProx = aux;
                    lista->pElemCorr->pProx = novo;
                    aux->pAnt = novo;
           } else {
                    novo->pProx = NULL;
           }
           return LIS_CondRetOK;
  }  /* Fim função: LIS  &Inserir nó na lista */

  /***************************************************************************
*
*  Função: LIS  &Obter nó na Lista
*  ****/
   
   LIS_tpCondRet LIS_ObterNo(LIS_tppLista lista, void **referencia) {
           #ifdef _DEBUG
           assert( lista != NULL ) ;
           #endif
           if(lista->pElemCorr == NULL) {
                    return LIS_CondRetListaVazia;
           }
           //strcpy(s, (char *)lista->pElemCorr->pValor);
           *referencia = lista->pElemCorr->pValor;
           return LIS_CondRetOK;
   }  /* Fim função: LIS  &Obter Nó na lista */

   /***************************************************************************
*
*  Função: LIS  &Excluir nó corrente
*  ****/
   
   LIS_tpCondRet LIS_ExcluirNoCorrente(LIS_tppLista lista) {
           #ifdef _DEBUG
           assert(lista != NULL ) ;
           #endif
           
           tpElemLista * pElem;
           pElem = lista->pElemCorr;
           if(lista->pElemCorr == NULL) {
                    return LIS_CondRetListaVazia;
           }
           /* Desencadeia esquerda */

         if ( pElem->pAnt != NULL )
         {
            pElem->pAnt->pProx   = pElem->pProx ;
            lista->pElemCorr    = pElem->pAnt ;
         } else {
            lista->pElemCorr    = pElem->pProx ;
            lista->pOrigemLista = lista->pElemCorr ;
         } /* if */

      /* Desencadeia direita */

         if ( pElem->pProx != NULL )
         {
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
            lista->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( lista , pElem ) ;

      return LIS_CondRetOK;
            
   }/* fim função: LIS &Excluir nó corrente */

   /***************************************************************************
*
*  Função: LIS  &Ir para o próximo nó
*  ****/
  
  LIS_tpCondRet LIS_IrProx(LIS_tppLista lista) {
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
  }/* fim função: LIS &Ir para o próximo nó

   /***************************************************************************
*
*  Função: LIS  &Ir para o nó anterior
*  ****/
   LIS_tpCondRet LIS_IrAnt(LIS_tppLista lista) {
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
  }/* fim função: LIS &Ir para o nó anterior */
   
     /***************************************************************************
*
*  Função: LIS  &Alterar nó corrente
*  ****/
   LIS_tpCondRet LIS_AlterarNoCorrente(LIS_tppLista lista, void *referencia) {
           if(lista != NULL ) {
                    return LIS_CondRetFimLista;
           }
           
           if(lista->pElemCorr == NULL) {
                    return LIS_CondRetListaVazia;
           }  
           
           //strcpy(lista->pElemCorr->pValor, novo);
           lista->pElemCorr->pValor = referencia;
           return LIS_CondRetOK;
   }/* fim função: LIS &Alterar nó corrente */
    
        /***************************************************************************
*
*  Função: LIS  &Destruir lista
*  ****/
      LIS_tpCondRet LIS_DestroiLista(LIS_tppLista lista) {

          if(lista == NULL) {
                   return LIS_CondRetFimLista;
          } 

      EsvaziarLista( lista );

      free( lista );
      return LIS_CondRetOK;
   } /* Fim função: LIS  &Destruir lista */

/***************************************************************************


/*****  Código das funções encapsuladas no módulo  *****/
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
                         tpElemLista  * pElem   )
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

   tpElemLista * CriarElemento( LIS_tppLista lista ,
                                void *       pValor  )
   {

      tpElemLista * pElem ;

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
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

   void EsvaziarLista( LIS_tppLista lista ) {

      tpElemLista * pElem ;
      tpElemLista * pProx ;

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

      LimparCabeca( lista ) ;

   } /* Fim função: LIS  &Esvaziar lista */

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/
