#include "Lista.h"
#if ! defined( Tabuleiro_ )
#define Tabuleiro_

typedef struct casa Casa;

typedef tabuleiro Casa[8][8];




typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista não contÈm elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

         LIS_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar um elemento de lista */

   } LIS_tpCondRet ;
   
Lis_tpCondRet InserirPeca(int x,char y,char *cor);

Lis_tpCondRet MoverPeca(int xo,char yo,int xd,char yd);

LIS_tpCondRet RetirarPeca(int x, char y);

LIS_tpCondRet ObterPeca(int x, char y,char *nome,char *cor);

LIS_tpCondRet ObterListaAmeacantes(int x,char y,LIS_tppLista lista); //a ser editada

LIS_tpCondRet ObterListaAmeacados(int x,char y,LIS_tppLista lista); //a ser editada

LIS_tpCondRet DestruirTabuleiro();




#endif
