#include<stdio.h>
#include<stdlib.h>
#include "peca.h"
#include "lista.h"
typedef enum {

         TAB_CondRetOK ,
               /* Concluiu corretamente */

         TAB_CondRetCasaVazia ,
               /* A casa n�o cont�m pe�as */

         TAB_CondRetCoordenadaNExiste ,
               /* coordenada inserida n�o existe */

         TAB_CondRetNaoAchouPeca ,
               /* N�o encontrou a peca procurada */

         TAB_CondRetFaltouMemoria ,
               /* Faltou mem�ria ao tentar criar uma lista dentro da casa*/
         
         TAB_CondRetListaAmeacadosNaoExiste ,
               /* lista de elementos amea�ados pela pe�a n�o foi criado*/
         
         TAB_CondRetListaAmeacantesNaoExiste ,
               /* lista de elementos que amea�am a pe�a n�o foi criado*/
         
         TAB_CondRetMovimentoIrregular,
              /* o movimento que foi tentando � irregular */
         TAB_CondRetComeu, 
               /* um movimento v�lido fez com que uma pe�a fosse comida */
         TAB_CondRetCasaTemDono,

              /* um movimento v�lido fez com que uma pe�a fosse para um posi��o onde h� um pe�a de sua cor */

		 TAB_CondRetCorErrada,
		     /* cor obtida est� errado */
		 TAB_CondRetIdErrado
		    /* id obtido est� errado */
   } TAB_tpCondRet ;

char idListaPecas[5] = "PeLi"; //identifica��o da lista de pe�as
LIS_tppLista listaPecas;
LIS_tpCondRet  retLis = LIS_CondRetOK;
LIS_tpCondRet retLis2 = LIS_CondRetOK;
PEC_tpCondRet retPeca = PEC_CondRetOK;


typedef struct casa {
         LIS_tppLista ameacados;
         /* ponteiro para a cabe�a da lista que cont�m as pe�as amea�adas pela pe�a da casa */
         LIS_tppLista ameacantes;
         /* ponteiro para a cabe�a da lista que cont�m as pe�as que amea�am a pe�a da casa */
         void *elemento;
         /*ponteiro para o elemento contido na casa */
   } Casa;


   void destruirValor(void *pValor) {
        free(pValor);
   }/* Fim fun��o: TAB  -Destruir Valor*/
TAB_tpCondRet criarListaPecas() {
    retLis = LIS_CriarLista(&listaPecas,idListaPecas,destruirValor);
    if(retLis == LIS_CondRetOK) {
        return TAB_CondRetOK;
    }
    return TAB_CondRetFaltouMemoria;
}

TAB_tpCondRet TAB_CriaTabuleiro(Casa *tabuleiro,int TamLinhas, int TamColunas) {
    int i = 0,j=0;
	LIS_tppLista listaAmeacados;
	LIS_tppLista listaAmeacantes;   
    char idListaAmeacadosX = '1';//linha da casa onde reside a lista ameacados
    char idListaAmeacadosY; //coluna da casa onde reside a lista ameacados
    char idListaAmeacantesX = '1';//linha da casa onde reside a lista ameacantes
    char idListaAmeacantesY;//coluna da casa onde reside a lista ameacantes
    char idListaAmeacados[4] = "Amd";
    char idListaAmeacantes[4] = "Amn";

    criarListaPecas();

    while(i<TamLinhas) {
             idListaAmeacadosY = 'A';
             idListaAmeacantesY = 'A';
         while(j<TamColunas) {
              //as 3 linhas acima fazem com que a string identificadora da lista ameacantes fique da forma "linhaColunaB"
			  printf("declarei aqui a casa\n");
			  listaAmeacados = tabuleiro[i * TamLinhas + j].ameacados;
			  listaAmeacantes = tabuleiro[i * TamLinhas + j].ameacantes;
              retLis = LIS_CriarLista(&listaAmeacados,idListaAmeacados,destruirValor);
              if(retLis == LIS_CondRetFaltouMemoria) {
                    return TAB_CondRetFaltouMemoria;
              }
              retLis2 = LIS_CriarLista(&listaAmeacantes,idListaAmeacantes,destruirValor);
              if(retLis2 == LIS_CondRetFaltouMemoria) {
                    return TAB_CondRetFaltouMemoria;
              }
              PEC_CriaPeca((Peca **)&(tabuleiro[i * TamLinhas + j].elemento),'V','V');
              idListaAmeacadosY++;
              idListaAmeacantesY++;
              j++;
         }
         idListaAmeacadosX++;
         idListaAmeacantesX++;
         i++;
    }
       return TAB_CondRetOK;
   }
 TAB_tpCondRet TAB_InserirPeca(Casa *tabuleiro,int x, int yi,char cor,char id) {
        //int yi = (int)(y - 'A');
	    char corObtida,idObtida;
       
		printf("Criou a lista\n");
        if(x>7 || x<0 || yi>7 || yi<0) {
            return TAB_CondRetCoordenadaNExiste; 
        }
		
        retPeca = PEC_CriaPeca((Peca **)&(tabuleiro[x * 8 + yi].elemento),id,cor);//cria pe�a novo
		printf("criou pe�a\n");
        if(retPeca == PEC_CondRetFaltouMemoria) {
            return TAB_CondRetFaltouMemoria;
        }
		printf("%d e %d\n",x,yi);
		//printf("cor obtida: %c e id obtida: %c\n",corObtida,idObtida);
        retLis = LIS_InserirNo(listaPecas,tabuleiro[x * 8 + yi].elemento); //insere pe�a nova na lista
        retPeca = PEC_EnsinaMovimentosPecasConhecidas((Peca **)&tabuleiro[x * 8 + yi].elemento); //obtem o movimento da pe�a caso esta for "conhecida"
		printf("Chegou aqui");
        if(retPeca == PEC_CondRetFaltouMemoria) {
            return TAB_CondRetOK;
        }
        if(retPeca == PEC_CondRetNaoAchouPeca) { //caso insere o movimento
             retPeca = PEC_EnsinaMovimentosPecasDesconhecidas((Peca **)&tabuleiro[x * 8 + yi].elemento);
             if(retPeca == PEC_CondRetFaltouMemoria) {
                return TAB_CondRetFaltouMemoria;
             }
        }
        return TAB_CondRetOK;
   }/* Fim fun��o: TAB  &Inserir Peca*/

 TAB_tpCondRet TAB_ObterPeca(Casa *tabuleiro,int x, int y, char *cor, char *id) {
          Peca *peca;
		  char corPec,idPec;
		  printf("Chegou aqui peca\n");
          if(x>7 || x<0 || y>7 || y < 0) {
			  printf("deu blade aqui\n");
             return TAB_CondRetCoordenadaNExiste; 
          }
          peca = (Peca *)(tabuleiro[x * 8 + y].elemento);
		  printf("cheguei aqui\n");
		  PEC_RetornaCor(peca,&corPec);
		  PEC_RetornaId(peca,&idPec);
          if(corPec== 'V' &&  idPec== 'V') {
			  printf("Ta vazio porra""\n");
             return TAB_CondRetCasaVazia;
          }
          printf("Cor: %c e id: %c\n",corPec,idPec);
          *cor = corPec;
          *id = idPec;
          return TAB_CondRetOK;
   }/* Fim fun��o: TAB  &Obter Peca */

    TAB_tpCondRet TAB_RetirarPeca(Casa *tabuleiro,int x,int y) {
          Peca *peca;
		  char corPec,idPec;
		  printf("\nRetirar");
          
          if(x>7 || x<0 || y>7 || y<0) {
             return TAB_CondRetCoordenadaNExiste; 
          }
		  peca = (Peca *)tabuleiro[x * 8 + y].elemento;
          PEC_RetornaCor(peca,&corPec);
		  PEC_RetornaId(peca,&idPec);
          if(corPec== 'V' &&  idPec== 'V') {
             return TAB_CondRetCasaVazia;
          }
          
			PEC_EliminarPeca(peca);
          return TAB_CondRetOK;
   }/* Fim fun��o: TAB  &Retirar Peca */
int main()
{
	 Casa  *tabuleiro[8][8];
	 char cor,id;
	 TAB_tpCondRet CondRet;
	 //Criar
	 CondRet = TAB_CriaTabuleiro((Casa*)tabuleiro,8,8);
	 //Inserir 
	 CondRet = TAB_InserirPeca((Casa*)tabuleiro, 0, 0, 'B','T');
	 CondRet = TAB_InserirPeca((Casa*)tabuleiro, 0, 7, 'B','T');
	 CondRet = TAB_InserirPeca((Casa*)tabuleiro, 7, 0, 'P','T');
	 CondRet = TAB_InserirPeca((Casa*)tabuleiro, 7, 7, 'P','T');
	 CondRet = TAB_InserirPeca((Casa*)tabuleiro, 0, 3, 'B','D');
	 CondRet = TAB_InserirPeca((Casa*)tabuleiro, 7, 3, 'P','D');
	 CondRet = TAB_InserirPeca((Casa*)tabuleiro, 0, 2, 'B','B');
	 CondRet = TAB_InserirPeca((Casa*)tabuleiro, 0, 5, 'B','B');
	 CondRet = TAB_InserirPeca((Casa*)tabuleiro, 7, 2, 'P','B');
	 CondRet = TAB_InserirPeca((Casa*)tabuleiro, 7, 5, 'P','B');
	 CondRet = TAB_InserirPeca((Casa*)tabuleiro, 0, 1, 'B','C');
	 CondRet = TAB_InserirPeca((Casa*)tabuleiro, 0, 6, 'B','C');
	 CondRet = TAB_InserirPeca((Casa*)tabuleiro, 7, 1, 'P','C');
	 CondRet = TAB_InserirPeca((Casa*)tabuleiro, 7, 6, 'P','C');
	 CondRet = TAB_InserirPeca((Casa*)tabuleiro, 0, 4, 'B','R');
	 CondRet = TAB_InserirPeca((Casa*)tabuleiro, 7, 4, 'P','R');
	 CondRet = TAB_InserirPeca((Casa*)tabuleiro,2,5,'B','H');

	 //Obter
	 CondRet = TAB_ObterPeca((Casa*)tabuleiro,0,0,&cor,&id);
	 printf("\nCOR:%c  \nID:%c",cor,id); 
	  CondRet = TAB_ObterPeca((Casa*)tabuleiro,0,7,&cor,&id);
	 printf("\nCOR:%c  \nID:%c",cor,id); 
	  CondRet = TAB_ObterPeca((Casa*)tabuleiro,7,0,&cor,&id);
	 printf("\nCOR:%c  \nID:%c",cor,id); 
	  CondRet = TAB_ObterPeca((Casa*)tabuleiro,7,7,&cor,&id);
	 printf("\nCOR:%c  \nID:%c",cor,id); 
	  CondRet = TAB_ObterPeca((Casa*)tabuleiro,0,3,&cor,&id);
	 printf("\nCOR:%c  \nID:%c",cor,id); 
	  CondRet = TAB_ObterPeca((Casa*)tabuleiro,7,3,&cor,&id);
	 printf("\nCOR:%c  \nID:%c",cor,id); 
	  CondRet = TAB_ObterPeca((Casa*)tabuleiro,0,2,&cor,&id);
	 printf("\nCOR:%c  \nID:%c",cor,id); 
	  CondRet = TAB_ObterPeca((Casa*)tabuleiro,0,5,&cor,&id);
	 printf("\nCOR:%c  \nID:%c",cor,id); 
	  CondRet = TAB_ObterPeca((Casa*)tabuleiro,7,2,&cor,&id);
	 printf("\nCOR:%c  \nID:%c",cor,id); 
	  CondRet = TAB_ObterPeca((Casa*)tabuleiro,7,5,&cor,&id);
	 printf("\nCOR:%c  \nID:%c",cor,id); 
	  CondRet = TAB_ObterPeca((Casa*)tabuleiro,0,1,&cor,&id);
	 printf("\nCOR:%c  \nID:%c",cor,id); 
	   CondRet = TAB_ObterPeca((Casa*)tabuleiro,0,6,&cor,&id);
	 printf("\nCOR:%c  \nID:%c",cor,id); 
	   CondRet = TAB_ObterPeca((Casa*)tabuleiro,7,1,&cor,&id);
	 printf("\nCOR:%c  \nID:%c",cor,id); 
	   CondRet = TAB_ObterPeca((Casa*)tabuleiro,7,6,&cor,&id);
	 printf("\nCOR:%c  \nID:%c",cor,id); 
	   CondRet = TAB_ObterPeca((Casa*)tabuleiro,0,4,&cor,&id);
	 printf("\nCOR:%c  \nID:%c",cor,id); 
	   CondRet = TAB_ObterPeca((Casa*)tabuleiro,7,4,&cor,&id);
	 printf("\nCOR:%c  \nID:%c",cor,id); 
	 CondRet = TAB_ObterPeca((Casa*)tabuleiro,2,5,&cor,&id);
	  printf("\nCOR:%c  \nI:%c",cor,id); 
	/* CondRet = TAB_RetirarPeca((Casa*)tabuleiro,1,5);
	 CondRet = TAB_ObterPeca((Casa*)tabuleiro,1,4,&cor,&id);
	 printf("\nCor:%c  \nId:%c",cor,id); 
	 CondRet = TAB_RetirarPeca((Casa*)tabuleiro,1,5);
	  CondRet = TAB_ObterPeca((Casa*)tabuleiro,1,5,&cor,&id);
	 printf("\nCor:%c  \nId:%c",cor,id);  
	 */
}