#include<stdio.h>
#include<stdlib.h>
#include "peca.h"
#include "lista.h"
#include"Tabuleiro.h"

   
int main()
{
	int i,j;
	char cor,id;
	ptTabuleiro tabu;

	TAB_CriaTabuleiro(&tabu,8,8);
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
}
