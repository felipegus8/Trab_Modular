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
char idLL[] = "LL";



typedef struct casa {
    LIS_tppLista ameacados;
    /* ponteiro para a cabeÁa da lista que contÈm as peÁas ameaÁadas pela peÁa da casa */
    LIS_tppLista ameacantes;
    /* ponteiro para a cabeÁa da lista que contÈm as peÁas que ameaÁam a peÁa da casa */
    void *elemento;
    /*ponteiro para o elemento contido na casa */
#ifdef _DEBUG
    char tipoElemento; //tipo do ponteiro void elemento
#endif
} Casa;

typedef struct TAG_tabuleiro {
    Casa *tab[8][8];
    #ifdef _DEBUG
        Casa *corrente; //ponteiro para a casa corrente
    #endif
}Tabuleiro;

//typedef Tabuleiro * ptTabuleiro;

/***** ProtÛtipos das funÁıes encapuladas no mÛdulo *****/
void destruirValor(void *pValor);
TAB_tpCondRet criarListaPecas();
TAB_tpCondRet verificaMovimento(int posIniX,int posIniY,Peca *p,int movX,int movY,LIS_tppLista pLista,char corPeca,int qtdUnitarios);
int verificaCondMov(LIS_tppLista pLista,int *movimentoX, int *movimentoY,int posX,int posY,int qtdMov,int qtdFaltaX,int qtdFaltaY,char cor);
int *verificaDirecaoSeguida(int *movimentoX,int *movimentoY,int qtdFaltaX,int qtdFaltaY,int qtdMov);
int contaUnitarios(Peca *pecaLista,int qtdMov);
int verificaCoordenadas(int x, int y);
int verificaPeao(LIS_tppLista pLista,int posIniX,int posIniY,int posFimX,int posFimY,char corPeao);

/*****  CÛdigo das funÁıes exportadas pelo mÛdulo  *****/


/***************************************************************************
 *
 *  FunÁ„o: TAB  &Criar Casa
 *  ****/

TAB_tpCondRet TAB_CriaCasa(pCasa*casa,char cor,char id) {
    pCasa novo;
    novo = (Casa *) malloc(sizeof(Casa));
#ifdef _DEBUG
    ////CED_DefinirTipoEspaco(casa,LIS_tpCasa);
#endif
    PEC_CriaPeca((Peca **)&(novo->elemento),cor,id);
    LIS_CriarLista((LIS_tppLista *)&(novo->ameacados),a,destruirValor,LIS_tpElemLista);
    LIS_CriarLista((LIS_tppLista *)&(novo->ameacantes),b,destruirValor,LIS_tpElemLista);
    *casa = novo;
    return TAB_CondRetOK;
}/* Fim função: TAB  &Criar Casa*/

/***************************************************************************
 *
 *  Função: TAB  &Criar lista de listas duplamente encadeada
 *  ****/

TAB_tpCondRet TAB_CriaLL(LIS_tppLista *pLista) {
    LIS_tppLista novo,novo2;
    Casa *novaCasa;
    int i,j;
    LIS_CriarLista(&novo,idLL,destruirValor,LIS_tpCabeca);
    criarListaPecas();
    for(i=0;i<8;i++) {
        LIS_CriarLista((LIS_tppLista *)&novo2,idLL,destruirValor,LIS_tpNoCasa);
        LIS_InserirNo(novo,(void *)novo2);
        for(j=0;j<8;j++) {
                TAB_CriaCasa((Casa **)&(novaCasa),'V','V');
            
            LIS_InserirNo(novo2,(void *)novaCasa);
        }
    }
    

    
    *pLista = novo;
    return TAB_CondRetOK;
}/* Fim função: TAB  &Criar lista de listas duplamente encadeada*/




/***************************************************************************
 *
 *  Função: TAB  &Converter coordenadas de matriz para lista de listas
 *  ****/

TAB_tpCondRet TAB_Converte(LIS_tppLista pLista,int x,int y,pCasa *casa) {
    int i;
    pCasa aux;
    LIS_tppLista cabecaNo;
    if(pLista == NULL) {
        return 1;
    }
    IrInicioLista(pLista);
    
    for(i=0;i<x;i++) {
        LIS_IrProx(pLista);
    }
    LIS_ObterNo(pLista,(void **)&cabecaNo);
    IrInicioLista(cabecaNo);
    for(i=0;i<y;i++) {
        
        LIS_IrProx(cabecaNo);
        
    }
    LIS_ObterNo(cabecaNo,(void **)&aux);
    *casa = aux;
    return TAB_CondRetOK;
} /*Fim Função: TAB  &Converter coordenadas de matriz para lista de listas */

#ifdef _DEBUG
TAB_tpCondRet TAB_Deturpa(LIS_tppLista tabu,int acao) {
    LIS_tppLista noCabecas;
    pCasa noCasa;
    switch (acao) {
        case 1:
            LIS_DeturpaEliminaCorrente(tabu);
            break;
        case 2:
			LIS_ObterNo(tabu,(void **)&noCabecas);
            LIS_DeturpaAtribuiNullSucessor(noCabecas);
            break;
        case 3:
			LIS_ObterNo(tabu,(void **)&noCabecas);
            LIS_DeturpaAtribuiNullAntecessor(noCabecas);
            break;
        case 4:
			LIS_ObterNo(tabu,(void **)&noCabecas);
            LIS_DeturpaAtribuiLixoSucessor(noCabecas);
            break;
        case 5:
			LIS_ObterNo(tabu,(void **)&noCabecas);
            LIS_DeturpaAtribuiLixoAntecessor(noCabecas);
            break;
        case 6:
            LIS_ObterNo(tabu, (void **)&noCabecas);
            LIS_DeturpaAtribuiNullValorNo(noCabecas);
            break;
        case 7:
            LIS_ObterNo(tabu, (void **)&noCabecas);
            LIS_ObterNo(noCabecas,(void **)&noCasa);
            noCasa->tipoElemento = 'i';
            break;
        case 8:
            LIS_DeturpaDesencadeiaSemFree(tabu);
            break;
        case 9:
            LIS_DeturpaAtribuiNullCorrente(tabu);
            break;
        case 10:
            LIS_ObterNo(tabu, (void **)&noCabecas);
            LIS_DeturpaNosApontamIgual(noCabecas);
            break;
        case 11:
            LIS_DeturpaAtribuiNullOrigem(tabu);
            break;
        case 12:
            LIS_DeturpaAtribuiNullFim(tabu);
            break;
        case 13:
            LIS_DeturpaTrocaNumElem(tabu);
            break;
        case 14:
            LIS_ObterNo(tabu, (void **)&noCabecas);
            LIS_DeturpaDesencadeiaSemFree(noCabecas);
            break;
        case 15:
            LIS_ObterNo(tabu, (void **)&noCabecas);
            LIS_DeturpaAtribuiNullCorrente(noCabecas);
            break;
        case 16:
            LIS_DeturpaTrocaTipoLista(tabu, LIS_tpElemLista);
        case 17:
            LIS_ObterNo(tabu, (void **)&noCabecas);
            LIS_DeturpaTrocaTipoLista(noCabecas, LIS_tpCabeca);
        default:
            break;
    }
    
    return TAB_CondRetOK;
}
#endif


#ifdef _DEBUG

void TAB_VerificaCabecaLista(LIS_tppLista cabecaLista,int *numErros) {
    void *pOrigem,*pFimLista,*pCorrente;
    int passouOrigem = 0,numElem;
    LIS_RetornaOrigemLista(cabecaLista, &pOrigem);
	LIS_RetornaNumElementos(cabecaLista,&numElem);
    LIS_ObterNo(cabecaLista, &pCorrente);
	
    if(pOrigem == NULL) {
        LIS_RetornaFimLista(cabecaLista, pFimLista);
        if(pFimLista != NULL) {
            //CNT_Contar("erro-OrigemNulaFimNaoNulo" , __LINE__ );
			(*numErros)++;
        }
        LIS_ObterNo(cabecaLista, &pCorrente);
        if(pCorrente != NULL) {
            //CNT_Contar("erro-OrigemNulaCorrenteNaoNulo" , __LINE__ );
			(*numErros)++;
        }
        passouOrigem = 1;
    }
    if (pFimLista == NULL && passouOrigem == 0) {
        //CNT_Contar("erro-OrigemNaoNulaFimNulo");
		(*numErros)++;
    }
    
	if(numElem>0) {
		//CNT_Contar("verifica-NumElemMaiorQueZero" , __LINE__ );
		if(numElem == 1) {
			//CNT_Contar("verifica-NumElemIgualUm" , __LINE__ );
			if(pOrigem == NULL) {
				//CNT_Contar("erro-OrigemNulaNumElemIgualUm" , __LINE__ );
				(*numErros)++;
			}
			if(pOrigem != pFimLista) {
				//CNT_Contar("erro-FimDifInicio" , __LINE__ );
				(*numErros)++;
			}
		}
	} else {
		if(pOrigem != NULL) {
			//CNT_Contar("erro-OrigemNulaENumElemNulo");
			(*numErros)++;
		}
		if(pFimLista != NULL) {
			//CNT_Contar("erro-FimNuloENumElemNulo");
			(*numErros)++;
		}
		if(pCorrente != NULL) {
			//CNT_Contar("erro-CorrenteNuloENumElemNulo");
			(*numErros)++;
		}
	}
}


TAB_tpCondRet TAB_VerificaTabuleiro(LIS_tppLista tabu, int *numErros) {
    int i, j,Iterador,EstaAtivo,TipoEspaco,numEspacos,k;
	LIS_tpEspaco tipoNoCabecaListaCabecas,tipoNoCabecaListaCasas;
    void *noSucessor,*noAntecessor,*PonteiroVoid,*noCorrente,*noAntDoProx,*noProxDoAnt ;
    LIS_tppLista noCabeca;
    pCasa noCasa,noCasaAux;
    LIS_tpCondRet retLis;
    
    TAB_VerificaCabecaLista(tabu,numErros);
    
    //CED_MarcarEspacoAtivo((void *)tabu);
    
    IrInicioLista(tabu);
		
	for(i=0;i<8;i++) {
		retLis = LIS_ObterNo(tabu,(void **)&noCabeca);
        if(retLis == LIS_CondRetListaVazia) {
            //CNT_Contar("erro-noCabecaNulo",__LINE__);
        } else {
		LIS_RetornaAntecessor(tabu,&noAntecessor);
		LIS_RetornaSucessor(tabu,&noSucessor);
		TAB_VerificaCabecaLista(noCabeca,numErros);
		tipoNoCabecaListaCabecas = LIS_RetornaTipoEspaco(tabu);
        if(tipoNoCabecaListaCabecas != LIS_tpCabeca) {
            //CNT_Contar("erro-tipoNoCabeca",__LINE__);
            (*numErros)++;
        }
		tipoNoCabecaListaCasas = LIS_RetornaTipoEspaco(noCabeca);
        if (tipoNoCabecaListaCasas != LIS_tpNoCasa) {
            //CNT_Contar("erro-tipoNoCasa",__LINE__);
            (*numErros)++;
        }
			if(noAntecessor == NULL) {
				//CNT_Contar("verifica-AntecessorNuloListaCabecas",__LINE__);
				if(i>0) {
					//CNT_Contar("erro-AntecessorNuloListaCabecas",__LINE__);
					(*numErros)++;
				}
				
			} else {
				//CNT_Contar("verifica-AntecessorNaoNuloListaCabecas",__LINE__);
				if(i == 0) {
					//CNT_Contar("erro-AntecessorNaoNuloListaCabecas",__LINE__);
					(*numErros)++;
				}
				if(noAntecessor == 12) {
					//CNT_Contar("erro-AntecessorLixoListaCabecas",__LINE__);
					(*numErros)++;
				} else {
					LIS_RetornaProximoDoAnterior(tabu,&noProxDoAnt);
					if(noProxDoAnt != noCabeca) {
						(*numErros)++;
						//CNT_Contar("erro-sucessorDoAnteriorDifCorrenteListaCabecas",__LINE__);
					}
				}
			}
			if(noSucessor == NULL) {
				//CNT_Contar("verifica-SucessorNuloListaCabecas",__LINE__);
				if(i<7) {
					//CNT_Contar("erro-sucessorNuloListaCabecas",__LINE__);
					(*numErros)++;
				}
			} else {
				//CNT_Contar("verifica-sucessorNaoNuloListaCabecas",__LINE__);
				if(i == 7) {
					//CNT_Contar("erro-sucessorNaoNuloListaCabecas",__LINE__);
					(*numErros)++;
				}
				if(noSucessor == 12) {
					//CNT_Contar("erro-SucessorLixoListaCabecas",__LINE__);
				} else {
					//CNT_Contar("verificar-SucessorNaoLixoListaCabecas",__LINE__);
					LIS_RetornaAnteriorDoProximo(tabu,&noAntDoProx);
					if(noAntDoProx != noCabeca) {
						(*numErros)++;
						//CNT_Contar("erro-anteriorDoSucessorDifCorrenteListaCabecas",__LINE__);
					}
				}
			}
        
			for(j=0;j<8;j++) {
				retLis = LIS_ObterNo(noCabeca,(void **)&noCasa);
                if(retLis == LIS_CondRetListaVazia) {
                    //CNT_Contar("erro-noCasaNulo",__LINE__);
                } else {
				LIS_RetornaAntecessor(tabu,&noAntecessor);
				LIS_RetornaSucessor(tabu,&noSucessor);
			if(noAntecessor == NULL) {
				//CNT_Contar("verifica-AntecessorNuloListaCasas",__LINE__);
				if(i>0) {
					//CNT_Contar("erro-AntecessorNuloListaCasas",__LINE__);
					(*numErros)++;
				}
				
			} else {
				//CNT_Contar("verifica-AntecessorNaoNuloListaCasas",__LINE__);
				if(i == 0) {
					//CNT_Contar("erro-AntecessorNaoNuloListaCasas",__LINE__);
					(*numErros)++;
				}
				if(noAntecessor == 12) {
					//CNT_Contar("erro-AntecessorLixoListaCasas",__LINE__);
					(*numErros)++;
				} else {
					LIS_RetornaProximoDoAnterior(tabu,&noProxDoAnt);
					if(noProxDoAnt != noCasa) {
						(*numErros)++;
						//CNT_Contar("erro-sucessorDoAnteriorDifCorrenteListaCasas",__LINE__);
					}
				}
			}
			if(noSucessor == NULL) {
				//CNT_Contar("verifica-SucessorNuloListaCasas",__LINE__);
				if(i<7) {
					//CNT_Contar("erro-sucessorNuloListaCasas",__LINE__);
					(*numErros)++;
				}
			} else {
				//CNT_Contar("verifica-sucessorNaoNuloListaCasas",__LINE__);
				if(i == 7) {
					//CNT_Contar("erro-sucessorNaoNuloListaCasas",__LINE__);
					(*numErros)++;
				}
				if(noSucessor == 12) {
					//CNT_Contar("erro-SucessorLixoListaCasas",__LINE__);
				} else {
					//CNT_Contar("verificar-SucessorNaoLixoListaCasas",__LINE__);
					LIS_RetornaAnteriorDoProximo(tabu,&noAntDoProx);
					if(noAntDoProx != noCasa) {
						(*numErros)++;
						//CNT_Contar("erro-anteriorDoSucessorDifCorrenteListaCasas",__LINE__);
					}
				}
			}
            }/*else grande */
				LIS_IrProx(noCabeca);
			}
        }/*else grande */
		LIS_IrProx(tabu);
	}
    
    /*Verifica se há dois nós casa iguais */
    for (i=0; i<8; i++) {
        LIS_ObterNo(tabu, (void **)&noCabeca);
        for (j=0; j<8; j++) {
            LIS_ObterNo(noCabeca, (void **)&noCasa);
            noCasaAux = noCasa;
            for (k=0; k<8; k++) {
                LIS_ObterNo(noCabeca, (void **)&noCasa);
                if(noCasa == noCasaAux) {
                    //CNT_Contar("erro-DuasCasasComMesmoEndereco",__LINE__);
                }
                LIS_IrProx(noCabeca);
            }
            for (k=7; k>j + 1; k--) {
                LIS_IrAnt(noCabeca);
            }
        }
        LIS_IrProx(tabu);
    }

    
    //numEspacos = //CED_ObterNumeroEspacosAlocados() ;

	//CED_InicializarIteradorEspacos() ;
        
	for(Iterador = 0;Iterador<numEspacos;Iterador++) {
		//PonteiroVoid = //CED_ObterPonteiroEspacoCorrente();
		//EstaAtivo = //CED_EhEspacoAtivo(PonteiroVoid);
		//TipoEspaco = //CED_ObterTipoEspaco(PonteiroVoid);
		if(TipoEspaco ==  LIS_tpCabeca || TipoEspaco ==  LIS_tpElemLista || TipoEspaco ==  LIS_tpCasa) {
			if(EstaAtivo == 0) {
				//CNT_CONTAR("erro-VazamentoDeMemoria",__LINE__);
				//CED_TerminarIteradorEspacos();
			}
		}
		//CED_AvancarProximoEspaco();
	}
	
	//CED_TerminarIteradorEspacos();
	
	
        
   
    return TAB_CondRetOK;
}

#endif

/***************************************************************************
 *
 *  FunÁ„o: TAB  &Inserir Peca
 *  ****/


TAB_tpCondRet TAB_InserirPeca(LIS_tppLista pLista,int x, int yi,char cor,char id) {
    Peca *pecaLista;
    pCasa aux;
    
    if(x>7 || x<0 || yi>7 || yi<0) {
        
        return TAB_CondRetCoordenadaNExiste;
    }
    
    
    
    TAB_Converte(pLista, x, yi, (Casa **)&aux);
    
    retPeca = PEC_CriaPeca((Peca **)&(aux->elemento),id,cor);//cria peça nova
    if(retPeca == PEC_CondRetFaltouMemoria) {
        
        return TAB_CondRetFaltouMemoria;
    }
    
    retPeca = PEC_CriaPeca((Peca **)&pecaLista,id,cor);//cria peÁa nova
    
    if(retPeca == PEC_CondRetFaltouMemoria) {
        return TAB_CondRetFaltouMemoria;
    }
    retLis = LIS_InserirNo(listaPecas,(void *)pecaLista); //insere peça nova na lista de peças
    
    
    return TAB_CondRetOK;
    
}/* Fim função: TAB  &Inserir Peca*/


/***************************************************************************
 *
 *  FunÁ„o: TAB  &Obter Peca
 *  ****/
TAB_tpCondRet TAB_ObterPeca(LIS_tppLista pLista,int x, int y, char *cor, char *id) {
    char corObtida,idObtido;
    pCasa aux;
    if(x>7 || x<0 || y>7 || y < 0) {
        return TAB_CondRetCoordenadaNExiste;
    }

    TAB_Converte(pLista, x, y, (Casa **)&aux);
    
    PEC_RetornaCor((Peca *)(aux->elemento),&corObtida);
    PEC_RetornaId((Peca *)(aux->elemento),&idObtido);
    *cor = corObtida;
    *id = idObtido;
    
    return TAB_CondRetOK;
}/* Fim funÁ„o: TAB  &Obter Peca */
/***************************************************************************
 *
 *  FunÁ„o: TAB  &Retirar Peca
 *  ****/
TAB_tpCondRet TAB_RetirarPeca(LIS_tppLista pLista,int x,int y) {
    char corObtida,idObtido;
  
    pCasa aux;
    if(x>7 || x<0 || y>7 || y<0) {
        return TAB_CondRetCoordenadaNExiste;
    }
    TAB_Converte(pLista, x, y, &aux);
    
    PEC_RetornaCor((Peca *)(aux->elemento),&corObtida);
    PEC_RetornaId((Peca *)(aux->elemento),&idObtido);
    
    if(corObtida== 'V' &&  idObtido== 'V') {
        return TAB_CondRetCasaVazia;
    }
    
    PEC_EliminarPeca((Peca *)(aux->elemento));
    return TAB_CondRetOK;
}/* Fim funÁ„o: TAB  &Retirar Peca */



/***************************************************************************
 *
 *  FunÁ„o: TAB  &Inicializa Lista Ameacados
 *  ****/

TAB_tpCondRet TAB_AtualizaListaAmeacadosEAmeacantes(LIS_tppLista pLista) {

    TAB_tpCondRet retTab;
    int i,j,k,xObtido,yObtido,qtdUnitarios,qtdMov,verificaMov;
    char corPecaUsada,corPecaUsada2,idPecaUsada,idPecaUsada2;
    Peca *pecaUsada;
    Peca *pecaUsada2;
    pCasa aux,aux2,aux3,aux4;
    
    
    
    for (i=0; i<8; i++) {
        for (j=0; j<8; j++) {
            TAB_Converte(pLista, i, j, &aux);
            EsvaziarLista(aux->ameacados);
            EsvaziarLista(aux->ameacantes);
           
        }
    }
    /*para cada casa no tabuleiro */
    for (i=0; i<8; i++) {
        for (j=0; j<8; j++) {
            /*cria uma peça identica à do peça do tabuleiro na posiçao (i,j) */
            
            TAB_Converte(pLista, i, j, &aux);
            
            pecaUsada = (Peca *) aux->elemento;
            
            PEC_RetornaCor(pecaUsada, &corPecaUsada);
            
            PEC_RetornaId(pecaUsada, &idPecaUsada);
            
            PEC_CriaPeca(&pecaUsada,idPecaUsada,corPecaUsada);
            
            
            PEC_RetornaQtd_Mov(pecaUsada, &qtdMov);
            qtdUnitarios = contaUnitarios(pecaUsada, qtdMov);
            //printf("(%d,%d)\n",i,j);
            if(corPecaUsada != 'V' && idPecaUsada != 'V') {//caso a casa na esteja vazia
                for(k=0;k<qtdMov;k++) {
                    pecaUsada = (Peca *) aux->elemento;
                    PEC_RetornaCor(pecaUsada, &corPecaUsada);
                    
                    PEC_RetornaId(pecaUsada, &idPecaUsada);
                    
                    PEC_CriaPeca(&pecaUsada,idPecaUsada,corPecaUsada);
                    PEC_RetornaXMovimento(pecaUsada, k, &xObtido);//recebe a coordenada x do movimento
                    PEC_RetornaYMovimento(pecaUsada, k, &yObtido);//recebe a coordenada y do movimento
                    if(idPecaUsada != 'P' && idPecaUsada  != 'R') {
                        
                        verificaMov = verificaMovimento(i, j, pecaUsada,i + xObtido,j + yObtido, pLista, corPecaUsada, qtdUnitarios);
                    } else if(idPecaUsada == 'P')  {
                        verificaMov = 7;
                        if(k == 0) { //para peão só precisamos verificar uma vez
                            if(corPecaUsada == 'B') {
                                retTab = TAB_ObterPeca(pLista, i + 1, j + 1,&corPecaUsada2 ,&idPecaUsada2);/*recebe cor e id de casa onde o peão poderia comer */
                                if(retTab == TAB_CondRetOK) {
                                    if(idPecaUsada2 != 'V' && corPecaUsada2 == 'P') {/*caso haja uma peça que possa ser comida pelo peão */
                                        PEC_CriaPeca(&pecaUsada2,idPecaUsada2,corPecaUsada2);/*cria peça que pode ser comida */
                                        TAB_Converte(pLista, i + 1, j + 1, &aux2);
                                        LIS_InserirNo(aux2->ameacantes, (void *)pecaUsada);/*insere peão comedor na lista de ameaçantes de peça que pode ser comida */
                                        TAB_Converte(pLista, i, j, &aux3);
                                        LIS_InserirNo(aux3->ameacados, (void *)pecaUsada2);/* insere peça que pode ser comida na lista de ameaçados pelo peão*/
                                       
                                    }
                                }
                                retTab = TAB_ObterPeca(pLista, i - 1, j + 1,&corPecaUsada2 ,&idPecaUsada2);/*recebe cor e id de casa onde o peão poderia comer */
                                if(retTab == TAB_CondRetOK) {
                                if(idPecaUsada2 != 'V' && corPecaUsada2 == 'P') {/*caso haja uma peça que possa ser comida pelo peão */
                                    PEC_CriaPeca(&pecaUsada2,idPecaUsada2,corPecaUsada2);/*cria peça que pode ser comida */
                                    TAB_Converte(pLista, i - 1, j + 1, &aux3);
                                    LIS_InserirNo(aux3->ameacantes, (void *)pecaUsada);/*insere peão comedor na lista de ameaçantes de peça que pode ser comida */
                                    TAB_Converte(pLista, i, j, &aux4);
                                    LIS_InserirNo(aux4->ameacados, (void *)pecaUsada2); /* insere peça que pode ser comida na lista de ameaçados pelo peão*/
                                   
                                }
                                }
                                continue;
                            
                            
                            } else {
                                retTab = TAB_ObterPeca(pLista, i + 1, j - 1,&corPecaUsada2 ,&idPecaUsada2);/*recebe cor e id de casa onde o peão poderia comer */
                                if(retTab == TAB_CondRetOK) {
                                    if(idPecaUsada2 != 'V' && corPecaUsada2 == 'B') {/*caso haja uma peça que possa ser comida pelo peão */
                                        PEC_CriaPeca(&pecaUsada2,idPecaUsada2,corPecaUsada2);/*cria peça que pode ser comida */
                                        TAB_Converte(pLista, i + 1, j  - 1, &aux2);
                                        LIS_InserirNo(aux2->ameacantes, (void *)pecaUsada);/*insere peão comedor na lista de ameaçantes de peça que pode ser comida */
                                        TAB_Converte(pLista, i, j, &aux3);
                                        LIS_InserirNo(aux3->ameacados, (void *)pecaUsada2);/* insere peça que pode ser comida na lista de ameaçados pelo peão*/
                                        
                                    }
                                }
                                retTab = TAB_ObterPeca(pLista, i - 1, j - 1,&corPecaUsada2 ,&idPecaUsada2);/*recebe cor e id de casa onde o peão poderia comer */
                                if(retTab == TAB_CondRetOK) {
                                    if(idPecaUsada2 != 'V' && corPecaUsada2 == 'B') {/*caso haja uma peça que possa ser comida pelo peão */
                                        PEC_CriaPeca(&pecaUsada2,idPecaUsada2,corPecaUsada2);/*cria peça que pode ser comida */
                                        TAB_Converte(pLista, i + 1, j  - 1, &aux3);
                                        LIS_InserirNo(aux3->ameacantes, (void *)pecaUsada);/*insere peão comedor na lista de ameaçantes de peça que pode ser comida */
                                        TAB_Converte(pLista, i, j, &aux4);
                                        LIS_InserirNo(aux4->ameacados, (void *)pecaUsada2);/* insere peça que pode ser comida na lista de ameaçados pelo peão*/
                                       
                                    }
                                }
                                continue;
                        }
                        }
                    } else {
                        verificaMov = TAB_VerificaMovimentoRei(pLista, i, j, corPecaUsada, i + xObtido, j + yObtido);
                    }
                    
                    if(verificaMov == 2) {//caso a peça na posição (i,j) n seja um peão e possa comer outra peça
                        if (verificaCoordenadas(i + xObtido, j + yObtido) == 0) {/*caso a coordenada obtida seja invalida */
                            continue;
                        }
                        TAB_Converte(pLista, i + xObtido, j + yObtido, &aux3);

                            pecaUsada2 = (Peca *) aux3->elemento;
                            
                            PEC_RetornaCor(pecaUsada2, &corPecaUsada2);
                            
                            PEC_RetornaId(pecaUsada2, &idPecaUsada2);
                            
                            PEC_CriaPeca(&pecaUsada2,idPecaUsada2,corPecaUsada2);
                        
                            /*
                            pecaUsada = (Peca *) tabu->tab[i][j]->elemento;
                            PEC_RetornaCor(pecaUsada, &corPecaUsada);
                        
                            PEC_RetornaId(pecaUsada, &idPecaUsada);
                        
                            PEC_CriaPeca(&pecaUsada,idPecaUsada,corPecaUsada);
                            */

                        PEC_RetornaCor(pecaUsada2, &corPecaUsada2);
                        PEC_RetornaId(pecaUsada2, &idPecaUsada2);
                        LIS_InserirNo(aux->ameacados, (void *)pecaUsada2);/*Insere na lista de ameçados da peça que come a peça que ele captura */
                        LIS_InserirNo(aux3->ameacantes, (void *)pecaUsada);/*Insere na lista de ameçantes da peça comida a peça que a captura */
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
TAB_tpCondRet TAB_ObterListaAmeacantes(LIS_tppLista pLista,int x, int y,LIS_tppLista *listaAmeacantes)
{
    pCasa aux;
    LIS_tppLista listaAmeacantesCopia = NULL;
    LIS_CriarLista(&listaAmeacantesCopia,a,destruirValor,LIS_tpElemLista);
    if(listaAmeacantesCopia == NULL) {
        return TAB_CondRetListaAmeacantesNaoExiste;
    }
    if(x>7 || x<0 || y>7 || y<0) {
        return TAB_CondRetCoordenadaNExiste;
    }
    
    TAB_Converte(pLista, x, y, &aux);
    
    listaAmeacantesCopia = aux->ameacantes;
    *listaAmeacantes = listaAmeacantesCopia;
    
    
    return TAB_CondRetOK;
}
/* Fim funÁ„o: TAB  &Obter Lista Ameacantes*/
/***************************************************************************
 *
 *  FunÁ„o: TAB  &Obter Lista Ameacados
 *  ****/
TAB_tpCondRet TAB_ObterListaAmeacados(LIS_tppLista pLista,int x, int y,LIS_tppLista *listaAmeacados)
{
    pCasa aux;
    LIS_tppLista listaAmeacadosCopia = NULL;
    LIS_CriarLista(&listaAmeacadosCopia,a,destruirValor,LIS_tpElemLista);
    if(listaAmeacadosCopia == NULL) {
        return TAB_CondRetListaAmeacantesNaoExiste;
    }
    if(x>7 || x<0 || y>7 || y<0) {
        return TAB_CondRetCoordenadaNExiste;
    }
    
    TAB_Converte(pLista, x, y, &aux);
    listaAmeacadosCopia = aux->ameacados;
    *listaAmeacados = listaAmeacadosCopia;
    
    return TAB_CondRetOK;
}
/* Fim funÁ„o: TAB  &Obter Lista Ameacados Peca */

/***************************************************************************
 *
 *  FunÁ„o: TAB  &Mover Peca
 *  ****/
TAB_tpCondRet TAB_MoverPeca(LIS_tppLista pLista,int xo,int yi,int xd,int yi2) {
    char corPecaLista,corPecaTabuleiro,idPecaLista,idPecaTabuleiro;
    int i,qtdMov,xObtido,yObtido,achou = 0,achou2 = 0,qtdUnitarios = 0,verificaMov;
    Peca *pecaLista = NULL;
   
	   PEC_CriaPeca(&pecaLista,'V','V');
	   
	   TAB_ObterPeca(pLista,xo,yi,&corPecaTabuleiro,&idPecaTabuleiro);
	   
	   
	   IrInicioLista(listaPecas);
	   
	   while(1) {
           
           
           LIS_ObterNo(listaPecas,(void **)&pecaLista);
           PEC_RetornaCor((Peca *)pecaLista,&corPecaLista);
           PEC_RetornaId((Peca *)pecaLista,&idPecaLista);
           if(idPecaTabuleiro == idPecaLista) {  //caso a peÁa esteja na lista sai do loop
               achou2 = 1;
               if (idPecaTabuleiro == 'P') {
                   printf("Entrou aqui\n");
                   achou = 1;
               }
               break;
           }
           if(LIS_IrProx(listaPecas) == LIS_CondRetFimLista) { //obtem a peÁa do nó corrente da lista
               break;
           }
           /* obtem a cor e o id da peÁa corrente */
           
       }
    
	   printf("depois %d\n",achou2);
	   
    PEC_RetornaQtd_Mov(pecaLista,&qtdMov); //obtem o movimento da peÁa
    
    qtdUnitarios = contaUnitarios(pecaLista, qtdMov);
    for(i=0;i<qtdMov;i++) {
        PEC_RetornaXMovimento(pecaLista,i,&xObtido);
        PEC_RetornaYMovimento(pecaLista,i,&yObtido);
        if (xObtido == xd - xo && yObtido == yi2 - yi) { /*caso haja algum movimento da peça que seja igual ao 
                                                          movimento proposta pelo usuário */
            achou = 1; //se houver achou = 1
        }
        
    }

    
    
    if(achou == 1) {
        if(idPecaTabuleiro != 'P' && idPecaTabuleiro != 'R') {
            verificaMov =  verificaMovimento(xo,yi,pecaLista,xd,yi2,pLista,corPecaTabuleiro,qtdUnitarios);
        } else if(idPecaTabuleiro == 'P') {
            verificaMov = verificaPeao(pLista, xo, yi, xd, yi2, corPecaTabuleiro);
        } else {
            verificaMov = TAB_VerificaMovimentoRei(pLista, xo, yi, corPecaTabuleiro, xd, yi2);
        }
        
        if(verificaMov == 2) { //caso alguma peça tenha sido comida no movimento
            TAB_RetirarPeca(pLista,xd,yi2); //retira a peça que foi comida do tabuleiro
        } else if(verificaMov == 7) { //caso o movimento seja inválido(no caso, se houver algum bloqueio)
            return TAB_CondRetMovimentoIrregular;
        }
        /*caso o movimento tenha sido bem su//CEDido */
        TAB_RetirarPeca(pLista,xo,yi); //retira peça de onde ele estava pré-movimento
        //printf("retirou e inseriu\n");
        
        
        TAB_InserirPeca(pLista,xo,yi,'V','V'); //Insere uma "casa vazia" no local onde a peça esta pré-movimento
        
        TAB_InserirPeca(pLista,xd,yi2,corPecaTabuleiro,idPecaTabuleiro); //Insere peça na posiçao pos-movimento
        TAB_AtualizaListaAmeacadosEAmeacantes(pLista);//atualiza lista de ameaçantes e ameaçados
        if(verificaMov == 0) {
        return TAB_CondRetOK;
        }
        return TAB_CondRetComeu;
    }
		  
    return TAB_CondRetMovimentoIrregular;
}/* Fim funÁ„o: TAB  &Mover Peca */

TAB_tpCondRet TAB_DestruirCasa(pCasa casa) {
    if(casa->elemento != NULL) {
        LIS_DestroiLista(casa->ameacados);
        LIS_DestroiLista(casa->ameacantes);
        PEC_LiberaPeca(casa->elemento);
    }
    return TAB_CondRetOK;
}

/***************************************************************************
 *
 *  FunÁ„o: TAB  &Destruir Tabuleiro
 *  ****/
TAB_tpCondRet TAB_DestruirTabuleiro(LIS_tppLista tabu) {
    int k,h;
    LIS_tppLista noLista;
    pCasa noCasa;
    IrInicioLista(tabu);
    for (k = 0; k<8; k++) {
        LIS_ObterNo(tabu, (void **)&noLista);
        IrInicioLista(noLista);
        for (h = 0; h<8; h++) {
            LIS_ObterNo(noLista, (void **)&noCasa);
            TAB_DestruirCasa(noCasa);
            LIS_IrProx(noLista);
        }
        
        
        LIS_IrProx(tabu);
    }
    
    
    LIS_DestroiLista(tabu);
    
    LIS_DestroiLista(listaPecas);
    return TAB_CondRetOK;
}/* Fim funÁ„o: TAB  &Destruir Tabuleiro*/

/***************************************************************************
 
 
 /*****  CÛdigo das funÁıes encapsuladas no mÛdulo  *****/

/***************************************************************************

 *
 *  FunÁ„o: TAB  &Destruir Valor
 *  ****/
void destruirValor(void *pValor) {
    free(pValor);
    #ifdef _DEBUG
        //CED_MarcarEspacoNaoAtivo(pValor);
    #endif
    //
}/* Fim funÁ„o: TAB  -Destruir Valor*/
/***************************************************************************
 *
 *  FunÁ„o: TAB  &Criar Lista Pecas
 *  ****/
TAB_tpCondRet criarListaPecas() {
    retLis = LIS_CriarLista(&listaPecas,idListaPecas,destruirValor,LIS_tpElemLista);
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
                //printf("Y : %d e %d\n",movimentoY[i],i);
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

int verificaCondMov(LIS_tppLista pLista,int *movimentoX, int *movimentoY,int posX,int posY,int qtdMov,int qtdFaltaX,int qtdFaltaY,char cor) {
    int *direcao,i,xDirecao,yDirecao,diretor,qtdFalta;
    char idObtido,corObtida;
    TAB_tpCondRet condRet;
    
    
    
    direcao = verificaDirecaoSeguida(movimentoX,movimentoY,qtdFaltaX,qtdFaltaY,qtdMov);
    
    
    xDirecao = direcao[0];
    yDirecao = direcao[1];
    
    
    
    
    if(direcao[0] == 0 && direcao[1] == 0) {
        return 0;
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
            condRet = TAB_ObterPeca(pLista,posX + xDirecao,posY + yDirecao,&corObtida,&idObtido);
            qtdFaltaX -= xDirecao;
            qtdFaltaY -= yDirecao;
            posX += xDirecao;
            posY += yDirecao;
            if (corObtida != 'V') {
                if (qtdFaltaX == 0 && qtdFaltaY == 0) {
                    if (corObtida != cor) {
                        //printf("Comeu\n");
                        return 2;
                    }
                    
                }
                return 0;
            } else {
                if (qtdFaltaX == 0 && qtdFaltaY == 0) {
                    //printf("Chegou sem comer\n");
                    return 1;
                }
            }
        }
        
    }
    
    free(direcao);
    return 0;
    
}/* Fim funÁ„o: TAB  -Verifica CondiÁ„o De Movimento*/

/***************************************************************************
 *
 *  FunÁ„o: TAB  &Verifica Validade Do Movimento
 *  ****/




TAB_tpCondRet verificaMovimento(int posIniX,int posIniY,Peca *p,int movX,int movY,LIS_tppLista pLista,char corPeca,int qtdUnitarios) {
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
            
            if((xObtido + posIniX) == movX && (yObtido + posIniY) == movY) {
                if ((xObtido + posIniX)<0 || (xObtido + posIniX)>7 || (posIniY + yObtido)<0 || (posIniY + yObtido)>7) {
                //printf("xObtido + posIniX: %d\n",yObtido + posIniY);
                return 7;
            }
                TAB_ObterPeca(pLista, xObtido + posIniX, yObtido + posIniY, &corObtida, &idObtido);
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
    
    
    retornoHard = verificaCondMov(pLista,movimentoX,movimentoY,posIniX,posIniY,qtdUnitarios,movX - posIniX,movY - posIniY,corPeca);
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
/***************************************************************************
 *
 *  FunÁ„o: TAB  &Verifica Validade Do Movimento Do Peão
 *  ****/

int verificaPeao(LIS_tppLista pLista,int posIniX,int posIniY,int posFimX,int posFimY,char corPeao) {
    char corPecaAlvo,idPecaAlvo;
    TAB_ObterPeca(pLista, posFimX, posFimY, &corPecaAlvo, &idPecaAlvo);
    if(corPeao == 'B') {
    if (((posFimX - posIniX) == 1 && (posFimY - posIniY) == 1) || ((posFimX - posIniX) == -1 && (posFimY - posIniY) == 1)) {
        
        if(corPecaAlvo != 'V') {
            if (corPecaAlvo != corPeao) {
                return 2;
            }
        }
    } else if((posFimX - posIniX) == 0 && (posFimY - posIniY) == 1) {
        if (corPecaAlvo == 'V') {
            return 0;
        }
    }
    } else {
        if (((posFimX - posIniX) == -1 && (posFimY - posIniY) == -1) || ((posFimX - posIniX) == 1 && (posFimY - posIniY) == -1)) {
            
            
            if(corPecaAlvo != 'V') {
                if (corPecaAlvo != corPeao) {
                    return 2;
                }
            }
        } else if((posFimX - posIniX) == 0 && (posFimY - posIniY) == -1) {
            if (corPecaAlvo == 'V') {
                return 0;
            }
        }
    }
    return 7;
}/* Fim funÁ„o: TAB  -Verifica Validade Do Movimento Do Peão*/

/***************************************************************************
 *
 *  FunÁ„o: TAB  &Conta Movimentos Unitários De Uma Peça
 *  ****/
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
}/* Fim funÁ„o: TAB  -Conta Movimentos Unitários De Uma Peça*/

int verificaCoordenadas(int x, int y) {
    if(x>7 || x<0 || y>7 || y<0) {
        return 0;
    }
    return 1;
}

/***************************************************************************
 *
 *  FunÁ„o: TAB  &Verifica Se Movimento Deixa Rei Em Cheque
 *  ****/
int verificaSeMovimentoDeixaReiEmCheque(LIS_tppLista pLista,int posX,int posY,char cor) {
    char corObtida,idObtido,i,j,retornoVerifica = 7;
    pCasa aux;
    int qtdMov,qtdUnitarios;
    Peca *ameacante;
    /*quando a peça que pode comer um rei é o outro rei, podemos tratar o movimento dessa peça como se fosse uma peça qualquer, tendo em vista que se o rei1 puder comer o rei2, não importa se o movimento feito para levar o rei1 a comer o rei2 faça com que ele fique em cheque, pois se rei2 for comido, acaba o jogo */
    for(i=0;i<8;i++) {
        for (j=0; j<8; j++) {
            TAB_ObterPeca(pLista, i, j, &corObtida, &idObtido);
            if(corObtida != 'V') {
                TAB_Converte(pLista, i, j, &aux);
                ameacante = (Peca *)aux->elemento;
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
                        //printf("(%d,%d) e cor: %c e id: %c\n",posX,posY,corObtida,idObtido);
                        retornoVerifica = verificaMovimento(i, j, ameacante, posX, posY, pLista, cor, qtdUnitarios);
                        //printf("ret ver:%d\n",retornoVerifica);
                    } else  {
                        if((posX - i == 1 && posY - j == 1) || (posX - i == -1 && posY - j == 1)) {
                            retornoVerifica = 2;
                        }
                    }
                }
                
                
                
                if ((retornoVerifica == 0 || retornoVerifica == 2) && cor != corObtida) {
                   // printf("cor na checa: %c e %c e (%d,%d)\n",corObtida,idObtido,posX,posY);
                    return 0;
                }
            }
        }
    }
    return 1;
}/* Fim funÁ„o: TAB  -Verifica Se Movimento Deixa Rei Em Cheque*/


/***************************************************************************
 *
 *  FunÁ„o: TAB  &Verifica Movimento Do Rei
 *  ****/
TAB_tpCondRet TAB_VerificaMovimentoRei(LIS_tppLista pLista,int xRei, int yRei, char cor,int xFim,int yFim) {
    int retornoVerifica1,retornoVerifica2;
    pCasa aux;
    Peca *rei;
    TAB_Converte(pLista, xRei, yRei, &aux);
    rei = (Peca *)aux->elemento;
    PEC_AlteraCorEId(rei,'V','V');/*Finge que casa onde o rei está se encontra vazia,visto que a posição atual da rei poderia "barrar" alguma peça que poderia andar para alguma posição onde rei também poderia ir e, portanto, o deixando em cheque*/
    retornoVerifica1 = verificaMovimento(xRei, yRei, rei, xFim, yFim, pLista, cor, 8);
    if (retornoVerifica1 != 7) {
        retornoVerifica2 = verificaSeMovimentoDeixaReiEmCheque(pLista, xFim, yFim, cor);
        if (retornoVerifica2 == 1) {
            PEC_AlteraCorEId(rei, cor, 'R');/*coloca rei de volta */
            return retornoVerifica1;
        }
        //printf("movimento é valido,contudo deixa o rei em cheque, logo, ilegal\n");
    }
    PEC_AlteraCorEId(rei, cor, 'R');/*coloca rei de volta */
    return 7;
}/* Fim funÁ„o: TAB  -Verifica Movimento Do Rei*/

/***************************************************************************
 *
 *  FunÁ„o: TAB  &Verifica Check
 *  ****/
TAB_tpCondRet TAB_VerificaCheck(LIS_tppLista pLista,int xRei,int yRei) {
    int numElem;
    pCasa aux;
    TAB_Converte(pLista, xRei, yRei, &aux);
    LIS_RetornaNumElementos(aux->ameacantes, &numElem);
    if(numElem>0) {
        return TAB_CondRetCheck;
    }
    return TAB_CondRetNoCheck;
}/* Fim funÁ„o: TAB  -Verifica Check*/

/***************************************************************************
 *
 *  FunÁ„o: TAB  &Verifica Check Mate
 *  ****/
TAB_tpCondRet TAB_VerificaCheckMate(LIS_tppLista pLista,int xRei,int yRei,int xAmeacante,int yAmeacante) {
    Peca *pecaTabuleiro,*ameacante,*rei;
    pCasa aux;
    int qtdMovRei,podePular,i,j,xMovimento,yMovimento,retornoVerifica,podeMover = 0,podeSacrificar=0,numElemLista,qtdUnitarios,xDirecao,yDirecao,xSacrificio,ySacrificio,qtdMovTab,xSacrificioOG,ySacrificioOG;
    LIS_tppLista listaAmeacantes;
    char corRei,corPecaAmeacante,idPecaAmeacante,corPecaTabuleiro,idPecaTabuleiro,idTeste;
    //verifica se o rei pode se mexer
    TAB_Converte(pLista, xRei, yRei, &aux);
    rei = (Peca *)aux->elemento;
    TAB_Converte(pLista, xAmeacante, yAmeacante, &aux);
    ameacante = (Peca *)aux->elemento;
    PEC_RetornaQtd_Mov(rei, &qtdMovRei);
    PEC_RetornaCor(rei, &corRei);
    for(i=0;i<qtdMovRei;i++) { //analisa todos os movimentos que o rei pode fazer
        PEC_RetornaXMovimento(rei, i, &xMovimento);
        PEC_RetornaYMovimento(rei, i, &yMovimento);
        //printf("mov: (%d,%d) e i:%d\n",xRei + xMovimento,yRei+yMovimento,i);
        retornoVerifica = TAB_VerificaMovimentoRei(pLista, xRei, yRei, corRei, xRei + xMovimento, yRei + yMovimento);
        
        if(retornoVerifica != 7) { //verifica se o movimento é possível
            //printf("Não está em cheque, pois pode ir para (%d,%d)\n",xRei + xMovimento,yRei + yMovimento);
            podeMover = 1;
        }
        
    }
    /*caso o rei n possa se movimentar para sair do cheque */
    if(podeMover == 1) {//se puder se mover
        return TAB_CondRetEscapouSeMovimentando;
    }
    TAB_ObterListaAmeacantes(pLista, xAmeacante, yAmeacante, &listaAmeacantes);
    LIS_RetornaNumElementos(listaAmeacantes,&numElemLista);
    if(numElemLista>0) {//verifica se alguma peça pode comer a peça que ameaça o rei
        //printf("num real: %d\n",numElemLista);
        LIS_ObterNo(listaAmeacantes, (void **)&lis);
        PEC_RetornaId(lis, &idTeste);
        //printf("id Teste: %c\n",idTeste);
        printf("Há elementos que podem capturar a peça que colocou o rei em cheque\n");
        return TAB_CondRetComeuParaSalvar;//se puder
    }
    TAB_ObterPeca(pLista, xAmeacante, yAmeacante, &corPecaAmeacante, &idPecaAmeacante);
    PEC_RetornaPodePular(ameacante, &podePular);
    /*caso o rei n possa se movimentar para sair do cheque e nenhuma peça possa comer a peça que ameaça o rei*/
    /*Verifica se alguma peça pode "barrar" movimento da peça que ameaça o rei */
    if(podePular == 1 ||(((abs(xAmeacante - xRei)== 0) || abs(xAmeacante - xRei)== 1) && (abs(yAmeacante - yRei) == 0|| abs(yAmeacante - yRei) == 1))) {/*se a peça que ameaça o rei puder pular não há como "barrar" ela */
        return TAB_CondRetCheckMate;
        
    } else {
        /*obtem direção do movimento que a peça ameaçante fará para comer o rei*/
        xDirecao = xRei - xAmeacante;
        yDirecao = yRei - yAmeacante;
        //printf("xDir: %d e yDir: %d\n",xDirecao,yDirecao);
        /*obtem posição coordenada x da casa mais próxima do rei onde passa a peça ameaçante */
        if(xDirecao != 0) {
            xSacrificio = xRei -(xDirecao/(abs(xDirecao))); 
        } else {
            xSacrificio = xRei;
        }
        /*obtem posição coordenada y da casa mais próxima do rei onde passa a peça ameaçante */
        if(yDirecao != 0) {
            ySacrificio = yRei -(yDirecao/(abs(yDirecao)));
        } else {
            ySacrificio = yRei;
        }
        xSacrificioOG = xSacrificio;
        ySacrificioOG = ySacrificio;
        //printf("sac: (%d,%d)\n",xSacrificio,ySacrificio);
        for (i=0; i<8; i++) {
            for (j=0; j<8; j++) {
                TAB_Converte(pLista, i, j, &aux);
                pecaTabuleiro = (Peca *) aux->elemento;
                PEC_RetornaCor(pecaTabuleiro, &corPecaTabuleiro);
                PEC_RetornaId(pecaTabuleiro, &idPecaTabuleiro);
                PEC_RetornaQtd_Mov(pecaTabuleiro, &qtdMovTab);
                qtdUnitarios = contaUnitarios(pecaTabuleiro, qtdMovTab);
                if(corPecaTabuleiro == corRei && (i != xRei || j != yRei)) {
                    xSacrificio = xSacrificioOG;
                    ySacrificio = ySacrificioOG;
                    while(xSacrificio != xAmeacante || ySacrificio != yAmeacante) {/*para cada casa no caminho que a peça ameaçante faz para chegar até o rei */
                        /* verifica se alguma peça da cor do rei ameaçado pode entrar no caminho*/
                    if(idPecaTabuleiro != 'P') {
                        
                        retornoVerifica = verificaMovimento(i, j, pecaTabuleiro, xSacrificio, ySacrificio, pLista, corPecaTabuleiro, qtdUnitarios);
                    } else {
                        retornoVerifica = verificaPeao(pLista, i, j, xSacrificio, ySacrificio, corPecaTabuleiro);
                    }
                    if(retornoVerifica == 0) {/*caso possa */
                        printf("ALLAHU AKBAR!!!\n");
                        printf("Peca id: %c e cor: %c na posicao(%d,%d) pode se sacrificar\n",idPecaTabuleiro,corPecaTabuleiro,i,j);
                        podeSacrificar = 1;
                    }
                    
                        if(xDirecao != 0) {
                            xSacrificio -= (xDirecao/(abs(xDirecao)));
                        }
                        if(yDirecao != 0) {
                            ySacrificio -= (yDirecao/(abs(yDirecao)));
                        }
                         
                    }
                    
                }
            }
        }
        if(podeSacrificar == 1) {
            return TAB_CondRetSeSacrificou;
        }
        return TAB_CondRetCheckMate;
    }
    
    
}/* Fim funÁ„o: TAB  -Verifica Check Mate*/

/***************************************************************************
 *
 *  FunÁ„o: TAB  &Verifica Acha Peca Check
 *  ****/

TAB_tpCondRet TAB_AchaPecaCheck(LIS_tppLista pLista,char cor,char id,int *x,int *y,int xRei,int yRei) {
    int i,j,qtdMov,qtdUnitarios,retVerifica;
    pCasa aux;
    Peca *ameacante;
    char corObtida,idObtido;
    for (i=0; i<8; i++) {
        for (j=0; j<8; j++) {
            TAB_ObterPeca(pLista, i, j,&corObtida ,&idObtido);
            TAB_Converte(pLista, i, j, &aux);
            ameacante = (Peca *) aux->elemento;
            PEC_RetornaQtd_Mov(ameacante, &qtdMov);
            qtdUnitarios = contaUnitarios(ameacante, qtdMov);
            if (corObtida == cor && idObtido == id) {
                retVerifica = verificaMovimento(i, j, ameacante, xRei, yRei, pLista, corObtida, qtdUnitarios);
                if (retVerifica == TAB_CondRetComeu) {
                    *x = i;
                    *y = j;
                }
            }
        }
    }
    return 0;
}/* Fim funÁ„o: TAB  -Verifica Acha Peca Check*/




/********** Fim do mÛdulo de implementaÁ„o: TAB  Tabuleiro **********/
