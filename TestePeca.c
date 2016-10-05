#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TestePeca.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "peca.h"
#include    "TesteLista.h"

static const char CRIAR_PECA             	                            [ ] = "=criarpeca" ;
static const char ENSINA_MOVIMENTOS_PECAS_CONHECIDAS          	        [ ] = "=ensinamovimentospecasconhecidas"   ;
static const char ENSINA_MOVIMENTOS_PECAS_DESCONHECIDAS              	[ ] = "=ensinamovimentospecasdesconhecidas"      ;
static const char LIBERA_PECA               							[ ] = "=liberapeca"        ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_PECA   10
#define DIM_VALOR     100

Peca vtPecas[DIM_VT_PECA];

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/
 static int ValidarInxPeca( int inxPeca , int Modo ) ;


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TLIS &Testar lista
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 10 pe�as, identificadas pelos �ndices 0 a 10
*
*     Comandos dispon�veis:
*
*     =criarpeca					                 inxPeca  idPeca   corPeca(string)  CondRetEsp
*     =ensinamovimentospecasconhecidas               inxPeca  idPeca   corPeca(string)  CondRetEsp
*     =ensinamovimentospecasdesconhecidas            inxPeca   idPeca  corPeca(string)  qtdMovimentos  Movimentos(qtd determinada) CondRetEsp
*     =liberapeca                                    inxPeca   CondRetEsp
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	 int inxPeca  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      int CondRet ;

      char   StringDado[  DIM_VALOR ] ;
      char * pDado ;

      int ValEsp = -1 ;

      int i ;
	  Peca *novo;
      int numElem = -1 ;

       void * elemento;
      StringDado[ 0 ] = 0,StringDado2[0] = 0 ;

	   if ( strcmp( ComandoTeste , CRIAR_ PECA) == 0 )
	   {
		   numLidos = LER_LerParametros( "issi" ,
                       &inxPeca,StringDado,StringDado2,&CondRetEsp );
		   if (numLidos != 4)
		   {
			    return TST_CondRetParm;
		   }
		   vtPecas[inxPeca] = criaPeca(novo,StringDado,StringDado2);    
		 return TST_CompararPonteiroNulo( 1 , vtListas[ inxLista ] , "Erro em ponteiro de nova lista."  ) ;
	   }
	   else if (strcmp(ComandoTeste,ENSINA_MOVIMENTOS_PECAS_CONHECIDAS) == 0)
	   {
		   numLidos = LER_LerParametros("");
	   }
}
/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TLIS -Validar indice de lista
*
***********************************************************************/

   int ValidarInxPeca( int inxPeca , int Modo)
   {

      if ( ( inxPeca <  0 )
        || ( inxPeca >= DIM_VT_PECA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtPecas[ inxLPeca ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtPecas[ inxLista ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim fun��o: TLIS -Validar indice de lista */