#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <math.h>
#include <conio.h>
#include "libFuncoes.c"

int main (void){
	setlocale(LC_ALL, "Portuguese");
	int opcao;
	int codigo;
	int acesso;
	
	do{
		exibeMenu();
		opcao=validaOpcaoMenu();
		switch(opcao){
			case 1:
				principalCliente();
				break;
			case 2:
				principalProduto();
				break;
			case 3:
				principalLab();
				break;
			case 4: 
				principalVenda();
				break;
			//case 5:
		//		principalLogin();
		//		break;
		}
	} while(opcao!=0);

	
	
	
	return 0;
}

int menuMain(){
	int opcao;
	do{
		printf("ESCOLHA UMA OPCAO:\n");
		printf("1 - CLIENTE\n");
		printf("2 - PRODUTOS\n");
		printf("3 - LABORATORIOS\n");
		printf("4 - INICIAR VENDA\n");
		//printf("5 - GERENCIAR LOGIN\n");
		scanf("%d", &opcao);
		
		if(opcao < 1 || opcao > 5){
			printf("\nPor Favor digite uma opção válida!!!");
		}
		
	}while(opcao<1 || opcao > 5);
	
	
	return opcao;
	
}

void exibeMenu(){
	printf("....::: MENUS :::....\n");
	printf("1 - CLIENTE\n");
	printf("2 - PRODUTOS\n");
	printf("3 - LABORATORIOS\n");
	printf("4 - INICIAR VENDA\n");
//	printf("5 - GERENCIAR LOGIN\n");

}

int validaOpcaoMenu(void){
	int op;
	do{
		scanf("%d", &op);
		if(op<0 || op>5)
				printf("\nOpcao invalida!\nDigite novamente:\n");
	} while(op<0 || op>5);
	system("cls");
	return op;
}
