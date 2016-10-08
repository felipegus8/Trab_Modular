/***************************************************************************
*  $MCI Módulo de implementação: TTAB Teste Tabuleiro
*
*  Arquivo gerado:              TestaTabuleiro.c
*  Letras identificadoras:      TTAB

*  Autores: Felipe Viberti,Luis Claudio e Victor Nogueira
*
*  $HA Histórico de evolução:
*     Versão  Autores                                           Data          Observações
*     1       Felipe Viberti,Luis Claudio e Victor Nogueira   27/set/2016  início desenvolvimento
***************************************************************************/
#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_ESPC.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Tabuleiro.h"

static const char CRIAR_TABULEIRO          	                        [ ] = "=criartabuleiro" ;
static const char INSERE_PECA        	                            [ ] = "=inserepeca"   ;
static const char OBTER_LISTA_AMEACANTES                            [ ] = "=obterlistaameacantes"      ;
static const char OBTER_LISTA_AMEACADOS               				[ ] = "=obterlistaameacados"        ;
static const char OBTER_PECA              				            [ ] = "=obterpeca" ;
static const char RETIRAR_PECA              				        [ ] = "=retirarpeca"        ;
static const char MOVER_PECA              				            [ ] = "=moverpeca"        ;
static const char DESTRUIR_TABULEIRO                                [ ] = "=destruirtabuleiro"        ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_TAB   10
#define DIM_VALOR     100

Casa * tabuleiro[8][8];

LIS_tppLista   vtTab[ DIM_VT_TAB ] ;

/***** Prottotipos das funções encapuladas no modulo *****/

   static int ValidarInxTab( int inxTab , int Modo ) ;

/*****  Codigo das funções exportadas pelo modulo  *****/


/***********************************************************************
*
*  $FC Funcão: TLIS &Testar tabuleiro
*
*  $ED Descriçãoo da função
*     É criado um tabuleiro e nele pode operar todas as funções abaixo
*
*     Comandos disponiveis:
*
*     criartabuleiro            inxTab                                     CondRetEsp
*     inserepeca                intTab      int     char     char      char     CondRetEsp
*     obterlistaameacantes      inxTab     char     CondRetEsp
*     obterlistaameacados       inxTab     char     CondRetEsp
*     obterpeca                 inxTab     char     char      char         CondRetEsp
*     retirarpeca               inxTab     char     CondRetEsp
*     moverpeca                 inxTab     char     int       char        CondRetEsp
*     destruirtabuleiro         inxTab     CondRetEsp
*
***********************************************************************/

 TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxTab  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      TST_tpCondRet CondRet;

      char   StringDado[  DIM_VALOR ],StringDado2[  DIM_VALOR  ] ;

	  int x, xf;
	  char y, yf, cor, id;

	  LIS_tppLista *ameacas;

      StringDado[ 0 ] = 0 ;
      StringDado2[ 0 ] = 0;

      /* Criar Tabuleiro */

         if ( strcmp( ComandoTeste , CRIAR_TABULEIRO ) == 0 )
         {
            numLidos = LER_LerParametros( "ii" , &inxTab, &CondRetEsp ) ;

            if ( ( numLidos != 2 ) || ( ! ValidarInxTab( inxTab , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = TAB_CriaTabuleiro(tabuleiro);

            return TST_CompararPonteiroNulo( 1 , vtTab[ inxTab ] , "Erro em ponteiro de nova lista."  ) ;

         } /* FIM: Criar Tabuleiro */

      /* Insere Peca */

         else if ( strcmp( ComandoTeste , INSERE_PECA) == 0 )
         {

            numLidos = LER_LerParametros( "iiccci" , &inxTab, &x, &y, &cor, &id, &CondRetEsp) ;

            if ( ( numLidos != 6 )|| ( ! ValidarInxTab( inxTab , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = TAB_InserirPeca(*tabuleiro, x, y, cor,id);

            return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao ensinar o movimento a uma peça conhecida." );

         } /* fim ativa: InserePeca */

		 /* ObterPeca */

         else if ( strcmp( ComandoTeste , OBTER_PECA) == 0 )
         {

            numLidos = LER_LerParametros( "iiccci" , &inxTab, &x, &y, &cor, &id, &CondRetEsp) ;

            if ( ( numLidos != 6 )|| ( ! ValidarInxTab( inxTab , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = TAB_ObterPeca(*tabuleiro, x, y, cor,id);

            return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao ensinar o movimento a uma peça conhecida." );

         } /* fim ativa: ObterPeca */

		 /* Retirar Peca */

         else if ( strcmp( ComandoTeste , RETIRAR_PECA) == 0 )
         {

            numLidos = LER_LerParametros( "iici" , &inxTab, &x, &y, &CondRetEsp) ;

            if ( ( numLidos != 4 )|| ( ! ValidarInxTab( inxTab , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = TAB_RetirarPeca(*tabuleiro, x, y);

            return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao ensinar o movimento a uma peça conhecida." );

         } /* fim ativa: RetirarPeca */


		 /* Mover Peca */

         else if ( strcmp( ComandoTeste , MOVER_PECA) == 0 )
         {

            numLidos = LER_LerParametros( "iicici" , &inxTab, &x, &y, &xf, &yf, &CondRetEsp) ;

            if ( ( numLidos != 6 )|| ( ! ValidarInxTab( inxTab , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = TAB_MoverPeca(*tabuleiro, x, y, xf, yf);

            return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao ensinar o movimento a uma peça conhecida." );

         } /* fim ativa: Move Peca */

		 /* ObterListaAmeacantes */

         else if ( strcmp( ComandoTeste , OBTER_LISTA_AMEACANTES) == 0 )
         {

            numLidos = LER_LerParametros( "iici" , &inxTab, &x, &y, ameacas) ;

            if ( ( numLidos != 4 )|| ( ! ValidarInxTab( inxTab , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = TAB_ObterListaAmeacantes(*tabuleiro, x, y, ameacas);

            return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao ensinar o movimento a uma peça conhecida." );

         } /* fim ativa: ObterListaAmeacantes */

		 /* ObterListaAmeacados */

         else if ( strcmp( ComandoTeste , OBTER_LISTA_AMEACADOS) == 0 )
         {

            numLidos = LER_LerParametros( "iici" , &inxTab, &x,&y, ameacas) ;

            if ( ( numLidos != 4 )|| ( ! ValidarInxTab( inxTab , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = TAB_ObterListaAmeacantes(*tabuleiro, x, y, ameacas);

            return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao ensinar o movimento a uma peça conhecida." );

         } /* fim ativa: ObterListaAmeacados */


      /* Testar Destruir Tabuleiro */

         else if ( strcmp( ComandoTeste , DESTRUIR_TABULEIRO ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxTab ) ;

            if ( ( numLidos != 1 )|| ( ! ValidarInxTab( inxTab , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_DestruirLista( vtTab[ inxTab ] ) ;
            vtTab[ inxTab ] = NULL ;

			CondRet = TAB_DestruirTabuleiro(*tabuleiro);

            return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao ensinar o movimento a uma peça conhecida." );

         } /* fim ativa: Testar Destruir tabuleiro */
		 return TST_CondRetNaoConhec ;
}
/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de lista
*
***********************************************************************/

   int ValidarInxTab( int inxTab , int Modo )
   {

      if ( ( inxTab <  0 )
        || ( inxTab >= DIM_VT_TAB ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtTab[ inxTab ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtTab[ inxTab ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TLIS -Validar indice de lista */

/********** Fim do módulo de implementação: TTAB  TesteTabuleiro **********/