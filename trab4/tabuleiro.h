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

        TAB_CondRetComeu,
    

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

         TAB_CondRetCorErrada,
	      /* cor obtida está errado */
         TAB_CondRetIdErrado,
             /* id obtido está errado */
        TAB_CondRetCheck,
            /* rei está em cheque*/
        TAB_CondRetNoCheck,
            /* rei não está em cheque*/
         TAB_CondRetEscapouSeMovimentando,
             /* rei escapou do cheque se movimentando */
    
        TAB_CondRetCheckMate,
            /* rei está em cheque mate */
        TAB_CondRetCoordenadaNExiste,
            /* coordenada inserida não existe */
        TAB_CondRetSeSacrificou,
            /* peça se sacrificou para salvar o rei */
        TAB_CondRetComeuParaSalvar,
            /*peca comeu peça que estava colocando rei em cheque */
        #ifdef _DEBUG
            TAB_CondRetRetonoTamanhoPecaFalhou,
            /* retorno da função que retorna o tamanho da peça foi nulo */
            TAB_CondRetRetornoTamanhoListaFalhou
            /* retorno da função que retorna o tamanho da lista foi nulo */
        #endif
   } TAB_tpCondRet ;



/* Tipo Casa */
typedef struct casa* pCasa;
/*Tipo ponteiro para tabuleiro*/
typedef struct TAG_tabuleiro * ptTabuleiro;

/***********************************************************************

*  $FC Função: TAB &Cria Tabuleiro
*
*  $ED Descrição da função
*     Aloca dinamicamente um tabuleiro.O tamanho da matriz tabuleiro dependerá dos outros parâmetros passados para a função.
*
*  $EP Parâmetros
*    tabuleiro = Ponteiro para onde se quer alocar a matriz.
*
*  $FV Valor retornado
*    Se executou corretamente retona Ok.
*    Se houve algum problema por falta de memória retorna Faltou Memória.

***********************************************************************/
TAB_tpCondRet TAB_CriaTabuleiro(ptTabuleiro *tabu);


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
 //TAB_tpCondRet TAB_InserirPeca(ptTabuleiro tabuleiro,int x, int yi,char cor,char id);
TAB_tpCondRet TAB_InserirPeca(LIS_tppLista pLista,int x, int yi,char cor,char id);

TAB_tpCondRet TAB_CriaLL(LIS_tppLista *pLista);

TAB_tpCondRet TAB_Converte(LIS_tppLista pLista,int x,int y,pCasa *casa);


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
//TAB_tpCondRet TAB_MoverPeca(ptTabuleiro tabu,int xo,int yi,int xd,int yi2);

TAB_tpCondRet TAB_MoverPeca(LIS_tppLista pLista,int xo,int yi,int xd,int yi2);

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

 //TAB_tpCondRet TAB_RetirarPeca(ptTabuleiro tabu,int x,int y);

TAB_tpCondRet TAB_RetirarPeca(LIS_tppLista pLista,int x,int y);


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

//TAB_tpCondRet TAB_ObterPeca(ptTabuleiro tabu,int x, int y, char *cor, char *id);

TAB_tpCondRet TAB_ObterPeca(LIS_tppLista pLista,int x, int y, char *cor, char *id);

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

// TAB_tpCondRet TAB_ObterListaAmeacantes(ptTabuleiro tabu,int x, int y,LIS_tppLista *listaAmeacantes); //a ser editada

 TAB_tpCondRet TAB_ObterListaAmeacantes(LIS_tppLista pLista,int x, int y,LIS_tppLista *listaAmeacantes); //a ser editada



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
 TAB_tpCondRet TAB_ObterListaAmeacados(LIS_tppLista pLista,int x, int y,LIS_tppLista *listaAmeacados);  //a ser editada


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
TAB_tpCondRet TAB_DestruirTabuleiro(LIS_tppLista pLista);

/***********************************************************************
 
 *  $FC Função: TAB &Verifica Check
 *
 *  $ED Descrição da função
 *      Verifica se o rei que se situa na posição (xRei,yRei) está em cheque.
 *
 *  $EP Parâmetros
 *    tabu = Ponteiro para o tabuleiro que se quer verificar se o rei está em cheque.
 *    xRei= Coordenada X onde se situa o rei que se deseja verificar se está em cheque.
 *    yRei= Coordenada Y onde se situa o rei que se deseja verificar se está em cheque.
 *
 *  $FV Valor retornado
 *     Se o rei na posição (xRei, yRei) estiver em cheque retorna TAB_CondRetCheck.
 *     Se o rei que se encontra na posição (xRei, yRei) não estiver em cheque retorna TAB_CondRetNoCheck.
 
 ***********************************************************************/


TAB_tpCondRet TAB_VerificaCheck(LIS_tppLista pLista,int xRei,int yRei);

/***********************************************************************
 
 *  $FC Função: TAB &Verifica Check Mate
 *
 *  $ED Descrição da função
 *      Verifica se o rei que se situa na posição (xRei,yRei) está em cheque mate pela peça que o colocou em cheque.
 *
 *  $EP Parâmetros
 *    tabu = Ponteiro para o tabuleiro que se quer verificar se o rei está em cheque mate.
 *    xRei = Coordenada X onde se situa o rei que se deseja verificar se está em cheque mate.
 *    yRei = Coordenada Y onde se situa o rei que se deseja verificar se está em cheque mate.
 *    xAmeacante = Coordenada X onde se situa o rei a peça que está colocando o rei em cheque mate.
 *    yAmeacante = Coordenada Y onde se situa o rei a peça que está colocando o rei em cheque mate.
 *
 *  $FV Valor retornado
 *     Se o rei na posição (xRei, yRei) estiver em cheque mate pela peça que o colocou em cheque retorna TAB_CondRetCheckMate.
 *     Se o rei na posição (xRei, yRei) não estiver em cheque mate pela peça que o colocou em cheque, pois ele pode se mover retorna TAB_CondRetNoCheckMate.
 *     Se o rei na posição (xRei, yRei) não estiver em cheque mate pela peça que o colocou em cheque, pois alguma peça pode comer a peça que o deixa em cheque e, se rei não puder se movimentar, retorna TAB_CondRetComeuParaSalvar.
  *     Se o rei na posição (xRei, yRei) não puder se mover para sair do cheque,se nenhuma peça puder comer a peça que colocou o rei em cheque, se alguma peça da cor do rei possa entrar no caminho do movimento que a peça que coloca o rei em cheque faria para o capturar, retorna TAB_CondRetSeSacrificou
 
 ***********************************************************************/


//TAB_tpCondRet TAB_VerificaCheckMate(ptTabuleiro tabu,int xRei,int yRei,int xAmeacante,int yAmeacante);

TAB_tpCondRet TAB_VerificaCheckMate(LIS_tppLista pLista,int xRei,int yRei,int xAmeacante,int yAmeacante);

/***********************************************************************
 
 *  $FC Função: TAB &Acha Peca Check
 *
 *  $ED Descrição da função
 *      Acha a posição da peça que colocou o rei em cheque(no caso achará primeira peça que está na lista ameacantes do rei).
 *
 *  $EP Parâmetros
 *    tabu = Ponteiro para o tabuleiro onde se deseja encontrar a peça que colocou o rei que está na posição (xRei, yRei) em cheque.
 *    cor = Cor da peça que colocou o rei que está na posição (xRei, yRei) em cheque.
 *    id = Id da peça que colocou o rei em cheque.
 *    xAmeacante = Coordenada X que se deseja obter da peça que coloca o rei que está na posição (xRei, yRei) em cheque.
 *    yAmeacante = Coordenada Y que se deseja obter da peça que coloca o rei que está na posição (xRei, yRei) em cheque.
 *   xRei = Coordenada X do rei que está em cheque.
 *   yRei = Coordenada Y do rei que está em cheque.
 
 *  $FV Valor retornado
 *    Retorna TAB_CondRetOK
 
 ***********************************************************************/

//TAB_tpCondRet TAB_AchaPecaCheck(ptTabuleiro tabu,char cor,char id,int *xAmeacante,int *yAmeacante,int xRei,int yRei);

TAB_tpCondRet TAB_AchaPecaCheck(LIS_tppLista pLista,char cor,char id,int *xAmeacante,int *yAmeacante,int xRei,int yRei);

/***********************************************************************
 
 *  $FC Função: TAB &Verifica Movimento Rei
 *
 *  $ED Descrição da função
 *      Verifica se o movimento do rei que se encontra na posição (xRei,yRei) até a posição (xFim,yFim) é válido
 *
 *  $EP Parâmetros
 *    tabu = Ponteiro para o tabuleiro onde se deseja verifica se o movimento do rei na posição (xRei,yRei) até a posição (xFim,yFim) é válido
 *    xRei = Coordenada X onde se situa o rei que se deseja verificar se o movimento do rei na posição (xRei,yRei) até a posição (xFim,yFim) é válido.
 *    yRei = Coordenada Y onde se situa o rei que se deseja verificar se o movimento do rei na posição (xRei,yRei) até a posição (xFim,yFim) é válido.
 *    cor = Cor do rei
 *    xFim = Coordenada X da posição para onde o rei deseja se movimentar.
*     yFim = Coordenada Y da posição para onde o rei deseja se movimentar.
 
 
 *  $FV Valor retornado
 *    se o movimento proposto for válido e o rei não tiver comido alguma peça com esse movimento, Retorna TAB_CondRetOK
 *    se o movimento proposto for válido e o rei  tiver comido alguma peça com esse movimento, Retorna TAB_CondRetComeu
 *    se o movimento proposto for irregular, Retorna TAB_CondRetMovimentoIrregular.
 
 ***********************************************************************/

//TAB_tpCondRet TAB_VerificaMovimentoRei(ptTabuleiro tabu,int xRei, int yRei, char cor,int xFim,int yFim);

TAB_tpCondRet TAB_VerificaMovimentoRei(LIS_tppLista pLista,int xRei, int yRei, char cor,int xFim,int yFim);

/********** Fim do módulo de definição: TAB  Tabuleiro **********/
#endif
