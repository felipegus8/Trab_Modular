#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"jogo.h"


int converteCharParaInt(char i) {
    return (int)i - 'A';
}

JOG_tpCondRet inserirPecas(TAB_tpCondRet(*InserirNoTab)(ptTabuleiro tabu,int x,int y,char cor,char id),ptJudge j) {
    ptTabuleiro tabu;
    int y,xi,continuar = 1;
    char cor,id,x;
    /*
    do {
        printf("Entre com a identidade da peça\n");
        scanf(" %c",&id);
        printf("id peça: %d\n",id);
        printf("Entre com a cor da peça\n");
        scanf(" %c",&cor);
        printf("Entre com a coordenada X da peça\n");
        scanf(" %c",&x);
        printf("Entre com a coordenada Y da peça\n");
        scanf(" %d",&y);
        xi = converteCharParaInt(x);
        printf("convertido: %d\n",xi);
        JOG_ObtemTabuleiro(j, &tabu);
        y--;
        InserirNoTab(tabu, xi, y, cor, id);
        printf("se quiser continuar inserindo digite 1\n");
        scanf("%d",&continuar);
    } while (continuar == 1);
    */
     
    JOG_ObtemTabuleiro(j, &tabu);
    /*
    InserirNoTab(tabu,1,6,'B','R');
    InserirNoTab(tabu,2,2,'P','T');
    InserirNoTab(tabu,3,1,'P','D');
    InserirNoTab(tabu,4,4,'B','T');
     */
    //Insere peças brancas
    InserirNoTab(tabu,0,0,'B','T');
    InserirNoTab(tabu,1,0,'B','C');
    InserirNoTab(tabu,2,0,'B','B');
    InserirNoTab(tabu,3,0,'B','D');
    InserirNoTab(tabu,4,0,'B','R');
    InserirNoTab(tabu,5,0,'B','B');
    InserirNoTab(tabu,6,0,'B','C');
    InserirNoTab(tabu,7,0,'B','T');
    InserirNoTab(tabu,0,1,'B','P');
    InserirNoTab(tabu,1,1,'B','P');
    InserirNoTab(tabu,2,1,'B','P');
    InserirNoTab(tabu,3,1,'B','P');
    InserirNoTab(tabu,4,1,'B','P');
    InserirNoTab(tabu,5,1,'B','P');
    InserirNoTab(tabu,6,1,'B','P');
    InserirNoTab(tabu,7,1,'B','P');
    //Insere peças pretas
    InserirNoTab(tabu,0,7,'P','T');
    InserirNoTab(tabu,1,7,'P','C');
    InserirNoTab(tabu,2,7,'P','B');
    InserirNoTab(tabu,3,7,'P','D');
    InserirNoTab(tabu,4,7,'P','R');
    InserirNoTab(tabu,5,7,'P','B');
    InserirNoTab(tabu,6,7,'P','C');
    InserirNoTab(tabu,7,7,'P','T');
    InserirNoTab(tabu,0,6,'P','P');
    InserirNoTab(tabu,1,6,'P','P');
    InserirNoTab(tabu,2,6,'P','P');
    InserirNoTab(tabu,3,6,'P','P');
    InserirNoTab(tabu,4,6,'P','P');
    InserirNoTab(tabu,5,6,'P','P');
    InserirNoTab(tabu,6,6,'P','P');
    InserirNoTab(tabu,7,6,'P','P');
    return JOG_CondRetOK;
}


void recebeNomeJogadorA(char nomeA[30]) {
    char s[30];
    printf("Entre com o nome do jogador que joga com as peças brancas\n");
    scanf("%s",s);
    strcpy(nomeA,s);
}

void recebeNomeJogadorB(char nomeB[30]) {
    char s[30];
    printf("Entre com o nome do jogador que jogo com as peças pretas\n");
    scanf("%s",s);
    strcpy(nomeB,s);
}

void imprimeTabuleiro(char matrizTabuleiro[8][8][2]) {
    int x,y;
    char row = 'A';
    printf("\n");
    for (x=0; x<8; x++) {
        printf("%d\t",8 - x);
        for (y=0; y<8; y++) {
            printf("%c%c\t",matrizTabuleiro[y][7 - x][0],matrizTabuleiro[y][7 - x][1]);
        }
        printf("\n");
    }
    for (y=1; y<9; y++) {
        printf(" \t%c ",row);
        row++;
    }
    printf("\n");
}

void imprimeAmeacantes(char *corAmeacantes,char *idAmeacantes,int qtdAmeacantes) {
    int i;
    for (i=0; i<qtdAmeacantes; i++) {
        printf("cor ameacante: %c e id ameacante: %c\n",corAmeacantes[i],idAmeacantes[i]);
    }
}

void imprimeAmeacados(char *corAmeacados,char *idAmeacados,int qtdAmeacados) {
    int i;
    for (i=0; i<qtdAmeacados; i++) {
        printf("cor ameacado: %c e id ameacado: %c\n",corAmeacados[i],idAmeacados[i]);
    }
}

void loopJogo(ptJudge j) {
    char continuar[4];
    char coordXIni,coordXFim,corDavez,matrizTabuleiro[8][8][2],nome1[30],nome2[30],corAmeacantes[16],idAmeacantes[16],corAmeacados[16],idAmeacados[16];
    int coordYIni,coordYFim,i=0,vez=0,qtdAmeacantes,qtdAmeacados;
    JOG_tpCondRet resMovimento;
    do {
        JOG_RetornoNomeJogador1(j, nome1);
        JOG_RetornoNomeJogador2(j, nome2);
        if(i%2 == 0) {
            corDavez = 'P';
            printf("vez do jogador %s\n",nome1);
            vez = 0;
        } else {
            corDavez = 'B';
            printf("vez do jogador %s\n",nome2);
            vez = 1;
        }
        JOG_GeraMatrizTabuleiro(j, matrizTabuleiro);
        imprimeTabuleiro(matrizTabuleiro);
        
        printf("Insira a coordenada X da peça que deseja movimentar\n");
        scanf(" %c",&coordXIni);
        printf("Insira a coordenada Y da peça que deseja movimentar\n");
        scanf(" %d",&coordYIni);
        printf("Insira para qual coordenada X  deseja movimentar a peça\n");
        scanf(" %c",&coordXFim);
        printf("Insira para qual coordenada Y  deseja movimentar a peça\n");
        scanf(" %d",&coordYFim);
        coordYFim--;
        coordYIni--;
        resMovimento = JOG_EfetuarJogada(j, corDavez, converteCharParaInt(coordXIni), coordYIni, converteCharParaInt(coordXFim), coordYFim);
        if (resMovimento == JOG_CondRetOK) {
            printf("Movimento foi realizado com sucesso, sem capturar outra peça");
            JOG_DevolveAmeacantes(j, corAmeacantes, idAmeacantes, &qtdAmeacantes, converteCharParaInt(coordXFim), coordYFim);
            JOG_DevolveAmeacados(j, corAmeacados, idAmeacados, &qtdAmeacados, converteCharParaInt(coordXFim), coordYFim);
            imprimeAmeacantes(corAmeacantes,idAmeacantes,qtdAmeacantes);
            imprimeAmeacados(corAmeacados, idAmeacados, qtdAmeacados);
        } else if(resMovimento == JOG_CondRetComeu) {
            printf("Movimento foi realizado com sucesso, capturando outra peça\n");
            JOG_DevolveAmeacantes(j, corAmeacantes, idAmeacantes, &qtdAmeacantes, converteCharParaInt(coordXFim), coordYFim);
            JOG_DevolveAmeacados(j, corAmeacados, idAmeacados, &qtdAmeacados, converteCharParaInt(coordXFim), coordYFim);
            imprimeAmeacantes(corAmeacantes,idAmeacantes,qtdAmeacantes);
            imprimeAmeacados(corAmeacados, idAmeacados, qtdAmeacados);
        } else if(resMovimento == JOG_CondRetMovimentoIrregular) {
            printf("Movimento irregular\n");
        } else if(resMovimento == JOG_CondRetCheck) {
            printf("Cheque ");
            if(vez == 0) {
                printf("de %s\n",nome1);
            } else {
                printf("de %s\n",nome2);
            }
        } else if(resMovimento == JOG_CondRetCorErrada) {
            printf("Está tentando movimentar peça da cor errada\nFique mais atento e tenta novamente\n");
            i--;
        }else {
            printf("Check Mate e %d\n",resMovimento);
            if (vez == 0) {
                printf("%s ganhou!!\n",nome1);
            } else {
                printf("%s ganhou!!\n",nome2);
            }
            break;
        }
        printf("deseja continuar?\n");
        scanf(" %s",continuar);
        i++;
    } while (strcmp(continuar, "FIM") != 0);
}

int main()
{
    ptTabuleiro tabu;
    int ret;
    char cor,id,corAmeacados[16],idAmeacados[16];
    int numElem;
    ptJudge j;
    ptJogador a,b;
    LIS_tppLista elis;
    
    
    
    char nomeA[30],nomeB[30];
    recebeNomeJogadorA(nomeA);
    recebeNomeJogadorB(nomeB);
    JOG_CriaJogador(&a,nomeA,'P');
    JOG_CriaJogador(&b,nomeB,'B');
    JOG_CriaJuiz(&j, a, b);
    JOG_ObtemTabuleiro(j, &tabu);
    JOG_ComecarJogo(j, inserirPecas);
    /*
    ret = TAB_MoverPeca(tabu, 4, 6, 4, 5);
    ret = TAB_MoverPeca(tabu, 4, 5, 4, 4);
    ret = TAB_MoverPeca(tabu, 4, 4, 4, 3);
    printf("Entrei no ultimo");
    ret = TAB_MoverPeca(tabu, 4, 3, 4, 2);
    printf("%d\n",ret);
    JOG_DevolveAmeacantes(j, corAmeacados, idAmeacados, &numElem, 4, 2);
    */
    loopJogo(j);
    
}
