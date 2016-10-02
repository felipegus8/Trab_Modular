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

         TAB_CondRetCoordenadaNExiste ,
               /* coordenada inserida não existe */

         TAB_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

         TAB_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar uma lista dentro da casa*/

   } TAB_tpCondRet ;



   
TAB_tpCondRet InserirPeca(int x,char y,char *cor);

TAB_tpCondRet MoverPeca(int xo,char yo,int xd,char yd);

TAB_tpCondRet RetirarPeca(int x, char y);

TAB_tpCondRet ObterPeca(int x, char y,char *nome,char *cor);

TAB_tpCondRet ObterListaAmeacantes(int x,char y,LIS_tppLista lista); //a ser editada

TAB_tpCondRet ObterListaAmeacados(int x,char y,LIS_tppLista lista); //a ser editada

TAB_tpCondRet DestruirTabuleiro();




#endif
