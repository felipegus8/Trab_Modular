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
         
         TAB_CondRetListaAmeacadosNaoExiste ,
               /* lista de elementos ameaçados pela peça não foi criado*/
         
         TAB_CondRetListaAmeacantesNaoExiste ,
               /* lista de elementos que ameaçam a peça não foi criado*/
         
         TAB_CondRetMovimentoIrregular,
              /* o movimento que foi tentando é irregular */
         TAB_CondRetComeu, 
               /* um movimento válido fez com que uma peça fosse comida */
         TAB_CondRetCasaTemDono

              /* um movimento válido fez com que uma peça fosse para um posição onde há um peça de sua cor */

   } TAB_tpCondRet ;



/* Tipo Casa */
typedef struct casa Casa;


/***********************************************************************

*  $FC Função: TAB &Cria Tabuleiro
*
*  $ED Descrição da função
*     
*
*  $EP Parâmetros
*    tabuleiro = 
*
*  $FV Valor retornado
*    

***********************************************************************/
 TAB_tpCondRet TAB_CriaTabuleiro(Casa **tabuleiro,int TamLinhas, int TamColunas);


/***********************************************************************

*  $FC Função: TAB &Inserir Peca
*
*  $ED Descrição da função
*     
*
*  $EP Parâmetros
*    tabuleiro = 
*    x = 
*    y = 
*    cor = cor da Peça que se quer inserir
*    id = id da Peça que se quer inserir
*
*  $FV Valor retornado
*    

***********************************************************************/
TAB_tpCondRet TAB_InserirPeca(Casa **tabuleiro,int x, int yi,char cor,char id);



/***********************************************************************

*  $FC Função: TAB &Mover Peca
*
*  $ED Descrição da função
*     
*
*  $EP Parâmetros
*    tabuleiro = 
*    xo = 
*    yo =
*    xd =
*    yd = 
*
*  $FV Valor retornado
*    

***********************************************************************/
 TAB_tpCondRet TAB_MoverPeca(Casa **tabuleiro,int xo,int yi,int xd,int yi2);


/***********************************************************************

*  $FC Função: TAB &Retirar Peca
*
*  $ED Descrição da função
*     
*
*  $EP Parâmetros
*    tabuleiro = 
*    x = 
*    y=
*
*  $FV Valor retornado
*    

***********************************************************************/

 TAB_tpCondRet TAB_RetirarPeca(Casa **tabuleiro,int x,int yi);


/***********************************************************************

*  $FC Função: TAB &Obter Peca
*
*  $ED Descrição da função
*     
*
*  $EP Parâmetros
*    tabuleiro = 
*    x = 
*    y =
*    cor = cor da Peca que se quer obter
*    id = id da Peça que se quer obter
*
*  $FV Valor retornado
*    

***********************************************************************/

 TAB_tpCondRet TAB_ObterPeca(Casa **tabuleiro,int x, int y, char *cor, char *id);

/***********************************************************************

*  $FC Função: TAB &Obter Lista Ameacantes
*
*  $ED Descrição da função
*     
*
*  $EP Parâmetros
*    tabuleiro = 
*    x=
*    y=
*    listaAmeacantes = 
*
*  $FV Valor retornado
*    

***********************************************************************/
TAB_tpCondRet TAB_ObterListaAmeacantes(Casa **tabuleiro,int x, int yi,LIS_tppLista listaAmeacantes); //a ser editada



/***********************************************************************

*  $FC Função: TAB &Obter Lista Ameaçados
*
*  $ED Descrição da função
*     
*
*  $EP Parâmetros
*    tabuleiro = 
*    x=
*    y=
*    listaAmeacados = 
*
*  $FV Valor retornado
*    

***********************************************************************/
TAB_tpCondRet TAB_ObterListaAmeacados(Casa **tabuleiro,int x, int yi,LIS_tppLista listaAmeacados); //a ser editada


/***********************************************************************

*  $FC Função: TAB &Destruir Tabuleiro
*
*  $ED Descrição da função
*     
*
*  $EP Parâmetros
*    tabuleiro = 
*
*  $FV Valor retornado
*    

***********************************************************************/
TAB_tpCondRet TAB_DestruirTabuleiro(Casa **tabuleiro);



/********** Fim do módulo de definição: TAB  Tabuleiro **********/
#endif
