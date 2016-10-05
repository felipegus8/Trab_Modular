/***********************************************************************
*
*  $FC Função: TSTE &Efetuar comandos de teste específicos
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     sendo testado.
*
*     Cada módulo de teste específico deve desenvolver esta função.
*     Poderá conter diversas outras conforme necessário. No entanto
*     estas devem todas ser funções encapsuladas no módulo (static)
*
*     Freqüentemente é necessário desenvolver um contexto para o teste.
*     Por exemplo, pode ser necessário tratar n elementos disponibilizados
*     pelo módulo sob teste. Neste caso deveria ser criado um vetor
*     global com referências para estas elemento. Ao iniciar os teste
*     este vetor deverá ser inicializado. Ao terminar, os elementos do
*     vetor referenciando algum elemento devem ser destruídos.
*
*     Uma das formas para estabelecer o contexto seria a de incluir
*     no mçodulo de teste específico comando semelhantes a:
*
*       =iniciaXXX  que inicializa o contexto do módulo sob teste para
*                   vazio. Este comando deve ser utilizado uma única vez
*                   logo ao inciar a execução do teste.
*       =reset      restaura o contexto para vazio. Este comando usualmente
*                   assumirá que o contexto a esvaziar esteja correto.
*                   O comando deverá liberar os espaços alocados aos
*                   elementos, anular as referências a ele, inicializar
*                   valores de vetores de referências, etc.
*                   O comando tem utilidade especial ao segmentar um teste
*                   em partes estanques e ao controlar vazamento de
*                   memória.
*       =terminaXXX este comando destrói todo o contexto e não o
*                   reinicializa. O objetivo é poder verificar vazamento
*                   de memória.
*
*     Evidentemente, outra forma seria a de alterar as funções de
*     inicialização e término do módulo de teste genérico o que é pouco
*     recomendável pois viola o princípio de um mesmo módulo genérico
*     servir para testar todos os construtos.
*
*     Para cada função do módulo a ser testado deve existir pelo menos
*     um comando. Em alguns casos pode ser interessante criar
*     comandos que armazenem, alterem ou consultem variáveis de
*     estado do próprio módulo de teste. Ver os comentários sobre
*     contexto acima.
*
*     Todos os controles de consistência devem ser realizados no
*     módulo de teste específico.
*
*     A função TST_EfetuarComando( ) deve retornar as condições de retorno
*     identificadas no tipo TST_tpCondRet definida no módulo TesteGen.
*
*     As funções do módulo sob teste que retornam algum valor sempre
*     devem sempre ter este valor verificado, mesmo sendo uma condição de
*     retorno. Para fazer a vereficação da corretude, recomenda-se
*     utilizar as funções TST_CompararXXX definidas no módulo genérico.
*     Assegura-se assim a uniformidade da saída gerada durante o teste.
*
*     Para realizar a análise de um comando de teste recomenda-se
*     utilizar as funções definidas no módulo LerParm. Elas, além
*     de realizarem a análise léxica, permitem o uso intercambiável
*     de parâmetros simbólicos ou literais. Também realizam a
*     verificação da corretude dos tipos dos parâmetros, contribuindo
*     assim para a redução de erros de redação de scripts de teste
*     que possam passar despercebidos.
*
*     As funções a serem testadas que requeiram algum argumento, devem
*     ser chamadas com valores (parâmetros) extraídos do comando de
*     teste sendo executado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     TST_CondRetXXX       - veja a descriÓcão dos possíveis valores
*                            retornados na especificação do correspondente
*                            enum
*
***********************************************************************/
TST_tpCondRet TST_EfetuarComando( char * ComandoTeste ) ;

/********** Fim do módulo de definição: TSTE Interface de teste específico **********/