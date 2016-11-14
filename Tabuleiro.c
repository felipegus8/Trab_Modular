/***************************************************************************
 *  $MCI MÛdulo de implementaÁ„o: TAB  Tabuleiro
 *  Arquivo gerado:              Tabuleiro.c
 *  Letras identificadoras:      TAB
 *
 *  Autores: Felipe Viberti,Luis Claudio e Victor Nogueira
 *
 *  $HA HistÛrico de evoluÁ„o:
 *     Vers„o  Autores                                           Data          ObservaÁıes
 *     1       Felipe Viberti,Luis Claudio e Victor Nogueira   27/set/2016  inÌcio desenvolvimento
 *
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Tabuleiro.h"

char idListaPecas[5] = "PeLi"; //identificaÁ„o da lista de peÁas
LIS_tppLista listaPecas;
Peca *lis;
LIS_tpCondRet  retLis = LIS_CondRetOK;
LIS_tpCondRet retLis2 = LIS_CondRetOK;
PEC_tpCondRet retPeca = PEC_CondRetOK;
char a[] = "amd";
char b[] = "amn";


typedef struct casa {
    LIS_tppLista ameacados;
    /* ponteiro para a cabeÁa da lista que contÈm as peÁas ameaÁadas pela peÁa da casa */
    LIS_tppLista ameacantes;
    /* ponteiro para a cabeÁa da lista que contÈm as peÁas que ameaÁam a peÁa da casa */
    void *elemento;
    /*ponteiro para o elemento contido na casa */
} Casa;

typedef struct TAG_tabuleiro {
    Casa tab[8][8];
}Tabuleiro;

//typedef Tabuleiro * ptTabuleiro;

/***** ProtÛtipos das funÁıes encapuladas no mÛdulo *****/
void destruirValor(void *pValor);
TAB_tpCondRet criarListaPecas();
void TAB_VerificaSeCome(ptTabuleiro tabu,int xo,int yo,int xd,int yd,char corRecebida,char idRecebido);
TAB_tpCondRet verificaMovimento(int posIniX,int posIniY,Peca *p,int movX,int movY,Tabuleiro *tabu,char corPeca,int qtdUnitarios,int entra);
int verificaCondMov(ptTabuleiro tabu,int *movimentoX, int *movimentoY,int posX,int posY,int qtdMov,int qtdFaltaX,int qtdFaltaY,char cor);
int *verificaDirecaoSeguida(int *movimentoX,int *movimentoY,int qtdFaltaX,int qtdFaltaY,int qtdMov);
void buscaNaLista(Peca **pecaLista,char *corPecaLista,char idPecaLista,char idPecaTabuleiro);
int contaUnitarios(Peca *pecaLista,int qtdMov);
int verificaCoordenadas(int x, int y);
int verificaPeao(ptTabuleiro tabu,int posIniX,int posIniY,int posFimX,int posFimY,char corPeao);

/*****  CÛdigo das funÁıes exportadas pelo mÛdulo  *****/
/***************************************************************************
 *
 *  FunÁ„o: TAB  &Criar Tabuleiro
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
}/* Fim funÁ„o: TAB  &Criar Tabuleiro*/
/***************************************************************************
 *
 *  FunÁ„o: TAB  &Inserir Peca
 *  ****/
TAB_tpCondRet TAB_InserirPeca(ptTabuleiro tabuleiro,int x, int yi,char cor,char id) {
    //int yi = (int)(y - 'A');
    //printf("Criou a lista\n");
    
    if(x>7 || x<0 || yi>7 || yi<0) {
        
        return TAB_CondRetCoordenadaNExiste;
    }
    
    
    retPeca = PEC_CriaPeca((Peca **)&(tabuleiro->tab[x][yi].elemento),id,cor);//cria peÁa nova
    //printf("criou peÁa\n");
    
    if(retPeca == PEC_CondRetFaltouMemoria) {
        
        return TAB_CondRetFaltouMemoria;
    }
    //printf("%d e %d\n",x,yi);
    //printf("cor obtida: %c e id obtida: %c\n",corObtida,idObtida);
    retLis = LIS_InserirNo(listaPecas,(void *)(tabuleiro->tab[x][yi].elemento)); //insere peÁa nova na lista
    
    //retPeca = PEC_EnsinaMovimentosPecasConhecidas((Peca **)&(tabuleiro->tab[x][yi].elemento)); //obtem o movimento da peÁa caso esta for "conhecida"
    //printf("Chegou aqui");
    /*
     if(retPeca == PEC_CondRetFaltouMemoria) {
     
     return TAB_CondRetOK;
     }
     
     if(retPeca == PEC_CondRetNaoAchouPeca) { //caso insere o movimento
     
     retPeca = PEC_EnsinaMovimentosPecasDesconhecidas((Peca **)&(tabuleiro->tab[x][yi].elemento));
     printf("ENtrou na insere\n");
     if(retPeca == PEC_CondRetFaltouMemoria) {
     
     return TAB_CondRetFaltouMemoria;
     }
     }
     */
    return TAB_CondRetOK;
    
}/* Fim funÁ„o: TAB  &Inserir Peca*/


/***************************************************************************
 *
 *  FunÁ„o: TAB  &Obter Peca
 *  ****/
TAB_tpCondRet TAB_ObterPeca(ptTabuleiro tabu,int x, int y, char *cor, char *id) {
    char corObtida,idObtido;
    
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
}/* Fim funÁ„o: TAB  &Obter Peca */

/***************************************************************************
 *
 *  FunÁ„o: TAB  &Retirar Peca
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
}/* Fim funÁ„o: TAB  &Retirar Peca */

void apagaListas(ptTabuleiro tabu) {
    int i,j;
    for (i=0; i<8; i++) {
        for (j=0; j<8; j++) {
            EsvaziarLista(tabu->tab[i][j].ameacados);
        }
    }
}


/***************************************************************************
 *
 *  FunÁ„o: TAB  &Inicializa Lista Ameacados
 *  ****/

TAB_tpCondRet TAB_AtualizaListaAmeacadosEAmeacantes(ptTabuleiro tabu) {
    /*
     
     char idPecaTabuleiro,corPecaTabuleiro,corPecaUsada,corPecaUsada2,idPecaUsada,idPecaUsada2;
     int qtdUnitarios,qtdMov,verificaMov;
     */
    int i,j,k,xObtido,yObtido,qtdUnitarios,qtdMov,verificaMov;
    char corPecaUsada,corPecaUsada2,idPecaUsada,idPecaUsada2;
    Peca *pecaUsada;
    Peca *pecaUsada2;
    
    
    
    //PEC_CriaPeca(&pecaUsada2, 'V', 'V');
    
    //PEC_CriaPeca(&pecaUsada,'V','V');
    
    for (i=0; i<8; i++) {
        for (j=0; j<8; j++) {
            EsvaziarLista(tabu->tab[i][j].ameacados);
            EsvaziarLista(tabu->tab[i][j].ameacantes);
        }
    }
    
    
    for (i=0; i<8; i++) {
        for (j=0; j<8; j++) {
            pecaUsada = (Peca *) tabu->tab[i][j].elemento;
            PEC_RetornaCor(pecaUsada, &corPecaUsada);
            PEC_RetornaId(pecaUsada, &idPecaUsada);
            PEC_RetornaQtd_Mov(pecaUsada, &qtdMov);
            qtdUnitarios = contaUnitarios(pecaUsada, qtdMov);
            if(corPecaUsada != 'V' && idPecaUsada != 'V') {
            for(k=0;k<qtdMov;k++) {
                PEC_RetornaXMovimento(pecaUsada, k, &xObtido);
                PEC_RetornaYMovimento(pecaUsada, k, &yObtido);
                if(idPecaUsada != 'P' && idPecaUsada  != 'R') {
                    verificaMov = verificaMovimento(i, j, pecaUsada,i + xObtido,j + yObtido, tabu, corPecaUsada, qtdUnitarios,0);
                } else if(idPecaUsada == 'P')  {
                    
                    verificaMov = verificaPeao(tabu, i, j, i + xObtido, j + yObtido, corPecaUsada);
                } else {
                    verificaMov = TAB_VerificaMovimentoRei(tabu, i, j, corPecaUsada, i + xObtido, j + yObtido);
                }
                if(verificaMov == 2) {
                    printf("cor e id in hell comeu: %c e %c e pos:(%d,%d) e %d\n",corPecaUsada,idPecaUsada,i,j,pecaUsada);
                    pecaUsada2 = (Peca *) tabu->tab[i + xObtido][j + yObtido].elemento;
                    printf("isso e %d\n",i + xObtido);
                    PEC_RetornaCor(pecaUsada2, &corPecaUsada2);
                    //printf("Verificou\n");
                    //printf("pos comedor(%d,%d) e posComido(%d,%d)\nidComedor: %c e cor comedor: %c e cor comido: %c\n",i,j,i + xObtido,j + yObtido,idPecaUsada,corPecaUsada,corPecaUsada2);
                    LIS_InserirNo(tabu->tab[i][j].ameacados, (void *)pecaUsada2);
                    LIS_InserirNo(tabu->tab[i + xObtido][j + yObtido].ameacantes, (void *)pecaUsada);
                }
            }
            
            }
        }
    }
    
    
    
    return TAB_CondRetOK;
}

/***************************************************************************
 *
 *  FunÁ„o: TAB  &Obter Lista Ameacantes
 *  ****/
TAB_tpCondRet TAB_ObterListaAmeacantes(ptTabuleiro tabu,int x, int y,LIS_tppLista *listaAmeacantes)
{
    
    LIS_tppLista listaAmeacantesCopia = NULL;
    LIS_CriarLista(&listaAmeacantesCopia,a,destruirValor);
    //printf("to na obter ameaÁantes\n");
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
/* Fim funÁ„o: TAB  &Obter Lista Ameacantes*/
/***************************************************************************
 *
 *  FunÁ„o: TAB  &Obter Lista Ameacados
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
/* Fim funÁ„o: TAB  &Obter Lista Ameacados Peca */

/***************************************************************************
 *
 *  FunÁ„o: TAB  &Mover Peca
 *  ****/
TAB_tpCondRet TAB_MoverPeca(ptTabuleiro tabu,int xo,int yi,int xd,int yi2) {
    char corPecaLista,corPecaTabuleiro,idPecaLista,idPecaTabuleiro;
    int i,qtdMov,moveParaTras,xObtido,yObtido,achou = 0,qtdUnitarios = 0,verificaMov,j;
    Peca *pecaLista = NULL;
    
    //printf("ta na movimento\n");
    
	   PEC_CriaPeca(&pecaLista,'V','V');
	   //printf("sai da criar peÁa\n");
	   
	   //LIS_ObterNo(listaPecas,(void **)&pecaLista); //obtem cor e id de peÁa do tabuleiro
	   
	   TAB_ObterPeca(tabu,xo,yi,&corPecaTabuleiro,&idPecaTabuleiro);
	   
	   /*  obtem cor e id de peÁa da lista */
	   //PEC_RetornaCor((Peca *)pecaLista,&corPecaLista);
	   //PEC_RetornaId((Peca *)pecaLista,&idPecaLista);
	   
	   IrInicioLista(listaPecas);
	   
	   while(1) {
           
           
           LIS_ObterNo(listaPecas,(void **)&pecaLista);
           PEC_RetornaCor((Peca *)pecaLista,&corPecaLista);
           PEC_RetornaId((Peca *)pecaLista,&idPecaLista);
           //printf("%c e %c\n",corPecaLista,idPecaLista);
           if(idPecaTabuleiro == idPecaLista) {  //caso a peÁa esteja na lista sai do loop
               printf("idPEca: %c\n",idPecaTabuleiro);
               break;
           }
           if(LIS_IrProx(listaPecas) == LIS_CondRetFimLista) { //obtem a peÁa do nÛ corrente da lista
               //return TAB_CondRetNaoAchouPeca;
               break;
           }
           /* obtem a cor e o id da peÁa corrente */
           
       }
    
	   //printf("depois\n");
	   
    PEC_RetornaQtd_Mov(pecaLista,&qtdMov); //obtem o movimento da peÁa
    //descobre se a peÁa pode andar para tr·s
    
		  //printf("Entrarei na verifica\n");
    
    //printf("Qtd MOv:%d\n",qtdMov);
    
    //printf("xd - xo: %d\n e yi2 - yi: %d\n",xd - xo, yi2 - yi);
    
    //printf("id: %c\n",idPecaLista);
    
    //printf("qtdMov: %d\n",qtdMov);
    
    qtdUnitarios = contaUnitarios(pecaLista, qtdMov);
    
    for(i=0;i<qtdMov;i++) {
        //printf("Entrei no for\n");
        //printf("antes\n");
        PEC_RetornaXMovimento(pecaLista,i,&xObtido);
        PEC_RetornaYMovimento(pecaLista,i,&yObtido);
        //printf("depois\n");
        //printf("Sai dos retorna\n");
        //printf("xObtido: %d e yObtido: %d e i: %d\n",xObtido,yObtido,i);
        if (xObtido == xd - xo && yObtido == yi2 - yi) {
            //printf("idPeca achou %c\n",idPecaTabuleiro);
            //printf("(%d,%d) e %d e %d e %d e %d\n",xObtido,yObtido,xd,xo,yi2,yi);
            achou = 1;
        }
        /*
         if(0<=abs(xObtido) && abs(xObtido)<=1 && abs(yObtido)>=0 && abs(yObtido)<=1 && (xObtido != 0 || yObtido != 0)) {
         printf("X: %d\n",xObtido);
         printf("Y: %d\n",yObtido);
         printf("\n\n");
         qtdUnitarios++;
         }
         */
    }

    
    if(achou == 0) {
        printf("n da\n");
    }
    
    if(achou == 1) {
        if(idPecaTabuleiro != 'P' && idPecaTabuleiro != 'R') {
            verificaMov =  verificaMovimento(xo,yi,pecaLista,xd,yi2,tabu,corPecaTabuleiro,qtdUnitarios,1);
        } else if(idPecaTabuleiro == 'P') {
            verificaMov = verificaPeao(tabu, xo, yi, xd, yi2, corPecaTabuleiro);
        } else {
            verificaMov = TAB_VerificaMovimentoRei(tabu, xo, yi, corPecaTabuleiro, xd, yi2);
        }
        
        if(verificaMov == 2) {
            TAB_RetirarPeca(tabu,xd,yi2);
        } else if(verificaMov == 7) {
            return TAB_CondRetMovimentoIrregular;
        }
        //printf("saiu das verificacoes");
        TAB_RetirarPeca(tabu,xo,yi);
        //printf("retirou e inseriu\n");
        TAB_InserirPeca(tabu,xo,yi,'V','V');
        
        TAB_InserirPeca(tabu,xd,yi2,corPecaTabuleiro,idPecaTabuleiro);
        TAB_AtualizaListaAmeacadosEAmeacantes(tabu);
        if(verificaMov == 0) {
        return TAB_CondRetOK;
        }
        return TAB_CondRetComeu;
    }
		  /*
           for(i=0;i<qtdMov;i++) {
           movX = xd - xo; //quantidade de passos que a peÁa tentar· se mover na horizontal
           printf("MOVX:%d",movX);
           movY = yi2 - yi; //quantidade de passos que a peÁa tentar· se mover na vertical
           printf("MOVY:%d",movY);
           PEC_RetornaXMovimento(pecaLista,i,&xRet);//recebe a quantidade de peÁas na horizontal que a peÁa realiza
           printf("\nX:%d\n",xRet);
           PEC_RetornaYMovimento(pecaLista,i,&yRet);//recebe a quantidade de peÁas na vertical que a peÁa realiza
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
}/* Fim funÁ„o: TAB  &Mover Peca */

/***************************************************************************
 *
 *  FunÁ„o: TAB  &Destruir Tabuleiro
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
    LIS_DestroiLista(listaPecas);
    return TAB_CondRetOK;
}/* Fim funÁ„o: TAB  &Destruir Tabuleiro*/

/***************************************************************************
 
 
 /*****  CÛdigo das funÁıes encapsuladas no mÛdulo  *****/

/***************************************************************************
 *
 *  FunÁ„o: TAB  -Verifica Se Come
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
}/* Fim funÁ„o: TAB  -Verifica Se Come*/



/***************************************************************************
 *
 *  FunÁ„o: TAB  &Destruir Valor
 *  ****/
void destruirValor(void *pValor) {
    //printf("na destruir valor: %x\n",pValor);
    free(pValor);
}/* Fim funÁ„o: TAB  -Destruir Valor*/
/***************************************************************************
 *
 *  FunÁ„o: TAB  &Criar Lista Pecas
 *  ****/
TAB_tpCondRet criarListaPecas() {
    retLis = LIS_CriarLista(&listaPecas,idListaPecas,destruirValor);
    if(retLis == LIS_CondRetOK) {
        return TAB_CondRetOK;
    }
    return TAB_CondRetFaltouMemoria;
}/* Fim funÁ„o: TAB  -Criar Lista Pecas*/

/***************************************************************************
 *
 *  FunÁ„o: TAB  &Verifica DireÁ„o Seguida
 *  ****/

int *verificaDirecaoSeguida(int *movimentoX,int *movimentoY,int qtdFaltaX,int qtdFaltaY,int qtdMov){
    int i,*retorno;
    retorno = (int *) malloc(sizeof(int) *2);
    //printf("qtd UNi: %d\n",qtdMov);
    if(retorno == 0) {
        printf("Erro no retorno\n");
        exit(-1);
    }
    retorno[0] = 0;
    retorno[1] = 0;
    //printf("Qtd falta: (%d,%d)\n",qtdFaltaX,qtdFaltaY);
    for (i=0;i<qtdMov;i++) {
        
        if(movimentoX[i] != 0 && movimentoY[i] != 0) {
            
            if(qtdFaltaX/movimentoX[i]== qtdFaltaY / movimentoY[i] && qtdFaltaX/movimentoX[i]> 0 && qtdFaltaY/movimentoY[i]>0) {
                retorno[0] = movimentoX[i];
                retorno[1] = movimentoY[i];
            }
        } else {
            if(qtdFaltaX == 0) {
                printf("Y : %d e %d\n",movimentoY[i],i);
                if (movimentoX[i] == 0 && qtdFaltaY/movimentoY[i]>0) {
                    retorno[0] = movimentoX[i];
                    retorno[1] = movimentoY[i];
                }
            } else if(qtdFaltaY == 0){
                //printf("X: %d\n",movimentoX[i]);
                if (movimentoY[i] == 0 && qtdFaltaX/movimentoX[i]>0) {
                    retorno[0] = movimentoX[i];
                    retorno[1] = movimentoY[i];
                }
            }
        }
    }
    return retorno;
}/* Fim funÁ„o: TAB  -Verifica DireÁ„o*/

/***************************************************************************
 *
 *  FunÁ„o: TAB  &Verifica CondiÁ„o De movimento
 *  ****/

int verificaCondMov(Tabuleiro *tabu,int *movimentoX, int *movimentoY,int posX,int posY,int qtdMov,int qtdFaltaX,int qtdFaltaY,char cor) {
    int *direcao,i,xDirecao,yDirecao,diretor,qtdFalta;
    char idObtido,corObtida,corTeste,idTeste;
    TAB_tpCondRet condRet;
    
    
    
    direcao = verificaDirecaoSeguida(movimentoX,movimentoY,qtdFaltaX,qtdFaltaY,qtdMov);
    
    
    xDirecao = direcao[0];
    yDirecao = direcao[1];
    
    printf("Retorno: (%d,%d)\n",direcao[0],direcao[1]);
    
    
    
    if(direcao[0] == 0 && direcao[1] == 0) {
        return 0;
        //exit(-1);
    }
    
    if(xDirecao == 0) {
        diretor = yDirecao;
        qtdFalta = qtdFaltaY;
    } else {
        diretor = xDirecao;
        qtdFalta = qtdFaltaX;
    }
    
    //printf("AtÈ: %d\n",qtdFalta/diretor);
    
    for (i=0; i<qtdFalta/diretor; i++) {
        //printf("ENtrei no loop\n");
        if((posX + xDirecao) <8 && (posX + xDirecao)>=0 && (posY + yDirecao)<8 && (posY + yDirecao)>=0) {
            condRet = TAB_ObterPeca(tabu,posX + xDirecao,posY + yDirecao,&corObtida,&idObtido);
            qtdFaltaX -= xDirecao;
            qtdFaltaY -= yDirecao;
            posX += xDirecao;
            posY += yDirecao;
            if (corObtida != 'V') {
                if (qtdFaltaX == 0 && qtdFaltaY == 0) {
                    if (corObtida != cor) {
                        printf("Comeu\n");
                        return 2;
                    }
                    
                }
                return 0;
            } else {
                if (qtdFaltaX == 0 && qtdFaltaY == 0) {
                    printf("Chegou sem comer\n");
                    return 1;
                }
            }
        }
        
    }
    
    //printf("mov Irregularm");
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
    
}/* Fim funÁ„o: TAB  -Verifica CondiÁ„o De Movimento*/

/***************************************************************************
 *
 *  FunÁ„o: TAB  &Verifica Validade Do Movimento
 *  ****/




TAB_tpCondRet verificaMovimento(int posIniX,int posIniY,Peca *p,int movX,int movY,Tabuleiro *tabu,char corPeca,int qtdUnitarios,int entra) {
    int qtdMov,*movimentoX,*movimentoY,i,j=0,retornoHard,xObtido,yObtido,podePular;
    char corObtida,idObtido;
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
    
    PEC_RetornaPodePular(p, &podePular);
    
    
		  //printf("i dps: %d\n",i);
		  //printf("Entre na verifica\n");
    for(i=0;i<qtdMov;i++) {
        //printf("Entrei no for\n");
        PEC_RetornaXMovimento(p,i,&xObtido);
        PEC_RetornaYMovimento(p,i,&yObtido);
        //printf("Sai dos retorna\n");
        
        if (podePular == 1) {
            if ((xObtido + posIniX)<0 || (xObtido + posIniX)>7 || (posIniY + yObtido)<0 || (posIniY + yObtido)>7) {
                return 7;
            }
            if((xObtido + posIniX) == movX && (yObtido + posIniY) == movY) {
                TAB_ObterPeca(tabu, xObtido + posIniX, yObtido + posIniY, &corObtida, &idObtido);
                if (corObtida != 'V') {
                    if (corObtida != corPeca) {
                        return 2;
                    } else {
                        return 7;
                    }
                } else {
                    return 0;
                }
            }
        }
        
        if(0<=abs(xObtido) && abs(xObtido)<=1 && abs(yObtido)>=0 && abs(yObtido)<=1 && (xObtido != 0 || yObtido != 0)) {
            movimentoX[j] = xObtido;
            movimentoY[j] = yObtido;
            //printf("X: %d\n",xObtido);
            //printf("Y: %d\n",yObtido);
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
    
    
    retornoHard = verificaCondMov(tabu,movimentoX,movimentoY,posIniX,posIniY,qtdUnitarios,movX - posIniX,movY - posIniY,corPeca);
    //printf("saiu de lá\n");
    if(retornoHard == 1) {
        //printf("/*--------------------: %d\n-------------*/\n",j);
        return TAB_CondRetOK;
    } else if(retornoHard == 2) {
        return TAB_CondRetComeu;
    }
    
		  //printf("sai da verifica\n");
    return TAB_CondRetMovimentoIrregular;
    
}/* Fim funÁ„o: TAB  -Verifica Validade Do Movimento*/


int verificaPeao(ptTabuleiro tabu,int posIniX,int posIniY,int posFimX,int posFimY,char corPeao) {
    char corPecaAlvo,idPecaAlvo;
    TAB_ObterPeca(tabu, posFimX, posFimY, &corPecaAlvo, &idPecaAlvo);
    if (((posFimX - posIniX) == 1 && (posFimY - posIniY) == 1) || ((posFimX - posIniX) == -1 && (posFimY - posIniY) == 1)) {
        
        printf("passou peao e %c e %c\n",corPecaAlvo,corPeao);
        
        if(corPecaAlvo != 'V') {
            if (corPecaAlvo != corPeao) {
                printf("xaxando\n");
                return 2;
            }
        }
    } else if((posFimX - posIniX) == 0 && (posFimY - posIniY) == 1) {
        printf("Entrou aqui peao\n");
        if (corPecaAlvo == 'V') {
            return 0;
        }
    }
    return 7;
}

void buscaNaLista(Peca **pecaLista,char *corPecaLista,char idPecaLista,char idPecaTabuleiro) {
    IrInicioLista(listaPecas);
    while(1) {
        LIS_ObterNo(listaPecas,(void **)pecaLista);
        PEC_RetornaCor((Peca *)*pecaLista,corPecaLista);
        PEC_RetornaId((Peca *)*pecaLista,&idPecaLista);
        //printf("%c e %c\n",*corPecaLista,idPecaLista);
        if(idPecaTabuleiro == idPecaLista) {  //caso a peÁa esteja na lista sai do loop
            break;
        }
        if(LIS_IrProx(listaPecas) == LIS_CondRetFimLista) { //obtem a peÁa do nÛ corrente da lista
            //return TAB_CondRetNaoAchouPeca;
            break;
        }
        /* obtem a cor e o id da peÁa corrente */
    }
    
}


int contaUnitarios(Peca *pecaLista,int qtdMov) {
    int xObtido,yObtido,i,qtdUnitarios=0;
    for(i=0;i<qtdMov;i++) {
        PEC_RetornaXMovimento(pecaLista,i,&xObtido);
        PEC_RetornaYMovimento(pecaLista,i,&yObtido);
        if(0<=abs(xObtido) && abs(xObtido)<=1 && abs(yObtido)>=0 && abs(yObtido)<=1 && (xObtido != 0 || yObtido != 0)) {
            qtdUnitarios++;
        }
    }
    return qtdUnitarios;
}

int verificaCoordenadas(int x, int y) {
    if(x>7 || x<0 || y>7 || y<0) {
        return 0;
    }
    return 1;
}

void trocaReiPorVazio(ptTabuleiro tabu,int xRei,int yRei) {
    Peca *rei;
    rei = (Peca *)tabu->tab[xRei][yRei].elemento;
    
}

int verificaSePecaChegaEmPos(ptTabuleiro tabu,int posX,int posY,char cor) {
    char corObtida,idObtido,i,j,qtdUnitarios,retornoVerifica = 7;
    int qtdMov;
    Peca *ameacante;
    /*quando a peça que pode comer um rei é o outro rei, podemos tratar o movimento dessa peça como se fosse uma peça qualquer, tendo em vista que se o rei1 puder comer o rei2, não importa se o movimento feito para levar o rei1 a comer o rei2 faça com que ele fique em cheque, pois se um rei2 for comido, acaba o jogo */
    for(i=0;i<8;i++) {
        for (j=0; j<8; j++) {
            TAB_ObterPeca(tabu, i, j, &corObtida, &idObtido);
            if(corObtida != 'V') {
                ameacante = (Peca *)tabu->tab[i][j].elemento;
                PEC_RetornaQtd_Mov(ameacante, &qtdMov);
                qtdUnitarios = contaUnitarios(ameacante, qtdMov);
                
                /*
                 if(corObtida == 'P') {
                 
                 } else {
                 if(idObtido != 'P') {
                 retornoVerifica = verificaMovimento(i, j, ameacante, posX, posY, tabu, 'P', qtdUnitarios);
                 } else {
                 retornoVerifica = verificaPeao(tabu, i, j, posX, posY, 'P');
                 if(((posX - i == 1 && posY - j == 1) || (posX - i == -1 && posY - j == 1)) && cor != corObtida) {
                 retornoVerifica = 2;
                 }
                 }
                 }
                 */
                if(corObtida != cor) {
                    if(idObtido != 'P') {
                        printf("(%d,%d) e cor: %c e id: %c\n",posX,posY,corObtida,idObtido);
                        retornoVerifica = verificaMovimento(i, j, ameacante, posX, posY, tabu, cor, qtdUnitarios,0);
                        printf("ret ver:%d\n",retornoVerifica);
                    } else  {
                        if((posX - i == 1 && posY - j == 1) || (posX - i == -1 && posY - j == 1)) {
                            retornoVerifica = 2;
                        }
                    }
                }
                
                
                
                if ((retornoVerifica == 0 || retornoVerifica == 2) && cor != corObtida) {
                    printf("cor na checa: %c e %c e (%d,%d)\n",corObtida,idObtido,posX,posY);
                    return 0;
                }
            }
        }
    }
    return 1;
}

TAB_tpCondRet TAB_VerificaMovimentoRei(ptTabuleiro tabu,int xRei, int yRei, char cor,int xFim,int yFim) {
    int retornoVerifica1,retornoVerifica2;
    Peca *rei;
    rei = (Peca *)tabu->tab[xRei][yRei].elemento;
    PEC_FingeQueTira(rei);
    retornoVerifica1 = verificaMovimento(xRei, yRei, rei, xFim, yFim, tabu, cor, 8,0);
    if (retornoVerifica1 != 7) {
        retornoVerifica2 = verificaSePecaChegaEmPos(tabu, xFim, yFim, cor);
        if (retornoVerifica2 == 1) {
            TAB_InserirPeca(tabu, xRei, yRei, cor, 'R');
            return retornoVerifica1;
        }
        printf("movimento é valido,contudo deixa o rei em cheque, logo, ilegal\n");
    }
    TAB_InserirPeca(tabu, xRei, yRei, cor, 'R');
    return 7;
}

TAB_tpCondRet TAB_VerificaCheck(ptTabuleiro tabu,int xRei,int yRei) {
    int numElem;
    LIS_RetornaNumElementos(tabu->tab[xRei][yRei].ameacantes, &numElem);
    if(numElem>0) {
        return TAB_CondRetCheck;
    }
    return TAB_CondRetNoCheck;
}



TAB_tpCondRet TAB_VerificaCheckMate(ptTabuleiro tabu,int xRei,int yRei,int xAmeacante,int yAmeacante) {
    Peca *pecaTabuleiro,*ameacante,*rei;
    int qtdMovRei,podePular,i,j,xMovimento,yMovimento,retornoVerifica,podeMover = 0,podeSacrificar=0,numElemLista,qtdUnitarios,xDirecao,yDirecao,xSacrificio,ySacrificio,qtdMovTab;
    LIS_tppLista listaAmeacantes;
    char corRei,corPecaAmeacante,idPecaAmeacante,corPecaTabuleiro,idPecaTabuleiro,idTeste;
    //ver se o rei pode se mexer
    rei = (Peca *)tabu->tab[xRei][yRei].elemento;
    ameacante = (Peca *)tabu->tab[xAmeacante][yAmeacante].elemento;
    PEC_RetornaQtd_Mov(rei, &qtdMovRei);
    PEC_RetornaCor(rei, &corRei);
    xDirecao = xRei - xAmeacante;
    yDirecao = yRei - yAmeacante;
    if(xDirecao != 0) {
        xSacrificio = xRei -(xDirecao/(abs(xDirecao)));
    } else {
        xSacrificio = xRei;
    }
    if(yDirecao != 0) {
        ySacrificio = yRei -(yDirecao/(abs(yDirecao)));
    } else {
        ySacrificio = yRei;
    }
    printf("sac: (%d,%d)\n",xSacrificio,ySacrificio);
    for(i=0;i<qtdMovRei;i++) { //analisa todos os movimentos que o rei pode fazer
        PEC_RetornaXMovimento(rei, i, &xMovimento);
        PEC_RetornaYMovimento(rei, i, &yMovimento);
        //printf("mov: (%d,%d) e i:%d\n",xRei + xMovimento,yRei+yMovimento,i);
        retornoVerifica = TAB_VerificaMovimentoRei(tabu, xRei, yRei, corRei, xRei + xMovimento, yRei + yMovimento);
        
        if(retornoVerifica != 7) { //verifica se o movimento é possível
            printf("Não está em cheque, pois pode ir para (%d,%d)\n",xRei + xMovimento,yRei + yMovimento);
            podeMover = 1;
        }
        
    }
    if(podeMover == 1) {
        return TAB_CondRetNoCheckMate;
    }
    TAB_ObterListaAmeacantes(tabu, xAmeacante, yAmeacante, &listaAmeacantes);
    LIS_RetornaNumElementos(listaAmeacantes,&numElemLista);
    if(numElemLista>0) {
        //printf("num real: %d\n",numElemLista);
        LIS_ObterNo(listaAmeacantes, (void **)&lis);
        PEC_RetornaId(lis, &idTeste);
        //printf("id Teste: %c\n",idTeste);
        printf("Há elementos que podem capturar a peça que colocou o rei em cheque\n");
        return TAB_CondRetNoCheckMate;
    }
    TAB_ObterPeca(tabu, xAmeacante, yAmeacante, &corPecaAmeacante, &idPecaAmeacante);
    PEC_RetornaPodePular(ameacante, &podePular);
    
    
    if(podePular == 1 ||(((abs(xAmeacante - xRei)== 0) || abs(xAmeacante - xRei)== 1) && (abs(yAmeacante - yRei) == 0|| abs(yAmeacante - yRei) == 1))) {
        return TAB_CondRetCheckMate;
        
    } else {
        xDirecao = xRei - xAmeacante;
        yDirecao = yRei - yAmeacante;
        //printf("xDir: %d e yDir: %d\n",xDirecao,yDirecao);
        if(xDirecao != 0) {
            xSacrificio = xRei -(xDirecao/(abs(xDirecao)));
        } else {
            xSacrificio = xRei;
        }
        if(yDirecao != 0) {
            ySacrificio = yRei -(yDirecao/(abs(yDirecao)));
        } else {
            ySacrificio = yRei;
        }
        //printf("sac: (%d,%d)\n",xSacrificio,ySacrificio);
        for (i=0; i<8; i++) {
            for (j=0; j<8; j++) {
                pecaTabuleiro = (Peca *) tabu->tab[i][j].elemento;
                PEC_RetornaCor(pecaTabuleiro, &corPecaTabuleiro);
                PEC_RetornaId(pecaTabuleiro, &idPecaTabuleiro);
                PEC_RetornaQtd_Mov(pecaTabuleiro, &qtdMovTab);
                qtdUnitarios = contaUnitarios(pecaTabuleiro, qtdMovTab);
                if(corPecaTabuleiro == corRei && i != xRei && j != yRei) {
                    if(idPecaTabuleiro != 'P') {
                        printf("%c\n",idPecaTabuleiro);
                        retornoVerifica = verificaMovimento(i, j, pecaTabuleiro, xSacrificio, ySacrificio, tabu, corPecaTabuleiro, qtdUnitarios,0);
                    } else {
                        retornoVerifica = verificaPeao(tabu, i, j, xSacrificio, ySacrificio, corPecaTabuleiro);
                    }
                    if(retornoVerifica == 0) {
                        printf("ALLAHU AKBAR!!!\n");
                        printf("Peca id: %c e cor: %c na posicao(%d,%d) pode se sacrificar\n",idPecaTabuleiro,corPecaTabuleiro,i,j);
                        podeSacrificar = 1;
                    }
                }
            }
        }
        if(podeSacrificar == 1) {
            return TAB_CondRetNoCheckMate;
        }
        return TAB_CondRetCheckMate;
    }
    
    
}

TAB_tpCondRet TAB_AchaPecaCheck(ptTabuleiro tabu,char cor,char id,int *x,int *y,int xRei,int yRei) {
    int i,j,qtdMov,qtdUnitarios,retVerifica;
    Peca *ameacante;
    char corObtida,idObtido;
    for (i=0; i<8; i++) {
        for (j=0; j<8; j++) {
            TAB_ObterPeca(tabu, i, j,&corObtida ,&idObtido);
            ameacante = (Peca *) tabu->tab[i][j].elemento;
            PEC_RetornaQtd_Mov(ameacante, &qtdMov);
            qtdUnitarios = contaUnitarios(ameacante, qtdMov);
            if (corObtida == cor && idObtido == id) {
                retVerifica = verificaMovimento(i, j, ameacante, xRei, yRei, tabu, corObtida, qtdUnitarios,0);
                if (retVerifica == TAB_CondRetComeu) {
                    *x = i;
                    *y = j;
                }
            }
        }
    }
    return 0;
}


/********** Fim do mÛdulo de implementaÁ„o: TAB  Tabuleiro **********/
