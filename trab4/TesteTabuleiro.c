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

#ifdef _DEBUG
#include "CESPDIN.H"
#endif

static const char CRIAR_TABULEIRO          	                        [ ] = "=criartabuleiro" ;
static const char INSERE_PECA        	                            [ ] = "=inserepeca"   ;
static const char OBTER_LISTA_AMEACANTES                            [ ] = "=obterlistaameacantes"      ;
static const char OBTER_LISTA_AMEACADOS               				[ ] = "=obterlistaameacados"        ;
static const char OBTER_PECA              				            [ ] = "=obterpeca" ;
static const char RETIRAR_PECA              				        [ ] = "=retirarpeca"        ;
static const char MOVER_PECA              				            [ ] = "=moverpeca"        ;
static const char DESTRUIR_TABULEIRO                                [ ] = "=destruirtabuleiro"        ;
#ifdef _DEBUG
    static const char DETURPA                                           [ ] = "=deturpa"     ;
    static const char VERIFICA                                          [ ] = "=verifica" ;
#endif


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_TAB   10
#define DIM_VALOR     100

LIS_tppLista tabu;


/***** Prottotipos das funções encapuladas no modulo *****/

int converteCoordenadaCharParaInt(char coordYChar);
int diminui1DeX(int coordX);


/*****  Codigo das funções exportadas pelo modulo  *****/


/***********************************************************************
*
*  $FC Funcão: TTAB &Testar tabuleiro
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
          CondRetEsp = -1  ,acao,numErrosEsperados,numErrosEncontrados = 0;

      TST_tpCondRet CondRet;

      char   StringDado[  DIM_VALOR ],StringDado2[  DIM_VALOR  ] ;

	  int x, xf,coordYInt,coordYInt2,iterador;
	  char y, yf, cor, id,corLida,idLido;

	  LIS_tppLista ameacas;


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

			  #ifdef _DEBUG
			CED_InicializarIteradorEspacos();
				while( CED_ExisteEspacoCorrente() != 0)
				{
					CED_ExcluirEspacoCorrente();
				}
			#endif
            CondRet = TAB_CriaLL(&tabu);
			printf("%d\n",CondRet);

            return TST_CompararPonteiroNulo( 1 , tabu , "Erro em ponteiro de nova lista."  ) ;

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

            CondRet = TAB_InserirPeca(tabu, x, coordYInt, cor,id);


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

            CondRet = TAB_ObterPeca(tabu, x, coordYInt, &cor,&id);
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

            CondRet = TAB_RetirarPeca(tabu, x, coordYInt);

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
           CondRet = TAB_MoverPeca(tabu, x, coordYInt, xf, coordYInt2);

            return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao mover uma peca" );

         } /* fim ativa: Move Peca */

		 /* ObterListaAmeacantes */

         else if ( strcmp( ComandoTeste , OBTER_LISTA_AMEACANTES) == 0 )
         {

            numLidos = LER_LerParametros( "ici" , &x, &y,&CondRetEsp) ;

            if ( numLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

			//coordX = diminui1DeX(x);

			coordYInt = converteCoordenadaCharParaInt(y);

            CondRet = TAB_ObterListaAmeacantes(tabu, x, coordYInt, &ameacas);

           
            return TST_CompararPonteiroNulo( CondRetEsp , ameacas,
               "Erro em ponteiro de lista de ameacantes."  ) ;

         } /* fim ativa: ObterListaAmeacantes */

		 /* ObterListaAmeacados */

         else if ( strcmp( ComandoTeste , OBTER_LISTA_AMEACADOS) == 0 )
         {

            numLidos = LER_LerParametros( "ici" , &x,&y, &CondRetEsp) ;

            if (numLidos != 3)
            {
               return TST_CondRetParm ;
            } /* if */

			//coordX = diminui1DeX(x);

			coordYInt = converteCoordenadaCharParaInt(y);

           CondRet = TAB_ObterListaAmeacantes(tabu, x, coordYInt, &ameacas);

            return TST_CompararPonteiroNulo( CondRetEsp , ameacas,
               "Erro em ponteiro de lista de ameacados."  ) ;

         } /* fim ativa: ObterListaAmeacados */


      /* Testar Destruir Tabuleiro */

         else if ( strcmp( ComandoTeste , DESTRUIR_TABULEIRO ) == 0 )
         {
            numLidos = LER_LerParametros( "i" , &CondRetEsp) ;

            if ( numLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */
			 
			 CondRet = TAB_DestruirTabuleiro(tabu);

			 #ifdef _DEBUG
			CED_InicializarIteradorEspacos();
				while( CED_ExisteEspacoCorrente() != 0)
				{
					CED_ExcluirEspacoCorrente();
				}
			#endif


            return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao destruir um tabuleiro" );

         } /* fim ativa: Testar Destruir tabuleiro */
       #ifdef _DEBUG
         /* Deturpar Tabuleiro */
         else if(strcmp( ComandoTeste , DETURPA ) == 0) {
             numLidos = LER_LerParametros("i",&acao);
             if (numLidos != 1) {
                 return TST_CondRetParm ;
             }
             TAB_Deturpa(tabu,acao);
			 return  TST_CondRetOK;
         }
       
         /*Testar Verificação do Tabuleiro */
         else if(strcmp( ComandoTeste , VERIFICA ) == 0) {
             numLidos = LER_LerParametros("i",&numErrosEsperados);
             if (numLidos != 1) {
                 return TST_CondRetParm ;
             }
			 numErrosEncontrados = 0;
             TAB_VerificaTabuleiro(tabu,&numErrosEncontrados);
             return TST_CompararInt(numErrosEsperados, numErrosEncontrados,"Numeros de erros esperados é distinto do numero encontrado");
         }
       #endif
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
