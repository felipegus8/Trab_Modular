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
*/

static const char EFETUAR_JOGADA             							[ ] = "=efetuarjogada" ;
static const char CRIA_JUIZ          	                                [ ] = "=criajuiz"   ;
static const char COMECAR_JOGO              	                        [ ] = "=comecarjogo"      ;
static const char ASSASINAR_JUIZ               							[ ] = "=assasinarjuiz"        ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1
#define DIM_VT_JOG   10

ptJudge juiz;
ptJogador JogadorA, JogadorB;
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
*	comecarjogo     //Comletar
*	assasinarjuiz   CondRetEsp

***********************************************************************/
 //AE: Recebe um comando defido pelo modulo
TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	 int inxPeca  = -1 , numLidos   = -1 , CondRetEsp = -1  ;
	 TST_tpCondRet CondRet ;
     char   StringDado[  DIM_VALOR ],StringDado2[DIM_VALOR] ;
	 char idPeca,corPeca;
     char * pDado ;
     int ValEsp = -1 ;
     int i ;
     int numElem = -1 ;
     void * elemento;
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

            return TST_CompararPonteiroNulo( 1 , juiz , "Erro em criar juiz"  ) ;

       }/*Fim ativa: Efetuar Jogada */
	   //Inicio da Efetuar jogada
	   else if ( strcmp( ComandoTeste , EFETUAR_JOGADA) == 0 )
         {

            numLidos = LER_LerParametros( "iciiiii" ,&juiz, &corDaVez, &xi, &yi, &xf, &yf, &CondRetEsp) ; //ptJudge j, char corDaVez,int posIniX,int posIniY,int posFimX,int posFimY

            if (  numLidos != 7 )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,"Erro ao efetuar Jogada" );
         }//Fim da efetuar jogada
	   	   else if ( strcmp( ComandoTeste , ASSASINAR_JUIZ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,  &CondRetEsp) ;

            if (  numLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

             return TST_CompararPonteiroNulo( 1 , juiz , "Erro em assasinar juiz"  ) ;
         }

}