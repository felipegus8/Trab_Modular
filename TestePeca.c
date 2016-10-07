/***************************************************************************
*  $MCI Módulo de implementação: TPEC Teste Peca
*
*  Arquivo gerado:              TestePeca.c
*  Letras identificadoras:      TPEC
*
*  Autores: Felipe Viberti,Luis Claudio e Victor Nogueira
*
*  $HA Histórico de evolução:
*     Versão  Autores                                           Data          Observações
*     1       Felipe Viberti,Luis Claudio e Victor Nogueira   02/out/2016  início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>
#include    <stdlib.h>

#include    "Generico.h"
#include    "LerParm.h"

#include    "peca.h"
#include    "TST_ESPC.h"

static const char CRIAR_PECA             								[ ] = "=criarpeca" ;
static const char ENSINA_MOVIMENTOS_PECAS_CONHECIDAS          	        [ ] = "=ensinamovimentospecasconhecidas"   ;
static const char ENSINA_MOVIMENTOS_PECAS_DESCONHECIDAS              	[ ] = "=ensinamovimentospecasdesconhecidas"      ;
static const char LIBERA_PECA               							[ ] = "=liberapeca"        ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_PECA   100
#define DIM_VALOR     100

Peca* vtPecas[DIM_VT_PECA];

/***** Protótipos das funções encapuladas no módulo *****/
 static int ValidarInxPeca( int inxPeca , int Modo ) ;


/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TLIS &Testar Peça
*
*  $ED Descrição da função
*     Podem ser criadas até 100 peças, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =criarpeca					                 inxPeca  idPeca   corPeca(string)  CondRetEsp
*     =ensinamovimentospecasconhecidas               inxPeca  idPeca   corPeca(string)  CondRetEsp
*     =ensinamovimentospecasdesconhecidas            inxPeca   idPeca  corPeca(string)    NomeArquivo(Onde as peças novas ficam guardadas) CondRetEsp
*     =liberapeca                                    inxPeca   CondRetEsp
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	 int inxPeca  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;
      TST_tpCondRet CondRet ;
      char   StringDado[  DIM_VALOR ],StringDado2[DIM_VALOR] ;
	  char idPeca,corPeca;
      char * pDado ;
      int ValEsp = -1 ;
      int i ;
		Peca *novo;
      int numElem = -1 ;
	  
       void * elemento;
      StringDado[ 0 ] = 0,StringDado2[0] = 0;

	   if ( strcmp( ComandoTeste , CRIAR_PECA) == 0 )
	   {
		   numLidos = LER_LerParametros( "icci" ,
                       &inxPeca,&idPeca,&corPeca,&CondRetEsp );
		   if ((numLidos != 4) || (( ! ValidarInxPeca( inxPeca , VAZIO ))))
		   {
			    return TST_CondRetParm;
		   }
		   CondRet = PEC_CriaPeca( &vtPecas[inxPeca],idPeca,corPeca);    
		 return TST_CompararPonteiroNulo( 1 , vtPecas[inxPeca] , "Erro em ponteiro de nova lista."  ) ;
	   }/* fim ativa: Testar CriarPeca */
	   else if (strcmp(ComandoTeste,ENSINA_MOVIMENTOS_PECAS_CONHECIDAS) == 0)
	   {
		   numLidos = LER_LerParametros("ii", &inxPeca,&CondRetEsp);
		  if ((numLidos != 2) || (( ! ValidarInxPeca( inxPeca , NAO_VAZIO ))))
		   {
			    return TST_CondRetParm;
		   }
		CondRet = PEC_EnsinaMovimentosPecasConhecidas(&vtPecas[inxPeca]);
		return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao ensinar o movimento a uma peça conhecida." );
	   }/* fim ativa: Testar EnsinaMovimentosPecasConhecidas */
	   else if (strcmp(ComandoTeste,ENSINA_MOVIMENTOS_PECAS_DESCONHECIDAS) == 0)
	   {
		   numLidos = LER_LerParametros("ii",&inxPeca,&CondRetEsp);
		    if ((numLidos != 2) || (( ! ValidarInxPeca( inxPeca , NAO_VAZIO ))))
		   {
			    return TST_CondRetParm;
			}
		CondRet = PEC_EnsinaMovimentosPecasDesconhecidas(&vtPecas[inxPeca]);
		return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao ensinar o movimento a uma peça desconhecida.");
	   }/* fim ativa: Testar EnsinaMovimentosPecasDesconhecidas */


	   else if(strcmp(ComandoTeste,LIBERA_PECA) == 0)
	   {
		    numLidos = LER_LerParametros("ii", &inxPeca,&CondRetEsp);
		  if ((numLidos != 2) || (( ! ValidarInxPeca( inxPeca , NAO_VAZIO ))))
		   {
			    return TST_CondRetParm;
		   }
		  CondRet = PEC_LiberaPeca(vtPecas[inxPeca]);
		  vtPecas[inxPeca] = NULL;
		   return TST_CompararInt( CondRetEsp ,CondRet  ,"Condição de retorno errada ao liberar uma peça" ) ;
	   }/* fim ativa: Testar LiberaPeca */
}
/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TLIS -Validar indice da peca.

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
         if ( vtPecas[ inxPeca ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtPecas[ inxPeca ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TLIS -Validar indice de lista */
