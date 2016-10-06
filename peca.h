#include <stdio.h>
/***************************************************************************
*
*  $MCD Módulo de definição: PEC  Peca
*
*  Arquivo gerado:              Peca.h
*  Letras identificadoras:      PEC
*
*
*  $ED Descrição do módulo
*     Implementa peças a serem usadas em um jogo de xadrez.
		Essas peças podem ser as tradicionais de um jogo normal de xadrez ou podem ser criadas pelo usuário.
		No caso de serem criadas pelo usuário este fornecerá o movimento da peça.
		O movimento da peça é um vetor da forma (x,y) que fica armazenado na struct movimento.
		A estrutura da peça tem um ponteiro para o movimento da mesma,além de ter o Id da Peça e sua cor.
* 
*
***************************************************************************/
/***********************************************************************
*
*  $TC Tipo de dados: PEC Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da peça
*
***********************************************************************/
typedef enum {

         PEC_CondRetOK ,
               /* Concluiu corretamente */

         PEC_CondRetCasaVazia ,
               /* A casa não contém peças */

         PEC_CondRetCoordenadaNExiste ,
               /* coordenada inserida não existe */

         PEC_CondRetNaoAchouPeca ,
               /* Não encontrou a peca procurada */

         PEC_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar uma lista dentro da casa*/

   } PEC_tpCondRet ;

/* Tipo referencia para um movimento */
typedef struct movimento Movimento;
/* Tipo referencia para uma peça */
typedef struct peca Peca;




/***********************************************************************
*  $FC Função: PEC  &Criar Peça
*
*  $ED Descrição da função
*     Cria uma peça para um jogo de xadrez.
*     As peças podem ser as tradicionais ou novas inseridas pelo usuário do jogo.
*
*  $EP Parâmetros
*     pnovo  - ponteiro para a peça que será criado.
*     id - Caracter contendo o Id da peça a ser criada.
*		cor- Caracter contendo a cor da Peça.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a peça por referência.
*	O valor retornado pela função mesmo é OK caso tenha executado corretamente.
*     Este ponteiro deve ser utilizado pelas funções que manipulem esta peça.
*
*     Se ocorreu algum erro, por exemplo falta de memória a função retorna FaltouMemoria.
*  
*
***********************************************************************/
PEC_tpCondRet criaPeca(Peca **novo,char id,char cor);


/***********************************************************************
*  $FC Função: PEC  &EnsinaMovimentosPecasConhecidas
*
*  $ED Descrição da função
*  Atribui ao campo movimento da struct peça o movimento da mesma.
*  Nessa função são tratadas apenas as peças tradicionais de um jogo de xadrez.
*
*
*  $EP Parâmetros
*     pnovo  - ponteiro para a peça que terá seu movimento inserida.Esta peça já tem que estar criada e conter seu Id e sua cor.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a peça com o movimento da mesma dentro por referência.
*     O valor retornado pela função mesmo é OK caso tenha executado corretamente.	
*      Se ocorreu algum erro, por exemplo falta de memória a função retorna FaltouMemoria.
*
*  
*
***********************************************************************/
PEC_tpCondRet ensinaMovimentosPecasConhecidas(Peca **novo);

/***********************************************************************
*  $FC Função: PEC  &EnsinaMovimentosPecasDesconhecidas
*
*  $ED Descrição da função
*  Atribui ao campo movimento da struct peça o movimento da mesma.
*  Nessa função são tratadas apenas as peças inseridas pelo usuário,ou seja,aquelas que o movimento não é conhecido previamente.
*  O movimento das peças novas está no arquivo PecasNovas.txt que é lido pela função;
*
*
*  $EP Parâmetros
*     pnovo  - ponteiro para a peça que terá seu movimento inserida.Esta peça já tem que estar criada e conter seu Id e sua cor.
*	
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a peça com o movimento da mesma dentro por referência.
*     O valor retornado pela função mesmo é OK caso tenha executado corretamente.	
*      Se ocorreu algum erro, por exemplo falta de memória a função retorna FaltouMemoria.
*
*  
*
***********************************************************************/
PEC_tpCondRet ensinaMovimentosPecasDesconhecidas(Peca **novo);

/***********************************************************************
*  $FC Função: PEC  &Libera Peça
*
*  $ED Descrição da função
*  Libera uma peça qualquer passada como parâmetro
*
*
*  $EP Parâmetros
*     pnovo  - ponteiro para a peça que será liberada.
*	
*
*  $FV Valor retornado
*     Se executou corretamente retorna OK.
*    
*
*  
*
***********************************************************************/
PEC_tpCondRet liberaPeca(Peca *peca);

/********** Fim do módulo de definição: PEC  Peça **********/

