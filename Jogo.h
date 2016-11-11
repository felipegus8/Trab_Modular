#if ! defined( Jogo_ )
#define Jogo_

/***************************************************************************
*
*  $MCD Módulo de definição: JOG  Jogo
*
*  Arquivo gerado:              Jogo.h
*  Letras identificadoras:      JOG
*
*
*  $ED Descrição do módulo
*     A implementação do módulo jogo diz respeito de como deve se estruturar o as regras execução do jogo
* 
*  Autores: Felipe Viberti,Luis Claudio e Victor Nogueira
*
*  $HA Histórico de evolução:
*     Versão  Autores                                           Data          Observações
*     1       Felipe Viberti,Luis Claudio e Victor Nogueira   10/Nov/2016  início desenvolvimento
*
***************************************************************************/

/***********************************************************************
*
*  $TC Tipo de dados: JOG Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do Jogo.
*
***********************************************************************/
typedef enum {

         JOG_CondRetOK ,
               /* Concluiu corretamente */

         JOG_CondRetFaltouMemoria ,
               /* Faltou memória ao tentar criar uma lista dentro da casa*/
         
   } JOG_tpCondRet ;

#include "lista.h"
#include "peca.h"
#include "Tabuleiro.h"


/***********************************************************************
*  $FC Função: JOG &Pede Nomes Jogadores
*
*  $ED Descrição da função
*     Pede como input o nome de dois jogadores para preencher o vetor de nomes
*
*  $EP Parâmetros
*    Duas structs jogadores
*
*  $FV Valor retornado
*    Se executou corretamente retona Ok.
*    Se houve algum problema por falta de memória retorna Faltou Memória.

***********************************************************************/
void JOG_PedeNomesJogadores(Jogador *a,Jogador *b);