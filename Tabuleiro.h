#include "Lista.h"
#if ! defined( Tabuleiro_ )
#define Tabuleiro_

typedef struct casa Casa;

typedef tabuleiro Casa[8][8];

typedef enum {

         TAB_CondRetOK ,
               /* Concluiu corretamente */

         TAB_CondRetCasaVazia ,
               /* A casa não contém peças */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

         TAB_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar uma lista dentro da casa*/

   } TAB_tpCondRet ;



   
Lis_tpCondRet InserirPeca(int x,char y,char *cor);

Lis_tpCondRet MoverPeca(int xo,char yo,int xd,char yd);

LIS_tpCondRet RetirarPeca(int x, char y);

LIS_tpCondRet ObterPeca(int x, char y,char *nome,char *cor);

LIS_tpCondRet ObterListaAmeacantes(int x,char y,LIS_tppLista lista); //a ser editada

LIS_tpCondRet ObterListaAmeacados(int x,char y,LIS_tppLista lista); //a ser editada

LIS_tpCondRet DestruirTabuleiro();




#endif
