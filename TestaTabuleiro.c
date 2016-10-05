#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_ESPC.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Tabuleiro.h"

//DestruirTabuleiro
static const char CRIAR_TABULEIRO          	                        [ ] = "=criartabuleiro" ;
static const char INSERE_PECA        	                              [ ] = "=inserepeca"   ;
static const char OBTER_LISTA_AMEACANTES                            [ ] = "=obterlistaameacantes"      ;
static const char OBTER_LISTA_AMEACADOS               				      [ ] = "=obterlistaameacados"        ;
static const char OBTER_PECA              				                  [ ] = "=obterpeca"        ;
static const char RETIRAR_PECA              				                [ ] = "=retirarpeca"        ;
static const char MOVER_PECA              				                  [ ] = "=moverpeca"        ;
static const char DESTRUIR_TABULEIRO                                [ ] = "=destruirtabuleiro"        ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_PECA   64
#define DIM_VALOR 100
