/***************************************************************************
*  $MCI Módulo de implementação: TJOG Teste Jogo
*
*  Arquivo gerado:              TesteJogo.c
*  Letras identificadoras:      TJOG
*
*  Autores: Felipe Viberti,Luis Claudio e Victor Nogueira
*
*  $HA Histórico de evolução:
*     Versão  Autores                                           Data          Observações
*     1       Felipe Viberti,Luis Claudio e Victor Nogueira   13/Nov/2016  início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>
#include    <stdlib.h>

#include    "Generico.h"
#include    "LerParm.h"

#include    "Jogo.h"
#include    "TST_ESPC.h"

/*
JOG_tpCondRet JOG_EfetuarJogada(ptJudge j, char corDaVez,int posIniX,int posIniY,int posFimX,int posFimY);
JOG_tpCondRet JOG_CriaJuiz(ptJudge *j,ptJogador a,ptJogador b);
JOG_tpCondRet JOG_ComecarJogo(ptJudge j,ptJogador a,ptJogador b,char *nomeA,char *nomeB,int (*InserirPecas)(TAB_tpCondRet(*InserirNoTab)(ptTabuleiro,int x,int y,char cor,char id)));
JOG_tpCondRet JOG_AssasinarJuiz(ptJudge j);

JOG_tpCondRet JOG_ObtemTabuleiro(ptJudge j,ptTabuleiro *tabu);

JOG_tpCondRet JOG_GeraMatrizTabuleiro(ptJudge j,char matriz[8][8][2]);

JOG_tpCondRet JOG_CriaJogador(ptJogador *j,char *nome,char cor);

JOG_tpCondRet JOG_RetornoNomeJogador1(ptJudge j,char nome[30]);

JOG_tpCondRet JOG_RetornoNomeJogador2(ptJudge j,char nome[30]);

JOG_tpCondRet JOG_DevolveAmeacantes(ptJudge j,char *corAmeacantes,char *idAmeacantes,int *qtdAmeacantes,int x,int y);

JOG_tpCondRet JOG_DevolveAmeacados(ptJudge j,char *corAmeacados,char *idAmeacados,int *qtdAmeacados,int x,int y);
*/
static const char EFETUAR_JOGADA             							[ ] = "=efetuarjogada" ;
static const char CRIA_JUIZ          	                                [ ] = "=criajuiz"   ;
static const char COMECAR_JOGO              	                        [ ] = "=comecarjogo"      ;
static const char ASSASINAR_JUIZ                						[ ] = "=assasinarjuiz"        ;
static const char OBTEM_TABULEIRO               						[ ] = "=obtemtabuleiro"        ;
static const char GERA_MATRIZ_TABULEIRO              					[ ] = "=geramatriztabuleiro"        ;
static const char CRIA_JOGADOR              							[ ] = "=criajogador"        ;
static const char RETORNO_NOME_JOGADOR_1               					[ ] = "=retornonomejogador1"        ;
static const char RETORNO_NOME_JOGADOR_2               					[ ] = "=retornonomejogador2"        ;
static const char DEVOLVE_AMEACANTES              						[ ] = "=devolveameacantes"        ;
static const char DEVOLVE_AMEACADOS               						[ ] = "=devolveameacados"        ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1
#define DIM_VT_JOG   10

ptJudge juiz;
ptJogador JogadorA, JogadorB;
ptTabuleiro tabu;
//#define DIM_VT_PECA   100
//#define DIM_VALOR     100
/***********************************************************************
*
*  $FC Funcão: TJOG &Testar Jogo
*
*  $ED Descriçãoo da função
*     O jogo controla o gameplay entre os jogadores
*
*     Comandos disponiveis:
*
*	efetuarjogada	 char int int int int CondRetEsp
*	criajuiz		CondRetEsp
*	comecarjogo     //int int int str str CondRetEsp CondRet
*	assasinarjuiz   CondRetEsp

***********************************************************************/
 //AE: Recebe um comando defido pelo modulo
TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	 int numLidos   = -1 , CondRetEsp = -1  ;
	 TST_tpCondRet CondRet ;
     char   StringDado[  DIM_VALOR ],StringDado2[DIM_VALOR], id ;
     int ValEsp = -1 ;
     int i ;
     int numElem = -1 ;
	 int xi,  yi, xf, yf;
     StringDado[ 0 ] = 0,StringDado2[0] = 0;

	   if ( strcmp( ComandoTeste , CRIA_JUIZ) == 0 )
	   {
		   numLidos = LER_LerParametros( "i", &CondRetEsp) ;
		   if ( numLidos != 1 )
            {
               return TST_CondRetParm ;
            } 
		   CondRet = JOG_CriaJuiz(&juiz, JogadorA, JogadorB);
		   printf("%d\n",CondRet);

			return TST_CompararInt( CondRetEsp , CondRet ,"Erro em criar juiz" );
       }/*Fim ativa: Efetuar Jogada */

	   //Inicio da Efetuar jogada
	   else if ( strcmp( ComandoTeste , EFETUAR_JOGADA) == 0 )
         {

            numLidos = LER_LerParametros( "iciiiii" ,&juiz, &corDaVez, &xi, &yi, &xf, &yf, &CondRetEsp) ; //ptJudge j, char corDaVez,int posIniX,int posIniY,int posFimX,int posFimY

            if (  numLidos != 7 )
            {
               return TST_CondRetParm ;
            } /* if */
			CondRet = JOG_EfetuarJogada(juiz, corDaVez, xi, yi, xf, yf, CondRetEsp);
			//JOG_tpCondRet JOG_EfetuarJogada(ptJudge j, char corDaVez,int posIniX,int posIniY,int posFimX,int posFimY);
            return TST_CompararInt( CondRetEsp , CondRet ,"Erro ao efetuar Jogada" );
         }//Fim da efetuar jogada
	   //Inicio da assasinar juiz
	   	   else if ( strcmp( ComandoTeste , ASSASINAR_JUIZ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,  &CondRetEsp) ;

            if (  numLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRet = JOG_AssasinarJuiz(juiz);
			//JOG_tpCondRet JOG_AssasinarJuiz(ptJudge j);
             return TST_CompararInt( CondRetEsp , CondRet ,"Assasinar Juiz" );
         }//Fim de assasinar Juiz
	   //Inicio de começar Jogo
		else if ( strcmp( ComandoTeste , COMECAR_JOGO) == 0 )
         {

            numLidos = LER_LerParametros( "ssi" ,StringDado, StringDado2, &CondRetEsp); 

            if (  numLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRet = JOG_tpCondRet JOG_ComecarJogo(juiz, TAB_InserirPeca(xi, yi, corDaVez, id)
			//JOG_tpCondRet JOG_ComecarJogo(ptJudge j,JOG_tpCondRet (*InserirPecas)(TAB_tpCondRet(*InserirNoTab)(ptTabuleiro,int x,int y,char cor,char id),ptJudge j));
            return TST_CompararInt( CondRetEsp , CondRet ,"Erro ao ComeçarJogo" );
         }//Fim de começar jogo
		   //Inicio obtem tabuleiro 
		else if ( strcmp( ComandoTeste , OBTEM_TABULEIRO) == 0 )
         {

            numLidos = LER_LerParametros( "i", &CondRetEsp); 

            if (  numLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			//JOG_tpCondRet JOG_ObtemTabuleiro(ptJudge j,ptTabuleiro *tabu);
            return TST_CompararInt( CondRetEsp , CondRet ,"Erro em obter tabuleiro" );
         }
		//Fim de obtem tabuleiro
}
/*
JOG_tpCondRet JOG_ObtemTabuleiro(ptJudge j,ptTabuleiro *tabu);

JOG_tpCondRet JOG_GeraMatrizTabuleiro(ptJudge j,char matriz[8][8][2]);

JOG_tpCondRet JOG_CriaJogador(ptJogador *j,char *nome,char cor);

JOG_tpCondRet JOG_RetornoNomeJogador1(ptJudge j,char nome[30]);

JOG_tpCondRet JOG_RetornoNomeJogador2(ptJudge j,char nome[30]);

JOG_tpCondRet JOG_DevolveAmeacantes(ptJudge j,char *corAmeacantes,char *idAmeacantes,int *qtdAmeacantes,int x,int y);

JOG_tpCondRet JOG_DevolveAmeacados(ptJudge j,char *corAmeacados,char *idAmeacados,int *qtdAmeacados,int x,int y);
*/