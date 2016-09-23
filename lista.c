#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "Lista.h"

typedef struct LIS_tagLista {

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* Número de elementos da lista */
               
         char id[4];
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

   LIS_tppLista LIS_CriarLista(
             void   ( * ExcluirValor ) ( void * pDado ), char *idLista )
   {

      LIS_tpLista * pLista = NULL ;

      pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
      if ( pLista == NULL )
      {
         return NULL ;
      } /* if */

      LimparCabeca( pLista ) ;

      pLista->ExcluirValor = ExcluirValor;
      
      pLista->idLista = (char *) malloc(sizeof(char) * strlen(idLista));

      return pLista ;

   } /* Fim função: LIS  &Criar lista */

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
