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
#include "Tabuleiro.h"
#include "jogo.h"

ptTabuleiro tabu;
LIS_tppLista lista;

typedef struct jogador
{
    char nome[30];
    char cor;
}Jogador;

int verificaChequeMate(ptTabuleiro tabu) {
    //inferno
    return 0;
}

int verificaCheque(ptTabuleiro tabu) {
    int i,j;
    char corPecaTabuleiro,idPecaTabuleiro;
    for (i=0; i<8; i++) {
        for (j=0; j<8; j++) {
            TAB_ObterPeca(tabu, i, j, &corPecaTabuleiro, &idPecaTabuleiro);
            if (idPecaTabuleiro == 'R') {
                TAB_ObterListaAmeacantes(tabu, i, j, &lista);
                if (LIS_RetornaNumElementos(lista)>0) {
                    if(corPecaTabuleiro == 'P') {
                        printf("cheque rei afordescendente na posição(%d,%d)\n",i,j);
                    } else {
                        printf("cheque rei caucasiano na posição(%d,%d)\n",i,j);
                    }
                }
            }
        }
    }
    return 0;
}


void JOG_PedeNomesJogadores(Jogador *a,Jogador *b)
{
    printf("Insira o nome do jogador 1:");
    scanf("%[ˆ\n]",a->nome);
    printf("Insira o nome do jogador 2:");
    scanf("%[ˆ\n]",b->nome);
}



void loopJogo() {
    char querContinuar[4];
    int rodada = 0;
    do {
        printf("Ohh ilustre!!\nDeseja prosseguir o jogo\n");
        scanf("%s",querContinuar);
        if (rodada % 2 == 0) {
            
        } else {
            
        }
        rodada++;
    } while (strcmp(querContinuar, "Fim") == 0);

}

