#include<stdio.h>
#include<stdlib.h>
#include"Tabuleiro.h"

   
int main()
{
	int i,j;
	char cor,id;
	ptTabuleiro tabu;

	TAB_CriaTabuleiro(&tabu);
	//Inserindo Pecas
	TAB_InserirPeca(tabu,1,6,'B','R');
	TAB_InserirPeca(tabu,2,2,'P','T');
	TAB_InserirPeca(tabu,3,3,'P','D');
	printf("\n");
   	//Esse movimento coloca o rei em cheque
	TAB_MoverPeca(tabu,2,2,1,2);
	//Rei sai do cheque
	TAB_MoverPeca(tabu,1,6,0,5);
	//Rainha coloca o rei em cheque mate
	TAB_MoverPeca(tabu,3,3,0,3);
	
	//Destruir o Tabuleiro
	TAB_DestruirTabuleiro(tabu);
	
	//Criar um novo tabuleiro e simular outra situação
	TAB_CriaTabuleiro(&tabu);
	
	//Inserindo Peças
	TAB_InserirPeca(tabu,1,6,'B','R');
	TAB_InserirPeca(tabu,2,2,'P','T');
	TAB_InserirPeca(tabu,3,3,'P','D');
	TAB_InserirPeca(tabu,3,5,'B','T');
	//Esse movimento coloca o rei em cheque
	TAB_MoverPeca(tabu,2,2,1,2);
	//Rei sai do cheque
	TAB_MoverPeca(tabu,1,6,0,5);
	//Rainha coloca o rei em um cheque que ele não consegue sair sozinho
	TAB_MoverPeca(tabu,3,3,0,3);
	//Torre branca captura a rainha preta e tira o rei do cheque
	TAB_MoverPeca(tabu,3,5,3,3);
	
	
	//Destruir o Tabuleiro
	TAB_DestruirTabuleiro(tabu);
	
	
	//Criar um novo tabuleiro e simular outra situação
	TAB_CriaTabuleiro(&tabu);
	
	//Inserindo Peças
	TAB_InserirPeca(tabu,1,6,'B','R');
	TAB_InserirPeca(tabu,2,2,'P','T');
	TAB_InserirPeca(tabu,3,1,'P','D');
	TAB_InserirPeca(tabu,4,4,'B','T');
	//Esse movimento coloca o rei em cheque
	TAB_MoverPeca(tabu,2,2,1,2);
	//Rei sai do cheque
	TAB_MoverPeca(tabu,1,6,0,5);
	//Rainha coloca o rei em um cheque que ele não consegue sair sozinho
	TAB_MoverPeca(tabu,3,1,0,1);
	//Torre Branca bloqueia o cheque da rainha
	TAB_MoverPeca(tabu,4,4,0,4);
	//Rainha captura a torre Branca e aí sim coloca o rei em cheque mate
	TAB_MoverPeca(tabu,0,1,0,4);
	
	//Destruir o Tabuleiro
	TAB_DestruirTabuleiro(tabu);
}