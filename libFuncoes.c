#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <tchar.h>
#include <windows.h>
#define ARQ_LG "login.dat"
#define ARQ_LG_TMP "login.tmp"
#define ARQ_LG_CSV "login.csv"
#define ARQ_CLIENTEBIN "cliente.bin"
#define ARC_CLIENTETXT "cliente.csv"
#define VENDA_TXT "venda.txt"
#define VENDA_BIN "venda.bin"

#define TAM 10
#define OPCOES 7

// --- REGISTROS ---
/* estrutura de registro */
struct tProduto{
	int cod;
	char nome[30];
	float valor;
	int qtdDisp;
	char flag;
};


struct tCliente{
	int codigo;
	char nome[20];
	char cpf[12];
	char telefoneContato[15];
	char flag;
};

struct tLaboratorio{
	int codigo;
	char nome[18];
	char flag;
	
};

struct tVenda{
	int codigo;
	char cpfCliente[TAM];
	int idProduto;
	int quantidade;
	float valorTotal;
};


struct tLogin {
	//Atributos
	int codigo;
	char usuario[TAM];
	char senha[TAM];
	int nivel;
	//Marcadores
	char lixo; // *=deletado; espaco=OK
};




// --- PRODUTO ---
void exibeMenuProduto(void);
void exibeProduto(int);
int validaOpcaoMenuProduto(void);
void recebendoDadosProduto();
int incrementaCodigoProduto(void);
void leValidaStringProduto (char*);
float leValidaValorProduto(void);
void cadastraProduto();
void mensagemContinuar(void);
void mensagemErroArquivo(void);
void listaProduto(void);
void mostraDadosProduto();
int recebeCodigoProduto(void);
void consultaProduto(void);
void alteraProduto(void);
void opcaoExcluirProduto(void);
char mensagemExcluirProduto(void);
void excluirProdutoTemp(void);
void excluirProdutoPermanente(void);
void exportarExcel(void);
int leValidaQtdProduto(void);


// --- CLIENTE ---

void exibeMenuCliente(void);
void exibeCliente(int);
int validaOpcaoMenuCliente(void);
void recebeDadosCliente();
int incrementaCodigoCliente(void);
void leValidaStringCliente (char*);
void cadastraCliente();
void listaCliente(void);
void mostraDadosCliente();
int recebeCodigoCliente(void);
void consultaCliente(void);
void alteraCliente(void);
void opcaoExcluirCliente(void);
char mensagemExcluirCliente(void);
void excluirClienteTemp(void);
void excluirClientePermanente(void);
void exportarExcel(void);

// --- LABORATORIO ---

void exibeMenuLab(void);
int validaOpcaoMenuLab(void);
float calculaTotal(int, int);

int principalCliente (void){
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
				opcaoExcluirCliente();
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
		printf("COD. | NOME                    | CPF                 | TEL. CONTATO       |\n");
		while(fread(&cliente, sizeof(cliente), 1, arquivoCliente))
		if(cliente.flag!='*')
			printf("%c%4d%21s%25s%17s\n", cliente.flag, cliente.codigo, cliente.nome, cliente.cpf, cliente.telefoneContato);
		
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

void mostraDadosCliente(struct tCliente cl){
	printf("\nExibindo dados encontrados...\n");
	exibeCliente(cl.codigo);
	printf("\n  Nome: %s", cl.nome);
	printf("\n  CPF: %s", cl.cpf);
	printf("\n  Tel. Contato: %s", cl.telefoneContato);
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

void opcaoExcluirCliente(void){
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
				//remove(arquivoCliente);
			//	rename(arquivoClienteTemp, arquivoCliente); //erro aqui 
				
		}
	}
}

// exportacao em arquivo de valores
void exportarExcel(void){

	struct tCliente cliente;
	FILE *arquivoClienteBin;
	FILE *arquivoClienteTxt;
	arquivoClienteBin=fopen(ARQ_CLIENTEBIN, "rb");
	arquivoClienteTxt=fopen(ARC_CLIENTETXT, "w");
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
		system(ARC_CLIENTETXT); //erro aqui 
	}
	
	mensagemContinuar();
}



//------------------------------------------------------------------------------------------------------------------------------

int principalProduto(void){
	setlocale(LC_ALL, "Portuguese");
	FILE *arquivoProduto;
	struct tProduto produto;
	int codigo;
	int opcao;
	
	do{
		exibeMenuProduto();
		opcao=validaOpcaoMenuProduto();
		
		switch(opcao){
			case 1:
				printf("... CADASTRO ...\n");
				produto.cod=incrementandoCodigoProduto();
				recebendoDadosProduto(&produto);
				cadastraProduto(produto);
				mensagemContinuar();
				break;
			case 2: 
				printf("... LISTANDO PRODUTOS ...\n");
				listaProduto();
				break;
			case 3: 
				printf("... CONSULTAR ...\n");
				consultaProduto();
				break;
			case 4: 
				printf("... ALTERAR CADASTRO ...\n");
				alteraProduto();
				break;
			case 5: 
				printf("... EXCLUIR CLIENTE ...\n");
				opcaoExcluirCliente();
				break;
			case 6: 
				printf("... EXPORTAÇÃO ...\n");
			//	exportarExcel();
				break;
			
		}
	} while(opcao !=0);
	
	return 0;
}

// Função Exibir Menu do Produto

void exibeMenuProduto(void){
	printf("\n ..:: PRODUTO ::..\n\n");
	printf("  1 - CADASTRAR \n");
	printf("  2 - LISTAR\n");
	printf("  3 - CONSULTAR POR CODIGO\n");
	printf("  4 - ALTERAÇÃO DO CADASTRO\n");
	printf("  5 - EXCLUIR DO CADASTRO\n");
	printf("  6 - EXPORTAR\n");
	printf("  0 - VOLTAR\n"); 
	printf("\n\n  ESCOLHA UMA OPÇÃO: ");
}

// Código aleatório para o produto (pk)
void exibeProduto(int cod){
	printf("\n...:: PRODUTO - %d ::... \n", cod);
}

// Função Validar opcao do Menu
int validaOpcaoMenuProduto(void){
	int op;
	do{
		scanf("%d", &op);
		if(op<0 || op>6)
			printf("\nOpção Inválida! \n Digite novamente: ");
		}while(op<0 || op>6);
		
		system("cls");
		return op;
}

// Função que valida a quantidade de produto
int leValidaQtdProduto(){
	struct tProduto produto;
	do{
		fflush(stdin);
		scanf("%d", &produto.qtdDisp);
		if(produto.qtdDisp < 0){
			printf("\nEntre com uma quantidade válida...");
		}
	}while(produto.qtdDisp < 0);
}


// Recebendo dados
void recebendoDadosProduto(struct tProduto *p1){
	exibeProduto(p1->cod);
	printf("\nNome do Produto: ");
	leValidaStringProduto(p1->nome);
	printf("\nValor do Produto: ");
	p1->valor=leValidaValorProduto();
	printf("\nQuantidade do Produto: ");
	p1->qtdDisp=leValidaQtdProduto();
	fflush(stdin);
}

// Incrementando código sequencial
int incrementandoCodigoProduto(void){
	int cod = 1;
	struct tProduto produto;
	FILE *arquivoProduto;
	arquivoProduto = fopen("produto.bin", "rb");
	if(arquivoProduto == NULL)
		return cod;
	while(fread(&produto, sizeof(produto), 1, arquivoProduto))
		cod = produto.cod;
	fclose(arquivoProduto);
	return ++cod;
}


// Função que valida a preço do produto
float leValidaValorProduto(){
	struct tProduto produto;
	do{
		fflush(stdin);
		scanf("%f", &produto.valor);
		if(produto.valor < 0){
			printf("\nEntre com um valor válidao...");
		}
	}while(produto.valor < 0);
	
	return produto.valor;
}


// Função que valida variáveis do tipo String
void leValidaStringProduto(char *string){
	do{
		fflush(stdin);
		gets(string);
		  if(strlen(string)==0){
		  	printf("\n-> Digite algo: ");
		  }
	}while(strlen(string)==0);
}

// Cadastrando novo produto 
void cadastraProduto(struct tProduto p1){
	FILE *arquivoProduto;
	
	arquivoProduto = fopen("produto.bin", "ab");
	
	if(arquivoProduto == NULL)
		mensagemErroArquivo();
	else{
		fwrite(&p1, sizeof(p1), 1, arquivoProduto);
		
	}
	fclose(arquivoProduto);
}



// ERRO na abertura de arquivo


// listagem de produtos que não estão excluídos
void listaProduto(void){
	struct tProduto produto;
	FILE *arquivoProduto;
	arquivoProduto=fopen("produto.bin", "rb");
	if(arquivoProduto==NULL)
		mensagemErroArquivo();
	else{
		printf("COD. | NOME              | VALOR      | QUANTIDADE\n");
		while(fread(&produto, sizeof(produto), 1, arquivoProduto))
			printf("%4d%27s%.2f%7d\n", produto.cod, produto.nome, produto.valor, produto.qtdDisp);
			
		mensagemContinuar();
	}
	fclose(arquivoProduto);
	
}
// mostrando dados do produto
void mostraDadosProduto(struct tProduto p1){
	printf("\nExibindo dados encontrados...\n");
	exibeProduto(p1.cod);
	printf("\n Nome do Produto: %s", p1.nome);
	printf("\n Valor: %0.2f", p1.valor);
	printf("\n Quantidade: %d", p1.qtdDisp);
}

//recebendo código
int recebeCodigoProduto(void){
	int cod;
	printf("\nDigite o código para ser consultado: ");
	scanf("%d", &cod);
	return cod;
}

// COnsultando produto nos arquivos e registros
void consultaProduto(void){
	int cod, achei=0;
	struct tProduto produto;
	FILE *arquivoProduto;
	arquivoProduto=fopen("produto.bin", "rb");
	if(arquivoProduto==NULL)
		mensagemErroArquivo();
	
	else{
		cod=recebeCodigoProduto();
		while(fread(&produto, sizeof(produto), 1, arquivoProduto))
			if(cod == produto.cod){
				mostraDadosProduto(produto);
				achei=1;
			}
			if(!achei)
				printf("ERRO: Cliente não encontrado. \n");
			
			mensagemContinuar();
	}
}

// Fazendo alteração no produto buscado
void alteraProduto(void){
	int cod, achei=0;
	struct tProduto produto;
	FILE *arquivoProduto;
	arquivoProduto=fopen("produto.bin", "r+b");
	if(arquivoProduto==NULL)
		mensagemErroArquivo();
	else{
		cod=recebeCodigoProduto();
		while(fread(&produto, sizeof(produto), 1, arquivoProduto))
			if(cod==produto.cod){
				mostraDadosProduto(produto);
				printf("\n\n*** ATENÇÃO: CÓDIGO NÃO PODERÁ SER ALTERADO!. ***\n\n");
				printf("\nDigite os novos dados: ");
				recebendoDadosProduto(&produto);
				achei=1;
				fseek(arquivoProduto, sizeof(produto), SEEK_CUR); //posicionando o ponteiro no registro
				fwrite(&produto, sizeof(produto), 1, arquivoProduto);
				fseek(arquivoProduto, 0, SEEK_CUR); //fixando ponteiro 
			}
			if(!achei)
				printf("ERRO: Produto não encontrado. \n");
				
			mensagemContinuar();
	}
	fclose(arquivoProduto);
}

// mostrando opcoes de exclusao 

void opcaoExcluirProduto(void){
	int opcao;
	
	do{
		printf("*** ESCOLHA UMA OPÇÃO ***\n\n");
		printf("1 - Excluir todo o registro \n");
		printf("2 - Excluir um dado do registro \n");
		scanf("%d", &opcao);
	} while (opcao!=1 && opcao!=2);
	
	if(opcao==1)
		excluirProdutoPermanente();
	if(opcao==2)
		excluirProdutoTemp();
	
}

// mensagem de warning 
char mensagemExcluirProduto(void){
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

// Exclusão de apenas 1 registro do arquivo

void excluirProdutoTemp(void){
	int cod, achei=0;
	struct tProduto produto;
	FILE *arquivoProduto;
	arquivoProduto=fopen("produto.bin", "r+b");
	if(arquivoProduto==NULL)
		mensagemErroArquivo();
	else{
		cod = recebeCodigoProduto();
		while(fread(&produto, sizeof(produto), 1, arquivoProduto))
			if(cod == produto.cod && produto.flag!='*'){
				mostraDadosProduto(produto);
				achei=1;
				if(mensagemExcluirProduto()=='S'){
					produto.flag = '*';
					fseek(arquivoProduto, sizeof(produto), 1);	
				}
				
			}
			if(!achei)
				printf("\nERRO: Produto não encontrado. \n");
				mensagemContinuar();
	}
	fclose(arquivoProduto);
}

 //Exclusão do Arquivo todo 
void excluirProdutoPermanente(void){
	struct tProduto produto;
	FILE *arquivoProduto;
	FILE *arquivoProdutoTemp;
	arquivoProduto=fopen("produto.bin", "r+b");
	arquivoProdutoTemp=fopen("produtoTemp.bin", "wb");
	if(arquivoProduto==NULL)
		mensagemErroArquivo();
	else{
		if(mensagemExcluirProduto()=='S'){
			while(fread(&produto, sizeof(produto), 1, arquivoProduto))
				if(produto.flag!='*')
					fwrite(&produto, sizeof(produto), 1, arquivoProdutoTemp);
				fclose(arquivoProduto);
				fclose(arquivoProdutoTemp);
				//remove(arquivoProduto);
				//rename(arquivoProdutoTemp, arquivoProduto); //############################
		}
	}
}


// Exportação de Arquvos em valores
/*
void exportarExcel(void){
	struct tProduto produto;
	FILE *arquivoProdutoBin;
	FILE *arquivoProdutoTxt;
	arquivoProdutoBin=fopen("produto.bin", "rb");
	arquivoProdutoTxt=fopen("produto.txt", "w");
	if(arquivoProdutoBin==NULL || arquivoProdutoTxt==NULL)
		mensagemErroArquivo();
	else{
		fprintf(arquivoProdutoTxt, "COD;NOME;VALOR;QUANTIDADE\n");
		while(fread(&produto, sizeof(produto), 1, arquivoProdutoBin)){
			// adicionar flag aqui
			fprintf(arquivoProdutoTxt, "%d;%s;%2.2f;%d", produto.cod, produto.nome, produto.valor, produto.qtdDisp);
		}
		fclose(arquivoProdutoBin);
		fclose(arquivoProdutoTxt);
		printf(" *** ABRINDO EXCEL... ***\n");
		system(arquivoProdutoTxt); //################################
	}
	
	mensagemContinuar();
} */

// -------------------------- LABORATORIO -------------------------------------------------------------------------------------------

int principalLab (void){
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
	fflush(stdin);
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



void listaLab(void){
	struct tLaboratorio lab;
	FILE *arqvLab;
	arqvLab=fopen("lab.bin", "rb");
	if(arqvLab==NULL)
		mensagemErroArquivo();
	else {
		printf("COD. | NOME              |\n");
		while(fread(&lab, sizeof(lab), 1, arqvLab))
		if(lab.flag!='*')
			printf("%4d%18s\n", lab.codigo, lab.nome);
		
		mensagemContinuar();
	}
	fclose(arqvLab);
	
} 
/*
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
*/
// ----------------------------------- VENDA -----------------------------------------------------------------------------------------------



int principalVenda (void){
	struct tVenda venda;
	int codigo;
	int opcao;
	
	do{
		exibeMenuVenda();
		opcao=validaOpcaoMenuVenda();
		
		switch(opcao){
			case 1:
				printf("... ::: INICIAR VENDA :::...\n");
				venda.codigo=incrementaCodigoVenda();
				recebeDadosVenda(&venda);
				cadastraVenda(venda);
				break;
				
			case 2:
				printf("... ::: LISTAR VENDAS :::...\n");
				listaVenda();
				break;
				
			case 3:
				printf("...::: CONSULTAR VENDAS POR CPF :::...\n");
				consultaVenda();
				break;
		}
		
		
	} while (opcao!=0);
	
	return 0;
}

void exibeMenuVenda(void){
	printf("\n  ..:: VENDA ::..\n\n");
	printf("  1 - INICIAR VENDAS\n");
	printf("  2 - LISTAR REMEDIOS VENDIDOS \n");
	printf("  3 - CONSULTAR VENDAS POR CPF\n");
	printf("  0 - VOLTAR\n"); // executado na "main.c" volta
	printf("\n\nEscolha uma opcao: ");	
}

int validaOpcaoMenuVenda(void){
	int op;
	do{
		fflush(stdin);
		scanf("%d", &op);
		if(op<0 || op>3)
			printf("\nOpcao invalida! \nDigite novamente: ");	
	}while(op<0 || op>3);
	system("cls");
	return op;
}


void exibeVenda(int cod){
	printf("\n...::: VENDA - %d :::...\n", cod);
}

void recebeDadosVenda(struct tVenda *venda){
	exibeVenda(venda->codigo);
	printf("\n DIGITE O CPF DO CLIENTE: \n");
	leValidaCpfCliente(venda->cpfCliente);
	listaProduto();
	printf("\n DIGITE O ID DO REMEDIO: \n");
	leValidaIdProduto(&venda->idProduto);
	printf("\nDIGITE A QUANTIDADE DE REMEDIOS DESEJADA: \n");
	scanf("%d", &venda->quantidade);
	
	venda->valorTotal = calculaTotal(venda->idProduto, venda->quantidade);
}

void leValidaIdProduto(int *idProduto){
	struct tProduto produto;
	int achei;
	FILE *arquivoProduto;
	do{
		scanf("%d", idProduto);
		arquivoProduto=fopen("produto.bin", "rb");
		achei=0;
		while(fread(&produto, sizeof(produto), 1, arquivoProduto))
			if(produto.flag!='*' && produto.cod == *idProduto)
				achei=1;
		if(!achei)
			printf("Produto invalido! Digite novamente: \n");
		fclose(arquivoProduto);
		
	} while (!achei);
}

void leValidaCpfCliente(char *cpfCliente[]){
	struct tCliente cliente;
	int achei;
	char opcao;
	FILE *arquivoCliente;
	do{
		fflush(stdin);
		gets(cpfCliente);
		fflush(stdin);
		arquivoCliente=fopen("cliente.bin", "rb");
		achei=0;
		while(fread(&cliente, sizeof(cliente), 1, arquivoCliente))
			if(cliente.flag!='*' && strcmp(cpfCliente, cliente.cpf)==0)
				achei=1;
		if(!achei){
			do{
				fflush(stdin);
				printf("\nCliente nao cadastrado! Deseja cadastra-lo? [S] - SIM / [N] - NAO");
				fflush(stdin);
				opcao=getchar();
				opcao=toupper(opcao);
				
			} while (opcao!='S' && opcao!='N');
			
			if(opcao=='S'){
				fflush(stdin);
				printf(" ---- CADASTRO DE CLIENTE ----\n");
				cliente.codigo=incrementaCodigoCliente();
				recebeDadosCliente(&cliente);
				cadastraCliente(cliente);
				
			}
			fflush(stdin);
			printf("Digite o CPF do cliente: \n");
		}
		fclose(arquivoCliente);
	} while (!achei);
	
		
}

float calculaTotal(int idEvento, int qtd){
	struct tProduto produto;
	float total;
	FILE *arquivoProduto;
	arquivoProduto = fopen("produto.bin", "rb");	
	while(fread(&produto, sizeof(produto), 1, arquivoProduto))
		if(produto.flag != '*' && produto.cod == idEvento)
				total = produto.valor*qtd;
	fclose(arquivoProduto);
	return total;
}


int incrementaCodigoVenda(void){
	int cod = 1;
	struct tVenda venda;
	FILE *arquivoVenda;
	arquivoVenda = fopen("venda.bin", "rb");
	if (arquivoVenda == NULL)	
		return cod;		
	while(fread(&venda, sizeof(venda), 1, arquivoVenda))	
		cod = venda.codigo;			
	fclose(arquivoVenda);			
	return ++cod;
}

void cadastraVenda(struct tVenda vd){
	int op;
	FILE *arquivoVenda;
	
	arquivoVenda = fopen("venda.bin", "ab");
	
	if (arquivoVenda == NULL)	
		mensagemErroVenda();
	else {
		system("cls");
			
		printf(" --- MOSTRANDO DADOS DA COMPRA  ---\n");
		clienteVenda(vd.cpfCliente);
		remedioVenda(vd.idProduto);
		printf("\n >>> Quantidade de remedios: %d", vd.quantidade);
		printf("\n >>> Valor Total: R$%.2f <<<", vd.valorTotal);
		do{
			printf("\n Deseja confirmar [s] - [n]:\n");
			fflush(stdin);
			op=getchar();
			op=toupper(op);
		} while(op != 'S' && op !='N');	
		if(op!='S'){
			printf("Compra cancelada!\n");
			printf("Aguarde...\n");
			Sleep(2000);			
		} else {
			printf("Compra confirmada!\n");
			/* MOSTRA DADOS DA COMPRA: NOME DO CLIENTE, NOME DO EVENTO,
			DATA DO EVENTO, VALOR PAGO NO TOTAL, QUANTIDADE COMPRADA 
			--- SALVAR EM ARQUIVO TXT --- */
			fwrite(&vd, sizeof(vd), 1, arquivoVenda);
			fclose(arquivoVenda);
			printf("Aguarde...\n");
			Sleep(2000);
			do{
				printf("\n\nDeseja gerar nota fiscal? [s] - [n]:\n");
				fflush(stdin);
				op=getchar();
				op=toupper(op);
			} while(op != 'S' && op !='N');
			if(op=='S')
				gerarNota(vd.codigo);	
		}
	}
}

void mostrarDadosProduto(struct tProduto prods){
	int i;
	printf("\n  Exibindo dados encontrados...\n");
	exibeProduto(prods.cod);
	printf("\n  Nome: %s", prods.nome);
	printf("\n  Quantidade disponivel: %d", prods.qtdDisp);
	printf("\n  Valor unitario: %.2f", prods.valor);
}

void remedioVenda(int idProduto){
	int cod, achei = 0;
	struct tProduto produto;
	FILE *arquivoProduto;		
	arquivoProduto = fopen("produto.bin", "rb");	
	if (arquivoProduto == NULL)	
		mensagemErroProduto();
	else {	
		while(fread(&produto, sizeof(produto), 1, arquivoProduto))
			if (idProduto == produto.cod && produto.flag != '*')
				mostrarDadosProduto(produto);
	}		
	fclose(arquivoProduto);
}	

void mensagemErroProduto(void){
	printf("ARQUIVO NAO PODE SER ABERTO\n");
	getch();
	
}

void mensagemErroVenda(){
	printf("\nErro na abertura do arquivo \n");
	getch();
}

void mensagemErroCliente(){
	printf("\nErro na abertura do arquivo \n");
	getch();
}


void clienteVenda(char cpfCliente[]){
	int cod, achei = 0;
	struct tCliente cliente;
	FILE *arquivoCliente;		
	arquivoCliente = fopen("cliente.bin", "rb");	
	if (arquivoCliente == NULL)	
		mensagemErroCliente();
	else {	
		while(fread(&cliente, sizeof(cliente), 1, arquivoCliente))
			if (strcmp(cpfCliente, cliente.cpf) == 0 && cliente.flag != '*')
				mostraDadosCliente(cliente);
	}		
	fclose(arquivoCliente);
}	

void listaVenda(void){
	struct tVenda venda;
	FILE *arquivoVenda;	
	arquivoVenda = fopen("venda.bin", "rb");	
	if (arquivoVenda == NULL)	
		mensagemErroVenda();
	else {	
		printf("COD |IdCliente  |IdProduto  |ValorTotal\n\n");
		while(fread(&venda, sizeof(venda), 1, arquivoVenda))
				printf("%4d|%12s|%11d|R$%11.2f\n\n", venda.codigo, venda.cpfCliente, venda.idProduto, venda.valorTotal);	
		mensagemContinuarVenda();	
	}		
	fclose(arquivoVenda);
}

void mensagemContinuarVenda(void){
	printf("\n\nDigite algo para continuar...");
	getch();
	system("cls");
}

void consultaVenda(void){
	int cod, achei = 0;
	char cpf[TAM];
	char op;
	struct tVenda venda;
	FILE *arquivoVenda;		
	arquivoVenda = fopen("venda.bin", "rb");	
	if (arquivoVenda == NULL)	
		mensagemErroVenda();
	else {	
		printf("\nDigite o cpf do cliente para ser consultado:");
		fflush(stdin);
		gets(cpf);
		while(fread(&venda, sizeof(venda), 1, arquivoVenda))
			if(strcmp(cpf, venda.cpfCliente) == 0){
				mostrarDadosVenda(venda);
				achei = 1;				
			}
		do{
			printf("\n\n>>Deseja gerar nota fiscal [S] - [N]:\n");
			fflush(stdin);
			op=getchar();
			op=toupper(op);
		} while(op != 'S' && op !='N');	
		if(op=='S'){
			printf("\n--Digite o codigo da venda: ");
			scanf("%d", &cod);
			gerarNota(cod);	
		}
		if (!achei)
			printf("\nErro: Venda nao encontrada.\n");
		mensagemContinuarVenda();
	}		
	fclose(arquivoVenda);
}

void gerarNota(int idVenda){
	#define VENDA_TXT "venda.txt"
	#define VENDA_BIN "venda.bin"
	struct tVenda venda;
	FILE *arquivoVendaBin;
	FILE *arquivoVendaTxt;
	arquivoVendaBin = fopen(VENDA_BIN, "rb");
	arquivoVendaTxt = fopen(VENDA_TXT, "w");	
	if(arquivoVendaBin == NULL)
		mensagemErroVenda();
	else {	
		fprintf(arquivoVendaTxt, "#### NOTA FISCAL ####\n");
		while(fread(&venda, sizeof(venda), 1, arquivoVendaBin)){
			if(idVenda==venda.codigo)
				fprintf(arquivoVendaTxt, "CLIENTE: %s\n\n Produto: %d\n", venda.cpfCliente, venda.idProduto);
		}
		fclose(arquivoVendaBin);
		fclose(arquivoVendaTxt);
		printf("\nGerando nota...\n");
		system(VENDA_TXT);
	}
	mensagemContinuarVenda();
}


void mostrarDadosVenda(struct tVenda vd){
	printf("\nExibindo dados encontrados...\n");
	exibeVenda(vd.codigo);
	printf("\nCPF Cliente: %s", vd.cpfCliente);
	printf("\nId Produto: %d", vd.idProduto);
	printf("\nQuantidade: %d", vd.quantidade);
	printf("\nValor Total: R$ %.2f", vd.valorTotal);
}




int principalLogin (void){
	struct tLogin login;
	int codigo;
	int opcao;
	do{
		exibeMenuLogin();
		opcao = validaOpcaoMenuLogin();		
		switch(opcao){
			case 1:
				printf("Cadastro de Logins\n\n");
				login.codigo = incrementaCodigoLogin();
				recebeDadosLogin(&login);
				cadastraLogin(login);
				break;	
			case 2:
				printf("Lista de Logins\n\n");
				listaLogin();
				break;		
			case 3:
				printf("Consulta de Logins\n");
				consultaLogin();
				break;
		}		
	} while (opcao!=0);
	return 0;
}
// ------------------ EXIBICAO ------------------
// Funcao Exibir Menu da Login
void exibeMenuLogin(void){
	printf("\n>> LOGIN <<\n\n");
	printf("1. CADASTRAR\n");
	printf("2. LISTAR\n");
	printf("3. CONSULTAR\n");
	printf("4. ALTERAR \n");
	printf("5. EXCLUIR TEMPORARIAMENTE\n");
	printf("6. EXCLUIR PERMANENTEMENTE\n");
	printf("7. EXPORTAR\n");
	printf("0. VOLTAR\n"); // executado na "main.c" volta
	printf("\n\nEscolha uma opcao: ");	
}
void exibeLogin(int cod){
	printf("\n>> LOGIN - COD: %d <<\n", cod);
}
void mensagemContinuarLogin(void){
	printf("\n\nDigite algo para continuar...", ARQ_LG);
	getch();
	system("cls");
}
void mensagemErroLogin(){
	printf("\nErro na abertura do arquivo %s \n", ARQ_LG);
	getch();
}
char mensagemExcluirLogin(void){
	char op;
	printf("\n\n*** ATENCAO: ESSA ACAO NAO PODERA SER DESFEITA.");
	printf("\n    TEM CERTEZA QUE DESEJA CONTINUAR?");
	do{
		printf("\n    Digite \"S\" se SIM ou \"N\" se NAO: ");
		fflush(stdin);
		op=getchar();
		op=toupper(op);
	} while(op != 'S' && op !='N');	
	return op;
}
// ------------------ Incrementa Codigo ------------------
int incrementaCodigoLogin(void){
	int cod = 1;
	struct tLogin login;
	FILE *arq_login;
	arq_login = fopen(ARQ_LG, "rb");
	if (arq_login == NULL)	
		return cod;		
	while(fread(&login, sizeof(login), 1, arq_login))	
		cod = login.codigo;			
	fclose(arq_login);			
	return ++cod;
}
// ------------------ Receber Codigo para consulta ------------------
int recebeCodigoLogin(void){
	int cod;
	printf("\nDigite o codigo para ser consultado:");
	scanf("%d", &cod);
	return cod;
}
// ------------------ Receber Dados ------------------
void recebeDadosLogin(struct tLogin *lg){
	exibeLogin(lg->codigo);
	printf("\n>> Usuario: ");
	leValidaStringLogin (&lg->usuario);
	printf("\n>> Senha: ");
	getsSenhaWallisson(&lg->senha);
	// ------------- Nivel -------------
	do{
		printf("\n\n***Nivel de acesso***\n 2-Gerente\n 3-Atendente");
		printf("\n\n>> Escolha um nivel: ");
		scanf("%d", &lg->nivel);
	}while(lg->nivel!=2 && lg->nivel!=3);	
}
// ------------------ Cadastrar ------------------
void cadastraLogin(struct tLogin lg){
	FILE *arq_login;
	
	arq_login = fopen(ARQ_LG, "ab");
	
	if (arq_login == NULL)	
		mensagemErroLogin();
	else {
		lg.lixo = ' ';
		fwrite(&lg, sizeof(lg), 1, arq_login);
	}
	mensagemContinuarLogin();	
	fclose(arq_login);
}
// ------------------ Listar ------------------
void listaLogin(void){
	struct tLogin login;
	FILE *arq_login;	
	arq_login = fopen(ARQ_LG, "rb");	
	if (arq_login == NULL)	
		mensagemErroLogin();
	else {	
		printf(" COD  USUARIO SENHA NIVEL \n\n");
		while(fread(&login, sizeof(login), 1, arq_login))
			//if(login.lixo != '*')
				printf(" %d %s  %s  %d\n\n", login.codigo, 
					login.usuario, login.senha, login.nivel);	
		mensagemContinuarLogin();	
	}		
	fclose(arq_login);
}
// ------------------ Consultar ------------------
void consultaLogin(void){
	int cod, achei = 0;
	struct tLogin login;
	FILE *arq_login;		
	arq_login = fopen(ARQ_LG, "rb");	
	if (arq_login == NULL)	
		mensagemErroLogin();
	else {	
		cod = recebeCodigoLogin();
		while(fread(&login, sizeof(login), 1, arq_login))
			if (cod == login.codigo && login.lixo != '*'){
				mostrarDadosLogin(login);
				achei = 1;
			}
		if (!achei)
			printf("\nErro: Login nao encontrada.\n");
		mensagemContinuarLogin();
	}		
	fclose(arq_login);
}
// ------------------ Alterar ------------------
void alteraLogin(void){
	int cod, achei = 0;
	struct tLogin login;
	FILE *arq_login;		
	arq_login = fopen(ARQ_LG, "r+b");	
	if (arq_login == NULL)	
		mensagemErroLogin();
	else {	
		cod = recebeCodigoLogin();
		while(fread(&login, sizeof(login), 1, arq_login))
			if (cod == login.codigo && login.lixo != '*'){
				mostrarDadosLogin(login);
				printf("\n\n*** ATENCAO: CODIGO NAO PODERA SER ALTERADO. ***\n");
				printf("Digite os novos dados:");	
				recebeDadosLogin(&login);
				achei = 1;
				/* posicionando o cursor no registro encontrado */
				fseek(arq_login, -sizeof(login), SEEK_CUR); 
				fwrite(&login, sizeof(login), 1, arq_login);			
				fseek(arq_login, 0, SEEK_CUR); // fixar ponteiro
				}
		if (!achei)
			printf("\nErro: Login nao encontrada.\n");
		mensagemContinuarLogin();
	}		
	fclose(arq_login);
}
// ------------------ Exclusao Temporaria ------------------
void excluiTempLogin(void){
	int cod, achei = 0;
	struct tLogin login;
	FILE *arq_login;		
	arq_login = fopen(ARQ_LG, "r+b");	
	if (arq_login == NULL)	
		mensagemErroLogin();
	else {	
		cod = recebeCodigoLogin();
		while(fread(&login, sizeof(login), 1, arq_login))
			if (cod == login.codigo && login.lixo != '*'){
				mostrarDadosLogin(login);
				achei = 1;
				if (mensagemExcluirLogin()=='S'){
					login.lixo = '*'; // adicionar um texcolor com vermelho aqui
					/* posicionando o cursor no registro encontrado */
					fseek(arq_login, -sizeof(login), SEEK_CUR); 
					fwrite(&login, sizeof(login), 1, arq_login);			
					fseek(arq_login, 0, SEEK_CUR); // fixar ponteiro
				}
			}
		if (!achei)
			printf("\nErro: Login nao encontrada.\n");
		mensagemContinuarLogin();
	}		
	fclose(arq_login);
}
// ------------------ Exclusao Permanente ------------------ 
void excluiPermanenteLogin(){
	struct tLogin login;
	FILE *arq_login_novo;
	FILE *arq_login_velho;	
	arq_login_velho = fopen(ARQ_LG, "rb");
	arq_login_novo = fopen(ARQ_LG_TMP, "wb");
	if (arq_login_velho == NULL)	
		mensagemErroLogin();
	else {	
		if (mensagemExcluirLogin()=='S'){
			while(fread(&login, sizeof(login), 1, arq_login_velho))
				if (login.lixo != '*')
					fwrite(&login, sizeof(login), 1, arq_login_novo);	
			fclose(arq_login_velho);
			fclose(arq_login_novo);				
			remove(ARQ_LG);
			rename(ARQ_LG_TMP, ARQ_LG);	
		}
	}		
}
// ------------------ Exporta para o Excel ------------------
void exportaExcelLogin(void){
	struct tLogin login;
	FILE *arq_login_bin;
	FILE *arq_login_texto;
	arq_login_bin = fopen(ARQ_LG, "rb");
	arq_login_texto = fopen(ARQ_LG_CSV, "w");	
	if (arq_login_bin == NULL || arq_login_texto == NULL)	
		mensagemErroLogin();
	else {	
		fprintf(arq_login_texto, " COD;  USUARIO; SENHA; NIVEL\n");
		while(fread(&login, sizeof(login), 1, arq_login_bin)){
			fprintf(arq_login_texto, " %d; %s;  %s;  %d\n", login.codigo, 
					login.usuario, login.senha, login.nivel);
		}
		fclose(arq_login_bin);
		fclose(arq_login_texto);
		printf("\nAbrindo Excel...\n");
		system(ARQ_LG_CSV);
	}
	mensagemContinuarLogin();
}
// ------------------ Mostrar Dados ------------------
void mostrarDadosLogin(struct tLogin lg){
	printf("\nExibindo dados encontrados...\n");
		exibeLogin(lg.codigo);
		printf("\nUsuario: %s", lg.usuario);
		printf("\nSenha: %d", lg.senha);
		printf("\nNivel: %s", lg.nivel);
}
// ------------------ VALIDACAO DE DADOS ------------------
// Funcao Validar opcao do MENU
int validaOpcaoMenuLogin(void){
	int op;
	do{
		scanf("%d", &op);
		if(op<0 || op>OPCOES)
			printf("\nOpcao invalida! \nDigite novamente: ");	
	}while(op<0 || op>OPCOES);
	system("cls");
	return op;
}
// Funcao que valida variaveis do tipo STRING 
void leValidaStringLogin (char *string[]){
	do{
		fflush(stdin);
		gets(string);
		  if(strlen(string)==0){
			printf("\n---->Digite algo:");
		} 		
	} while(strlen(string)==0);
}
//Valida senha
void getsSenhaWallisson(char *string[]){
	int pos;
	
	pos = 0;
	
	do{	
		string[pos] =  getch();
		if(string[pos]!=13)
			printf("*");	
	}while(string[pos++]!=13);

	string[pos-1]='\0';
}

//PROCESSAMENTO LOGIN
int logar(void){
	int achei = 0;
	char user[TAM], password[TAM];
	struct tLogin login;
	FILE *arq_login;
	do{		
		arq_login = fopen(ARQ_LG, "rb");	
		if (arq_login == NULL)	
			mensagemErroLogin();
		else {	
			printf("<<< LOGIN >>>");
			printf("\n>> Usuario: ");
			fflush(stdin);
			leValidaStringLogin (&user);
			printf("\n>> Senha: ");
			fflush(stdin);
			getsSenhaWallisson(&password);
			while(fread(&login, sizeof(login), 1, arq_login))
				if (login.lixo != '*' && strcmp(user, login.usuario) == 0 && strcmp(password, login.senha) == 0){
					achei = 1;
					printf("\n\nAguarde...\n");
					Sleep(2000);
					system("cls");
					return login.nivel;
				}
			if (!achei)
				printf("\nErro: Usuario ou Senha invalidos!\n");
		}		
		fclose(arq_login);
	}while(!achei);	
}
