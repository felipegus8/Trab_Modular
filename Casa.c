#include <stdio.h>
#include <stdlib.h>



typedef struct casa {
         LIS_tppLista *ameacados;
         /* ponteiro para a cabeça da lista que contém as peças ameaçadas pela peça da casa */
         LIS_tppLista *amecantes;
         /* ponteiro para a cabeça da lista que contém as peças que ameaçam a peça da casa */
         void *elemento;
         /*ponteiro para o elemento contido na casa */
   } Casa;
   
   
   GEN_tpCondRet criaCasa(Casa *casa) {
              casa->ameacados = (LIS_tppLista *) malloc(sizeof(LIS_tppLista));
              if(casa->ameacados == NULL) {
                   return GEN_CondRetFaltouMemoria;
              }
              casa->ameacadas = (LIS_tppLista *) malloc(sizeof(LIS_tppLista));
              if(casa->ameacantes == NULL) {
                   return GEN_CondRetFaltouMemoria;
              }
   }
   
   GEN_tpCondRet obterListaAmeacantes(Casa *casa,LIS_tppLista *ameacantes) {
                    ameacantes = casa->ameacantes;
   }

   GEN_tpCondRet obterListaAmeacados(Casa *casa,LIS_tppLista *ameacados) {
                    ameacados = casa->ameacados;
   }


   GEN_tpCondRet liberaCasa(Casa *casa) {
                    free(casa->ameacados);
                    free(casa->ameacantes);
                    if(casa->elemento == NULL) {
                         return GEN_CondRetNExiste;
                    }
                    free(casa->elemento);
                    free(Casa);
   }

