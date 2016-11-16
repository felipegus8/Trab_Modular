#if ! defined( Jogo_ )
#define Jogo_

/***************************************************************************
 *
 *  $MCD Módulo de definição: JOG  Jogo
 *
 *  Arquivo gerado:              Jogo.h
 *  Letras identificadoras:      JOG
 *
 *
 *  $ED DescriÁ„o do mÛdulo
 *     A implementação do módulo jogo diz respeito de como deve se estruturar o as regras  de execução do jogo
 *
 *  Autores: Felipe Viberti,Luis Claudio e Victor Nogueira
 *
*  $HA Histórico de evolução:
 *     Versão  Autores                                             Data          Observações
 *     1       Felipe Viberti,Luis Claudio e Victor Nogueira   10/Nov/2016  inÌcio desenvolvimento
 *
 ***************************************************************************/

/***********************************************************************
 *
 *  $TC Tipo de dados: JOG Condições de retorno
 *
 *
 *  $ED Descrição do tipo
 *     Condições de retorno das funções do Jogo.
 *
 ***********************************************************************/
typedef enum {
    
    JOG_CondRetOK ,
    /* Concluiu corretamente */
    
    JOG_CondRetFaltouMemoria ,
    /* Faltou memÛria ao tentar criar uma lista dentro da casa*/
    
    JOG_CondRetCorErrada,
	/* Tentou mexer a peça da cor errada */
    
    JOG_CondRetMovimentoIrregular,
    /* Tentou realizar um movimento irregular */ 
	
    JOG_CondRetComeu,
	/*Capturou uma peça adversária*/
    
    JOG_CondRetCheckMate,
    /*Rei está em Cheque Mate*/
	
    JOG_CondRetNoCheckMate,
	/*Rei nao está em Cheque Mate*/
    
    JOG_CondRetCheck,
	
    /*Rei está em Cheque*/
    JOG_CondRetTabuleiroNulo
	
	/*O tabuleiro é nulo*/
    
} JOG_tpCondRet ;

#include "Tabuleiro.h"

/* Tipo Ponteiro para jogador */
typedef struct jogador* ptJogador;
/* Tipo Ponteiro para juiz */
typedef struct juiz* ptJudge;


/***********************************************************************

*  $FC Função: JOG &Efetuar Jogada
*
*  $ED Descrição da função
*     Realiza uma jogada no tabuleiro de xadrez.A função verifica se a jogada que está sendo realizada é válida.Se não for não a realiza.A função também verifica se o rei está em cheque ou cheque Mate após a realização da jogada.
*
*  $EP Parâmetros
*    juiz = Ponteiro para o  juiz que está julgando a jogada.
*    corDaVez = Char que pode ser P ou B dependendo de quem for a vez.
*    posIniX = Posição inicial em X que a peça que se quer mover está.
*    posIniY = Posição inicial em Y que a peça que se quer mover está.
*    posFimX = Posição final em X para que a peça vai.
*    posFimY = Posição final em Y para que a peça vai.
*
*  $FV Valor retornado
*    Se executou corretamente retona OK.
*    Se está tentando mover uma peça da cor errada retorna CorErrada.
*    Se o movimento resultou em um cheque retorna Check.
*    Se o movimento resultou em um cheque Mate retorna CheckMate.
*    Se o movimento resultou na captura de uma peça retorna Comeu.

***********************************************************************/
JOG_tpCondRet JOG_EfetuarJogada(ptJudge j, char corDaVez,int posIniX,int posIniY,int posFimX,int posFimY);

/***********************************************************************

*  $FC Função: JOG &Cria Juiz
*
*  $ED Descrição da função
*     Aloca dinamicamente todos os elementos necessários para a criação da struct e cria a struct juiz em si.
*
*  $EP Parâmetros
*    juiz = Ponteiro para o  juiz que está sendo criado.
*    nomeJogadorA = String que contem o nome do primeiro jogador(que controla as peças brancas).
*    nomeJogadorB = String que contem o nome do segundo jogador(que controla as peças pretas).
*   
*
*  $FV Valor retornado
*    Se executou corretamente retona OK.
*    Se houve algum problema por falta de memória retorna Faltou Memória.
*    Se o tabuleiro for nulo retorna  TabuleiroNulo.
*    

***********************************************************************/

JOG_tpCondRet JOG_CriaJuiz(ptJudge *j,char nomeJogadorA[30], char nomeJogadorB[30]);

/***********************************************************************

*  $FC Função: JOG &Começar Jogo
*
*  $ED Descrição da função
*     Inicia o jogo inserindo todas as peças na posição inicial padrão de um jogo de xadrez.
*
*  $EP Parâmetros
*    juiz = Ponteiro para o  juiz que vai começar o jogo.
*    inserirPecas = Ponteiro para a função que insere as Peças no tabuleiro.
*   
*
*  $FV Valor retornado
*    Se executou corretamente retona OK.

***********************************************************************/
JOG_tpCondRet JOG_ComecarJogo(ptJudge j,void (*InserirPecas)(TAB_tpCondRet(*InserirNoTab)(ptTabuleiro,int x,int y,char cor,char id),ptJudge j));

/***********************************************************************

*  $FC Função: JOG &Assasinar Juiz
*
*  $ED Descrição da função
*     Destroi todos os elementos da struct Juiz recebida incluindo o tabuleiro.
*
*  $EP Parâmetros
*    juiz = Ponteiro para o  juiz que se quer destruir.
*   
*
*  $FV Valor retornado
*    Se executou corretamente retona OK.

***********************************************************************/
JOG_tpCondRet JOG_AssasinarJuiz(ptJudge j);

/***********************************************************************

*  $FC Função: JOG &Obtem Tabuleiro
*
*  $ED Descrição da função
*    Recebe um tabuleiro e o conecta com a struct juiz.
*
*  $EP Parâmetros
*    juiz = Ponteiro para o  juiz que se quer colocar o tabuleiro.
*    tabuleiro = Ponteiro para o tabuleiro que se quer associar ao juiz.
*   
*
*  $FV Valor retornado
*    Se executou corretamente retona OK.
*    Se o tabuleiro for nulo retorna  TabuleiroNulo.

***********************************************************************/
JOG_tpCondRet JOG_ObtemTabuleiro(ptJudge j,ptTabuleiro *tabu);

/***********************************************************************

*  $FC Função: JOG &Gera Matriz Tabuleiro
*
*  $ED Descrição da função
*    Monta uma matriz iniciada com as peças padrão.
*
*  $EP Parâmetros
*    juiz = Ponteiro para o  juiz que se quer colocar o tabuleiro.
*    matriz = Ponteiro para a matriz que se quer inicializar.
*   
*  $FV Valor retornado
*    Se executou corretamente retona OK.

***********************************************************************/
JOG_tpCondRet JOG_GeraMatrizTabuleiro(ptJudge j,char matriz[8][8][2]);

/***********************************************************************

*  $FC Função: JOG &Cria Jogador
*
*  $ED Descrição da função
*    Cria um jogador.
*
*  $EP Parâmetros
*    juiz = Ponteiro para o  juiz que se quer criar o jogador.
*    nome = Nome do jogador que quer se criar.
*    cor = Cor das peças controladas pelo jogador que se quer criar.
*   
*  $FV Valor retornado
*    Se executou corretamente retona OK.
*    Se houve algum problema por falta de memória retorna Faltou Memória.

***********************************************************************/
JOG_tpCondRet JOG_CriaJogador(ptJogador *j,char *nome,char cor);

/***********************************************************************

*  $FC Função: JOG &Retorno Nome Jogador 1
*
*  $ED Descrição da função
*    Retorno o nome do jogador 1.
*
*  $EP Parâmetros
*    juiz = Ponteiro para o  juiz que contem o jogador.
*    nome = Nome do jogador que se quer obter.
*   
*  $FV Valor retornado
*    Se executou corretamente retona OK.

***********************************************************************/
JOG_tpCondRet JOG_RetornoNomeJogador1(ptJudge j,char nome[30]);

/***********************************************************************

*  $FC Função: JOG &Retorno Nome Jogador 2
*
*  $ED Descrição da função
*    Retorno o nome do jogador 2.
*
*  $EP Parâmetros
*    juiz = Ponteiro para o  juiz que se quer colocar o tabuleiro.
*    nome = Nome do jogador que quer se criar.
*    cor = Cor das peças controladas pelo jogador que se quer criar.
*   
*  $FV Valor retornado
*    Se executou corretamente retona OK.

***********************************************************************/
JOG_tpCondRet JOG_RetornoNomeJogador2(ptJudge j,char nome[30]);

/***********************************************************************

*  $FC Função: JOG &Devolve Ameaçantes
*
*  $ED Descrição da função
*    Retorna a lista de ameaçantes de uma casa do Tabuleiro.
*
*  $EP Parâmetros
*    juiz = Ponteiro para o  juiz que se quer colocar o tabuleiro.
*    corAmeacantes = Ponteiro onde será colocada a cor das peças que ameaçam aquela casa.
*    idAmeacantes  = Ponteiro onde serão colocados os Id´s das peças ameaçando aquela casa.
*    qtdAmeacantes  = Quantidade de peças ameaçando a casa.
*    x = Coordenada X da casa em questão no tabuleiro.
*    y = Coordenada Y da casa em questão no tabuleiro.
* 
*
*   
*  $FV Valor retornado
*    Se executou corretamente retona OK.

***********************************************************************/
JOG_tpCondRet JOG_DevolveAmeacantes(ptJudge j,char *corAmeacantes,char *idAmeacantes,int *qtdAmeacantes,int x,int y);

/***********************************************************************

*  $FC Função: JOG &Devolve Ameaçados
*
*  $ED Descrição da função
*    Retorna a lista de ameaçados de uma casa do Tabuleiro.
*
*  $EP Parâmetros
*    juiz = Ponteiro para o  juiz que se quer colocar o tabuleiro.
*    corAmeacantes = Ponteiro onde será colocada a cor das peças que são ameaçadas pela peça naquela casa.
*    idAmeacantes  = Ponteiro onde serão colocados os Id´s das peças que são ameaçadas pela peça naquela casa.
*    qtdAmeacantes  = Quantidade de peças que são ameaçadas pela peça naquela casa.
*    x = Coordenada X da casa em questão no tabuleiro.
*    y = Coordenada Y da casa em questão no tabuleiro.
* 
*
*   
*  $FV Valor retornado
*    Se executou corretamente retona OK.

***********************************************************************/
JOG_tpCondRet JOG_DevolveAmeacados(ptJudge j,char *corAmeacados,char *idAmeacados,int *qtdAmeacados,int x,int y);

#endif
