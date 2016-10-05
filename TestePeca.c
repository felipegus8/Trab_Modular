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

#define DIM_VT_PECA   100
#define DIM_VALOR     100

Peca vtPecas[DIM_VT_PECA];

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
      int CondRet ;

      char   StringDado[  DIM_VALOR ],StringDado2[DIM_VALOR],NomeArquivo[DIM_VALOR],ConteudoArquivo[1000],strAux[1000] ;
	  char idPeca,corPeca,idLido,corLido;
      char * pDado ;
	  FILE *fp;
      int ValEsp = -1 ;

      int i ;
	  Peca *novo;
      int numElem = -1 ;
	  Movimento *mov;
       void * elemento;
      StringDado[ 0 ] = 0,StringDado2[0] = 0;

	   if ( strcmp( ComandoTeste , CRIAR_ PECA) == 0 )s
	   {
		   numLidos = LER_LerParametros( "issi" ,
                       &inxPeca,StringDado,StringDado2,&CondRetEsp );
		   if ((numLidos != 4) || (( ! ValidarInxPeca( inxPeca , VAZIO ))))
		   {
			    return TST_CondRetParm;
		   }
		   vtPecas[inxPeca] = criaPeca(novo,StringDado,StringDado2);    
		 return TST_CompararPonteiroNulo( 1 , vtPecas[ inxPeca ] , "Erro em ponteiro de nova lista."  ) ;
	   }/* fim ativa: Testar CriarPeca */


	   else if (strcmp(ComandoTeste,ENSINA_MOVIMENTOS_PECAS_CONHECIDAS) == 0)
	   {
		   numLidos = LER_LerParametros("isssi", &inxPeca,StringDado,StringDado2,&CondRetEsp);
		  if ((numLidos != 4) (( ! ValidarInxPeca( inxPeca , NAO_VAZIO ))))
		   {
			    return TST_CondRetParm;
		   }
		CondRet = ensinaMovimentosPecasConhecidas(vtPecas[inxPeca]);
		return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao ensinar o movimento a uma peça conhecida." );
	   }/* fim ativa: Testar EnsinaMovimentosPecasConhecidas */

	   else if (strcmp(ComandoTeste,ENSINA_MOVIMENTOS_PECAS_DESCONHECIDAS) == 0)
	   {
		   numLidos = LER_LerParametros("iccsi",&inxPeca,idPeca,CorPeca,NomeArquivo,&CondRetEsp);
		    if ((numLidos != 5) (( ! ValidarInxPeca( inxPeca , NAO_VAZIO ))))
		   {
			    return TST_CondRetParm;
			}
			if ((fp=fopen("PecasNovas.txt","r"))==NULL)
			{
			 printf("Error! opening file");
			exit(1);         
			}
			i = 0;
		while(fscanf(fp,"%c %c",&idLido,&corLido))
		{
			if ((idLido == idPeca) && (corLido == corPeca))
			{
				while (fscanf(fp,"%d %d",&x,&y))
				{
					i++;
				}
				break;
			}

		}
		mov = (Movimento*)malloc(sizeof(Movimento)*i);
		i = 0;
		fclose(fp);
		if ((fp=fopen("PecasNovas.txt","r"))==NULL)
			{
			 printf("Error! opening file");
			exit(1);         
			}
		while(fscanf(fp,"%c %c",&idLido,&corLido))
		{
			if ((idLido == idPeca) && (corLido == corPeca))
			{
				while (fscanf(fp,"%d %d",&x,&y))
				{
					 mov[i].x = x;
					 mov[i].y = y;
					i++;
				}
				break;
			}

		}
		for(j = 0;j<i;j++)
		{
			printf("%d %d",mov[j].x,mov[j].y);
			printf("\n");
		}
		CondRet = ensinaMovimentosPecasDesconhecidas(novo,mov);
		return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao ensinar o movimento a uma peça desconhecida.");
	   }/* fim ativa: Testar EnsinaMovimentosPecasDesconhecidas */


	   else if(strcmp(ComandoTeste,LIBERA_PECA) == 0)
	   {
		    numLidos = LER_LerParametros("issi", &inxPeca,StringDado,StringDado2,&CondRetEsp);
		  if ((numLidos != 4) (( ! ValidarInxPeca( inxPeca , NAO_VAZIO ))))
		   {
			    return TST_CondRetParm;
		   }
		  CondRet = liberaPeca(vtPecas[inxPeca]);
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

   } /* Fim função: TLIS -Validar indice de lista */