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

typedef stuct jogador
{
	char nome[30];
	char cor;
}Jogador;


void JOG_PedeNomesJogadores(Jogador *a,Jogador *b)
{
	printf("Insira o nome do jogador 1:");
	scanf("%[ˆ\n],a->nome");
	printf("Insira o nome do jogador 2:");
	scanf("%[ˆ\n],b->nome");
}
