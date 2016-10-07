#if ! defined( Tabuleiro_ )
#define Tabuleiro_

/***************************************************************************
*
*  $MCD Módulo de definição: TAB  Tabuleiro
*
*  Arquivo gerado:              Tabuleiro.h
*  Letras identificadoras:      TAB
*
*
*  $ED Descrição do módulo
*     Implementa um tabuleiro representada por uma matriz 8*8 da struct casa.
*     Cada casa do tabuleiro contem uma lista para as peças que ameaçam aquela casa,outra para as peças que aquela casa ameaça,além do próprio elemento contido na casa.
* 
*  Autores: Felipe Viberti,Luis Claudio e Victor Nogueira
*
*  $HA Histórico de evolução:
*     Versão  Autores                                           Data          Observações
*     1       Felipe Viberti,Luis Claudio e Victor Nogueira   27/set/2016  início desenvolvimento
*
***************************************************************************/

#include "lista.h"
#include "peca.h"
/***********************************************************************
*
*  $TC Tipo de dados: TAB Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do Tabuleiro.
*
***********************************************************************/
typedef enum {

         TAB_CondRetOK ,
               /* Concluiu corretamente */

         TAB_CondRetCasaVazia ,
               /* A casa não contém peças */

         TAB_CondRetCoordenadaNExiste ,
               /* coordenada inserida não existe */

         TAB_CondRetNaoAchouPeca ,
               /* Não encontrou a peca procurada */

         TAB_CondRetFaltouMemoria ,
               /* Faltou memória ao tentar criar uma lista dentro da casa*/
         
         TAB_CondRetListaAmecadosNaoExiste ,
               /* lista de elementos ameaçados pela peça não foi criado*/
         
         TAB_CondRetListaAmecantesNaoExiste ,
               /* lista de elementos que ameaçam a peça não foi criado*/
         
        TAB_CondRetMovimentoIrregular

   } TAB_tpCondRet ;


/* Tipo Casa */
typedef struct casa Casa;



 TAB_tpCondRet TAB_CriaTabuleiro(Casa *tabuleiro[8][8]);
   
TAB_tpCondRet TAB_InserirPeca(Casa tabuleiro[8][8],int x, char y,char cor,char id)

 TAB_tpCondRet TAB_MoverPeca(Casa tabuleiro[8][8],int xo,char yo,int xd,char yd)

 TAB_tpCondRet TAB_RetirarPeca(Casa tabuleiro[8][8],int x,char y)

 TAB_tpCondRet TAB_ObterPeca(Casa tabuleiro[8][8],int x, char y, char cor, char id)

TAB_tpCondRet TAB_ObterListaAmeacantes(Casa tabuleiro[8][8],int x, char y,LIS_tppLista *listaAmeacantes); //a ser editada

TAB_tpCondRet TAB_ObterListaAmeacados(Casa tabuleiro[8][8],int x, char y,LIS_tppLista *listaAmeacados); //a ser editada

TAB_tpCondRet TAB_DestruirTabuleiro(Casa tabuleiro[8][8])



/********** Fim do módulo de definição: TAB  Tabuleiros **********/
#endif
