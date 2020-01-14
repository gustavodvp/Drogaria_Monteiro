// ------------------- colocar limpador de tela nas funcoes -----------------------
/* Bibliotecas */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

/* Prototipos */
void exibeMenuCliente(void);
void exibeCliente(int);
int validaOpcaoMenuCliente(void);
void recebeDadosCliente();
int incrementaCodigoCliente(void);
void leValidaStringCliente (char*);
void cadastraCliente();
void mensagemContinuar(void);
void mensagemErroArquivo(void);
void listaCliente(void);
void mostraDadosCliente();
int recebeCodigoCliente(void);
void consultaCliente(void);
void alteraCliente(void);
void opcaoExcluir(void);
char mensagemExcluirCliente(void);
void excluirClienteTemp(void);
void excluirClientePermanente(void);
void exportarExcel(void);

/* estrutura de registro */
struct tCliente{
	int codigo;
	char nome[20];
	char cpf[12];
	char telefoneContato[15];
	char flag;
};

/* Inicio */

int main (void){
	setlocale(LC_ALL, "Portuguese");
	FILE *arquivoCliente;
	struct tCliente cliente;
	int codigo;
	int opcao;
	
	do{
		exibeMenuCliente();
		opcao=validaOpcaoMenuCliente();
		
		switch(opcao){
			case 1: 
				printf("... CADASTRO ...\n");
				cliente.codigo=incrementaCodigoCliente();
				recebeDadosCliente(&cliente);
				cadastraCliente(cliente);
				mensagemContinuar();
				break;
			case 2:
				printf("... LISTANDO CLIENTES ...\n");
				listaCliente();
				break;
			case 3:
				printf("... CONSULTAR ...\n");
				consultaCliente();
				break;
				
			case 4:
				printf("... ALTERAR CADASTRO ...\n");
				alteraCliente();
				break;
			case 5:
				printf("... EXCLUIR CLIENTE...\n");
				opcaoExcluir();
				break;
			 case 6:
			 	printf("... EXPORTACAO ...\n");
			 	exportarExcel();
			 	break;
		}
		
	} while(opcao!=0);
	
	return 0;
}

// Funcao Exibir Menu da Cliente
void exibeMenuCliente(void){
	printf("\n  ..:: CLIENTE ::..\n\n");
	printf("  1 - CADASTRAR \n");
	printf("  2 - LISTAR\n");
	printf("  3 - CONSULTAR POR CODIGO\n");
	printf("  4 - ALTERAÇÃO DO CADASTRO\n");
	printf("  5 - EXCLUIR DO CADASTRO\n");
	printf("  6 - EXPORTAR\n");
	printf("  0 - VOLTAR\n"); 
	printf("\n\n  ESCOLHA UMA OPÇÃO: ");	
}

// Gerando codigo aleatorio do cliente (chave primaria)
void exibeCliente(int cod){
	printf("\n...:: CLIENTE - %d ::... \n", cod);
}

// Funcao Validar opcao do MENU
int validaOpcaoMenuCliente(void){
	int op;
	do{
		scanf("%d", &op);
		if(op<0 || op>6)
			printf("\nOpcao invalida! \nDigite novamente: ");	
	}while(op<0 || op>6);
	system("cls");
	return op;
}

// Recebendo dados
void recebeDadosCliente(struct tCliente *cl){
	exibeCliente(cl->codigo);
	printf("\nNome: ");
	leValidaStringCliente (cl->nome);
	printf("\nCPF: ");
	leValidaStringCliente (cl->cpf);
	printf("\nNumero de Contato: ");
	fflush(stdin);
	gets(cl->telefoneContato);
	
}

// incrementando codigo sequencial
int incrementaCodigoCliente(void){
	int cod = 1;
	struct tCliente cliente;
	FILE *arquivoCliente;
	arquivoCliente = fopen("cliente.bin", "rb");
	if (arquivoCliente == NULL)	
		return cod;		
	while(fread(&cliente, sizeof(cliente), 1, arquivoCliente))	
		cod = cliente.codigo;			
	fclose(arquivoCliente);			
	return ++cod;
}

// Funcao que valida variaveis do tipo STRING 
void leValidaStringCliente (char *string){
	do{
		fflush(stdin);
		gets(string);
		  if(strlen(string)==0){
			printf("\n-> Digite algo:");
		} 		
	} while(strlen(string)==0);
}

/* cadastrando novo cliente */
void cadastraCliente(struct tCliente cl){
	FILE *arquivoCliente;
	
	arquivoCliente = fopen("cliente.bin", "ab");
	
	if (arquivoCliente == NULL)	
		mensagemErroArquivo();
	else {
		fwrite(&cl, sizeof(cl), 1, arquivoCliente);
	}
	fclose(arquivoCliente);
}

// pausa no programa
void mensagemContinuar(void){
	printf("\n\nDigite algo para continuar...");
	getch();
	system("cls");
}

// ERRO na abertura de arquivo
void mensagemErroArquivo(void){
	printf("\nErro na abertura do arquivo. \n");
	getch();
}

// listagem de clientes que nao estao excluidos
void listaCliente(void){
	struct tCliente cliente;
	FILE *arquivoCliente;
	arquivoCliente=fopen("cliente.bin", "rb");
	if(arquivoCliente==NULL)
		mensagemErroArquivo();
	else {
		printf("COD. | NOME                 | CPF             | TEL. CONTATO       |\n");
		while(fread(&cliente, sizeof(cliente), 1, arquivoCliente))
		if(cliente.flag!='*')
			printf("%c%4d%18s%19s%15s\n", cliente.flag, cliente.codigo, cliente.nome, cliente.cpf, cliente.telefoneContato);
		
		mensagemContinuar();
	}
	fclose(arquivoCliente);
	
} 

// mostrando dados do cliente - funcoa usada dentro de outras funcoes 
// nao mexer!.
void mostrarDadosCliente(struct tCliente cl){
	printf("\nExibindo dados encontrados...\n");
	exibeCliente(cl.codigo);
	printf("\n  Nome: %s", cl.nome);
	printf("\n  CPF: %s", cl.cpf);
	printf("\n  Tel. Contato: %s", cl.telefoneContato);
}

// recebendo codigo
int recebeCodigoCliente(void){
	int cod;
	printf("\nDigite o codigo para ser consultado:");
	scanf("%d", &cod);
	return cod;
}

// consultando cliente nos arquivos e registros
void consultaCliente(void){
	int cod, achei=0;
	struct tCliente cliente;
	FILE *arquivoCliente;
	arquivoCliente=fopen("cliente.bin", "rb");
	if(arquivoCliente==NULL)
		mensagemErroArquivo();
	
	else {
		cod=recebeCodigoCliente();
		while(fread(&cliente, sizeof(cliente), 1, arquivoCliente))
			if(cod == cliente.codigo){
				mostrarDadosCliente(cliente);
				achei=1;
				
			}
		if(!achei)
			printf("ERRO: Cliente não encontrado. \n");
			
		mensagemContinuar();
	}
}

// fazendo alteracao do cadastro do cliente buscado
void alteraCliente(void){
	int cod, achei=0;
	struct tCliente cliente;
	FILE *arquivoCliente;
	arquivoCliente=fopen("cliente.bin", "r+b");
	if(arquivoCliente==NULL)
		mensagemErroArquivo();
	else {
		cod=recebeCodigoCliente();
		while(fread(&cliente, sizeof(cliente), 1, arquivoCliente))
			if(cod==cliente.codigo){
				mostrarDadosCliente(cliente);
				printf("\n\n*** ATENCAO: CODIGO NAO PODERA SER ALTERADO!. ***\n\n");
				printf("\nDigite os novos dados: ");
				recebeDadosCliente(&cliente);
				achei=1;
				fseek(arquivoCliente, -sizeof(cliente), SEEK_CUR); // posicionando ponteiro no registro
				fwrite(&cliente, sizeof(cliente), 1, arquivoCliente);
				fseek(arquivoCliente, 0, SEEK_CUR); // fixando ponteiro
			}
			if(!achei)
				printf("ERRO: Cliente não encontrado.\n");
			
			mensagemContinuar();
			
	}
		
	fclose(arquivoCliente);
}

// mostrando opcoes de exclusao 

void opcaoExcluir(void){
	int opcao;
	
	do{
		printf("*** ESCOLHA UMA OPÇÃO ***\n\n");
		printf("1 - Excluir todo o registro \n");
		printf("2 - Excluir um dado do registro \n");
		scanf("%d", &opcao);
	} while (opcao!=1 && opcao!=2);
	
	if(opcao==1)
		excluirClientePermanente();
	if(opcao==2)
		excluirClienteTemp();
	
}

// mensagem de warning 
char mensagemExcluirCliente(void){
	char opcao;
	printf("\n\n**** ATENCAO: ESSA ACAO NAO PODERA SER DESFEITA.");
	printf("\n 		 TEM CERTEZA QUE DESEJA CONTINUAR?     *****");
	do{
		printf("\n\nDigite [S] - SIM ou [N] - NAO : \n");
		fflush(stdin);
		opcao=getchar();
		opcao=toupper(opcao);
		
	} while (opcao!='S' && opcao!= 'N');
	
	return opcao;
}

// exclusao de apenas um registro do arquivo

void excluirClienteTemp(void){
	int cod, achei=0;
	struct tCliente cliente;
	FILE *arquivoCliente;
	arquivoCliente=fopen("cliente.bin", "r+b");
	if (arquivoCliente==NULL)
		mensagemErroArquivo();
	else {
		cod = recebeCodigoCliente ();
		while (fread(&cliente, sizeof(cliente), 1, arquivoCliente))
			if(cod == cliente.codigo && cliente.flag!='*'){
				mostrarDadosCliente(cliente);
				achei=1;
				if(mensagemExcluirCliente()=='S'){
					cliente.flag = '*'; 
					fseek(arquivoCliente, -sizeof(cliente), SEEK_CUR);
					fwrite(&cliente, sizeof(cliente), 1, arquivoCliente);
					fseek(arquivoCliente, 0, SEEK_CUR);
					
				}
			}
			if(!achei)
				printf("\n ERRO: Cliente não encontrado. \n");
				mensagemContinuar();
	}
	fclose(arquivoCliente);
	
}

// exclusao do arquivo todo

void excluirClientePermanente(void){
	struct tCliente cliente;
	FILE *arquivoCliente;
	FILE *arquivoClienteTemp;
	arquivoCliente=fopen("cliente.bin", "r+b");
	arquivoClienteTemp=fopen("clienteTemp.bin", "wb");
	if(arquivoCliente==NULL)
		mensagemErroArquivo();
	else {
		if(mensagemExcluirCliente()=='S'){
			while(fread(&cliente, sizeof(cliente), 1, arquivoCliente))
				if(cliente.flag!='*')
					fwrite(&cliente, sizeof(cliente), 1, arquivoClienteTemp);
				fclose(arquivoCliente);
				fclose(arquivoClienteTemp);
				remove(arquivoCliente);
				rename(arquivoClienteTemp, arquivoCliente); //erro aqui 
				
		}
	}
}

// exportacao em arquivo de valores
void exportarExcel(void){
	struct tCliente cliente;
	FILE *arquivoClienteBin;
	FILE *arquivoClienteTxt;
	arquivoClienteBin=fopen("cliente.bin", "rb");
	arquivoClienteTxt=fopen("cliente.csv", "w");
	if(arquivoClienteBin==NULL || arquivoClienteTxt==NULL)
		mensagemErroArquivo();
	
	else{
		fprintf(arquivoClienteTxt, "COD;NOME;CPF;TEL CONTATO\n");
		while (fread(&cliente, sizeof(cliente), 1, arquivoClienteBin)){
			// adicionar flag aqui
			fprintf(arquivoClienteTxt, "%d;%s;%s;%s\n", cliente.codigo, cliente.nome, cliente.cpf, cliente.telefoneContato);
		}
		fclose(arquivoClienteBin);
		fclose(arquivoClienteTxt);
		printf(" *** ABRINDO EXCEL.... *** \n");
		system(arquivoClienteTxt); //erro aqui 
	}
	
	mensagemContinuar();
}







