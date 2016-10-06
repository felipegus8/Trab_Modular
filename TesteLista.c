#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_ESPC.h"

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

#define DIM_VT_LISTA   10
#define DIM_VALOR     100

LIS_tppLista   vtListas[ DIM_VT_LISTA ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxLista( int inxLista , int Modo ) ;
   
   static int ValidarString(char* str);

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TLIS &Testar lista
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
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

      int CondRet ;

      char   StringDado[  DIM_VALOR ],idLista[4];
      char * pDado ;

      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;

       void * elemento;
      StringDado[ 0 ] = 0 ;
	  
	   if ( strcmp( ComandoTeste , CRIAR_LISTA ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxLista,StringDado,&CondRetEsp ) ;

            if ( ( numLidos != 3 ) || ( ! ValidarInxLista( inxLista , VAZIO )) || !(ValidarString(StringDado)))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = LIS_CriarLista( vtListas[inxLista],StringDado,DestruirValor ) ;

            return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao criar uma lista" ) ;

         } /* fim ativa: Testar CriarLista */
		 else if (strcmp(ComandoTeste , OBTER_ID_LISTA) == 0)
		 {
			 numLidos = LER_LerParametros("is",&inxLista,idLista);
			  if ( ( numLidos != 2 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) || !(ValidarString(StringDado)))
            {
               return TST_CondRetParm ;
            } /* if */
			
			 CondRet =  obterIdLista( vtListas[ inxLista ],idLista);

            return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao obter o Id da lista." ) ;
         } /* fim ativa: Testar obter valor do idLista */
		 
		 else if (strcmp(ComandoTeste,INSERIR_NO) == 0)
		 {
			  numLidos = LER_LerParametros( "isi" ,
                       &inxLista , StringDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) || !(ValidarString(StringDado)) )
            {
               return TST_CondRetParm ;
            } /* if */
			pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , StringDado ) ;
			 elemento = (void*)malloc(sizeof(void*));
             
			CondRet = inserirNo( vtListas[ inxLista ] , elemento ) ;
             strcpy((char)elemento,pDado);

            if ( CondRet != 0 )
            {
               free( pDado ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao inserir o nó." ) ;
		 }/*fim ativa:Testar inserir nó*/
		 
		 else if (strcmp(ComandoTeste,OBTER_NO) == 0)
		 {
			  numLidos = LER_LerParametros( "isi" ,
                       &inxLista , StringDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) || !(ValidarString(StringDado)) )
            {
               return TST_CondRetParm ;
            } /* if */
			pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , StringDado ) ;
            
             elemento = (void*)malloc(sizeof(void*));
             
			CondRet = obterNo(vtListas[inxLista],elemento);
             
             strcpy((char)elemento,pDado);
             
			 if ( CondRet != 0 )
            {
               free( pDado ) ;
            } /* if */
			  return TST_CompararString( StringDado , pDado ,"Valor Encontrado diferente do esperado." ) ;
		 }/*fim ativa:Testar obter nó*/
		 
		 else if (strcmp(ComandoTeste,EXCLUIR_NO_CORRENTE) == 0)
		 {
				numLidos = LER_LerParametros("i",&inxLista);
				if ( ( numLidos != 1 )|| ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
			CondRetEsp = 0;
			return TST_CompararInt( CondRetEsp ,excluirNoCorrente( vtListas[ inxLista ] ) ,"Condição de retorno errada ao excluir o no corrente."  ) ;
		 }/*fim ativa:Testar excluir nó corrente*/
		 
		 
		 else if (strcmp(ComandoTeste,IR_PROX) == 0)
		 {
			 numLidos = LER_LerParametros("ii",&inxLista,&CondRetEsp);
			 if ( ( numLidos != 2 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
			CondRet = irProx(vtListas[inxLista]);
			return TST_CompararInt( CondRetEsp ,CondRet,"Condição de retorno errada ao ir para o próximo elemento da lista"  ) ;
		 }/*fim ativa:Testar ir próximo*/
		 
		 
		 else if (strcmp(ComandoTeste,IR_ANT) == 0)
		 {
			 numLidos = LER_LerParametros("ii",&inxLista,&CondRetEsp);
			 if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
			CondRet = irAnt(vtListas[inxLista]);
			return TST_CompararInt( CondRetEsp ,CondRet ,"Condição de retorno errada ao ir para o elemento anterior da lista" ) ;
		 }/*fim ativa:Testar ir anterior*/
		 
		 
		 else if(strcmp(ComandoTeste,ALTERAR_NO_CORRENTE) == 0)
		 {
			 numLidos = LER_LerParametros("isi",&inxLista,StringDado,&CondRetEsp);
			 if ( ( numLidos != 2 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
			pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , StringDado);
             
             elemento = (void*)malloc(sizeof(void*));
             
			CondRet = alterarNoCorrente(vtListas[inxLista],elemento);
             strcpy((char)elemento,pDado);
			return TST_CompararInt( CondRetEsp ,CondRet  ,"Condição de retorno errada ao alterar o conteúdo do nó corrente" ) ;
		 }/*fim ativa:Testar alterar nó corrente*/
		 
		 else if(strcmp(ComandoTeste,DESTROI_LISTA) == 0)
		 {
			  numLidos = LER_LerParametros( "i" ,&inxLista,&CondRetEsp ) ;

            if ( ( numLidos != 2 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = destroiLista( vtListas[ inxLista ] ) ;
            vtListas[ inxLista ] = NULL ;
            return TST_CompararInt( CondRetEsp ,CondRet  ,"Condição de retorno errada ao destruir a lista" ) ;
		 }/*fim ativa:Testar destrói lista*/	 
		 
		return TST_CondRetNaoConhec ;
   }  /* Fim função: TLIS &Testar lista */
	  
	  
	  
/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim função: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de lista
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

   } /* Fim função: TLIS -Validar indice de lista */
/***********************************************************************
*
*  $FC Função: TLIS -Validar String
*
***********************************************************************/
int ValidarString(char* str)
{
	int i;
	for(i=0;str[i]!='\0';i++);
	if (i>0 && i<=4)
	return TRUE;
	return FALSE;
}
/* Fim função: TLIS -Validar String */
