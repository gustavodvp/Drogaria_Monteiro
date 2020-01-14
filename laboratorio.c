#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>


// Prototipos 

void exibeMenuLab(void);
int validaOpcaoMenuLab(void);


struct tLaboratorio{
	int codigo;
	char nome[15];
	char flag;
	
};

int main (void){
	setlocale(LC_ALL, "Portuguese");
	struct tLaboratorio lab;
	int codigo, opcao;
	
	do{
		exibeMenuLab();
		opcao=validaOpcaoMenuLab();
		
		switch(opcao){
			case 1:
				printf("... CADASTRO DE NOVO LABORATÓRIO ...\n");
				lab.codigo=incrementaCodigoLab();
				recebeDadosLab(&lab);
				cadastraLab(lab);
				mensagemContinuar();
				break;
			
			case 2:
				printf("...::: LISTANDO LABORATORIOS ::...\n");
				listaLab();
				break;
				
			case 3:
				printf("...::: EXPORTACAO :::....\n");
				exportarExcel();
				
				break;
		}
		
	} while (opcao!=0);
	
	return 0;
}

void exibeMenuLab(void){
	printf("...:: LABORATÓRIO ::...\n");
	printf("1 - CADASTRAR NOVO\n");
	printf("2 - LISTAR LABORATORIOS\n");
	printf("3 - EXPORTAR DADOS\n");
	printf("0 - VOLTAR\n");
	printf("\n\nESCOLHA UMA OPÇÃO: ");
	
}

void exibeLab(int cod){
	printf("\n...:: LABORATORIO - %d ::... \n", cod);
}

int validaOpcaoMenuLab(void){
	int op;
	do{
		scanf("%d", &op);
		if(op<0 || op>3)
			printf("\nOpcao invalida! \nDigite novamente: ");	
	}while(op<0 || op>3);
	system("cls");
	return op;
}

int incrementaCodigoLab(void){
	int cod = 1;
	struct tLaboratorio lab;
	FILE *arqvLab;
	arqvLab = fopen("lab.bin", "rb");
	if (arqvLab == NULL)	
		return cod;		
	while(fread(&lab, sizeof(lab), 1, arqvLab))	
		cod = lab.codigo;			
	fclose(arqvLab);			
	return ++cod;
}

void leValidaString (char *string){
	do{
		fflush(stdin);
		gets(string);
		  if(strlen(string)==0){
			printf("\n-> Digite algo:");
		} 		
	} while(strlen(string)==0);
}

void recebeDadosLab(struct tLaboratorio *lab){
	exibeLab(lab->codigo);
	printf("\nNome: ");
	leValidaString (lab->nome);	
}

void cadastraLab(struct tLaboratorio lab){
	FILE *arqvLab;
	
	arqvLab = fopen("lab.bin", "ab");
	
	if (arqvLab == NULL)	
		mensagemErroArquivo();
	else {
		fwrite(&lab, sizeof(lab), 1, arqvLab);
	}
	fclose(arqvLab);
}

void mensagemErroArquivo(void){
	printf("\nErro na abertura do arquivo. \n");
	getch();
}

void mensagemContinuar(void){
	printf("\n\nDigite algo para continuar...");
	getch();
	system("cls");
}

void listaLab(void){
	struct tLaboratorio lab;
	FILE *arqvLab;
	arqvLab=fopen("lab.bin", "rb");
	if(arqvLab==NULL)
		mensagemErroArquivo();
	else {
		printf("COD. | NOME                 | CPF             | TEL. CONTATO       |\n");
		while(fread(&lab, sizeof(lab), 1, arqvLab))
		if(lab.flag!='*')
			printf("%c%4d%18s%19s%15s\n", lab.flag, lab.codigo, lab.nome);
		
		mensagemContinuar();
	}
	fclose(arqvLab);
	
} 

void exportarExcel(void){
	struct tLaboratorio lab;
	FILE *arqvLabBin;
	FILE *arqvLabTxt;
	arqvLabBin=fopen("cliente.bin", "rb");
	arqvLabTxt=fopen("cliente.csv", "w");
	if(arqvLabBin==NULL || arqvLabTxt==NULL)
		mensagemErroArquivo();
	
	else{
		fprintf(arqvLabTxt, "COD;NOME;CPF;TEL CONTATO\n");
		while (fread(&lab, sizeof(lab), 1, arqvLabBin)){
			// adicionar flag aqui
			fprintf(arqvLabTxt, "%d;%s;%s;%s\n", lab.codigo, lab.nome);
		}
		fclose(arqvLabBin);
		fclose(arqvLabTxt);
		printf(" *** ABRINDO EXCEL.... *** \n");
		system(arqvLabTxt); //erro aqui 
	}
	
	mensagemContinuar();
}


