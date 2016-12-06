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
 
 *  Autores: Felipe Viberti,Luis Claudio e Victor Nogueira
 *
 *  $HA Histórico de evolução:
 *     Versão  Autores                                           Data          Observações
 *     1       Felipe Viberti,Luis Claudio e Victor Nogueira   02/out/2016  início desenvolvimento
 *
 ***************************************************************************/
#include <stdio.h>
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
PEC_tpCondRet PEC_AlteraCorEId(Peca *peca,char cor,char id);
PEC_tpCondRet PEC_CriaPeca(Peca **novo,char id,char cor);
PEC_tpCondRet PEC_FingeQueTira(Peca *peca);


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
PEC_tpCondRet PEC_EnsinaMovimentosPecasConhecidas(Peca **novo);

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
PEC_tpCondRet PEC_EnsinaMovimentosPecasDesconhecidas(Peca **novo);

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
PEC_tpCondRet PEC_LiberaPeca(Peca *peca);

/***********************************************************************
 *  $FC Função: PEC  &Retorna Id
 *
 *  $ED Descrição da função
 *  Retorna por referencia o id de uma peça.
 *
 *
 *  $EP Parâmetros
 *     peca-peca que se quer obter o id.
 *     id - ponteiro onde o id da peça será colocado.
 *
 *
 *  $FV Valor retornado
 *     Se executou corretamente retorna OK.
 *
 *
 *
 *
 ***********************************************************************/
PEC_tpCondRet PEC_RetornaId(Peca *peca,char *id);

/***********************************************************************
 *  $FC Função: PEC  &Retorna Cor
 *
 *  $ED Descrição da função
 *  Retorna por referencia a cor de uma peça.
 *
 *
 *  $EP Parâmetros
 *     peca-peca que se quer obter a cor.
 *     cor - ponteiro onde a cor da peça será colocado.
 *
 *
 *  $FV Valor retornado
 *     Se executou corretamente retorna OK.
 *
 *
 *
 *
 ***********************************************************************/
PEC_tpCondRet PEC_RetornaCor(Peca *peca,char *cor);

/***********************************************************************
 *  $FC Função: PEC  &Retorna Id
 *
 *  $ED Descrição da função
 *  Retorna por referencia a quantidade de movimentos válidos de uma peça.
 *
 *
 *  $EP Parâmetros
 *     peca-peca que se quer obter a quantidade de movimentos válidos.
 *     qtdMov - ponteiro onde a quantidade de movimentos da peça será colocada.
 *
 *
 *  $FV Valor retornado
 *     Se executou corretamente retorna OK.
 *
 *
 *
 *
 ***********************************************************************/
PEC_tpCondRet PEC_RetornaQtd_Mov(Peca *peca,int *qtdMov);

/***********************************************************************
 *  $FC Função: PEC  &Retorna Move Para Tras
 *
 *  $ED Descrição da função
 *  Retorna por referencia se uma peca se move para tras ou não.
 *
 *
 *  $EP Parâmetros
 *     peca-peca que se quer obter o id.
 *     moveParaTras - ponteiro onde o int(0 ou 1) que determina se a peça se move Para Trás ou não será colocado.
 *
 *
 *  $FV Valor retornado
 *     Se executou corretamente retorna OK.
 *
 *
 *
 *
 ***********************************************************************/
PEC_tpCondRet PEC_RetornaPodePular(Peca *peca,int *podePular);



/***********************************************************************
 *  $FC Função: PEC  &Retorna X Movimento
 *
 *  $ED Descrição da função
 *  Retorna por referencia a coordenada x de um movimento válido da peça.
 *
 *
 *  $EP Parâmetros
 *     peca-peca que se quer obter o movimento.
 *     i - posição do vetor de movimentos que se quer acessar.
 *     x - ponteiro onde a coordenada x será colocada.
 *
 *
 *  $FV Valor retornado
 *     Se executou corretamente retorna OK.
 *
 *
 *
 *
 ***********************************************************************/
PEC_tpCondRet PEC_RetornaXMovimento(Peca *peca,int i,int *x);

/***********************************************************************
 *  $FC Função: PEC  &Retorna Y Movimento
 *
 *  $ED Descrição da função
 *  Retorna por referencia a coordenada y de um movimento válido da peça.
 *
 *
 *  $EP Parâmetros
 *     peca-peca que se quer obter o movimento.
 *     i - posição do vetor de movimentos que se quer acessar.
 *     y - ponteiro onde a coordenada y será colocada.
 *
 *
 *  $FV Valor retornado
 *     Se executou corretamente retorna OK.
 *
 *
 *
 *
 ***********************************************************************/
PEC_tpCondRet PEC_RetornaYMovimento(Peca *peca,int i,int *y);

/***********************************************************************
 *  $FC Função: PEC  &Eliminar Peca
 *
 *  $ED Descrição da função
 *  Preenche os campos id e cor da Peca recebida como V indicando que ela está vazia.
 *
 *
 *  $EP Parâmetros
 *     peca-peca que se "eliminar"
 *
 *  $FV Valor retornado
 *     Se executou corretamente retorna OK.
 *
 *
 *
 *
 ***********************************************************************/
PEC_tpCondRet PEC_EliminarPeca(Peca *peca);


/***********************************************************************
 *  $FC Função: PEC  &Retorna Tamanho Peça
 *
 *  $ED Descrição da função
 *  Retorna o tamanho em bytes da peça dada como parametro
 *
 *
 *  $EP Parâmetros
 *     peca - peca que se quer obter o tamanho
 *     tamanhoPeca - ponteiro para o inteiro que receberá o tamanho da peça
 *
 *  $FV Valor retornado
 *     Retorna OK se peça não for nula
 *     Retorna NaoAchouPeca se peça for nula
 *
 *
 *
 *
 ***********************************************************************/

#ifdef _DEBUG
PEC_tpCondRet PEC_RetornaTamanhoPeca(Peca *peca,int *tamanhoPeca);
#endif

/********** Fim do módulo de definição: PEC  Peça **********/

