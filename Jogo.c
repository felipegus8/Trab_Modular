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
    int xReiBranco;
    int yReiBranco;
    int xReiPreto;
    int yReiPreto;
    int vez;
}Judge;


JOG_tpCondRet JOG_CriaJogador(ptJogador *j,char *nome,char cor) {
    ptJogador novo;
    novo = (Jogador *) malloc(sizeof(Jogador));
    if(novo == NULL) {
        return JOG_CondRetFaltouMemoria;
    }
    strcpy(novo->nome, nome);
    novo->cor = cor;
    *j = novo;
    printf("jogador: %d\n",novo);
    return JOG_CondRetOK;
}

JOG_tpCondRet JOG_ObtemTabuleiro(ptJudge j,ptTabuleiro *tabu) {
    if(j->tabu == NULL) {
        return JOG_CondRetFaltouMemoria;
    }
    *tabu = j->tabu;
    return JOG_CondRetOK;
}

JOG_tpCondRet JOG_CriaJuiz(ptJudge *j,ptJogador a,ptJogador b) {
    ptJudge novo;
    novo = (Judge *) malloc(sizeof(Judge));
    if(novo == NULL) {
        return JOG_CondRetFaltouMemoria;
    }
    novo->jogador1 = a;
    novo->jogador2 = b;
    TAB_CriaTabuleiro(&(novo->tabu));
    novo->xReiBranco = 1;
    novo->yReiBranco = 6;
    novo->xReiPreto = 4;
    novo->yReiPreto = 6;
    *j = novo;
    return  JOG_CondRetOK;
}

JOG_tpCondRet JOG_AvaliaCheck(ptJudge j,int corRei) {
    Peca *ameacante;
    TAB_tpCondRet retCheckMate;
    int xAmeacante,yAmeacante;
    char corAmeacante,idAmeacante;
    LIS_tppLista ameacantes;
    TAB_ObterListaAmeacantes(j->tabu, j->xReiBranco, j->yReiBranco, &ameacantes);
    LIS_ObterNo(ameacantes, (void **)&ameacante);
    PEC_RetornaCor(ameacante, &corAmeacante);
    PEC_RetornaId(ameacante, &idAmeacante);
    if(corRei == 'B') {
        TAB_AchaPecaCheck(j->tabu, corAmeacante, idAmeacante, &xAmeacante, &yAmeacante, j->xReiBranco, j->yReiBranco);retCheckMate = TAB_VerificaCheckMate(j->tabu, j->xReiBranco, j->yReiBranco, xAmeacante, yAmeacante);
    } else {
        TAB_AchaPecaCheck(j->tabu, corAmeacante, idAmeacante, &xAmeacante, &yAmeacante, j->xReiPreto, j->yReiPreto);
        retCheckMate = TAB_VerificaCheckMate(j->tabu, j->xReiBranco, j->yReiBranco, xAmeacante, yAmeacante);
    }
    if (retCheckMate == TAB_CondRetCheckMate) {
        return JOG_CondRetCheckMate;
    }
    return JOG_CondRetNoCheckMate;
    
}

JOG_tpCondRet JOG_EfetuarJogada(ptJudge j, char corDaVez,int posIniX,int posIniY,int posFimX,int posFimY) {
    char cor,id;
    int x,y;
    TAB_tpCondRet retCheck;
    JOG_tpCondRet jogCheckMate;
    LIS_tppLista lis;
    TAB_ObterPeca(j->tabu,posIniX , posIniY, &cor, &id);
    if(cor != corDaVez) {
        printf("cor: %c e da vez: %c\n",cor,corDaVez);
        return JOG_CondRetCorErrada;
    }
    condRetTab = TAB_MoverPeca(j->tabu, posIniX, posIniY, posFimX, posFimY);
    if(condRetTab != 7) {
        if(id == 'R') {
            if(cor == 'B') {
                j->xReiBranco = posFimX;
                j->yReiBranco = posFimY;
            } else  {
                j->xReiPreto = posFimX;
                j->yReiPreto = posFimY;
            }
        }
        retCheck = TAB_VerificaCheck(j->tabu, j->xReiBranco, j->yReiBranco);
        printf("check: %d\n",retCheck);
        if(retCheck == TAB_CondRetCheck) {
            printf("passou pelo check\n");
            jogCheckMate = JOG_AvaliaCheck(j,'B');
            if (jogCheckMate == JOG_CondRetCheckMate) {
                printf("passou pelo check mate\n");
                return jogCheckMate;
            }
        }
        
        retCheck = TAB_VerificaCheck(j->tabu, j->xReiPreto, j->yReiPreto);
        if(retCheck == TAB_CondRetCheck) {
            jogCheckMate = JOG_AvaliaCheck(j,'P');
            printf("%d\n",jogCheckMate);
            if (jogCheckMate == JOG_CondRetCheckMate) {
                return jogCheckMate;
            }
        }
        
        
        
        
        if(condRetTab == JOG_CondRetOK) {
            return JOG_CondRetOK;
        } else {
            return JOG_CondRetComeu;
        }
    }
    
        
    
    return JOG_CondRetMovimentoIrregular;
}

JOG_tpCondRet JOG_RetornoNomeJogador1(ptJudge j,char nome[30]) {
    strcpy(nome, j->jogador1->nome);
    return JOG_CondRetOK;
}

JOG_tpCondRet JOG_RetornoNomeJogador2(ptJudge j,char nome[30]) {
    strcpy(nome, j->jogador2->nome);
    return JOG_CondRetOK;
}

JOG_tpCondRet JOG_GeraMatrizTabuleiro(ptJudge j,char matriz[8][8][2]) {
    int x,y;
    char cor,id;
    for (x=0; x<8; x++) {
        for (y=0; y<8; y++) {
            TAB_ObterPeca(j->tabu, x, y, &cor, &id);
            //printf("x: %d\n",x);
            //printf("y: %d\n",y);
            printf("%c e %c\n",cor,id);
            matriz[x][y][0] = id;
            matriz[x][y][1] = cor;
            printf("cor: %c e id: %c\n",cor,id);
        }
    }
    return JOG_CondRetOK;
}

JOG_tpCondRet JOG_ComecarJogo(ptJudge j,JOG_tpCondRet (*InserirPecas)(TAB_tpCondRet(*InserirNoTab)(ptTabuleiro tabu,int x,int y,char cor,char id),ptJudge j)) {
    JOG_tpCondRet ret;
    char cor2,id2;
    int i,k;

    InserirPecas(TAB_InserirPeca,j);
    
    return JOG_CondRetOK;
}

JOG_tpCondRet JOG_DevolveAmeacantes(ptJudge j,char *corAmeacantes,char *idAmeacantes,int *qtdAmeacantes,int x,int y) {
    LIS_tppLista ameacantes;
    Peca *ameacante;
    int numElem,i;
    printf("x: %d e y: %d\n",x,y);
    TAB_ObterListaAmeacantes(j->tabu, x, y, &ameacantes);
    LIS_RetornaNumElementos(ameacantes, &numElem);
    *qtdAmeacantes = numElem;
    IrInicioLista(ameacantes);
    for (i=0; i<numElem; i++) {
        LIS_ObterNo(ameacantes, (void **)&ameacante);
        PEC_RetornaCor(ameacante, &corAmeacantes[i]);
        PEC_RetornaId(ameacante, &idAmeacantes[i]);
        printf("cor: %c e id: %c\n",corAmeacantes[i],idAmeacantes[i]);
        LIS_IrProx(ameacantes);
    }
    return JOG_CondRetOK;
}

JOG_tpCondRet JOG_DevolveAmeacados(ptJudge j,char *corAmeacados,char *idAmeacados,int *qtdAmeacados,int x,int y) {
    LIS_tppLista ameacados;
    Peca *ameacado;
    int numElem,i;
    printf("x: %d e y: %d\n",x,y);
    TAB_ObterListaAmeacados(j->tabu, x, y, &ameacados);
    LIS_RetornaNumElementos(ameacados, &numElem);
    *qtdAmeacados = numElem;
    IrInicioLista(ameacados);
    for (i=0; i<numElem; i++) {
        LIS_ObterNo(ameacados, (void **)&ameacado);
        PEC_RetornaCor(ameacado, &corAmeacados[i]);
        PEC_RetornaId(ameacado, &idAmeacados[i]);
        printf("cor: %c e id: %c\n",corAmeacados[i],idAmeacados[i]);
        LIS_IrProx(ameacados);
    }
    return JOG_CondRetOK;
}


JOG_tpCondRet JOG_AssasinarJuiz(ptJudge j) {
    TAB_DestruirTabuleiro(j->tabu);
    free(j->jogador1);
    free(j->jogador2);
    free(j);
    return JOG_CondRetOK;
}



