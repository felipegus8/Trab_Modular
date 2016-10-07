#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*
*  $ED Descrição do módulo
*     Implementa listas genéricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogenea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contÈm.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluÌdo
*        È realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necess·rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação pode ser NULL .
*        Caso o elemento da lista seja a ˙nica ‚ncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
*  Autores: Felipe Viberti,Luis Claudio e Victor Nogueira
*
*  $HA Histórico de evolução:
*     Versão  Autores                                           Data          Observações
*     1       Felipe Viberti,Luis Claudio e Victor Nogueira   27/set/2016  início desenvolvimento
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referencia para uma lista */

typedef struct LIS_tagLista *  LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS CondiÁıes de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funÁıes da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista não contÈm elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

         LIS_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar um elemento de lista */

   } LIS_tpCondRet ;


/***********************************************************************/


/***********************************************************************
*  $FC Função: LIS  &Criar lista
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Há uma string de até 4 caracteres que serve como identificador da lista.
*
*  $EP Parâmetros
	lista - ponteiro para a lista que será criada.
	idLista - String contendo o id da lista que será criada.
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro ser· utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornar· NULL.
*     Não ser dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

    LIS_tpCondRet LIS_CriarLista(LIS_tppLista *lista,char idLista[4],void( * ExcluirValor ) ( void * pDado ));
             
             
             
/***********************************************************************

*  $FC Função: LIS  &Obter Id Lista
*
*  $ED Descrição da função
*     Obtem idLista de uma lista duplamente encadeada 
*
*  $EP Parâmetros
*     pLista = ponteiro para a lista de onde deve ser obtido o valor de IdLista
*     IdLista = string identificador da lista
*
*  $FV Valor retornado
*     Se executou corretamente retorna OK.
*     Se ocorreu algum erro, por exemplo pLista não existe,
*     a função retorna NaoAchou.


***********************************************************************/

  LIS_tpCondRet LIS_ObterIdLista(LIS_tppLista lista, char idLista[4]);

/************************************************************************

*  $FC Função: LIS  &Inserir nó na lista
*
*  $ED Descrição da função
*     Insere elemento do tipo char na posição seguinte à corrente
*
*  $EP Parâmetros
*     pLista = ponteiro para a lista onde deverá ser inserido o elemento
      elemento = ponteiro para void que será inserido no nó seguinte ao nó corrente
*
*  $FV Valor retornado
*     Retorna OK, caso a inserção tenha sido bem sucedida.
*     Já, em caso de, retorna FaltouMemoria.

***********************************************************************/


   LIS_tpCondRet LIS_InserirNo(LIS_tppLista lista, void *elemento);
   
/************************************************************************

*  $FC Função: LIS  &Obter nó na lista
*
*  $ED Descrição da função
*     Obtem valor contido no nó corrente e o copia para s
*
*  $EP Parâmetros
*     pLista = ponteiro para a lista de onde deverá ser obtido o elemento
      referencia = ponteiro  para  void onde será copiado o valor contido no elemento corrente.
*
*  $FV Valor retornado
*     Retorna OK caso tenha obtido corretamente.
*     Já,se a lista estiver vazia, retorna ListaVazia
   
************************************************************************/   
   
  LIS_tpCondRet LIS_ObterNo(LIS_tppLista lista, void **referencia);

/************************************************************************

*  $FC Função: LIS  &Excluir nó corrente
*
*  $ED Descrição da função
*     exclui o nó corrente da lista
*
*  $EP Parâmetros
*     pLista = ponteiro para a lista de onde deverá ser excluido o nó corrente
    
*
*  $FV Valor retornado
*     Retorna OK caso tenha excluido corretamente.
*     Já,se a lista estiver vazia, não faz nada e retorna ListaVazia
   
************************************************************************/   

LIS_tpCondRet LIS_ExcluirNoCorrente(LIS_tppLista lista);

/************************************************************************

*  $FC Função: LIS  &Ir para o próximo nó
*
*  $ED Descrição da função
*     Avança o elemento corrente um elemento a frente
*
*  $EP Parâmetros
*     pLista = ponteiro para a lista de onde deverá ser excluido o nó corrente
    
*
*  $FV Valor retornado
*     Retorna OK caso a movimentação tenha sido bem sucedida
*     Retorna ListaVazia, caso a lista esteja vazia.
*     Retorna FimLista, caso o nó corrente seja o ultimo
   
************************************************************************/   

LIS_tpCondRet LIS_IrProx(LIS_tppLista lista);

/************************************************************************

*  $FC Função: LIS  &Ir para o nó anterior
*
*  $ED Descrição da função
*     Retorna o elemento corrente um elemento para trás
*
*  $EP Parâmetros
*     pLista = ponteiro para a lista de onde deverá ser excluido o nó corrente
    
*
*  $FV Valor retornado
*     Retorna OK caso a movimentação tenha sido bem sucedida
*     Retorna ListaVazia, caso a lista esteja vazia.
*     Retorna FimLista, caso o nó corrente seja o primeiro
   
************************************************************************/   

LIS_tpCondRet LIS_IrAnt(LIS_tppLista lista);

/************************************************************************

*  $FC Função: LIS  &Alterar nó corrente
*
*  $ED Descrição da função
*     Altera o valor do elemento corrente para o valor da string passada como parâmetro
*
*  $EP Parâmetros
*     pLista = ponteiro para a lista de onde deverá ser excluido o nó corrente
*     referencia = ponteiro para void contendo o valor o qual substituirá o valor do elemento corrente 
*
*  $FV Valor retornado
*     Retorna OK caso a alteração tenha sido bem sucedida
*     Retorna ListaVazia, caso a lista esteja vazia.
*     Retorna FimLista, caso a lista não exista
   
************************************************************************/  

LIS_tpCondRet LIS_AlterarNoCorrente(LIS_tppLista lista, void *referencia);

/************************************************************************

*  $FC Função: LIS  &Destroi lista
*
*  $ED Descrição da função
*     Destroi a cabeça da lista fornecida como parâmetro e todos os nós existentes na lista.
*
*  $EP Parâmetros
*     pLista = ponteiro para a lista que deverá ser excluida
*
*  $FV Valor retornado
*     Retorna OK caso a destruição tenha sido bem sucedida
*     Retorna FimLista, caso a lista não exista

************************************************************************/ 

   LIS_tpCondRet LIS_DestroiLista(LIS_tppLista lista);

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#endif
