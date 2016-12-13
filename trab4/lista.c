#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "lista.h"


typedef struct tagElemLista {
    
    void * pValor ;
    /* Ponteiro para o valor contido no elemento */
    
    struct tagElemLista * pAnt ;
    /* Ponteiro para o elemento predecessor */
    
    struct tagElemLista * pProx ;
    /* Ponteiro para o elemento sucessor */
    
#ifdef _DEBUG
    LIS_tppLista cabeca;
#endif
    
    
} tpElemLista ;


typedef struct LIS_tagLista {
    
    tpElemLista * pOrigemLista ;
    /* Ponteiro para a origem da lista */
    
    tpElemLista * pFimLista ;
    /* Ponteiro para o final da lista */
    
    tpElemLista * pElemCorr ;
    /* Ponteiro para o elemento corrente da lista */
    
    int numElem ;
    /* Número de elementos da lista */
    
    char *idLista;
    /*  String que identifica a lista */
    void ( * ExcluirValor ) ( void * pValor ) ;
    /* Ponteiro para a função de destruição do valor contido em um elemento */
    
#ifdef _DEBUG
    LIS_tpEspaco tipo;
#endif
    
    
} LIS_tpLista ;

/***** Protótipos das funções encapuladas no módulo *****/

static void LiberarElemento( LIS_tppLista   lista ,
                            tpElemLista  * pElem   ) ;

static tpElemLista * CriarElemento( LIS_tppLista lista ,
                                   void *       pValor  ) ;

static void LimparCabeca( LIS_tppLista lista );

//static void EsvaziarLista(LIS_tppLista lista);

/*****  Código das funções exportadas pelo módulo  *****/
/***************************************************************************
 *
 *  Função: LIS  &Criar lista
 *  ****/
//AE:A lista não possui nenhum elemento e deve receber ponteiro LIS_tppLista e um ponteiro com a id
LIS_tpCondRet LIS_CriarLista(LIS_tppLista *lista,char *idLista,
                             void   ( * ExcluirValor ) ( void * pDado ),LIS_tpEspaco tipo)
{
    
    //LIS_tppLista * lista = NULL ;
    
	   LIS_tppLista listaCopia;
    
	   listaCopia = (LIS_tpLista *) malloc(sizeof(LIS_tpLista));
	   
    
    if ( listaCopia == NULL )
    {
        return LIS_CondRetFaltouMemoria ;
    } /* if */
    
#ifdef _DEBUG
    //CED_DefinirTipoEspaco(listaCopia,LIS_tpCabeca);
    listaCopia->tipo = tipo;
#endif
    
    
    
    LimparCabeca(listaCopia );
    
    listaCopia->idLista = (char *) malloc(strlen(idLista) + 1);
	   
    strcpy(listaCopia->idLista,idLista);
	   
    listaCopia->ExcluirValor = ExcluirValor;
    
    
    
    *lista = listaCopia;
    
    return LIS_CondRetOK;
    
} /* Fim função: LIS  &Criar lista */
//AS: Uma lista foi criada com id e cabeça

/***************************************************************************
 *
 *  Função: LIS  &Obter Id Lista
 *  ****/

LIS_tpCondRet LIS_ObterIdLista(LIS_tppLista lista, char idLista[4]) {
    if(lista == NULL) {
        return LIS_CondRetNaoAchou;
    }
    strcpy(idLista,lista->idLista);
    return LIS_CondRetOK;
}

/***************************************************************************
 *
 *  Função: LIS  &Inserir nó na lista
 *  ****/
//AE: Recebe uma LIS_tppLista lista já criada e um ponteiro para um valor generico
LIS_tpCondRet LIS_InserirNo(LIS_tppLista pLista, void *pValor) {
    tpElemLista * pElem ;
    
#ifdef _DEBUG
    assert( pLista != NULL ) ;
#endif
    
    /* Criar elemento a inerir após */
    
    pElem = CriarElemento( pLista , pValor ) ;
    if ( pElem == NULL )
    {
        return LIS_CondRetFaltouMemoria ;
    } /* if */
    
    /* Encadear o elemento após o elemento */
    
    if ( pLista->pElemCorr == NULL )
    {
        pLista->pOrigemLista = pElem ;
        pLista->pFimLista = pElem ;
    } else
    {
        if ( pLista->pElemCorr->pProx != NULL )
        {
            pElem->pProx  = pLista->pElemCorr->pProx ;
            pLista->pElemCorr->pProx->pAnt = pElem ;
        } else
        {
            pLista->pFimLista = pElem ;
        } /* if */
        
        pElem->pAnt = pLista->pElemCorr ;
        pLista->pElemCorr->pProx = pElem ;
        
    } /* if */
    
    pLista->pElemCorr = pElem ;
    
#ifdef _DEBUG
    pElem->cabeca = pLista;
#endif
    
    
    
    return LIS_CondRetOK ;
    
} /* Fim função: LIS  &Inserir elemento após */
//AS:Um elemento foi inserido na lista que é apontado pelo ponteiro corrente

/***************************************************************************
 *
 *  Função: LIS  &Obter nó na Lista
 *  ****/

//AE: Recebe uma LIS_tppLista lista já criada e ponteiro que aponta para o ponteiro void de um valor
LIS_tpCondRet LIS_ObterNo(LIS_tppLista lista, void **referencia) {
#ifdef _DEBUG
    assert( lista != NULL ) ;
#endif
    if(lista->pElemCorr == NULL) {
        *referencia = NULL;
        return LIS_CondRetListaVazia;
    }
    
    *referencia = lista->pElemCorr->pValor;
    return LIS_CondRetOK;
}
//AS: A função fara que um ponteiro referencia aponte para um valor da lista
/***************************************************************************
 
 *
 *  Função: LIS  &Ir para o elemento inicial
 *  ****/

void IrInicioLista( LIS_tppLista pLista )
{
    
#ifdef _DEBUG
    assert( pLista != NULL ) ;
#endif
    
    pLista->pElemCorr = pLista->pOrigemLista ;
    
} /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
 
 *
 *  Função: LIS  &Excluir nó corrente
 *  ****/

//AE:Recebe uma LIS_tppLista lista já criada
LIS_tpCondRet LIS_ExcluirNoCorrente(LIS_tppLista lista) {
    
    tpElemLista * pElem;
    
#ifdef _DEBUG
    assert(lista != NULL ) ;
#endif
    pElem = lista->pElemCorr;
    if(lista->pElemCorr == NULL) {
        return LIS_CondRetListaVazia;
    }
    /* Desencadeia esquerda */
    
    if ( pElem->pAnt != NULL )
    {
        pElem->pAnt->pProx   = pElem->pProx ;
        lista->pElemCorr    = pElem->pAnt ;
    } else {
        lista->pElemCorr    = pElem->pProx ;
        lista->pOrigemLista = lista->pElemCorr ;
    } /* if */
    /* Desencadeia direita */
    
    if ( pElem->pProx != NULL )
    {
        pElem->pProx->pAnt = pElem->pAnt ;
    } else
    {
        lista->pFimLista = pElem->pAnt ;
    } /* if */
    LiberarElemento( lista , pElem ) ;
    
    return LIS_CondRetOK;
    
}/* fim função: Lis &Excluir nó  */
//AS: O elemento apontado pelo nó corrente foi excluido e o corrente passa a ser o anterior ao excluido
/***************************************************************************
 *
 *  Função: LIS  &Ir para o próximo nó
 *  ****/
//AE:Recebe uma LIS_tppLista lista já criada
LIS_tpCondRet LIS_IrProx(LIS_tppLista pLista) {
    
    tpElemLista * pElem ;
    
#ifdef _DEBUG
    assert(pLista != NULL ) ;
#endif
    if ( pLista->pElemCorr == NULL )
    {
        
        return LIS_CondRetListaVazia ;
        
    } /* fim ativa: Tratar lista vazia */
    
    /* Tratar avançar para frente */
    
    
    
    pElem = pLista->pElemCorr ;
    
    pElem    = pElem->pProx ;
    
    if ( pElem != NULL )
    {
        pLista->pElemCorr = pElem ;
        return LIS_CondRetOK ;
    } /* if */
    pLista->pElemCorr = pLista->pFimLista ;
    return LIS_CondRetFimLista ;
    
}/* fim função: Lis &Ir para o próximo nó
  //AS: O corrente deve apontar agora para o o nó logo ao da frente recibido inicialmente na função
  /***************************************************************************
  *
  *  Função: LIS  &Ir para o nó anterior
  *  ****/
//AE:Recebe uma LIS_tppLista lista já criada
LIS_tpCondRet LIS_IrAnt(LIS_tppLista pLista) {
    
    tpElemLista * pElem ;
#ifdef _DEBUG
    assert(pLista != NULL ) ;
#endif
    
    pElem = pLista->pElemCorr ;
    printf("%d\n",pElem);
    pElem = pElem->pAnt ;
    
    if ( pElem != NULL )
    {
        pLista->pElemCorr = pElem ;
        return LIS_CondRetOK ;
    } /* if */
    
    pLista->pElemCorr = pLista->pOrigemLista ;
    return LIS_CondRetFimLista ;
}/* fim função: Lis &Ir para o nó anterior */
//AS: O corrente deve apontar agora para o o nó na posição anterior ao do recibido inicialmente na função
/***************************************************************************
 *
 *  Função: LIS  &Alterar nó corrente
 *  ****/
//AE: Recebe uma LIS_tppLista lista já criada e ponteiro void
LIS_tpCondRet LIS_AlterarNoCorrente(LIS_tppLista lista, void *referencia) {
    
    if(lista->pElemCorr == NULL) {
        return LIS_CondRetListaVazia;
    }
    
    //strcpy(lista->pElemCorr->pValor, novo);
    lista->pElemCorr->pValor = referencia;
    return LIS_CondRetOK;
}/* fim função: Lis &Alterar nó corrente */
//AS: O nó corrente passara a apontar para o ponteiro recebido como paramentro
/***************************************************************************
 *
 //AE:Recebe uma LIS_tppLista lista já criada
 *  Função: LIS  &Destruir lista
 *  ****/
LIS_tpCondRet LIS_DestroiLista(LIS_tppLista lista) {
    
    if(lista == NULL) {
        return LIS_CondRetFimLista;
    }
    
    EsvaziarLista( lista );
    
    free( lista );
    return LIS_CondRetOK;
} /* Fim funÁ„o: LIS  &Destruir lista */
//AS: A lista criada deverá excluir todos os nós delas e ainda libera da memória a propria lista recebida como parametro
/***************************************************************************
 
 
 /*****  Código das funções encapsuladas no módulo  *****/
/***********************************************************************
 *
 *  $FC Função: LIS  -Liberar elemento da lista
 *
 *  $ED Descrição da função
 *     Elimina os espaços apontados pelo valor do elemento e o
 *     próprio elemento.
 *
 ***********************************************************************/
//AE:Recebe uma LIS_tppLista lista já criada
void LiberarElemento( LIS_tppLista   lista ,
                     tpElemLista  * pElem   )
{
    
    if ( ( lista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
    {
        lista->ExcluirValor( pElem->pValor ) ;
    } /* if */
    
    free( pElem ) ;
    
    lista->numElem-- ;
    
} /* Fim função: LIS  -Liberar elemento da lista */
//AS: Elimina da lista o conteudo apontado pelo elemento recebido e o proprio elemento

/***********************************************************************
 *
 *  $FC Função: LIS  -Criar o elemento
 *
 ***********************************************************************/
//AE:AE:Recebe uma LIS_tppLista lista já criada e ponteiro apontando para um valor
tpElemLista * CriarElemento( LIS_tppLista lista ,
                            void *       pValor  )
{
    
    tpElemLista * pElem ;
    
    pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
    if ( pElem == NULL )
    {
        return NULL ;
    } /* if */
    
#ifdef _DEBUG
    //CED_DefinirTipoEspaco(listaCopia,LIS_tpElemLista);
#endif
    
    
    
    pElem->pValor = pValor ;
    pElem->pAnt   = NULL  ;
    pElem->pProx  = NULL  ;
    
    lista->numElem ++ ;
    
    return pElem ;
    
} /* Fim função: LIS  -Criar o elemento */
//AS: Na lista recebida foi adiciona um ponteiro para o valor

/***********************************************************************
 *
 *  $FC Função: LIS  -Limpar a cabeça da lista
 *
 ***********************************************************************/
//AE:Recebe uma LIS_tppLista lista já criada
void LimparCabeca( LIS_tppLista lista )
{
    
    lista->pOrigemLista = NULL ;
    lista->pFimLista = NULL ;
    lista->pElemCorr = NULL ;
    lista->numElem   = 0 ;
    
} /* Fim função: LIS  -Limpar a cabeça da lista */
//AS: A cabeça da lista será limpada de seus valores originais
/***************************************************************************
 *
 *  Função: LIS  &Esvaziar lista
 *  ****/
//AE:Recebe uma LIS_tppLista lista já criada
void EsvaziarLista( LIS_tppLista lista ) {
    
    tpElemLista * pElem ;
    tpElemLista * pProx ;
    
#ifdef _DEBUG
    assert( lista != NULL ) ;
#endif
    
    pElem = lista->pOrigemLista;

    while ( pElem != NULL )
    {
        pProx = pElem->pProx ;
        LiberarElemento(lista , pElem ) ;
        pElem = pProx ;
    } /* while */
    
    LimparCabeca( lista ) ;
    
} /* Fim função: LIS  &Esvaziar lista */
//AS: A lista recebida foi desvinculada de todos seus nó e cabeça

LIS_tpCondRet LIS_RetornaNumElementos(LIS_tppLista lista,int *numElem) {
    if(lista == NULL) {
        return LIS_CondRetListaNExiste;
    }
    *numElem = lista->numElem;
    return LIS_CondRetOK;
}



#ifdef _DEBUG


LIS_tpCondRet LIS_insereTipo(LIS_tppLista pLista,LIS_tpEspaco tipo) {
    if(pLista == NULL) {
        return LIS_CondRetListaNExiste;
    }
    pLista->tipo = tipo;
    
    return LIS_CondRetOK;
}





LIS_tpCondRet LIS_DeturpaAtribuiNullOrigem(LIS_tppLista pLista) {
    if(pLista == NULL) {
        return LIS_CondRetListaNExiste;
    }
    pLista->pOrigemLista = NULL;
    return LIS_CondRetOK;
}

LIS_tpCondRet LIS_DeturpaAtribuiNullFim(LIS_tppLista pLista) {
    if(pLista == NULL) {
        return LIS_CondRetListaNExiste;
    }
    pLista->pFimLista = NULL;
    return LIS_CondRetOK;
}

LIS_tpCondRet LIS_DeturpaAtribuiNullValorNo(LIS_tppLista pLista) {
    if(pLista == NULL) {
        return LIS_CondRetListaNExiste;
    }
    if(pLista->pElemCorr == NULL) {
        return LIS_CondRetListaVazia;
    }
    pLista->pElemCorr->pValor = NULL;
    return LIS_CondRetOK;
}

LIS_tpCondRet LIS_DeturpaAtribuiNullSucessor(LIS_tppLista pLista) {
    if(pLista == NULL) {
        return LIS_CondRetListaNExiste;
    }
    if(pLista->pElemCorr == NULL) {
        return LIS_CondRetListaVazia;
    }
    pLista->pElemCorr->pProx = NULL;
    return LIS_CondRetOK;
}

LIS_tpCondRet LIS_DeturpaAtribuiNullAntecessor(LIS_tppLista pLista) {
    if(pLista == NULL) {
        return LIS_CondRetListaNExiste;
    }
    if(pLista->pElemCorr == NULL) {
        return LIS_CondRetListaVazia;
    }
    pLista->pElemCorr->pAnt = NULL;
    return LIS_CondRetOK;
}

LIS_tpCondRet LIS_DeturpaAtribuiLixoSucessor(LIS_tppLista pLista) {
    if(pLista == NULL) {
        return LIS_CondRetListaNExiste;
    }
    if(pLista->pElemCorr == NULL) {
        return LIS_CondRetListaVazia;
    }
    pLista->pElemCorr->pProx = 12;
    return LIS_CondRetOK;
}

LIS_tpCondRet LIS_DeturpaAtribuiLixoAntecessor(LIS_tppLista pLista) {
    if(pLista == NULL) {
        return LIS_CondRetListaNExiste;
    }
    if(pLista->pElemCorr == NULL) {
        return LIS_CondRetListaVazia;
    }
    pLista->pElemCorr->pAnt = 12;
    return LIS_CondRetOK;
}

LIS_tpCondRet LIS_DeturpaDesencadeiaSemFree(LIS_tppLista pLista) {
    tpElemLista * pElem;
    
    if(pLista == NULL) {
        return LIS_CondRetListaVazia;
    }

    pElem = pLista->pElemCorr;
    if(pLista->pElemCorr == NULL) {
        return LIS_CondRetListaVazia;
    }
    /* Desencadeia esquerda */
    
    if ( pElem->pAnt != NULL )
    {
        pElem->pAnt->pProx   = pElem->pProx ;
        pLista->pElemCorr    = pElem->pAnt ;
    } else {
        pLista->pElemCorr    = pElem->pProx ;
        pLista->pOrigemLista = pLista->pElemCorr ;
    } /* if */
    /* Desencadeia direita */
    
    if ( pElem->pProx != NULL )
    {
        pElem->pProx->pAnt = pElem->pAnt ;
    } else
    {
        pLista->pFimLista = pElem->pAnt ;
    } /* if */
    return LIS_CondRetOK;
}

LIS_tpCondRet LIS_DeturpaNosApontamIgual(LIS_tppLista pLista) {
    if(pLista == NULL) {
        return LIS_CondRetListaNExiste;
    }
    if(pLista->pElemCorr == NULL) {
        return LIS_CondRetListaVazia;
    }
    pLista->pElemCorr->pValor = pLista->pFimLista->pValor;
    return LIS_CondRetOK;
}

LIS_tpCondRet LIS_DeturpaTrocaNumElem(LIS_tppLista pLista) {
    if(pLista == NULL) {
        return LIS_CondRetListaNExiste;
    }
    if(pLista->pElemCorr == NULL) {
        return LIS_CondRetListaVazia;
    }
    pLista->numElem = 2;
    return LIS_CondRetOK;
}

LIS_tpCondRet LIS_DeturpaTrocaTipoLista(LIS_tppLista pLista,LIS_tpEspaco novoTipo) {
    if (pLista == NULL) {
        return LIS_CondRetListaNExiste;
    }
    pLista->tipo = novoTipo;
    return LIS_CondRetOK;
}


LIS_tpCondRet LIS_RetornaAntecessor(LIS_tppLista pLista,void **antecessor) {
    
    if(pLista == NULL) {
        return LIS_CondRetListaNExiste;
    }
    if(pLista->pElemCorr == NULL) {
        return LIS_CondRetListaVazia;
    }
    *antecessor = pLista->pElemCorr->pAnt;
    return LIS_CondRetOK;
}

LIS_tpCondRet LIS_RetornaSucessor(LIS_tppLista pLista,void **sucessor) {
    
    if(pLista == NULL) {
        return LIS_CondRetListaNExiste;
    }
    if(pLista->pElemCorr == NULL) {
        return LIS_CondRetListaVazia;
    }
    *sucessor = pLista->pElemCorr->pProx;
    return LIS_CondRetOK;
}

LIS_tpCondRet LIS_RetornaOrigemLista(LIS_tppLista pLista, void **pOrigem) {
    if(pLista == NULL) {
        return LIS_CondRetListaNExiste;
    }
    if(pLista->pElemCorr == NULL) {
        return LIS_CondRetListaVazia;
    }
    *pOrigem = pLista->pOrigemLista;
    return LIS_CondRetOK;
}

LIS_tpCondRet LIS_RetornaFimLista(LIS_tppLista pLista, void **pFinal) {
    if(pLista == NULL) {
        return LIS_CondRetListaNExiste;
    }
    if(pLista->pElemCorr == NULL) {
        return LIS_CondRetListaVazia;
    }
    *pFinal = pLista->pFimLista;
    return LIS_CondRetOK;
}

LIS_tpCondRet LIS_RetornaAnteriorDoProximo(LIS_tppLista pLista,void **antDoProx) {
	if(pLista == NULL) {
        return LIS_CondRetListaNExiste;
    }
    if(pLista->pElemCorr == NULL) {
        *antDoProx = NULL;
        return LIS_CondRetListaVazia;
    }
    if(pLista->pElemCorr->pProx != NULL) {
        if(pLista->pElemCorr->pProx->pAnt != NULL && pLista->pElemCorr->pProx->pAnt != 12) {
            printf("prox: %x\n",pLista->pElemCorr->pProx->pAnt);
            *antDoProx = pLista->pElemCorr->pProx->pAnt->pValor;
        }
    }
	return LIS_CondRetOK;
}

LIS_tpCondRet LIS_RetornaProximoDoAnterior(LIS_tppLista pLista,void **proxDoAnt) {
	if(pLista == NULL) {
        return LIS_CondRetListaNExiste;
    }
    if(pLista->pElemCorr == NULL) {
        return LIS_CondRetListaVazia;
    }
    if(pLista->pElemCorr->pAnt != NULL) {
        if(pLista->pElemCorr->pAnt->pProx != NULL) {
            *proxDoAnt = pLista->pElemCorr->pAnt->pProx->pValor;
        }
    }
	return LIS_CondRetOK;
}

LIS_tpEspaco LIS_RetornaTipoEspaco(LIS_tppLista pLista) {
    if(pLista == NULL) {
        return LIS_CondRetListaNExiste;
    }
	return pLista->tipo;
}

#endif


/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/
