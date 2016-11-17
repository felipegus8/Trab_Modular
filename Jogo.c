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
    /*Ponteiro para o primeiro jogador associado ao juiz*/
    ptJogador jogador2;
    /*Ponteiro para o segundo jogador associado ao juiz*/
    ptTabuleiro tabu;
    /*Ponteiro para o tabuleiro associado ao juiz*/
    int xReiBranco;
    /*Posição Atual em X do Rei de Cor Branca*/
    int yReiBranco;
    /*Posição Atual em Y do Rei de Cor Branca*/
    int xReiPreto;
    /*Posição Atual em X do Rei de Cor Preta*/
    int yReiPreto;
    /*Posição Atual em Y do Rei de Cor Preta*/
}Judge;

/***** Protótipos das funções encapuladas no módulo *****/
JOG_tpCondRet JOG_AvaliaCheck(ptJudge j,int corRei);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
 *
 *  Função: JOG  &Cria Jogador
 *  ****/
JOG_tpCondRet JOG_CriaJogador(ptJogador *j,char *nome,char cor) {
    ptJogador novo;
    novo = (Jogador *) malloc(sizeof(Jogador));
    if(novo == NULL) {
        return JOG_CondRetFaltouMemoria;
    }
    strcpy(novo->nome, nome);
    novo->cor = cor;
    *j = novo;
    //printf("jogador: %d\n",novo);
    return JOG_CondRetOK;
}/* Fim função: JOG  &Cria Jogador*/

/***************************************************************************
 *
 *  Função: JOG  &Obtem Tabuleiro
 *  ****/
JOG_tpCondRet JOG_ObtemTabuleiro(ptJudge j,ptTabuleiro *tabu) {
    if(j->tabu == NULL) {
        return JOG_CondRetTabuleiroNulo;
    }
    *tabu = j->tabu;
    return JOG_CondRetOK;
}/* Fim função: JOG  &Obtem Tabuleiro*/

/***************************************************************************
 *
 *  Função: JOG  &Cria Juiz
 *  ****/
JOG_tpCondRet JOG_CriaJuiz(ptJudge *j,char nomeJogadorA[30],char nomeJogadorB[30]) {
    ptJudge novo;
    TAB_tpCondRet retTab;
    JOG_tpCondRet retJogo;
    novo = (Judge *) malloc(sizeof(Judge));
    if(novo == NULL) {
        return JOG_CondRetFaltouMemoria;
    }
    retJogo = JOG_CriaJogador(&(novo->jogador1),nomeJogadorA,'B');
    if(retJogo == JOG_CondRetFaltouMemoria) {
        return retJogo;
    }
    retJogo = JOG_CriaJogador(&(novo->jogador2),nomeJogadorB,'P');
    if(retJogo == JOG_CondRetFaltouMemoria) {
        return retJogo;
    }
    retTab = TAB_CriaTabuleiro(&(novo->tabu));
    if(retTab == TAB_CondRetFaltouMemoria) {
        return JOG_CondRetTabuleiroNulo;
    }
    novo->xReiBranco = 4;
    novo->yReiBranco = 0;
    novo->xReiPreto = 4;
    novo->yReiPreto = 7;
    *j = novo;
    return  JOG_CondRetOK;
}/* Fim função: JOG  &Cria Juiz*/


/***************************************************************************
 *
 *  Função: JOG  &Efetuar Jogada
 *  ****/
JOG_tpCondRet JOG_EfetuarJogada(ptJudge j, char corDaVez,int posIniX,int posIniY,int posFimX,int posFimY) {
    char cor,id;
    TAB_tpCondRet retCheck;
    JOG_tpCondRet jogCheckMate;
    TAB_ObterPeca(j->tabu,posIniX , posIniY, &cor, &id);
    if(cor != corDaVez) {
        //printf("cor: %c e da vez: %c\n",cor,corDaVez);
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
        
        if(retCheck == TAB_CondRetCheck) {
            //printf("passou pelo check\n");
            jogCheckMate = JOG_AvaliaCheck(j,'B');
            if (jogCheckMate == JOG_CondRetCheckMate) {
                //printf("passou pelo check mate\n");
                return jogCheckMate;
            }
            return JOG_CondRetCheck;
        }
        retCheck = TAB_VerificaCheck(j->tabu, j->xReiPreto, j->yReiPreto);
        if(retCheck == TAB_CondRetCheck) {
            //printf("ENtrei no check afro\n");
            jogCheckMate = JOG_AvaliaCheck(j,'P');
            printf("%d\n",jogCheckMate);
            if (jogCheckMate == JOG_CondRetCheckMate) {
                return jogCheckMate;
            }
            return JOG_CondRetCheck;
        }
        
        
        
        
        if(condRetTab == JOG_CondRetOK) {
            return JOG_CondRetOK;
        } else {
            return JOG_CondRetComeu;
        }
    }
    
    
    
    return JOG_CondRetMovimentoIrregular;
}/* Fim função: JOG  &Efetuar Jogada*/

/***************************************************************************
 *
 *  Função: JOG  &Retorno Nome Jogador 1
 *  ****/
JOG_tpCondRet JOG_RetornoNomeJogador1(ptJudge j,char nome[30]) {
    strcpy(nome, j->jogador1->nome);
    return JOG_CondRetOK;
}/* Fim função: JOG  &Retorno Nome Jogador 1*/
/***************************************************************************
 *
 *  Função: JOG  &Retorno Nome Jogador 2
 *  ****/
JOG_tpCondRet JOG_RetornoNomeJogador2(ptJudge j,char nome[30]) {
    strcpy(nome, j->jogador2->nome);
    return JOG_CondRetOK;
}/* Fim função: JOG  &Retorno Nome Jogador 2*/

/***************************************************************************
 *
 *  Função: JOG  &Gera Matriz Tabuleiro
 *  ****/

JOG_tpCondRet JOG_GeraMatrizTabuleiro(ptJudge j,char matriz[8][8][2]) {
    int x,y;
    char cor,id;
    for (x=0; x<8; x++) {
        for (y=0; y<8; y++) {
            TAB_ObterPeca(j->tabu, x, y, &cor, &id);
            //printf("x: %d\n",x);
            //printf("y: %d\n",y);
            //printf("%c e %c\n",cor,id);
            matriz[x][y][0] = id;
            matriz[x][y][1] = cor;
            //printf("cor: %c e id: %c\n",cor,id);
        }
    }
    return JOG_CondRetOK;
}/* Fim função: JOG  &Gera Matriz Tabuleiro*/

/***************************************************************************
 *
 *  Função: JOG  &Comecar Jogo
 *  ****/
JOG_tpCondRet JOG_ComecarJogo(ptJudge j,void (*InserirPecas)(TAB_tpCondRet(*InserirNoTab)(ptTabuleiro tabu,int x,int y,char cor,char id),ptJudge j)) {
    
    InserirPecas(TAB_InserirPeca,j);
    
    return JOG_CondRetOK;
}/* Fim função: JOG  &Comecar Jogo*/

/***************************************************************************
 *
 *  Função: JOG  &Devolve Ameacantes
 *  ****/
JOG_tpCondRet JOG_DevolveAmeacantes(ptJudge j,char *corAmeacantes,char *idAmeacantes,int *qtdAmeacantes,int x,int y) {
    LIS_tppLista ameacantes;
    Peca *ameacante;
    int numElem,i;
    
    TAB_ObterListaAmeacantes(j->tabu, x, y, &ameacantes);
    LIS_RetornaNumElementos(ameacantes, &numElem);
    *qtdAmeacantes = numElem;
    IrInicioLista(ameacantes);
    for (i=0; i<numElem; i++) {
        LIS_ObterNo(ameacantes, (void **)&ameacante);
        PEC_RetornaCor(ameacante, &corAmeacantes[i]);
        PEC_RetornaId(ameacante, &idAmeacantes[i]);
        LIS_IrProx(ameacantes);
    }
    return JOG_CondRetOK;
}/* Fim função: JOG  &Devolve Ameacantes*/

/***************************************************************************
 *
 *  Função: JOG  &Devolve Ameacados
 *  ****/
JOG_tpCondRet JOG_DevolveAmeacados(ptJudge j,char *corAmeacados,char *idAmeacados,int *qtdAmeacados,int x,int y) {
    LIS_tppLista ameacados;
    Peca *ameacado;
    int numElem,i;
    TAB_ObterListaAmeacados(j->tabu, x, y, &ameacados);
    LIS_RetornaNumElementos(ameacados, &numElem);
    *qtdAmeacados = numElem;
    IrInicioLista(ameacados);
    for (i=0; i<numElem; i++) {
        LIS_ObterNo(ameacados, (void **)&ameacado);
        PEC_RetornaCor(ameacado, &corAmeacados[i]);
        PEC_RetornaId(ameacado, &idAmeacados[i]);
        LIS_IrProx(ameacados);
    }
    return JOG_CondRetOK;
}/* Fim função: JOG  &Devolve Ameacados*/

/***************************************************************************
 *
 *  Função: JOG  &Assasinar Juiz
 *  ****/
JOG_tpCondRet JOG_AssasinarJuiz(ptJudge j) {
    TAB_DestruirTabuleiro(j->tabu);
    free(j->jogador1);
    free(j->jogador2);
    free(j);
    return JOG_CondRetOK;
}/* Fim função: JOG  &Assasinar Juiz*/

/***************************************************************************
 
 
 /*****  Código das funções encapsuladas no módulo  *****/

/***************************************************************************/

/***************************************************************************
 *
 *  Função: JOG   - Avalia Check
 *  ****/
JOG_tpCondRet JOG_AvaliaCheck(ptJudge j,int corRei) {
    Peca *ameacante;
    TAB_tpCondRet retCheckMate;
    int xAmeacante,yAmeacante,numElem;
    char corAmeacante,idAmeacante;
    LIS_tppLista ameacantes;
    
    
    if(corRei == 'B') {
        TAB_ObterListaAmeacantes(j->tabu, j->xReiBranco, j->yReiBranco, &ameacantes);
        LIS_ObterNo(ameacantes, (void **)&ameacante);
        PEC_RetornaCor(ameacante, &corAmeacante);
        PEC_RetornaId(ameacante, &idAmeacante);
        TAB_AchaPecaCheck(j->tabu, corAmeacante, idAmeacante, &xAmeacante, &yAmeacante, j->xReiBranco, j->yReiBranco);retCheckMate = TAB_VerificaCheckMate(j->tabu, j->xReiBranco, j->yReiBranco, xAmeacante, yAmeacante);
    } else {
        TAB_ObterListaAmeacantes(j->tabu, j->xReiPreto, j->yReiPreto, &ameacantes);
        LIS_ObterNo(ameacantes, (void **)&ameacante);
        PEC_RetornaCor(ameacante, &corAmeacante);
        PEC_RetornaId(ameacante, &idAmeacante);
        TAB_AchaPecaCheck(j->tabu, corAmeacante, idAmeacante, &xAmeacante, &yAmeacante, j->xReiPreto, j->yReiPreto);
        retCheckMate = TAB_VerificaCheckMate(j->tabu, j->xReiPreto, j->yReiPreto, xAmeacante, yAmeacante);
    }
    if (retCheckMate == TAB_CondRetNoCheckMate) {
        return JOG_CondRetNoCheckMate;
    } else if(retCheckMate == TAB_CondRetSeSacrificou || retCheckMate == TAB_CondRetComeuParaSalvar) {
        LIS_RetornaNumElementos(ameacantes, &numElem);
        if(numElem <=1) {
            /*Caso as peças tenham que se movimentar para salvar o rei, elas, logicamente, terão que usar um movimento. Nesse caso, se houver mais alguma outra peça que coloca o rei em cheque, acabará o jogo, visto que as peças da cor do rei terão que realizar um dos movimentos para evitar que o rei seja capturado pela primeira peça e, com isso, a segunda peça que ameaça o rei pode o capturar  */
            return JOG_CondRetNoCheckMate;
        }
        
    }
    return JOG_CondRetCheckMate;
    
}/* Fim função: JOG  &Avalia Check*/

/********** Fim do módulo de implementação: JOG  Jogo **********/
