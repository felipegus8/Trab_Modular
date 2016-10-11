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


Casa  *tabuleiro[8][8];


/***** Prottotipos das funções encapuladas no modulo *****/

int converteCoordenadaCharParaInt(char coordYChar);
int diminui1DeX(int coordX);


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
*     criartabuleiro            CondRetEsp
*     inserepeca                int     char     char      char     CondRetEsp
*     obterlistaameacantes      char     CondRetEsp
*     obterlistaameacados       char     CondRetEsp
*     obterpeca                 char     char      char         CondRetEsp
*     retirarpeca               char     CondRetEsp
*     moverpeca                 char     int       char        CondRetEsp
*     destruirtabuleiro         CondRetEsp
*
***********************************************************************/

 TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int  numLidos   = -1 ,
          CondRetEsp = -1  ;

      TST_tpCondRet CondRet;

      char   StringDado[  DIM_VALOR ],StringDado2[  DIM_VALOR  ] ;

	  int x, xf,coordX,coordX2,coordYInt,coordYInt2,TamColunas,TamLinhas;
	  char y, yf, cor, id,corLida,idLido;

	  LIS_tppLista *ameacas;

      StringDado[ 0 ] = 0 ;
      StringDado2[ 0 ] = 0;

      /* Criar Tabuleiro */

         if ( strcmp( ComandoTeste , CRIAR_TABULEIRO ) == 0 )
         {
            numLidos = LER_LerParametros( "i", &CondRetEsp) ;

            if ( numLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */


            CondRet = TAB_CriaTabuleiro((Casa *)tabuleiro,8,8);
			printf("%d\n",CondRet);

            return TST_CompararPonteiroNulo( 1 , tabuleiro , "Erro em ponteiro de nova lista."  ) ;

         } /* FIM: Criar Tabuleiro */

      /* Insere Peca */

         else if ( strcmp( ComandoTeste , INSERE_PECA) == 0 )
         {

            numLidos = LER_LerParametros( "iccci" , &x, &y, &cor, &id, &CondRetEsp) ;

            if (  numLidos != 5 )
            {
               return TST_CondRetParm ;
            } /* if */

			coordYInt = converteCoordenadaCharParaInt(y);
			//coordX = diminui1DeX(x);

            CondRet = TAB_InserirPeca((Casa *)tabuleiro, x, coordYInt, cor,id);


            return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao inserir uma peca." );

         } /* fim ativa: InserePeca */

		 /* ObterPeca */

         else if ( strcmp( ComandoTeste , OBTER_PECA) == 0 )
         {

            numLidos = LER_LerParametros( "iccci" , &x, &y, &corLida, &idLido, &CondRetEsp) ;


            if ( numLidos != 5 )
            {
               return TST_CondRetParm ;
            } /* if */


			coordYInt = converteCoordenadaCharParaInt(y);
			//coordX = diminui1DeX(x);

            CondRet = TAB_ObterPeca((Casa *)tabuleiro, x, coordYInt, &cor,&id);
			printf("\nIDRESULT:%c \nCORRESULT:%c\n",id,cor);
			if(corLida != cor)
			{
				printf("Cor errada");
			}
			if(idLido != id)
			{
				printf("Id errado");
			}

            return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao obter uma peca" );

         } /* fim ativa: ObterPeca */

		 /* Retirar Peca */

         else if ( strcmp( ComandoTeste , RETIRAR_PECA) == 0 )
         {

            numLidos = LER_LerParametros( "ici" , &x, &y, &CondRetEsp) ;

            if ( numLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

			//coordX = diminui1DeX(x);

			coordYInt = converteCoordenadaCharParaInt(y);

            CondRet = TAB_RetirarPeca((Casa *)tabuleiro, x, coordYInt);

            return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao retirar uma peca" );

         } /* fim ativa: RetirarPeca */


		 /* Mover Peca */

         else if ( strcmp( ComandoTeste , MOVER_PECA) == 0 )
         {

            numLidos = LER_LerParametros( "icici" , &x, &y, &xf, &yf, &CondRetEsp) ;

            if ( numLidos != 5 )
            {
               return TST_CondRetParm ;
            } /* if */

			//coordX = diminui1DeX(x);
			//coordX2 = diminui1DeX(xf);

			coordYInt = converteCoordenadaCharParaInt(y);
			coordYInt2 = converteCoordenadaCharParaInt(yf);

		 
           printf("Estou na mover peça no testelista.c\n");
            CondRet = TAB_MoverPeca((Casa *)tabuleiro, x, coordYInt, xf, coordYInt2);

            return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao mover uma peca" );

         } /* fim ativa: Move Peca */

		 /* ObterListaAmeacantes */

         else if ( strcmp( ComandoTeste , OBTER_LISTA_AMEACANTES) == 0 )
         {

            numLidos = LER_LerParametros( "ici" , &x, &y, ameacas) ;

            if ( numLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

			//coordX = diminui1DeX(x);

			coordYInt = converteCoordenadaCharParaInt(y);

            CondRet = TAB_ObterListaAmeacantes((Casa *)tabuleiro, x, coordYInt, ameacas);

            return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao obter a lista de ameacantes da peca." );

         } /* fim ativa: ObterListaAmeacantes */

		 /* ObterListaAmeacados */

         else if ( strcmp( ComandoTeste , OBTER_LISTA_AMEACADOS) == 0 )
         {

            numLidos = LER_LerParametros( "ici" , &x,&y, ameacas) ;

            if (numLidos != 3)
            {
               return TST_CondRetParm ;
            } /* if */

			//coordX = diminui1DeX(x);

			coordYInt = converteCoordenadaCharParaInt(y);

            CondRet = TAB_ObterListaAmeacantes((Casa *)tabuleiro, x, coordYInt, ameacas);

            return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao obter a lista de ameacados da peca." );

         } /* fim ativa: ObterListaAmeacados */


      /* Testar Destruir Tabuleiro */

         else if ( strcmp( ComandoTeste , DESTRUIR_TABULEIRO ) == 0 )
         {
            numLidos = LER_LerParametros( "i" , &CondRetEsp) ;

            if ( numLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */
			 
            //LIS_DestruirLista( tabuleiro ) ;
			CondRet = TAB_DestruirTabuleiro((Casa *)tabuleiro);

            return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao destruir um tabuleiro" );

         } /* fim ativa: Testar Destruir tabuleiro */
		 return TST_CondRetNaoConhec ;
}

int converteCoordenadaCharParaInt(char coordYChar) {
	int coordYInt;
	coordYInt = coordYChar - 'A';  //converte para int
	return coordYInt;
}

int diminui1DeX(int coordX) {
    return coordX - 1;
}