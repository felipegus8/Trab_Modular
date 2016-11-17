/***************************************************************************
*  $MCI MÛdulo de implementaÁ„o: TJOG Teste Jogo
*
*  Arquivo gerado:              TesteJogo.c
*  Letras identificadoras:      TJOG
*
*  Autores: Felipe Viberti,Luis Claudio e Victor Nogueira
*
*  $HA HistÛrico de evoluÁ„o:
*     Vers„o  Autores                                           Data          ObservaÁıes
*     1       Felipe Viberti,Luis Claudio e Victor Nogueira   13/Nov/2016  inÌcio desenvolvimento
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

/* funções encapsuladas no testejogo */
void inserirPecasPadrao(TAB_tpCondRet(*InserirNoTab)(ptTabuleiro tabu,int x,int y,char cor,char id),ptJudge j) ;
void inserirPecasNovas(TAB_tpCondRet(*InserirNoTab)(ptTabuleiro tabu,int x,int y,char cor,char id),ptJudge j) ;
/******************************************************************************************************************/
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
static const char COMECAR_JOGO_PADRAO              	                        [ ] = "=comecarjogopadrao"      ;
static const char COMECAR_JOGO_NOVAS              	                        [ ] = "=comecarjogonovas"      ;
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
#define DIM_VALOR     30


/***********************************************************************
*
*  $FC Func„o: TJOG &Testar Jogo
*
*  $ED DescriÁ„oo da funÁ„o
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
     char   StringDado[  DIM_VALOR ],StringDado2[DIM_VALOR],corRecebida[16],idRecebido[16],corDada[16],idDado[16],cor ;
     int ValEsp = -1 ;
     int x,y ;
     int numElem = -1 ;
	 ptTabuleiro tabu;
	 ptJudge j;
	 ptJogador jo;
	 int xi,  yi, xf, yf;
     StringDado[ 0 ] = 0,StringDado2[0] = 0;
	 idDado[ 0 ] = 0;
	 corDada[ 0 ] = 0;
	 

	   if ( strcmp( ComandoTeste , CRIA_JUIZ) == 0 )
	   {
		   numLidos = LER_LerParametros( "iss", &CondRetEsp,StringDado,StringDado2) ;
		   if ( numLidos != 3 )
            {
               return TST_CondRetParm ;
            }
		   CondRet = JOG_CriaJuiz(&j, StringDado, StringDado2);

			return TST_CompararInt( CondRetEsp , CondRet ,"Erro em criar juiz" );
       }/*Fim ativa: Efetuar Jogada */

	   //Inicio da Efetuar jogada
	   
	   else if ( strcmp( ComandoTeste , EFETUAR_JOGADA) == 0 )
         {

            numLidos = LER_LerParametros( "ciiiii" , &cor, &xi, &yi, &xf, &yf, &CondRetEsp) ; //ptJudge j, char corDaVez,int posIniX,int posIniY,int posFimX,int posFimY

            if (  numLidos != 6 )
            {
               return TST_CondRetParm ;
            } /* if */
			CondRet = JOG_EfetuarJogada(j, cor, xi, yi, xf, yf);
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

			CondRet = JOG_AssasinarJuiz(j);
             return TST_CompararInt( CondRetEsp , CondRet ,"Assasinar Juiz" );
         }//Fim de assasinar Juiz
	   //Inicio de começar Jogo com peças padrão
		else if ( strcmp( ComandoTeste , COMECAR_JOGO_PADRAO) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &CondRetEsp); 

            if (  numLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRet =  JOG_ComecarJogo(j, inserirPecasPadrao);
            return TST_CompararInt( CondRetEsp , CondRet ,"Erro ao ComeÁarJogo" );
         }//Fim de começar jogo com peças padrão
        //Inicio de começar Jogo com peças novas
        else if ( strcmp( ComandoTeste , COMECAR_JOGO_NOVAS) == 0 )
        {
            
            numLidos = LER_LerParametros( "i" , &CondRetEsp);
            
            if (  numLidos != 1 )
            {
                return TST_CondRetParm ;
            } /* if */
            
            CondRet =  JOG_ComecarJogo(j, inserirPecasNovas);
            return TST_CompararInt( CondRetEsp , CondRet ,"Erro ao ComeÁarJogo" );
        }//Fim de começar jogo com peças novas
		   //Inicio obtem tabuleiro 
		else if ( strcmp( ComandoTeste , OBTEM_TABULEIRO) == 0 )
         {

            numLidos = LER_LerParametros( "i", &CondRetEsp); 

            if (  numLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRet = JOG_ObtemTabuleiro(j,&tabu);
            return TST_CompararInt( CondRetEsp , CondRet ,"Erro em obter tabuleiro" );
         }//Fim de obtem tabuleiro
		//Inicio cria jogador
		
		else if(strcmp(ComandoTeste, CRIA_JOGADOR) == 0) {
		    numLidos = LER_LerParametros( "isc", &CondRetEsp,StringDado,&cor); 
			if(numLidos != 3) {
			   return TST_CondRetParm;
			}
			CondRet = JOG_CriaJogador(&jo,StringDado,cor);
			return TST_CompararInt(CondRetEsp, CondRet, "Erro ao criar jogador" );
		}//Fim cria jogador
		//Inicio retorna nome jogador 1
		
		else if(strcmp(ComandoTeste, RETORNO_NOME_JOGADOR_1) == 0) {
		    numLidos = LER_LerParametros("s",StringDado);
			if(numLidos != 1) {
			    return TST_CondRetParm;
			}
			CondRet = JOG_RetornoNomeJogador1(j,StringDado2);
			return TST_CompararString( StringDado , StringDado2 ,"Valor Encontrado diferente do esperado." ) ;
		}//FIM retorna nome jogador 1
		//Inicio retorna nome jogador 2
		
		else if(strcmp(ComandoTeste, RETORNO_NOME_JOGADOR_2) == 0) {
		    numLidos = LER_LerParametros("s",StringDado);
			if(numLidos != 1) {
			    return TST_CondRetParm;
			}
			CondRet = JOG_RetornoNomeJogador2(j,StringDado2);
			return TST_CompararString( StringDado , StringDado2 ,"Valor Encontrado diferente do esperado." ) ;
		}//Fim retorna nome jogador 2
		//Inicio devolve ameacantes
		
		else if(strcmp(ComandoTeste, DEVOLVE_AMEACANTES)) {
		     numLidos = LER_LerParametros("siii",idDado,&ValEsp,&x,&y);
			 if(numLidos != 3) {
			    return TST_CondRetParm;
			 }
			 CondRet = JOG_DevolveAmeacantes(j,corRecebida,idRecebido,&numElem,x,y);
			 if(numElem != ValEsp) {
			     return TST_CompararInt(numElem, ValEsp, "Quantidade de elementos ameacantes È diferente da quantia recebida " );
			 }
			 return TST_CompararString( idDado , idRecebido ,"Valor Encontrado diferente do esperado." ) ;
		}//Fim devolve ameacantes
		//Inicio devolve ameacados
		
		else if(strcmp(ComandoTeste, DEVOLVE_AMEACADOS)) {
		     numLidos = LER_LerParametros("siii",idDado,&ValEsp,&x,&y);
			 if(numLidos != 3) {
			    return TST_CondRetParm;
			 }
			 CondRet = JOG_DevolveAmeacados(j,corRecebida,idRecebido,&numElem,x,y);
			 if(numElem != ValEsp) {
			     return TST_CompararInt(numElem, ValEsp, "Quantidade de elementos ameacantes È diferente da quantia recebida " );
			 }
			 return TST_CompararString( idDado , idRecebido ,"Valor Encontrado diferente do esperado." ) ;
		}//Fim devolve ameacados
      return TST_CondRetNaoConhec ;
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

/* Inicio funcoes encapsuladas no testejogo*/

void inserirPecasPadrao(TAB_tpCondRet(*InserirNoTab)(ptTabuleiro tabu,int x,int y,char cor,char id),ptJudge j) {
    ptTabuleiro tabu;
    /*
    do {
        printf("Entre com a identidade da peÁa\n");
        scanf(" %c",&id);
        printf("id peÁa: %d\n",id);
        printf("Entre com a cor da peÁa\n");
        scanf(" %c",&cor);
        printf("Entre com a coordenada X da peÁa\n");
        scanf(" %c",&x);
        printf("Entre com a coordenada Y da peÁa\n");
        scanf(" %d",&y);
        xi = converteCharParaInt(x);
        printf("convertido: %d\n",xi);
        JOG_ObtemTabuleiro(j, &tabu);
        y--;
        InserirNoTab(tabu, xi, y, cor, id);
        printf("se quiser continuar inserindo digite 1\n");
        scanf("%d",&continuar);
    } while (continuar == 1);
    */
     
    JOG_ObtemTabuleiro(j, &tabu);
    /*
    InserirNoTab(tabu,1,6,'B','R');
    InserirNoTab(tabu,2,2,'P','T');
    InserirNoTab(tabu,3,1,'P','D');
    InserirNoTab(tabu,4,4,'B','T');
     */
    //Insere peÁas brancas
    InserirNoTab(tabu,0,0,'B','T');
    InserirNoTab(tabu,1,0,'B','C');
    InserirNoTab(tabu,2,0,'B','B');
    InserirNoTab(tabu,3,0,'B','D');
    InserirNoTab(tabu,4,0,'B','R');
    InserirNoTab(tabu,5,0,'B','B');
    InserirNoTab(tabu,6,0,'B','C');
    InserirNoTab(tabu,7,0,'B','T');
    InserirNoTab(tabu,0,1,'B','P');
    InserirNoTab(tabu,1,1,'B','P');
    InserirNoTab(tabu,2,1,'B','P');
    InserirNoTab(tabu,3,1,'B','P');
    InserirNoTab(tabu,4,1,'B','P');
    InserirNoTab(tabu,5,1,'B','P');
    InserirNoTab(tabu,6,1,'B','P');
    InserirNoTab(tabu,7,1,'B','P');
    //Insere peÁas pretas
    InserirNoTab(tabu,0,7,'P','T');
    InserirNoTab(tabu,1,7,'P','C');
    InserirNoTab(tabu,2,7,'P','B');
    InserirNoTab(tabu,3,7,'P','D');
    InserirNoTab(tabu,4,7,'P','R');
    InserirNoTab(tabu,5,7,'P','B');
    InserirNoTab(tabu,6,7,'P','C');
    InserirNoTab(tabu,7,7,'P','T');
    InserirNoTab(tabu,0,6,'P','P');
    InserirNoTab(tabu,1,6,'P','P');
    InserirNoTab(tabu,2,6,'P','P');
    InserirNoTab(tabu,3,6,'P','P');
    InserirNoTab(tabu,4,6,'P','P');
    InserirNoTab(tabu,5,6,'P','P');
    InserirNoTab(tabu,6,6,'P','P');
    InserirNoTab(tabu,7,6,'P','P');
}

void inserirPecasNovas(TAB_tpCondRet(*InserirNoTab)(ptTabuleiro tabu,int x,int y,char cor,char id),ptJudge j) {
    ptTabuleiro tabu;
    /*
     do {
     printf("Entre com a identidade da peça\n");
     scanf(" %c",&id);
     printf("id peça: %d\n",id);
     printf("Entre com a cor da peça\n");
     scanf(" %c",&cor);
     printf("Entre com a coordenada X da peça\n");
     scanf(" %c",&x);
     printf("Entre com a coordenada Y da peça\n");
     scanf(" %d",&y);
     xi = converteCharParaInt(x);
     printf("convertido: %d\n",xi);
     JOG_ObtemTabuleiro(j, &tabu);
     y--;
     InserirNoTab(tabu, xi, y, cor, id);
     printf("se quiser continuar inserindo digite 1\n");
     scanf("%d",&continuar);
     } while (continuar == 1);
     */
    
    JOG_ObtemTabuleiro(j, &tabu);
    /*
     InserirNoTab(tabu,1,6,'B','R');
     InserirNoTab(tabu,2,2,'P','T');
     InserirNoTab(tabu,3,1,'P','D');
     InserirNoTab(tabu,4,4,'B','T');
     */
    //Insere peças brancas
    InserirNoTab(tabu,0,0,'B','T');
    InserirNoTab(tabu,1,0,'B','C');
    InserirNoTab(tabu,2,0,'B','B');
    InserirNoTab(tabu,3,0,'B','D');
    InserirNoTab(tabu,4,0,'B','R');
    InserirNoTab(tabu,5,0,'B','B');
    InserirNoTab(tabu,6,0,'B','C');
    InserirNoTab(tabu,7,0,'B','T');
    InserirNoTab(tabu,0,1,'B','P');
    InserirNoTab(tabu,1,1,'B','P');
    InserirNoTab(tabu,2,1,'B','P');
    InserirNoTab(tabu,3,1,'B','X');
    InserirNoTab(tabu,4,1,'B','P');
    InserirNoTab(tabu,5,1,'B','P');
    InserirNoTab(tabu,6,1,'B','P');
    InserirNoTab(tabu,7,1,'B','P');
    //Insere peças pretas
    InserirNoTab(tabu,0,7,'P','T');
    InserirNoTab(tabu,1,7,'P','C');
    InserirNoTab(tabu,2,7,'P','B');
    InserirNoTab(tabu,3,7,'P','D');
    InserirNoTab(tabu,4,7,'P','R');
    InserirNoTab(tabu,5,7,'P','B');
    InserirNoTab(tabu,6,7,'P','C');
    InserirNoTab(tabu,7,7,'P','T');
    InserirNoTab(tabu,0,6,'P','P');
    InserirNoTab(tabu,1,6,'P','P');
    InserirNoTab(tabu,2,6,'P','P');
    InserirNoTab(tabu,3,6,'P','P');
    InserirNoTab(tabu,4,6,'P','P');
    InserirNoTab(tabu,5,6,'P','P');
    InserirNoTab(tabu,6,6,'P','P');
    InserirNoTab(tabu,7,6,'P','P');
}


/*Fim funÁıes encapsuladas no testejogo */
/*Fim testejogo */