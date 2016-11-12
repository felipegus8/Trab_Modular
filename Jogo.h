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
    
    JOG_CondRetComeu
    
} JOG_tpCondRet ;

#include "lista.h"
#include "peca.h"
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



JOG_tpCondRet JOG_CriaJuiz(ptJudge *j,ptJogador a,ptJogador b,ptTabuleiro tabu);

JOG_tpCondRet JOG_ComecarJogo(ptJudge j,ptJogador a,ptJogador b,char *nomeA,char *nomeB,ptTabuleiro tabu,int (*InserirPecas)(TAB_tpCondRet(*InserirNoTab)(ptTabuleiro,int x,int y,char cor,char id)));


JOG_tpCondRet JOG_AssasinarJuiz(ptJudge j);



#endif