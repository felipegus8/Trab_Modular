#include <stdio.h>
#include "Lista.h"


typedef struct casa Casa;

GEN_tpCondRet criaCasa(Casa *casa);
GEN_tpCondRet obterListaAmeacantes(Casa *casa,LIS_tppLista *ameacantes);
GEN_tpCondRet obterListaAmeacados(Casa *casa,LIS_tppLista *ameacados);
GEN_tpCondRet liberaCasa(Casa *casa);


