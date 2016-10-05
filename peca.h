#include <stdio.h>

typedef enum {

         PEC_CondRetOK ,
               /* Concluiu corretamente */

         PEC_CondRetCasaVazia ,
               /* A casa n�o cont�m pe�as */

         PEC_CondRetCoordenadaNExiste ,
               /* coordenada inserida n�o existe */

         PEC_CondRetNaoAchouPeca ,
               /* N�o encontrou a peca procurada */

         PEC_CondRetFaltouMemoria
               /* Faltou mem�ria ao tentar criar uma lista dentro da casa*/

   } PEC_tpCondRet ;

typedef struct peca Peca;
typedef struct movimento Movimento;
PEC_tpCondRet criaPeca(Peca *novo,char *id,char *cor);
PEC_tpCondRet ensinaMovimentosPecasConhecidas(Peca *novo);
PEC_tpCondRet ensinaMovimentosPecasDesconhecidas(Peca *novo,Movimento *movPecaNova);
PEC_tpCondRet liberarPeca(Peca *peca);

