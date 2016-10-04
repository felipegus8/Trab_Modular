#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"
#include "Casa.h"




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
              casa->ameacadas = (LIS_tppLista *) malloc(sizeof(LIS_tppLista));
   }
   
   
