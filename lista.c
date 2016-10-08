#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include "lista.h"


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
               
         char *idLista;
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

   LIS_tpCondRet LIS_CriarLista(LIS_tppLista *lista,char *idLista,
             void   ( * ExcluirValor ) ( void * pDado ))
   {

      //LIS_tppLista * lista = NULL ;

	   LIS_tppLista listaCopia = NULL;

	   listaCopia = (LIS_tpLista *) malloc(sizeof(LIS_tpLista));
	   
	  
      if ( listaCopia == NULL )
      {
         return LIS_CondRetFaltouMemoria ;
      } /* if */
	  
      LimparCabeca(listaCopia );
      
      listaCopia->idLista = (char *) malloc(strlen(idLista) + 1);
	   
      strcpy(listaCopia->idLista,idLista);
	   
      listaCopia->ExcluirValor = ExcluirValor;
      
     

	  *lista = listaCopia;
	   printf("Endereço passado: %d\n",ExcluirValor);
	   printf("outro endereço recebido: %d\n",(*listaCopia).ExcluirValor);
	   printf("Endereço recebido: %d\n",(*lista)->ExcluirValor);

      return LIS_CondRetOK;
	  
   } /* Fim função: LIS  &Criar lista */
   
   
/***************************************************************************
*
*  Função: LIS  &Obter Id Lista
*  ****/
   
   LIS_tpCondRet LIS_ObterIdLista(LIS_tppLista lista, char idLista[4]) {
	   printf("%d\n",lista->idLista);
            if(lista == NULL) {
                     return LIS_CondRetNaoAchou;
            }
            strcpy(idLista,lista->idLista);
            return LIS_CondRetOK;
   } 

/***************************************************************************
*
*  Função: LIS  &Inserir nó na lista
*  ****/

  LIS_tpCondRet LIS_InserirNo(LIS_tppLista pLista, void *pValor) {
            tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inerir após */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento após o elemento */

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pProx != NULL )
            {
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
               pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* if */
                  
         pLista->pElemCorr = pElem ;
	  
	  printf("ve se imprime algo dps disso\n");
	  
	 pLista->ExcluirValor(pElem->pValor);
	 printf("ALGO!!\n");
                  
         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento após */


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
   } 

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
            
   }/* fim função: Lis &Excluir nó  */

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
  }/* fim função: Lis &Ir para o próximo nó

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
  }/* fim função: Lis &Ir para o nó anterior */
   
     /***************************************************************************
*
*  Função: LIS  &Alterar nó corrente
*  ****/
   LIS_tpCondRet LIS_AlterarNoCorrente(LIS_tppLista lista, void *referencia) {
          
           if(lista->pElemCorr == NULL) {
                    return LIS_CondRetListaVazia;
           }  
           
           //strcpy(lista->pElemCorr->pValor, novo);
           lista->pElemCorr->pValor = referencia;
           return LIS_CondRetOK;
   }/* fim função: Lis &Alterar nó corrente */
    
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
   } /* Fim funÁ„o: LIS  &Destruir lista */

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
