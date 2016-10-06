#if ! defined( Tabuleiro_ )
#define Tabuleiro_
#include "lista.h"
#include "peca.h"
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
*
***************************************************************************/


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


/* Tipo referencia para uma casa */
typedef struct casa Casa;




   
TAB_tpCondRet InserirPeca(int x,char y,char *cor);

TAB_tpCondRet MoverPeca(int xo,char yo,int xd,char yd);

TAB_tpCondRet RetirarPeca(int x, char y);

TAB_tpCondRet ObterPeca(int x, char y,char *nome,char *cor);

TAB_tpCondRet ObterListaAmeacantes(int x,char y,LIS_tppLista listaAmeacados); //a ser editada

TAB_tpCondRet ObterListaAmeacados(int x,char y,LIS_tppLista listaAmeacantes); //a ser editada

TAB_tpCondRet DestruirTabuleiro();




#endif
