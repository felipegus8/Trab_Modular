#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TesteLista.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "lista.h"


static const char CRIAR_LISTA             	[ ] = "=criarlista"     ;
static const char OBTER_ID_LISTA          	[ ] = "=obterIdLista"   ;
static const char INSERIR_NO              	[ ] = "=inserirNo"      ;
static const char OBTER_NO                	[ ] = "=obterNo"        ;
static const char EXCLUIR_NO_CORRENTE     	[ ] = "=excluirNoCorrente";
static const char IR_PROX        			[ ] = "=irProx"          ;
static const char IR_ANT           			[ ] = "=irAnt"            ;
static const char ALTERAR_NO_CORRENTE       [ ] = "=alterarNoCorrente" ;
static const char DESTROI_LISTA             [ ] = "=destroiLista"     ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   100
#define DIM_VALOR     100

LIS_tppLista   vtListas[ DIM_VT_LISTA ] ;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxLista( int inxLista , int Modo ) ;
   
   static int ValidarString(char* str);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TLIS &Testar lista
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 100 listas, identificadas pelos �ndices 0 a 100
*
*     Comandos dispon�veis:
*
*     =criarlista                   inxLista  idLista   CondRetEsp
*     =obterIdLista                 inxLista  idLista
*     =inserirNo                   	inxLista   string  CondRetEsp
*     =obterNo                      inxLista   string  CondRetEsp
*     =excluirNoCorrente            inxLista
*     =irProx                       inxLista   CondRetEsp
*     =irAnt                        inxLista   CondRetEsp
*     =alterarNoCorrente            inxLista   string   CondRetEsp
*     =destroiLista                 inxLista   CondRetEsp
***********************************************************************/



 TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxLista  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      TST_tpCondRet CondRet ;

      char   StringDado[  DIM_VALOR ] ;
      char * pDado ;

      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;

      StringDado[ 0 ] = 0 ;
	  
	   if ( strcmp( ComandoTeste , CRIAR_LISTA ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxLista,StringDado,&CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , VAZIO )) || !(ValidarString(StringDado)))
            {
               return TST_CondRetParm ;
            } /* if */

            vtListas[ inxLista ] =
                 LIS_CriarLista( StringDado,DestruirValor ) ;

            return TST_CompararPonteiroNulo( 1 , vtListas[ inxLista ] ,
               "Erro em ponteiro de nova lista."  ) ;

         } /* fim ativa: Testar CriarLista */
		 else if (strcmp(ComandoTeste , OBTER_ID_LISTA) == 0)
		 {
			 numLidos = LER_LerParametros("is",&inxLista,StringDado);
			  if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) || !(ValidarString(StringDado)))
            {
               return TST_CondRetParm ;
            } /* if */
			
			 pDado = ( char * ) obterIdLista( vtListas[ inxLista ] ) ;

            return TST_CompararString( StringDado , pDado ,
                         "Valor do elemento errado." ) ;
         } /* fim ativa: Testar obter valor do idLista */
		 else if (strcmp(ComandoTeste,INSERIR_NO) == 0)
		 {
			 
		 }
		 }
   }
	  











/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim fun��o: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Fun��o: TLIS -Validar indice de lista
*
***********************************************************************/

   int ValidarInxLista( int inxLista , int Modo )
   {

      if ( ( inxLista <  0 )
        || ( inxLista >= DIM_VT_LISTA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtListas[ inxLista ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtListas[ inxLista ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim fun��o: TLIS -Validar indice de lista */
/***********************************************************************
*
*  $FC Fun��o: TLIS -Validar String
*
***********************************************************************/
int ValidarString(char* str)
{
	int i;
	for(i=0;str[i]!="\0";i++);
	if (i>0 && i<=4)
	return TRUE;
	return FALSE;
}
/* Fim fun��o: TLIS -Validar String */
