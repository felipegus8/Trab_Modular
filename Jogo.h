#if ! defined( Jogo_ )
#define Jogo_

/***************************************************************************
 *
 *  $MCD MÛdulo de definiÁ„o: JOG  Jogo
 *
 *  Arquivo gerado:              Jogo.h
 *  Letras identificadoras:      JOG
 *
 *
 *  $ED DescriÁ„o do mÛdulo
 *     A implementaÁ„o do mÛdulo jogo diz respeito de como deve se estruturar o as regras execuÁ„o do jogo
 *
 *  Autores: Felipe Viberti,Luis Claudio e Victor Nogueira
 *
 *  $HA HistÛrico de evoluÁ„o:
 *     Vers„o  Autores                                           Data          ObservaÁıes
 *     1       Felipe Viberti,Luis Claudio e Victor Nogueira   10/Nov/2016  inÌcio desenvolvimento
 *
 ***************************************************************************/

/***********************************************************************
 *
 *  $TC Tipo de dados: JOG CondiÁıes de retorno
 *
 *
 *  $ED DescriÁ„o do tipo
 *     CondiÁıes de retorno das funÁıes do Jogo.
 *
 ***********************************************************************/
typedef enum {
    
    JOG_CondRetOK ,
    /* Concluiu corretamente */
    
    JOG_CondRetFaltouMemoria ,
    /* Faltou memÛria ao tentar criar uma lista dentro da casa*/
    
    JOG_CondRetCorErrada,
    
    JOG_CondRetMovimentoIrregular,
    
    JOG_CondRetComeu,
    
    JOG_CondRetCheckMate,
    
    JOG_CondRetNoCheckMate,
    
    JOG_CondRetCheck,
    
    JOG_CondRetTabuleiroNulo
    
} JOG_tpCondRet ;

#include "Tabuleiro.h"

typedef struct jogador* ptJogador;
typedef struct juiz* ptJudge;
/***********************************************************************
 *  $FC FunÁ„o: JOG &Pede Nomes Jogadores
 *
 *  $ED DescriÁ„o da funÁ„o
 *     Pede como input o nome de dois jogadores para preencher o vetor de nomes
 *
 *  $EP Par‚metros
 *    Duas structs jogadores
 *
 *  $FV Valor retornado
 *    Se executou corretamente retona Ok.
 *    Se houve algum problema por falta de memÛria retorna Faltou MemÛria.
 
 ***********************************************************************/


JOG_tpCondRet JOG_EfetuarJogada(ptJudge j, char corDaVez,int posIniX,int posIniY,int posFimX,int posFimY);



JOG_tpCondRet JOG_CriaJuiz(ptJudge *j,char nomeJogadorA[30], char nomeJogadorB[30]);

JOG_tpCondRet JOG_ComecarJogo(ptJudge j,JOG_tpCondRet (*InserirPecas)(TAB_tpCondRet(*InserirNoTab)(ptTabuleiro,int x,int y,char cor,char id),ptJudge j));


JOG_tpCondRet JOG_AssasinarJuiz(ptJudge j);

JOG_tpCondRet JOG_ObtemTabuleiro(ptJudge j,ptTabuleiro *tabu);
JOG_tpCondRet JOG_GeraMatrizTabuleiro(ptJudge j,char matriz[8][8][2]);

JOG_tpCondRet JOG_CriaJogador(ptJogador *j,char *nome,char cor);

JOG_tpCondRet JOG_RetornoNomeJogador1(ptJudge j,char nome[30]);

JOG_tpCondRet JOG_RetornoNomeJogador2(ptJudge j,char nome[30]);

JOG_tpCondRet JOG_DevolveAmeacantes(ptJudge j,char *corAmeacantes,char *idAmeacantes,int *qtdAmeacantes,int x,int y);

JOG_tpCondRet JOG_DevolveAmeacados(ptJudge j,char *corAmeacados,char *idAmeacados,int *qtdAmeacados,int x,int y);

#endif
