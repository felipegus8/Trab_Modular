/***************************************************************************
 *  $MCI Módulo de implementação: PEC  Peca
 *
 *  Arquivo gerado:              Peca.c
 *  Letras identificadoras:      PEC
 *
 *  Autores: Felipe Viberti,Luis Claudio e Victor Nogueira
 *
 *  $HA Histórico de evolução:
 *     Versão  Autores                                           Data          Observações
 *     1       Felipe Viberti,Luis Claudio e Victor Nogueira   02/out/2016  início desenvolvimento
 *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "peca.h"


/***********************************************************************
 *
 *  $TC Tipo de dados: MOV Movimento da Peca
 *
 *
 ***********************************************************************/
typedef struct movimento{
    int x;
    int y;
}Movimento;

/***********************************************************************
 *
 *  $TC Tipo de dados: Peca Peca
 *
 *
 ***********************************************************************/
typedef struct peca {
    char id;  // string identificadora da peça
    char cor; //cor da peça
    int qtdMov; //quantidade de movimentos da peça
    int podePular; // Bool para ver se a peça move para trás ou não(0 ou 1).
    Movimento *movPeca; //Vetor da struct movimento contendo todos os movimentos que a peça pode fazer
}Peca;

PEC_tpCondRet retornoPeca;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
 *
 *  Função: PEC  &Criar peca
 *  ****/
PEC_tpCondRet PEC_CriaPeca(Peca **novo,char id,char cor) {
    Peca *novoCopia;
    novoCopia = (Peca *)malloc(sizeof(Peca));
    if(novoCopia == NULL) {
        return PEC_CondRetFaltouMemoria;
    }
		  novoCopia->id = id;
    
		  novoCopia->cor = cor;
    
    retornoPeca = PEC_EnsinaMovimentosPecasConhecidas(&novoCopia);
    if(retornoPeca == PEC_CondRetFaltouMemoria) {
        
        return PEC_CondRetFaltouMemoria;
    }
    
    if(retornoPeca == PEC_CondRetNaoAchouPeca) { //caso insere o movimento
        
        retornoPeca = PEC_EnsinaMovimentosPecasDesconhecidas(&novoCopia);
        if(retornoPeca == PEC_CondRetFaltouMemoria) {
            
            return PEC_CondRetFaltouMemoria;
        }
    }
    
		  *novo = novoCopia;
    return PEC_CondRetOK;
}/* Fim função: PEC  &Criar peca */

/***************************************************************************
 *
 *  Função: PEC  &Ensina Movimentos Pecas Conhecidas
 *  ****/
PEC_tpCondRet PEC_EnsinaMovimentosPecasConhecidas(Peca **novo)
{
    int i = 0,j = 0,k = 0 ;
    //Em todos os casos do switch a variável moveParaTras será preenchida como 1(Verdadeiro) exceto no peão,que será 0.
    switch((*novo)->id)
    {
        case 'T':
            (*novo)->movPeca = (Movimento*)malloc(sizeof(Movimento)*28);
            if((*novo)->movPeca == NULL)
            {
                return PEC_CondRetFaltouMemoria;
            }
            (*novo)->qtdMov = 28;
            (*novo)->podePular = 0;
            if((*novo)->movPeca == NULL)
            {
                return PEC_CondRetFaltouMemoria;
            }
            //Movimento na vertical da torre
            (*novo)->movPeca[i].x = 1;
            (*novo)->movPeca[i].y = 0;
            for(i=1;i<7;i++)
            {
                (*novo)->movPeca[i].x = i+1;
                (*novo)->movPeca[i].y = 0;
            }
            //Movimento na horizontal da torre
            for(j=1;j<8;j++)
            {
                (*novo)->movPeca[i].x = 0;
                (*novo)->movPeca[i].y = j;
                i++;
            }
            (*novo)->movPeca[14].x = -1;
            (*novo)->movPeca[14].y = 0;
            for (i=2; i<8; i++) {
                //printf("i: %d\n",i);
                (*novo)->movPeca[13 + i].x = -i;
                (*novo)->movPeca[13 + i].y = 0;
            }
            (*novo)->movPeca[21].x = 0;
            (*novo)->movPeca[21].y = -1;
            for (i=2; i<8; i++) {
                (*novo)->movPeca[20 + i].x = 0;
                (*novo)->movPeca[20 + i].y = -i;
            }
            for(i=0;i<28;i++) {
                //printf("(%d,%d)\n",(*novo)->movPeca[i].x,(*novo)->movPeca[i].y);
            }
            break;
        case 'C':
            (*novo)->movPeca = (Movimento*)malloc(sizeof(Movimento)*8);
            (*novo)->qtdMov = 8;
            (*novo)->podePular = 1;
            if((*novo)->movPeca == NULL)
            {
                return PEC_CondRetFaltouMemoria;
            }
            //Movimento do cavalo
            (*novo)->movPeca[0].x = 2;
            (*novo)->movPeca[0].y = 1;
            (*novo)->movPeca[1].x = 1;
            (*novo)->movPeca[1].y = 2;
            (*novo)->movPeca[2].x = -2;
            (*novo)->movPeca[2].y = -1;
            (*novo)->movPeca[3].x = -1;
            (*novo)->movPeca[3].y = -2;
            (*novo)->movPeca[4].x = -2;
            (*novo)->movPeca[4].y = 1;
            (*novo)->movPeca[5].x = -1;
            (*novo)->movPeca[5].y = 2;
            (*novo)->movPeca[6].x = 2;
            (*novo)->movPeca[6].y = -1;
            (*novo)->movPeca[7].x = 1;
            (*novo)->movPeca[7].y = -2;
            break;
        case 'B':
            (*novo)->movPeca = (Movimento*)malloc(sizeof(Movimento)*28);
            (*novo)->qtdMov = 28;
            (*novo)->podePular = 0;
            if((*novo)->movPeca == NULL)
            {
                return PEC_CondRetFaltouMemoria;
            }
            i = 2;
            //Movimento do bispo(diagonais)
            (*novo)->movPeca[0].x = 1;
            (*novo)->movPeca[0].y = 1;
            for(k=1;k<7;k++)
            {
                (*novo)->movPeca[k].x = i;
                (*novo)->movPeca[k].y = i;
                
                i++;
            }
            (*novo)->movPeca[7].x = 1;
            (*novo)->movPeca[7].y = -1;
            i++;
            for(k=8;k<14;k++)
            {
                (*novo)->movPeca[k].x = i - 7;
                (*novo)->movPeca[k].y = -i + 7;
                //printf("No Peca: (%d,%d)\n",(*novo)->movPeca[k].x,(*novo)->movPeca[k].y);
                i++;
            }
            (*novo)->movPeca[14].x = -1;
            (*novo)->movPeca[14].y = -1;
            i++;
            for(k=15;k<21;k++)
            {
                (*novo)->movPeca[k].x = -i + 14;
                (*novo)->movPeca[k].y = -i + 14;
                
                i++;
            }
            (*novo)->movPeca[21].x = -1;
            (*novo)->movPeca[21].y = 1;
            i++;
            for(k=22;k<28;k++)
            {
                (*novo)->movPeca[k].x = -i + 21;
                (*novo)->movPeca[k].y = i - 21;
                i++;
            }
            //printf("\n\n\n");
            break;
        case 'P':
            (*novo)->movPeca = (Movimento*)malloc(sizeof(Movimento)*2);
            (*novo)->qtdMov = 2;
            (*novo)->podePular = 0;
            if((*novo)->movPeca == NULL)
            {
                return PEC_CondRetFaltouMemoria;
            }
            //Movimento do peão.Aqui não se considera o fato dele poder se mover duas casas para frente na primeira jogada.
            (*novo)->movPeca[0].x = 0;
            (*novo)->movPeca[0].y = 1;
            (*novo)->movPeca[1].x = 1;
            (*novo)->movPeca[1].y = 1;
            break;
        case 'D':
            (*novo)->movPeca = (Movimento*)malloc(sizeof(Movimento)*56);
            (*novo)->qtdMov = 56;
            (*novo)->podePular = 0;
            i = 2;
            if((*novo)->movPeca == NULL)
            {
                return PEC_CondRetFaltouMemoria;
            }
            //movimento da rainha na diagonal
            (*novo)->movPeca[0].x = 1;
            (*novo)->movPeca[0].y = 1;
            for(k=1;k<7;k++)
            {
                (*novo)->movPeca[k].x = i;
                (*novo)->movPeca[k].y = i;
                
                i++;
            }
            (*novo)->movPeca[7].x = 1;
            (*novo)->movPeca[7].y = -1;
            i++;
            for(k=8;k<14;k++)
            {
                (*novo)->movPeca[k].x = i - 7;
                (*novo)->movPeca[k].y = -i + 7;
                //printf("No Peca: (%d,%d)\n",(*novo)->movPeca[k].x,(*novo)->movPeca[k].y);
                i++;
            }
            (*novo)->movPeca[14].x = -1;
            (*novo)->movPeca[14].y = -1;
            i++;
            for(k=15;k<21;k++)
            {
                (*novo)->movPeca[k].x = -i + 14;
                (*novo)->movPeca[k].y = -i + 14;
                
                i++;
            }
            (*novo)->movPeca[21].x = -1;
            (*novo)->movPeca[21].y = 1;
            i++;
            for(k=22;k<28;k++)
            {
                (*novo)->movPeca[k].x = -i + 21;
                (*novo)->movPeca[k].y = i - 21;
                i++;
            }
            //movimento da rainha na horizontal
            (*novo)->movPeca[28].x = 1;
            (*novo)->movPeca[28].y = 0;
            i++;
            for(k=29;k<35;k++) {
                (*novo)->movPeca[k].x = i - 28;
                (*novo)->movPeca[k].y = 0;
                i++;
            }
            (*novo)->movPeca[35].x = -1;
            (*novo)->movPeca[35].y = 0;
            i++;
            for(k=36;k<42;k++) {
                (*novo)->movPeca[k].x = -i + 35;
                (*novo)->movPeca[k].y = 0;
                i++;
            }
            //movimento da rainha na vertical
            (*novo)->movPeca[42].x = 0;
            (*novo)->movPeca[42].y = 1;
            i++;
            for(k=43;k<49;k++) {
                (*novo)->movPeca[k].x = 0;
                (*novo)->movPeca[k].y = i - 42;
                i++;
            }
            (*novo)->movPeca[49].x = 0;
            (*novo)->movPeca[49].y = -1;
            i++;
            for(k=50;k<56;k++) {
                (*novo)->movPeca[k].x = 0;
                (*novo)->movPeca[k].y = -i + 49;
                i++;
            }
            break;
        case 'R':
            (*novo)->movPeca = (Movimento*)malloc(sizeof(Movimento)*8);
            (*novo)->qtdMov = 8;
            (*novo)->podePular = 0;
            if((*novo)->movPeca == NULL)
            {
                return PEC_CondRetFaltouMemoria;
            }
            //Movimento do rei
            (*novo)->movPeca[0].x = 1;
            (*novo)->movPeca[0].y = 0;
            
            (*novo)->movPeca[1].x = 1;
            (*novo)->movPeca[1].y = 1;
            
            (*novo)->movPeca[2].x = 0;
            (*novo)->movPeca[2].y = 1;
            
            (*novo)->movPeca[3].x = -1;
            (*novo)->movPeca[3].y = 0;
            
            (*novo)->movPeca[4].x = -1;
            (*novo)->movPeca[4].y = -1;
            
            (*novo)->movPeca[5].x = 0;
            (*novo)->movPeca[5].y = -1;
            
            (*novo)->movPeca[6].x = 1;
            (*novo)->movPeca[6].y = -1;
            
            (*novo)->movPeca[7].x = -1;
            (*novo)->movPeca[7].y = 1;
            break;
        case 'V':
			(*novo)->qtdMov = 0;
			(*novo)->movPeca = NULL;
			(*novo)->podePular = 0;
            break;
            
        default:
            return PEC_CondRetNaoAchouPeca;
    }
    return PEC_CondRetOK;
} /* Fim função: PEC  &Ensina Movimentos Pecas Conhecidas */
/***************************************************************************
 *
 *  Função: PEC  &Ensina Movimentos Pecas Desconhecidas
 *  ****/
PEC_tpCondRet PEC_EnsinaMovimentosPecasDesconhecidas(Peca **novo)
{
    char idLido,corLido;
    int x,y,i;
    FILE *fp;
    fp = fopen("PecasNovas.txt","r");
    //O arquivo PecasNovas.txt contem todas as peças novas que podem ser usadas no jogo.Para criar uma nova peça,o usuário deve escrever nesse arquivo,seguindo o formato lá apresentado.
    if (fp==NULL)
    {
        printf("n tem arquivo\n");
        exit(1);
    }
    i = 0;
    while(fscanf(fp,"%c %c",&idLido,&corLido) == 2)
    {
        
        if ((idLido == (*novo)->id) && (corLido == (*novo)->cor))
        {
            while(fscanf(fp,"%d  %d",&x,&y) == 2)
                i++;
        }
        else
        {
            while(fscanf(fp,"%d  %d",&x,&y) == 2);
        }
    }
    (*novo)->movPeca = (Movimento*)malloc(sizeof(Movimento)*i);
    if ((*novo)->movPeca  == NULL)
    {
        return PEC_CondRetFaltouMemoria;
    }
    i = 0;
    fclose(fp);
    if ((fp=fopen("PecasNovas.txt","r"))==NULL)
    {
        exit(1);
    }
    while(fscanf(fp,"%c %c",&idLido,&corLido) == 2)
    {
        if ((idLido == (*novo)->id) && (corLido == (*novo)->cor))
        {
            while(fscanf(fp,"%d %d",&x,&y) == 2)
            {
                (*novo)->movPeca[i].x = x;
                (*novo)->movPeca[i].y = y;
                i++;
            }
        }
        else
        {
            while(fscanf(fp,"%d %d",&x,&y) == 2);
        }
    }
    (*novo)->qtdMov = i;
    fclose(fp);
    return PEC_CondRetOK;
}/* Fim função: PEC  &Ensina Movimentos Pecas Desconhecidas */



/***************************************************************************
 *
 *  Função: PEC  &Libera Peca
 *  ****/
PEC_tpCondRet PEC_LiberaPeca(Peca *peca) {
    free(peca);
    return PEC_CondRetOK;
}/* Fim função: PEC  &Libera Peca */

/***************************************************************************
 *
 *  Função: PEC  &Retorna Id
 *  ****/
PEC_tpCondRet PEC_RetornaId(Peca *peca,char *id)
{
    *id = peca->id;
    return PEC_CondRetOK;
}/* Fim função: PEC  &Retorna Id */

/***************************************************************************
 *
 *  Função: PEC  &Retorna Cor
 *  ****/
PEC_tpCondRet PEC_RetornaCor(Peca *peca,char *cor)
{
    if(peca == NULL) {
        printf("blade peça\n");
        exit(-1);
    }
    *cor = peca->cor;
    return PEC_CondRetOK;
}/* Fim função: PEC  &Retorna Cor */

/***************************************************************************
 *
 *  Função: PEC  &Retorna Qtd_Mov
 *  ****/
PEC_tpCondRet PEC_RetornaQtd_Mov(Peca *peca,int *qtdMov)
{
    *qtdMov = peca->qtdMov;
    return PEC_CondRetOK;
}/* Fim função: PEC  &Retorna Qtd_Mov */

/***************************************************************************
 *
 *  Função: PEC  &Retorna Move Para Tras
 *  ****/
PEC_tpCondRet PEC_RetornaPodePular(Peca *peca,int *podePular)
{
    *podePular = peca->podePular;
    //Move Para Tras sempre será 0 ou 1.
    return PEC_CondRetOK;
}/* Fim função: PEC  &Retorna Move Para Tras */


/***************************************************************************
 *
 *  Função: PEC  &Retorna X Movimento
 *  ****/
PEC_tpCondRet PEC_RetornaXMovimento(Peca *peca,int i,int *x)
{
    if(peca->movPeca != NULL) {
        *x = peca->movPeca[i].x;
    }
    return PEC_CondRetOK;
}/* Fim função: PEC  &Retorna X Movimento */

/***************************************************************************
 *
 *  Função: PEC  &Retorna Y Movimento
 *  ****/

PEC_tpCondRet PEC_RetornaYMovimento(Peca *peca,int i,int *y)
{
    if(peca->movPeca != NULL) {
        *y = peca->movPeca[i].y;
    }
    return PEC_CondRetOK;
}/* Fim função: PEC  &Retorna Y Movimento */

/***************************************************************************
 *
 *  Função: PEC  &Eliminar Peca
 *  ****/

PEC_tpCondRet PEC_EliminarPeca(Peca *peca)
{
    peca->id = 'V';
    peca->cor = 'V';
    peca->qtdMov = 0;
    peca->podePular = 0;
    peca->movPeca = NULL;
    free(peca);
    return PEC_CondRetOK;
}/* Fim função: PEC  &Eliminar Peca */

/***************************************************************************
 *
 *  Função: PEC  &Altera Cor E Id
 *  ****/

PEC_tpCondRet PEC_AlteraCorEId(Peca *peca,char cor,char id) {
    peca->id = id;
    peca->cor = cor;
    return PEC_CondRetOK;
}/* Fim função: PEC  &Altera Cor E Id */

/********** Fim do módulo de implementação: PEC  Peca **********/
