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
   //AE:A lista não possui nenhum elemento e deve receber ponteiro LIS_tppLista e um ponteiro com a id
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
   //AS: Uma lista foi criada com id e cabeça
   
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
//AE: Recebe uma LIS_tppLista lista já criada e um ponteiro para um valor generico
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
	  
	    
                  
         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento após */
  //AS:Um elemento foi inserido na lista que é apontado pelo ponteiro corrente

  /***************************************************************************
*
*  Função: LIS  &Obter nó na Lista
*  ****/

//AE: Recebe uma LIS_tppLista lista já criada e ponteiro que aponta para o ponteiro void de um valor
LIS_tpCondRet LIS_ObterNo(LIS_tppLista lista, void **referencia) {
	       #ifdef _DEBUG
           assert( lista != NULL ) ;
           #endif
           if(lista->pElemCorr == NULL) {
			   *referencia = NULL;
               return LIS_CondRetListaVazia;
           }
		   
           *referencia = lista->pElemCorr->pValor;
           return LIS_CondRetOK;
   } 
//AS: A função fara que um ponteiro referencia aponte para um valor da lista
   /***************************************************************************
*
*  Função: LIS  &Excluir nó corrente
*  ****/
   
//AE:Recebe uma LIS_tppLista lista já criada
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
   //AS: O elemento apontado pelo nó corrente foi excluido e o corrente passa a ser o anterior ao excluido
   /***************************************************************************
*
*  Função: LIS  &Ir para o próximo nó
*  ****/
  //AE:Recebe uma LIS_tppLista lista já criada
  LIS_tpCondRet LIS_IrProx(LIS_tppLista pLista) {
           #ifdef _DEBUG
           assert(lista != NULL ) ;
           #endif
           tpElemLista * pElem ;

           if ( pLista->pElemCorr == NULL )
         {

            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

      /* Tratar avançar para frente */

        

            pElem = pLista->pElemCorr ;
           
            pElem    = pElem->pProx ;

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetFimLista ;
           
  }/* fim função: Lis &Ir para o próximo nó
   //AS: O corrente deve apontar agora para o o nó logo ao da frente recibido inicialmente na função
   /***************************************************************************
*
*  Função: LIS  &Ir para o nó anterior
*  ****/
  //AE:Recebe uma LIS_tppLista lista já criada
   LIS_tpCondRet LIS_IrAnt(LIS_tppLista pLista) {

	      tpElemLista * pElem ;
           #ifdef _DEBUG
           assert(lista != NULL ) ;
           #endif

            pElem = pLista->pElemCorr ;
               pElem = pElem->pAnt ;

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetFimLista ;
  }/* fim função: Lis &Ir para o nó anterior */
   //AS: O corrente deve apontar agora para o o nó na posição anterior ao do recibido inicialmente na função
     /***************************************************************************
*
*  Função: LIS  &Alterar nó corrente
*  ****/
   //AE: Recebe uma LIS_tppLista lista já criada e ponteiro void
   LIS_tpCondRet LIS_AlterarNoCorrente(LIS_tppLista lista, void *referencia) {
          
           if(lista->pElemCorr == NULL) {
                    return LIS_CondRetListaVazia;
           }  
           
           //strcpy(lista->pElemCorr->pValor, novo);
           lista->pElemCorr->pValor = referencia;
           return LIS_CondRetOK;
   }/* fim função: Lis &Alterar nó corrente */
   //AS: O nó corrente passara a apontar para o ponteiro recebido como paramentro
        /***************************************************************************
*
//AE:Recebe uma LIS_tppLista lista já criada
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
//AS: A lista criada deverá excluir todos os nós delas e ainda libera da memória a propria lista recebida como parametro
/***************************************************************************


/*****  Código das funções encapsuladas no módulo  *****/
/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/
//AE:Recebe uma LIS_tppLista lista já criada
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
//AS: Elimina da lista o conteudo apontado pelo elemento recebido e o proprio elemento

/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
*
***********************************************************************/
   //AE:AE:Recebe uma LIS_tppLista lista já criada e ponteiro apontando para um valor
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
   //AS: Na lista recebida foi adiciona um ponteiro para o valor

/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
*
***********************************************************************/
//AE:Recebe uma LIS_tppLista lista já criada
   void LimparCabeca( LIS_tppLista lista )
   {

      lista->pOrigemLista = NULL ;
      lista->pFimLista = NULL ;
      lista->pElemCorr = NULL ;
      lista->numElem   = 0 ;

   } /* Fim função: LIS  -Limpar a cabeça da lista */
//AS: A cabeça da lista será limpada de seus valores originais
/***************************************************************************
*
*  Função: LIS  &Esvaziar lista
*  ****/
   //AE:Recebe uma LIS_tppLista lista já criada
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
//AS: A lista recebida foi desvinculada de todos seus nó e cabeça

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/
