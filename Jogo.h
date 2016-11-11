#if ! defined( Jogo_ )
#define Jogo_

/***************************************************************************
*
*  $MCD M�dulo de defini��o: JOG  Jogo
*
*  Arquivo gerado:              Jogo.h
*  Letras identificadoras:      JOG
*
*
*  $ED Descri��o do m�dulo
*     A implementa��o do m�dulo jogo diz respeito de como deve se estruturar o as regras execu��o do jogo
* 
*  Autores: Felipe Viberti,Luis Claudio e Victor Nogueira
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autores                                           Data          Observa��es
*     1       Felipe Viberti,Luis Claudio e Victor Nogueira   10/Nov/2016  in�cio desenvolvimento
*
***************************************************************************/

/***********************************************************************
*
*  $TC Tipo de dados: JOG Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es do Jogo.
*
***********************************************************************/
typedef enum {

         JOG_CondRetOK ,
               /* Concluiu corretamente */

         JOG_CondRetFaltouMemoria ,
               /* Faltou mem�ria ao tentar criar uma lista dentro da casa*/
         
   } JOG_tpCondRet ;

#include "lista.h"
#include "peca.h"
#include "Tabuleiro.h"


/***********************************************************************
*  $FC Fun��o: JOG &Pede Nomes Jogadores
*
*  $ED Descri��o da fun��o
*     Pede como input o nome de dois jogadores para preencher o vetor de nomes
*
*  $EP Par�metros
*    Duas structs jogadores
*
*  $FV Valor retornado
*    Se executou corretamente retona Ok.
*    Se houve algum problema por falta de mem�ria retorna Faltou Mem�ria.

***********************************************************************/
void JOG_PedeNomesJogadores(Jogador *a,Jogador *b);