#include<stdio.h>
#include<stdlib.h>
#include "peca.h"
#include "lista.h"
typedef enum {

         TAB_CondRetOK ,
               /* Concluiu corretamente */

         TAB_CondRetCasaVazia ,
               /* A casa não contém peças */

         TAB_CondRetCoordenadaNExiste ,
               /* coordenada inserida não existe */

         TAB_CondRetNaoAchouPeca ,
               /* Não encontrou a peca procurada */

         TAB_CondRetFaltouMemoria ,
               /* Faltou memória ao tentar criar uma lista dentro da casa*/
         
         TAB_CondRetListaAmeacadosNaoExiste ,
               /* lista de elementos ameaçados pela peça não foi criado*/
         
         TAB_CondRetListaAmeacantesNaoExiste ,
               /* lista de elementos que ameaçam a peça não foi criado*/
         
         TAB_CondRetMovimentoIrregular,
              /* o movimento que foi tentando é irregular */
         TAB_CondRetComeu, 
               /* um movimento válido fez com que uma peça fosse comida */
         TAB_CondRetCasaTemDono,

              /* um movimento válido fez com que uma peça fosse para um posição onde há um peça de sua cor */

		 TAB_CondRetCorErrada,
		     /* cor obtida está errado */
		 TAB_CondRetIdErrado
		    /* id obtido está errado */
   } TAB_tpCondRet ;

char idListaPecas[5] = "PeLi"; //identificação da lista de peças
LIS_tppLista listaPecas;
LIS_tpCondRet  retLis = LIS_CondRetOK;
LIS_tpCondRet retLis2 = LIS_CondRetOK;
PEC_tpCondRet retPeca = PEC_CondRetOK;


typedef struct casa {
         LIS_tppLista ameacados;
         /* ponteiro para a cabeça da lista que contém as peças ameaçadas pela peça da casa */
         LIS_tppLista ameacantes;
         /* ponteiro para a cabeça da lista que contém as peças que ameaçam a peça da casa */
         void *elemento;
         /*ponteiro para o elemento contido na casa */
   } Casa;

typedef struct TAG_tabuleiro {
	Casa tab[8][8];
}Tabuleiro;

typedef Tabuleiro * ptTabuleiro;


   void destruirValor(void *pValor) {
        free(pValor);
   }/* Fim função: TAB  -Destruir Valor*/
TAB_tpCondRet criarListaPecas() {
    retLis = LIS_CriarLista(&listaPecas,idListaPecas,destruirValor);
    if(retLis == LIS_CondRetOK) {
        return TAB_CondRetOK;
    }
    return TAB_CondRetFaltouMemoria;
}

TAB_tpCondRet TAB_CriaTabuleiro(ptTabuleiro *tabu,int TamLinhas, int TamColunas) {
	int i,j;
    ptTabuleiro novo = (Tabuleiro *) malloc(sizeof(Tabuleiro));
    char a[] = "amd";
    char b[] = "amn";
    char cor,id;
	criarListaPecas();
	
    if(novo == NULL) {
        printf("bayblade\n");
        exit(-1);
    }


    for(i=0;i<8;i++) {
        for(j=0;j<8;j++) {
            PEC_CriaPeca((Peca **)&(novo->tab[i][j].elemento),'V','V');
			LIS_CriarLista((LIS_tppLista *)&(novo->tab[i][j].ameacados),a,destruirValor);
			LIS_CriarLista((LIS_tppLista *)&(novo->tab[i][j].ameacados),a,destruirValor);
			PEC_RetornaCor((Peca *)(novo->tab[i][j].elemento),&cor);
			PEC_RetornaId((Peca *)(novo->tab[i][j].elemento),&id);
			printf("cor: %c e id: %c",cor,id);
        }
    }
    *tabu = novo;


	/*
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
	*/
	
       return TAB_CondRetOK;
   }
 TAB_tpCondRet TAB_InserirPeca(ptTabuleiro tabuleiro,int x, int yi,char cor,char id) {
        //int yi = (int)(y - 'A');
		printf("Criou a lista\n");
        if(x>7 || x<0 || yi>7 || yi<0) {
            return TAB_CondRetCoordenadaNExiste; 
        }
		
        retPeca = PEC_CriaPeca((Peca **)&(tabuleiro->tab[x][yi].elemento),id,cor);//cria peça nova
		printf("criou peça\n");
        if(retPeca == PEC_CondRetFaltouMemoria) {
            return TAB_CondRetFaltouMemoria;
        }
		printf("%d e %d\n",x,yi);
		//printf("cor obtida: %c e id obtida: %c\n",corObtida,idObtida);
		retLis = LIS_InserirNo(listaPecas,(void *)(tabuleiro->tab[x][yi].elemento)); //insere peça nova na lista
        retPeca = PEC_EnsinaMovimentosPecasConhecidas((Peca **)&(tabuleiro->tab[x][yi].elemento)); //obtem o movimento da peça caso esta for "conhecida"
		printf("Chegou aqui");
        if(retPeca == PEC_CondRetFaltouMemoria) {
            return TAB_CondRetOK;
        }
        if(retPeca == PEC_CondRetNaoAchouPeca) { //caso insere o movimento
             retPeca = PEC_EnsinaMovimentosPecasDesconhecidas((Peca **)&(tabuleiro->tab[x][yi].elemento));
             if(retPeca == PEC_CondRetFaltouMemoria) {
                return TAB_CondRetFaltouMemoria;
             }
        }
        return TAB_CondRetOK;
	
   }/* Fim função: TAB  &Inserir Peca*/

 TAB_tpCondRet TAB_ObterPeca(ptTabuleiro tabu,int x, int y, char *cor, char *id) {
	 char corObtida,idObtido;


      printf("Chegou aqui peca\n");
          if(x>7 || x<0 || y>7 || y < 0) {
			  printf("deu blade aqui\n");
             return TAB_CondRetCoordenadaNExiste; 
          }

	 PEC_RetornaCor((Peca *)(tabu->tab[x][y].elemento),&corObtida);
			PEC_RetornaId((Peca *)(tabu->tab[x][y].elemento),&idObtido);
			printf("linha: %d e coluna: %d\n",x,y);
			printf("cor: %c e id: %c\n",cor,id);

	 *cor = corObtida;
	 *id = idObtido;

	 /*
          Peca *peca;
		  char corPec,idPec;
		  
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
		  */
   }/* Fim função: TAB  &Obter Peca */

    TAB_tpCondRet TAB_RetirarPeca(ptTabuleiro tabu,int x,int y) {
		char corObtida,idObtido;
		
		 if(x>7 || x<0 || y>7 || y<0) {
             return TAB_CondRetCoordenadaNExiste; 
          }


		 PEC_RetornaCor((Peca *)(tabu->tab[x][y].elemento),&corObtida);
		 PEC_RetornaId((Peca *)(tabu->tab[x][y].elemento),&idObtido);
		 
		 if(corObtida== 'V' &&  idObtido== 'V') {
             return TAB_CondRetCasaVazia;
          }
		 PEC_EliminarPeca((Peca *)(tabu->tab[x][y].elemento));
          return TAB_CondRetOK;

		/*
          Peca *peca;
		  char corPec,idPec;
		  printf("\nRetirar");
          
          
		  peca = (Peca *)tabuleiro[x * 8 + y].elemento;
          PEC_RetornaCor(peca,&corPec);
		  PEC_RetornaId(peca,&idPec);
          
          
			
		  */
   }/* Fim função: TAB  &Retirar Peca */


 TAB_tpCondRet TAB_VerificaSeCome(ptTabuleiro tabu,int xo,int yo,int xd,int yd,char corRecebida,char idRecebido) {
	char corObtida,idObtido;
	  
        TAB_ObterPeca(tabu,xd,yd,&corObtida,&idObtido);
	  
	 if(corRecebida != corObtida) {
	      TAB_RetirarPeca(tabu,xd,yd);
	      TAB_RetirarPeca(tabu,xo,yo);
	      TAB_InserirPeca(tabu,xd,yd,corRecebida,idRecebido);
	      return TAB_CondRetComeu;
	 } 
	 if(idObtido == 'V' && corObtida == 'V') {
              TAB_RetirarPeca(tabu,xo,yo);
	      TAB_InserirPeca(tabu,xd,yd,corRecebida,idRecebido);
	      return TAB_CondRetOK;
	 }
         return TAB_CondRetCasaTemDono;
  }

   
   TAB_tpCondRet TAB_MoverPeca(ptTabuleiro tabu,int xo,int yi,int xd,int yi2) {
          char corPecaLista,corPecaTabuleiro,idPecaLista,idPecaTabuleiro;
          int i,qtdMov,movX,movY,moveParaTras,xRet,yRet;
          char id;
	  Peca *pecaLista = NULL;
	  
	   
	   PEC_CriaPeca((Peca **)&pecaLista,'V','V');
	   
	   LIS_ObterNo(listaPecas,(void **)&pecaLista); //obtem cor e id de peça do tabuleiro
	   
	   TAB_ObterPeca(tabu,xo,yi,&corPecaTabuleiro,&idPecaTabuleiro);
	   
	   /*  obtem cor e id de peça da lista */
	   PEC_RetornaCor((Peca *)pecaLista,&corPecaLista);   
	   PEC_RetornaId((Peca *)pecaLista,&idPecaLista);
	   
	   IrInicioLista(listaPecas);
	   
	   while(1) {   
		   
	        if(idPecaTabuleiro == idPecaLista) {  //caso a peça esteja na lista sai do loop
		      break;
		}
		LIS_ObterNo(listaPecas,(void **)&pecaLista);
			
		if(LIS_IrProx(listaPecas) == LIS_CondRetFimLista) { //obtem a peça do nó corrente da lista
		       return TAB_CondRetNaoAchouPeca;
		}
		/* obtem a cor e o id da peça corrente */
		PEC_RetornaCor((Peca *)pecaLista,&corPecaLista);   
	        PEC_RetornaId((Peca *)pecaLista,&idPecaLista);
		LIS_IrProx(listaPecas); //anda na lista
	   }
	   
	          PEC_RetornaQtd_Mov(pecaLista,&qtdMov); //obtem o movimento da peça
		  PEC_RetornaMoveParaTras(pecaLista,&moveParaTras); //descobre se a peça pode andar para trás
	   
	    for(i=0;i<qtdMov;i++) {
                movX = xd - xo; //quantidade de passos que a peça tentará se mover na horizontal
                movY = yi2 - yi; //quantidade de passos que a peça tentará se mover na vertical
				PEC_RetornaXMovimento(pecaLista,i,&xRet);//recebe a quantidade de peças na horizontal que a peça realiza
				PEC_RetornaYMovimento(pecaLista,i,&yRet);//recebe a quantidade de peças na vertical que a peça realiza
                if(abs(movX) == xRet && abs(movY) == yRet) {
                        if(movX<0 || movY <0) {
                              if(moveParaTras == 1) {
                                  TAB_VerificaSeCome(tabu,xo,yi,xd, yi2,corPecaTabuleiro,idPecaTabuleiro);
                              }
			      return TAB_CondRetMovimentoIrregular;
                        } else {
			       TAB_VerificaSeCome(tabu,xo,yi,xd, yi2,corPecaTabuleiro,idPecaTabuleiro); 
			}
                       return TAB_CondRetOK;
              }
          }
          return TAB_CondRetMovimentoIrregular;
	   
	   
	   
		 // char idPec;
          //Peca *elemento;
          //int movX,movY,xRet,yRet,moveParaTras;
          //Peca *peca;
	     // Peca *naLista;
		  //int qtdMov;
		  //int yi = (int)(yo - 'A');
          //int yi2 = (int)(yd - 'A');
	   
	   
	   
	   
	   /*
	  printf("Entrei no movimento\n");
          TAB_ObterPeca(tabu,xo,yi,&cor,&id);
	  printf("Passei da obter\n");
          LIS_ObterNo(listaPecas,(void **)&(tabu->tab[xo][yi].elemento));
	  printf("Obteve o nó\n");
          peca = (Peca *)elemento;
           xo--;
           if(xo>7 || xo<0 || yi>7 || yi<0) {
              return TAB_CondRetCoordenadaNExiste; 
           }
         
           xd--;
           if(xd>7 || xd<0 || yi2>7 || yi2<0) {
              return TAB_CondRetCoordenadaNExiste; 
           }
		    PEC_RetornaId(peca,&idPec);

          //procura na lista pelo id da peça e checa se o movimento está ok
          while(1) {
                if(LIS_ObterNo(listaPecas,(void **)(tabu->tab[xo][yi].elemento)) == LIS_CondRetFimLista) {
                     return TAB_CondRetNaoAchouPeca;
                }
                naLista = (Peca *) elemento;
		PEC_RetornaId(naLista, &id);
		if(idPec == id) {
		      break;
		}
              LIS_IrProx(listaPecas);
          }
		  PEC_RetornaQtd_Mov(peca,&qtdMov);
		  PEC_RetornaMoveParaTras(peca,&moveParaTras);
          for(i=0;i<qtdMov;i++) {
                movX = xd - xo;
                movY = yi2 - yi;
				PEC_RetornaXMovimento(peca,i,&xRet);
				PEC_RetornaYMovimento(peca,i,&yRet);
                if(abs(movX) == xRet && abs(movY) == yRet) {
                        if(movX<0 || movY <0) {
                              if(moveParaTras == 1) {
                                  TAB_VerificaSeCome((Casa*)tabuleiro,xd, yi2,cor);
                                   return TAB_CondRetOK;
                              } else {
                                   TAB_VerificaSeCome((Casa*)tabuleiro,xd, yi2,cor);
                                   return TAB_CondRetMovimentoIrregular;
                              }
                        }
                       return TAB_CondRetOK;
              }
          }
          return TAB_CondRetMovimentoIrregular;
   }/* Fim função: TAB  &Mover Peca*/
   }

   
int main()
{
	int i,j;
	char cor,id;
	ptTabuleiro tabu;

	TAB_CriaTabuleiro(&tabu,8,8);
	
	TAB_InserirPeca(tabu,0,1,'P','T');
	TAB_InserirPeca(tabu,1,2,'P','D');
	TAB_InserirPeca(tabu,3,2,'P','H');
	
	printf("\n");
    for(i=0;i<8;i++) {
        for(j=0;j<8;j++) {
			PEC_RetornaCor((Peca *)(tabu->tab[i][j].elemento),&cor);
			PEC_RetornaId((Peca *)(tabu->tab[i][j].elemento),&id);
			printf("linha: %d e coluna: %d\n",i,j);
			printf("cor: %c e id: %c\n",cor,id);
        }
    }
	TAB_MoverPeca(tabu,0,1,0,5);
	 for(i=0;i<8;i++) {
        for(j=0;j<8;j++) {
			PEC_RetornaCor((Peca *)(tabu->tab[i][j].elemento),&cor);
			PEC_RetornaId((Peca *)(tabu->tab[i][j].elemento),&id);
			printf("linha: %d e coluna: %d\n",i,j);
			printf("cor: %c e id: %c\n",cor,id);
        }
    }
	/*
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
