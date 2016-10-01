#include "Lista.h"
#if ! defined( Tabuleiro_ )
#define Tabuleiro_

typedef struct casa Casa;

typedef tabuleiro Casa[8][8];




   
Lis_tpCondRet InserirPeca(int x,char y,char *cor);

Lis_tpCondRet MoverPeca(int xo,char yo,int xd,char yd);

LIS_tpCondRet RetirarPeca(int x, char y);

LIS_tpCondRet ObterPeca(int x, char y,char *nome,char *cor);

LIS_tpCondRet ObterListaAmeacantes(int x,char y,LIS_tppLista lista); //a ser editada

LIS_tpCondRet ObterListaAmeacados(int x,char y,LIS_tppLista lista); //a ser editada

LIS_tpCondRet DestruirTabuleiro();




#endif
