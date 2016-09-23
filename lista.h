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
*     Implementa listas genÈricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista È homogenea quanto ao tipo dos dados que armazena.
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
*        assegurar a liberaÁ„o de todos os espaÁos referÍnciados pelo
*        valor contido em um elemento.
*        Esta funÁ„o È chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necess·rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a funÁ„o de liberaÁ„o poder· ser NULL .
*        Caso o elemento da lista seja a ˙nica ‚ncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referencia para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS CondiÁıes de retorno
*
*
*  $ED DescriÁ„o do tipo
*     CondiÁıes de retorno das funÁıes da lista
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


*
*  $FC Função: LIS  &Criar lista
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possÌveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Há uma string de até 4 caracteres que serve como identificador da lista.
*
*  $EP Parâmetros
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

   LIS_tppLista LIS_CriarLista(
             void   ( * ExcluirValor ) ( void * pDado ) ) ;

