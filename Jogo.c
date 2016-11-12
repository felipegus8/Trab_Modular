/***************************************************************************
 *  $MCI Módulo de implementação: Jogo
 *  Arquivo gerado:              Jogo.c
 *  Letras identificadoras:      JOG
 *
 *  Autores: Felipe Viberti,Luis Claudio e Victor Nogueira
 *
 *  $HA Histórico de evolução:
 *     Versão  Autores                                           Data          Observações
 *     1       Felipe Viberti,Luis Claudio e Victor Nogueira   29/out/2016     início desenvolvimento
 *
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "jogo.h"

TAB_tpCondRet condRetTab;

typedef struct jogador
{
    char nome[30];
    char cor;
}Jogador;

typedef struct juiz {
    ptJogador jogador1;
    ptJogador jogador2;
    ptTabuleiro tabu;
    int vez;
}Judge;


JOG_tpCondRet JOG_CriaJuiz(ptJudge *j,ptJogador a,ptJogador b) {
    ptJudge novo;
    novo = (Judge *) malloc(sizeof(Judge));
    if(novo == NULL) {
        return JOG_CondRetFaltouMemoria;
    }
    novo->jogador1 = a;
    novo->jogador2 = b;
    TAB_CriaTabuleiro(&(novo->tabu));
    *j = novo;
    return  JOG_CondRetOK;
}

JOG_tpCondRet JOG_EfetuarJogada(ptJudge j, char corDaVez,int posIniX,int posIniY,int posFimX,int posFimY) {
    char cor,id;
    TAB_ObterPeca(j->tabu,posIniX , posIniY, &cor, &id);
    if(cor != corDaVez) {
        return JOG_CondRetCorErrada;
    }
    condRetTab = TAB_MoverPeca(j->tabu, posIniX, posIniY, posFimX, posFimY);
    if(condRetTab == 0) {
        return JOG_CondRetOK;
    } else if (condRetTab == 2) {
        return JOG_CondRetComeu;
    }
    return JOG_CondRetMovimentoIrregular;
}




JOG_tpCondRet JOG_ComecarJogo(ptJudge j,ptJogador a,ptJogador b,char *nomeA,char *nomeB,int (*InserirPecas)(TAB_tpCondRet(*InserirNoTab)(ptTabuleiro tabu,int x,int y,char cor,char id))) {
    
    a->cor = 'B';
    b->cor = 'P';
    if(strlen(nomeA)<30) {
        strcpy(a->nome, nomeA);
    } else {
        return JOG_CondRetFaltouMemoria;
    }
    if(strlen(nomeB)<30) {
        strcpy(b->nome, nomeB);
    } else {
        return JOG_CondRetFaltouMemoria;
    }
    JOG_CriaJuiz(&j, a, b);
    InserirPecas(TAB_InserirPeca);
    
    return JOG_CondRetOK;
}

JOG_tpCondRet JOG_AssasinarJuiz(ptJudge j) {
    TAB_DestruirTabuleiro(j->tabu);
    free(j->jogador1);
    free(j->jogador2);
    free(j);
    return JOG_CondRetOK;
}



