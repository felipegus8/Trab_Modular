/***********************************************************************
*
*  $FC Fun��o: TSTE &Efetuar comandos de teste espec�ficos
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     sendo testado.
*
*     Cada m�dulo de teste espec�fico deve desenvolver esta fun��o.
*     Poder� conter diversas outras conforme necess�rio. No entanto
*     estas devem todas ser fun��es encapsuladas no m�dulo (static)
*
*     Freq�entemente � necess�rio desenvolver um contexto para o teste.
*     Por exemplo, pode ser necess�rio tratar n elementos disponibilizados
*     pelo m�dulo sob teste. Neste caso deveria ser criado um vetor
*     global com refer�ncias para estas elemento. Ao iniciar os teste
*     este vetor dever� ser inicializado. Ao terminar, os elementos do
*     vetor referenciando algum elemento devem ser destru�dos.
*
*     Uma das formas para estabelecer o contexto seria a de incluir
*     no m�odulo de teste espec�fico comando semelhantes a:
*
*       =iniciaXXX  que inicializa o contexto do m�dulo sob teste para
*                   vazio. Este comando deve ser utilizado uma �nica vez
*                   logo ao inciar a execu��o do teste.
*       =reset      restaura o contexto para vazio. Este comando usualmente
*                   assumir� que o contexto a esvaziar esteja correto.
*                   O comando dever� liberar os espa�os alocados aos
*                   elementos, anular as refer�ncias a ele, inicializar
*                   valores de vetores de refer�ncias, etc.
*                   O comando tem utilidade especial ao segmentar um teste
*                   em partes estanques e ao controlar vazamento de
*                   mem�ria.
*       =terminaXXX este comando destr�i todo o contexto e n�o o
*                   reinicializa. O objetivo � poder verificar vazamento
*                   de mem�ria.
*
*     Evidentemente, outra forma seria a de alterar as fun��es de
*     inicializa��o e t�rmino do m�dulo de teste gen�rico o que � pouco
*     recomend�vel pois viola o princ�pio de um mesmo m�dulo gen�rico
*     servir para testar todos os construtos.
*
*     Para cada fun��o do m�dulo a ser testado deve existir pelo menos
*     um comando. Em alguns casos pode ser interessante criar
*     comandos que armazenem, alterem ou consultem vari�veis de
*     estado do pr�prio m�dulo de teste. Ver os coment�rios sobre
*     contexto acima.
*
*     Todos os controles de consist�ncia devem ser realizados no
*     m�dulo de teste espec�fico.
*
*     A fun��o TST_EfetuarComando( ) deve retornar as condi��es de retorno
*     identificadas no tipo TST_tpCondRet definida no m�dulo TesteGen.
*
*     As fun��es do m�dulo sob teste que retornam algum valor sempre
*     devem sempre ter este valor verificado, mesmo sendo uma condi��o de
*     retorno. Para fazer a verefica��o da corretude, recomenda-se
*     utilizar as fun��es TST_CompararXXX definidas no m�dulo gen�rico.
*     Assegura-se assim a uniformidade da sa�da gerada durante o teste.
*
*     Para realizar a an�lise de um comando de teste recomenda-se
*     utilizar as fun��es definidas no m�dulo LerParm. Elas, al�m
*     de realizarem a an�lise l�xica, permitem o uso intercambi�vel
*     de par�metros simb�licos ou literais. Tamb�m realizam a
*     verifica��o da corretude dos tipos dos par�metros, contribuindo
*     assim para a redu��o de erros de reda��o de scripts de teste
*     que possam passar despercebidos.
*
*     As fun��es a serem testadas que requeiram algum argumento, devem
*     ser chamadas com valores (par�metros) extra�dos do comando de
*     teste sendo executado.
*
*  $EP Par�metros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     TST_CondRetXXX       - veja a descri�c�o dos poss�veis valores
*                            retornados na especifica��o do correspondente
*                            enum
*
***********************************************************************/
TST_tpCondRet TST_EfetuarComando( char * ComandoTeste ) ;

/********** Fim do m�dulo de defini��o: TSTE Interface de teste espec�fico **********/