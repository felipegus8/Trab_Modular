#if ! defined( Tabuleiro_ )
#define Tabuleiro_

/***************************************************************************
*
*  $MCD Módulo de definição: TAB  Tabuleiro
*
*  Arquivo gerado:              Tabuleiro.h
*  Letras identificadoras:      TAB
*
*
*  $ED Descrição do módulo
*     Implementa um tabuleiro representada por uma matriz 8*8 da struct casa.
*     Cada casa do tabuleiro contem uma lista para as peças que ameaçam aquela casa,outra para as peças que aquela casa ameaça,além do próprio elemento contido na casa.
* 
*  Autores: Felipe Viberti,Luis Claudio e Victor Nogueira
*
*  $HA Histórico de evolução:
*     Versão  Autores                                           Data          Observações
*     1       Felipe Viberti,Luis Claudio e Victor Nogueira   27/set/2016  início desenvolvimento
*
***************************************************************************/

#include "lista.h"
#include "peca.h"
/***********************************************************************
*
*  $TC Tipo de dados: TAB Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do Tabuleiro.
*
***********************************************************************/
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



/* Tipo Casa */
typedef struct casa Casa;

typedef struct tabuleiro * ptTabuleiro;

/***********************************************************************

*  $FC Função: TAB &Cria Tabuleiro
*
*  $ED Descrição da função
*     Aloca dinamicamente um tabuleiro.O tamanho da matriz tabuleiro dependerá dos outros parâmetros passados para a função.
*
*  $EP Parâmetros
*    tabuleiro = Ponteiro para onde se quer alocar a matriz.
*    TamLinhas - Quantidade de linhas que a matriz tabuleiro vai ter.
*    TamColunas - Quantidade de colunas que a matriz tabuleiro vai ter.
*
*  $FV Valor retornado
*    Se executou corretamente retona Ok.
*    Se houve algum problema por falta de memória retorna Faltou Memória.

***********************************************************************/
TAB_tpCondRet TAB_CriaTabuleiro(Casa *tabuleiro,int TamLinhas, int TamColunas);


/***********************************************************************

*  $FC Função: TAB &Inserir Peca
*
*  $ED Descrição da função
*     Insere uma Peça no Tabuleiro.
*     A função cria essa peça chamando a função do módulo Peça de criarPeca.
*     Além disso ela também atribui a essa peça seu movimento,novamente chamando funções do módulo peça.
*     Tem que receber um tabuleiro já alocado dinamicamente,além de um x e y indicando a posição que a peça será inserida nesse tabuleiro.
*
*  $EP Parâmetros
*    tabuleiro = Ponteiro para o tabuleiro que se quer inserir a peça.
*    x = Coordenada x de onde a peça será inserida no Tabuleiro.
*    yi = Coordenada y de onde a peça será inserida no Tabuleiro.
*    cor = cor da Peça que se quer inserir
*    id = id da Peça que se quer inserir
*
*  $FV Valor retornado
*     Se executou corretamente retona Ok.
*     Se houve algum problema por falta de memória retorna Faltou Memória.
*     Se alguma das coordenadas passadas como parâmetro estiver fora do intervalo de tamanho do tabuleiro retorna CoordenadaNExiste.

***********************************************************************/
TAB_tpCondRet TAB_InserirPeca(Casa *tabuleiro,int x, int yi,char cor,char id);



/***********************************************************************

*  $FC Função: TAB &Mover Peca
*
*  $ED Descrição da função
*     Move uma peça dentro do tabuleiro.A função recebe um tabuleiro já alocado dinamicamente.
*     Além disso recebe as coordenadas x e y de onde a peça está no tabuleiro para poder localizá-la.
*     Essa função também verifica se o Movimento da Peça em questão é válido.
*
*  $EP Parâmetros
*    tabuleiro = Ponteiro para o tabuleiro que se quer mover a peça.
*    xo = Coordenada x da posição atual da peça no tabuleiro.
*    yo = Coordenada y da posição atual da peça no tabuleiro.
*    xd = Coordenada x para onde se quer mover a peça no tabuleiro..
*    yd = Coordenada y para onde se quer mover a peça no tabuleiro.
*
*  $FV Valor retornado
*    Se executou corretamente retona Ok.
*    Se houve algum problema por falta de memória retorna Faltou Memória.
*    Se alguma das coordenadas passadas como parâmetro estiver fora do intervalo de tamanho do tabuleiro retorna CoordenadaNExiste.
*    Se a peça em questão não está no tabuleiro retorna Não Achou Peça.
*    Se a peça em questão não pode realizar aquele movimento retorna Movimento Irregular.

***********************************************************************/
 TAB_tpCondRet TAB_MoverPeca(Casa *tabuleiro,int xo,int yi,int xd,int yi2);


/***********************************************************************

*  $FC Função: TAB &Retirar Peca
*
*  $ED Descrição da função
*     Retira do tabuleiro uma peça.
*     A peça a ser retirada é conhecida pelas coordenadas x e y passadas para a função.
*     A função recebe um tabuleiro já alocado dinamicamente e que já deveria conter pelo menos uma peça.
*
*  $EP Parâmetros
*    tabuleiro = Ponteiro para o tabuleiro que se quer retirar a peça.
*    x =  Coordenada x da posição atual da peça  que se quer retirar no tabuleiro.
*    y =   Coordenada y da posição atual da peça que se quer retirar no tabuleiro.
*
*  $FV Valor retornado
*     Se executou corretamente retona Ok.
*     Se alguma das coordenadas passadas como parâmetro estiver fora do intervalo de tamanho do tabuleiro retorna CoordenadaNExiste.
*     Se a casa do tabuleiro não contiver nenhuma peça retorna Casa Vazia. 

***********************************************************************/

 TAB_tpCondRet TAB_RetirarPeca(Casa *tabuleiro,int x,int yi);


/***********************************************************************

*  $FC Função: TAB &Obter Peca
*
*  
*  $ED Descrição da função
*     Retorna por referencia a cor e o id da peça que está na posição(x e y) do tabuleiro,passada como parâmetro.
*
*  $EP Parâmetros
*    tabuleiro = Ponteiro para o tabuleiro que se quer obter a peça.
*    x = Coordenada x da posição atual da peça no tabuleiro.
*    y = Coordenada y da posição atual da peça no tabuleiro.
*    cor = cor da Peca que se quer obter
*    id = id da Peça que se quer obter
*
*  $FV Valor retornado
*     Se executou corretamente retona Ok.
*     Se alguma das coordenadas passadas como parâmetro estiver fora do intervalo de tamanho do tabuleiro retorna CoordenadaNExiste.
*     Se a casa do tabuleiro não contiver nenhuma peça retorna Casa Vazia. 

***********************************************************************/

 TAB_tpCondRet TAB_ObterPeca(Casa *tabuleiro,int x, int y, char *cor, char *id);

/***********************************************************************

*  $FC Função: TAB &Obter Lista Ameacantes
*
*  $ED Descrição da função
*     Retorna por referencia a lista de peças que estão ameaçando uma determinada casa do Tabuleiro.
*      No momento estas listas estão vazias.
*      Essa função será alterada para o Trabalho 3.
*
*  $EP Parâmetros
*    tabuleiro = Ponteiro para o tabuleiro que se quer obter a lista de ameacantes da peça.
*    x= Coordenada x da posição da peça no tabuleiro.
*    y= Coordenada y da posição  da peça no tabuleiro.
*    listaAmeacantes = Ponteiro para  a lista de Ameacantes que será preenchida na função.
*
*  $FV Valor retornado
*     Se executou corretamente retona Ok.
*     Se alguma das coordenadas passadas como parâmetro estiver fora do intervalo de tamanho do tabuleiro retorna CoordenadaNExiste.
*     Se a lista não existir retorna ListaAmeacantesNaoExiste.

***********************************************************************/
TAB_tpCondRet TAB_ObterListaAmeacantes(Casa *tabuleiro,int x, int yi,LIS_tppLista *listaAmeacantes); //a ser editada



/***********************************************************************

*  $FC Função: TAB &Obter Lista Ameaçados
*
*  $ED Descrição da função
*      Retorna por referencia a lista de peças que estão sendo ameaçadas pela peça em uma determinada casa do Tabuleiro.
*      No momento estas listas estão vazias.
*      Essa função será alterada para o Trabalho 3.
*
*  $EP Parâmetros
*    tabuleiro = Ponteiro para o tabuleiro que se quer obter a lista de ameacados da peca.
*    x= Coordenada x da posição da peça no tabuleiro.
*    y= Coordenada y da posição  da peça no tabuleiro.
*    listaAmeacados = Ponteiro para  a lista de Ameacados que será preenchida na função.
*
*  $FV Valor retornado
*     Se executou corretamente retona Ok.
*     Se alguma das coordenadas passadas como parâmetro estiver fora do intervalo de tamanho do tabuleiro retorna CoordenadaNExiste.
*     Se a lista não existir retorna ListaAmeacadosNaoExiste.

***********************************************************************/
TAB_tpCondRet TAB_ObterListaAmeacados(Casa *tabuleiro,int x, int yi,LIS_tppLista *listaAmeacados); //a ser editada


/***********************************************************************

*  $FC Função: TAB &Destruir Tabuleiro
*
*  $ED Descrição da função
*     Destroi um tabuleiro passado como parâmetro.
*
*  $EP Parâmetros
*    tabuleiro = Ponteiro para o tabuleiro que se quer destruir.
*
*  $FV Valor retornado
*     Se executou corretamente retona Ok.

***********************************************************************/
TAB_tpCondRet TAB_DestruirTabuleiro(Casa *tabuleiro);



/********** Fim do módulo de definição: TAB  Tabuleiro **********/
#endif
