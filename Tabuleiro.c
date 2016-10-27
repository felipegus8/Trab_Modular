/***************************************************************************
 *  $MCI Módulo de implementação: TAB  Tabuleiro
 *  Arquivo gerado:              Tabuleiro.c
 *  Letras identificadoras:      TAB
 *
 *  Autores: Felipe Viberti,Luis Claudio e Victor Nogueira
 *
 *  $HA Histórico de evolução:
 *     Versão  Autores                                           Data          Observações
 *     1       Felipe Viberti,Luis Claudio e Victor Nogueira   27/set/2016  início desenvolvimento
 *
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Tabuleiro.h"

char idListaPecas[5] = "PeLi"; //identificação da lista de peças
LIS_tppLista listaPecas;
LIS_tpCondRet  retLis = LIS_CondRetOK;
LIS_tpCondRet retLis2 = LIS_CondRetOK;
PEC_tpCondRet retPeca = PEC_CondRetOK;
char a[] = "amd";
char b[] = "amn";


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

//typedef Tabuleiro * ptTabuleiro;

/***** Protótipos das funções encapuladas no módulo *****/
void destruirValor(void *pValor);
TAB_tpCondRet criarListaPecas();
void TAB_VerificaSeCome(ptTabuleiro tabu,int xo,int yo,int xd,int yd,char corRecebida,char idRecebido);
TAB_tpCondRet verificaMovimento(int posIniX,int posIniY,Peca *p,int movX,int movY,Tabuleiro *tabu,char corPeca,int qtdUnitarios);
int verificaHard(Tabuleiro *tabu,int *movimentoX, int *movimentoY,int posX,int posY,int qtdMov,int qtdFaltaX,int qtdFaltaY,char cor);
/*****  Código das funções exportadas pelo módulo  *****/
/***************************************************************************
 *
 *  Função: TAB  &Criar Tabuleiro
 *  ****/


TAB_tpCondRet TAB_CriaTabuleiro(ptTabuleiro *tabu) {
    int i,j;
    ptTabuleiro novo = (Tabuleiro *) malloc(sizeof(Tabuleiro));
    
    char cor,id;
    criarListaPecas();
    
    if(novo == NULL) {
        //printf("bayblade\n");
        exit(-1);
    }
    for(i=0;i<8;i++) {
        for(j=0;j<8;j++) {
            PEC_CriaPeca((Peca **)&(novo->tab[i][j].elemento),'V','V');
            LIS_CriarLista((LIS_tppLista *)&(novo->tab[i][j].ameacados),a,destruirValor);
            LIS_CriarLista((LIS_tppLista *)&(novo->tab[i][j].ameacantes),b,destruirValor);
            PEC_RetornaCor((Peca *)(novo->tab[i][j].elemento),&cor);
            PEC_RetornaId((Peca *)(novo->tab[i][j].elemento),&id);
            //printf("cor: %c e id: %c",cor,id);
        }
    }
    *tabu = novo;
    return TAB_CondRetOK;
}/* Fim função: TAB  &Criar Tabuleiro*/
/***************************************************************************
 *
 *  Função: TAB  &Inserir Peca
 *  ****/
TAB_tpCondRet TAB_InserirPeca(ptTabuleiro tabuleiro,int x, int yi,char cor,char id) {
    //int yi = (int)(y - 'A');
    //printf("Criou a lista\n");
    if(x>7 || x<0 || yi>7 || yi<0) {
        return TAB_CondRetCoordenadaNExiste;
    }
    
    retPeca = PEC_CriaPeca((Peca **)&(tabuleiro->tab[x][yi].elemento),id,cor);//cria peça nova
    //printf("criou peça\n");
    if(retPeca == PEC_CondRetFaltouMemoria) {
        return TAB_CondRetFaltouMemoria;
    }
    //printf("%d e %d\n",x,yi);
    //printf("cor obtida: %c e id obtida: %c\n",corObtida,idObtida);
    retLis = LIS_InserirNo(listaPecas,(void *)(tabuleiro->tab[x][yi].elemento)); //insere peça nova na lista
    retPeca = PEC_EnsinaMovimentosPecasConhecidas((Peca **)&(tabuleiro->tab[x][yi].elemento)); //obtem o movimento da peça caso esta for "conhecida"
    //printf("Chegou aqui");
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


/***************************************************************************
 *
 *  Função: TAB  &Obter Peca
 *  ****/
TAB_tpCondRet TAB_ObterPeca(ptTabuleiro tabu,int x, int y, char *cor, char *id) {
    char corObtida,idObtido;
    //printf("Chegou aqui peca\n");
    if(x>7 || x<0 || y>7 || y < 0) {
        //printf("deu blade aqui\n");
        return TAB_CondRetCoordenadaNExiste;
    }
    
    PEC_RetornaCor((Peca *)(tabu->tab[x][y].elemento),&corObtida);
    PEC_RetornaId((Peca *)(tabu->tab[x][y].elemento),&idObtido);
			 //printf("linha: %d e coluna: %d\n",x,y);
    //printf("cor: %c e id: %c\n",corObtida,idObtido);
    *cor = corObtida;
    *id = idObtido;
    
    return TAB_CondRetOK;
}/* Fim função: TAB  &Obter Peca */

/***************************************************************************
 *
 *  Função: TAB  &Retirar Peca
 *  ****/
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
}/* Fim função: TAB  &Retirar Peca */

/***************************************************************************
 *
 *  Função: TAB  &Obter Lista Ameacantes
 *  ****/
TAB_tpCondRet TAB_ObterListaAmeacantes(ptTabuleiro tabu,int x, int y,LIS_tppLista *listaAmeacantes)
{
    
    LIS_tppLista listaAmeacantesCopia = NULL;
    LIS_CriarLista(&listaAmeacantesCopia,a,destruirValor);
    //printf("to na obter ameaçantes\n");
    if(listaAmeacantesCopia == NULL) {
        return TAB_CondRetListaAmeacantesNaoExiste;
    }
    //printf("%d\n",listaAmeacantesCopia);
    if(x>7 || x<0 || y>7 || y<0) {
        return TAB_CondRetCoordenadaNExiste;
    }
    //printf("tabu :%d\n",tabu->tab[x][y].ameacantes);
    listaAmeacantesCopia = tabu->tab[x][y].ameacantes;
    // printf("atribuiu\n");
    *listaAmeacantes = listaAmeacantesCopia;
    //printf("atribui2\n");
    //printf("Copia: %d\n",listaAmeacantesCopia);
    
    
    return TAB_CondRetOK;
}
/* Fim função: TAB  &Obter Lista Ameacantes*/
/***************************************************************************
 *
 *  Função: TAB  &Obter Lista Ameacados
 *  ****/
TAB_tpCondRet TAB_ObterListaAmeacados(ptTabuleiro tabu,int x, int y,LIS_tppLista *listaAmeacados)
{
    LIS_tppLista listaAmeacadosCopia = NULL;
    LIS_CriarLista(&listaAmeacadosCopia,a,destruirValor);
    if(listaAmeacadosCopia == NULL) {
        return TAB_CondRetListaAmeacantesNaoExiste;
    }
    if(x>7 || x<0 || y>7 || y<0) {
        return TAB_CondRetCoordenadaNExiste;
    }
    listaAmeacadosCopia = tabu->tab[x][y].ameacados;
    *listaAmeacados = listaAmeacadosCopia;
    
    return TAB_CondRetOK;
}
/* Fim função: TAB  &Obter Lista Ameacados Peca */

/***************************************************************************
 *
 *  Função: TAB  &Mover Peca
 *  ****/
TAB_tpCondRet TAB_MoverPeca(ptTabuleiro tabu,int xo,int yi,int xd,int yi2) {
    char corPecaLista,corPecaTabuleiro,idPecaLista,idPecaTabuleiro;
    int i,qtdMov,movX,movY,moveParaTras,xObtido,yObtido,achou = 0,qtdUnitarios = 0;
    Peca *pecaLista = NULL;
    
    //printf("ta na movimento\n");
    
	   PEC_CriaPeca((Peca **)&pecaLista,'V','V');
	   //printf("sai da criar peça\n");
	   
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
    
		  //printf("Entrarei na verifica\n");
    
    printf("xd - xo: %d\n e yi2 - yi: %d\n",xd - xo, yi2 - yi);
    
    printf("id: %c\n",idPecaLista);
    
    printf("qtdMov: %d\n",qtdMov);
    
    for(i=0;i<qtdMov;i++) {
        //printf("Entrei no for\n");
        //printf("antes\n");
        PEC_RetornaXMovimento(pecaLista,i,&xObtido);
        PEC_RetornaYMovimento(pecaLista,i,&yObtido);
        //printf("depois\n");
        //printf("Sai dos retorna\n");
        //printf("xObtido: %d e yObtido: %d e i: %d\n",xObtido,yObtido,i);
        if (xObtido == xd - xo && yObtido == yi2 - yi) {
            achou = 1;
        }
        if(0<=abs(xObtido) && abs(xObtido)<=1 && abs(yObtido)>=0 && abs(yObtido)<=1 && (xObtido != 0 || yObtido != 0)) {
            printf("X: %d\n",xObtido);
            printf("Y: %d\n",yObtido);
            printf("\n\n");
            qtdUnitarios++;
        }
    }
    printf("qtdUnitarios: %d\n",qtdUnitarios);
    
    printf("achou: %d\n",achou);
    
    if(achou == 1) {
        return verificaMovimento(xo,yi,pecaLista,xd,yi2,tabu,corPecaLista,qtdUnitarios);
    }
		  /*
           for(i=0;i<qtdMov;i++) {
           movX = xd - xo; //quantidade de passos que a peça tentará se mover na horizontal
           printf("MOVX:%d",movX);
           movY = yi2 - yi; //quantidade de passos que a peça tentará se mover na vertical
           printf("MOVY:%d",movY);
           PEC_RetornaXMovimento(pecaLista,i,&xRet);//recebe a quantidade de peças na horizontal que a peça realiza
           printf("\nX:%d\n",xRet);
           PEC_RetornaYMovimento(pecaLista,i,&yRet);//recebe a quantidade de peças na vertical que a peça realiza
           printf("\nY:%d\n",yRet);
           verificaMovimento(xo,yi,);
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
           */
    return TAB_CondRetMovimentoIrregular;
}/* Fim função: TAB  &Mover Peca */

/***************************************************************************
 *
 *  Função: TAB  &Destruir Tabuleiro
 *  ****/
TAB_tpCondRet TAB_DestruirTabuleiro(ptTabuleiro tabu) {
    int i=0,j;
    while(i<8) {
        j=0;
        while(j<8) {
            if(tabu->tab[i][j].elemento != NULL) {
                LIS_DestroiLista(tabu->tab[i][j].ameacados);
                LIS_DestroiLista(tabu->tab[i][j].ameacantes);
                
                PEC_LiberaPeca((Peca*)tabu->tab[i][j].elemento);
            }
            j++;
        }
        i++;
    }
    return TAB_CondRetOK;
}/* Fim função: TAB  &Destruir Tabuleiro*/

/***************************************************************************
 
 
 /*****  Código das funções encapsuladas no módulo  *****/

/***************************************************************************
 *
 *  Função: TAB  -Verifica Se Come
 *  ****/
void TAB_VerificaSeCome(ptTabuleiro tabu,int xo,int yo,int xd,int yd,char corRecebida,char idRecebido) {
    char corObtida,idObtido;
    
    TAB_ObterPeca(tabu,xd,yd,&corObtida,&idObtido);
    
    if(corRecebida != corObtida) {
        TAB_RetirarPeca(tabu,xd,yd);
        TAB_RetirarPeca(tabu,xo,yo);
        TAB_InserirPeca(tabu,xd,yd,corRecebida,idRecebido);
    } else {
        if(idObtido == 'V' && corObtida == 'V') {
            TAB_RetirarPeca(tabu,xo,yo);
            TAB_InserirPeca(tabu,xd,yd,corRecebida,idRecebido);
        }
    }
}/* Fim função: TAB  -Verifica Se Come*/



/***************************************************************************
 *
 *  Função: TAB  &Destruir Valor
 *  ****/
void destruirValor(void *pValor) {
    free(pValor);
}/* Fim função: TAB  -Destruir Valor*/
/***************************************************************************
 *
 *  Função: TAB  &Criar Lista Pecas
 *  ****/
TAB_tpCondRet criarListaPecas() {
    retLis = LIS_CriarLista(&listaPecas,idListaPecas,destruirValor);
    if(retLis == LIS_CondRetOK) {
        return TAB_CondRetOK;
    }
    return TAB_CondRetFaltouMemoria;
}/* Fim função: TAB  -Criar Lista Pecas*/

int *verificaDirecaoSeguida(int *movimentoX,int *movimentoY,int qtdFaltaX,int qtdFaltaY,int qtdMov){
    int i,*retorno;
    retorno = (int *) malloc(sizeof(int) *2);
    printf("qtd UNi: %d\n",qtdMov);
    if(retorno == 0) {
        printf("Erro no retorno\n");
        exit(-1);
    }
    retorno[0] = 0;
    retorno[1] = 0;
    printf("Qtd falta: (%d,%d)\n",qtdFaltaX,qtdFaltaY);
    for (i=0;i<qtdMov;i++) {
        
        if(movimentoX[i] != 0 && movimentoY[i] != 0) {
            
            if(qtdFaltaX/movimentoX[i]== qtdFaltaY / movimentoY[i] && qtdFaltaX/movimentoX[i]> 0 && qtdFaltaY/movimentoY[i]>0) {
                    retorno[0] = movimentoX[i];
                    retorno[1] = movimentoY[i];
            }
        } else {
            if(qtdFaltaX == 0) {
                printf("Y: %d\n",movimentoY[i]);
                if (movimentoX[i] == 0 && qtdFaltaY/movimentoY[i]>0) {
                    retorno[0] = movimentoX[i];
                    retorno[1] = movimentoY[i];
                }
            } else if(qtdFaltaY == 0){
                if (movimentoY[i] == 0 && qtdFaltaX/movimentoX[i]>0) {
                    retorno[0] = movimentoX[i];
                    retorno[1] = movimentoY[i];
                }
            }
        }
    }
    return retorno;
}


int verificaHard(Tabuleiro *tabu,int *movimentoX, int *movimentoY,int posX,int posY,int qtdMov,int qtdFaltaX,int qtdFaltaY,char cor) {
    int *direcao,i,xDirecao,yDirecao,diretor,qtdFalta;
    char idObtido,corObtida;
    TAB_tpCondRet condRet;
    
    
    direcao = verificaDirecaoSeguida(movimentoX,movimentoY,qtdFaltaX,qtdFaltaY,qtdMov);
    
    xDirecao = direcao[0];
    yDirecao = direcao[1];
    
    printf("Retorno: (%d,%d)\n",direcao[0],direcao[1]);
    
    if(xDirecao == 0) {
        diretor = yDirecao;
        qtdFalta = qtdFaltaY;
    } else {
        diretor = xDirecao;
        qtdFalta = qtdFaltaX;
    }

    printf("Até: %d\n",qtdFalta/diretor);
    
    for (i=0; i<qtdFalta/diretor; i++) {
        printf("ENtrei no loop\n");
        condRet = TAB_ObterPeca(tabu,posX + xDirecao,posY + yDirecao,&corObtida,&idObtido);
        qtdFaltaX -= xDirecao;
        qtdFaltaY -= yDirecao;
        posX += xDirecao;
        posY += yDirecao;
        if (corObtida != 'V') {
            if (qtdFaltaX == 0 && qtdFaltaY == 0) {
                if (corObtida != cor) {
                    printf("Comeu\n");
                    return 1;
                }
                printf("barrado\n");
            }
        } else {
            if (qtdFaltaX == 0 && qtdFaltaY == 0) {
                printf("Chegou sem comer\n");
                return 1;
            }
        }
        
        
    }
        
    
    //printf("Falta x: %d e Falta y: %d\n",qtdFaltaX,qtdFaltaY);
    //printf("Cheguei na hard\n");
    /*
    for(i=0;i<qtdMov;i++) {
        printf("(%d,%d)\n",movimentoX[i],movimentoY[i]);
        condRet = TAB_ObterPeca(tabu,posX + movimentoX[i],posY + movimentoY[i],&corObtida,&idObtido); obtem propriedades da peca para onde o movimentoCorrente levaria
        if(condRet == TAB_CondRetOK) {
            if(qtdFaltaX == movimentoX[i] && qtdFaltaY == movimentoY[i]) {
                printf("Entrei onde devia\n");
                if(idObtido != 'V') {
                    //printf("entrei aqui\n");
                    if(corObtida != cor) {
                        return 1;
                    }
                    return 0;
                }
                return 1;
            } else if((qtdFaltaX == 0 && movimentoX[i]!=0) || (qtdFaltaY == 0 && movimentoY[i] != 0)) {
                //printf("x: %d e y: %d\n",movimentoX[i],movimentoY[i]);
                //printf("Entrei onde n devia %d\n",i);
                continue;
            } else {
                if(idObtido == 'V') {
                    //printf("ENtrei no brabo\n");
                    retorno = verificaHard(tabu,movimentoX,movimentoY,posX + movimentoX[i],posY + movimentoY[i],qtdMov,qtdFaltaX - movimentoX[i], qtdFaltaY - movimentoY[i],cor);
                    if(retorno == 1) {
                        return 1;
                    }
                }
            }
        } else {
            return 0;
        }
    }
     */
    return 0;
    
}



TAB_tpCondRet verificaMovimento(int posIniX,int posIniY,Peca *p,int movX,int movY,Tabuleiro *tabu,char corPeca,int qtdUnitarios) {
    int qtdMov,*movimentoX,*movimentoY,i,j=0,retornoHard,xObtido,yObtido;
    PEC_RetornaQtd_Mov(p,&qtdMov);
		  //printf("qtd mov:%d\n",qtdMov);
		  //printf("%c\n\n\n\n\n",idPeca);
    movimentoX = (int *) malloc(sizeof(int) * qtdUnitarios);
		  if(movimentoX == NULL) {
              printf("deu ruim na criar X\n");
              exit(-1);
          }
    movimentoY = (int *) malloc(sizeof(int) * qtdMov);
		  if(movimentoY == NULL) {
              printf("deu ruim na criar Y\n");
              exit(-1);
          }
		  //printf("i dps: %d\n",i);
		  //printf("Entre na verifica\n");
    for(i=0;i<qtdMov;i++) {
        //printf("Entrei no for\n");
        PEC_RetornaXMovimento(p,i,&xObtido);
        PEC_RetornaYMovimento(p,i,&yObtido);
        printf("Sai dos retorna\n");
        if(0<=abs(xObtido) && abs(xObtido)<=1 && abs(yObtido)>=0 && abs(yObtido)<=1 && (xObtido != 0 || yObtido != 0)) {
            movimentoX[j] = xObtido;
            movimentoY[j] = yObtido;
            printf("X: %d\n",xObtido);
            printf("Y: %d\n",yObtido);
            j++;
            //printf("Consegui atribuir\n");
        }
        //printf("saiu do atribuir i:%d\n",i);
        
        /*
         if(movX==xObtido && movY==yObtido) {
         printf("Entrei no remainder\n");
         
         }
         */
        //printf("Chegou no fim do loop\n");
 	  }
    retornoHard = verificaHard(tabu,movimentoX,movimentoY,posIniX,posIniY,qtdUnitarios,movX - posIniX,movY - posIniY,corPeca);
    if(retornoHard == 1) {
        //printf("/*--------------------: %d\n-------------*/\n",j);
        return TAB_CondRetOK;
    }
    
		  //printf("sai da verifica\n");
    return TAB_CondRetMovimentoIrregular;
    
}


/********** Fim do módulo de implementação: TAB  Tabuleiro **********/
