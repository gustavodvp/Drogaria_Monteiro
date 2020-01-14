// ------------------- colocar limpador de tela nas funcoes -----------------------
/* Bibliotecas */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

/* Prototipos */
void exibeMenuLogin(void);
void exibeLogin(int);
int validaOpcaoMenuLogin(void);
void recebeDadosLogin();
int incrementaCodigoLogin(void);
void leValidaStringLogin (char*);
void cadastraLogin();
void mensagemContinuar(void);
void mensagemErroArquivo(void);
void listaLogin(void);
void mostraDadosLogin();
int recebeCodigoLogin(void);
void consultaLogin(void);
void alteraLogin(void);
void opcaoExcluir(void);
char mensagemExcluirLogin(void);
void excluirLoginTemp(void);
void excluirLoginPermanente(void);
void exportarExcel(void);
void getsSenha(char*);

/* estrutura de registro */
struct tLogin{
	int codigo;
	char usuario[20];
	char senha[13];
	char flag;
};

/* Inicio */

int main (void){
	setlocale(LC_ALL, "Portuguese");
	FILE *arquivoLogin;
	struct tLogin login;
	int codigo;
	int opcao;
	
	do{
		exibeMenuLogin();
		opcao=validaOpcaoMenuLogin();
		
		switch(opcao){
			case 1: 
				printf("... CADASTRO ...\n");
				login.codigo=incrementaCodigoLogin();
				recebeDadosLogin(&login);
				cadastraLogin(login);
				mensagemContinuar();
				break;
			case 2:
				printf("... LISTANDO LOGINS ...\n");
				listaLogin();
				break;
			case 3:
				printf("... CONSULTAR ...\n");
				consultaLogin();
				break;
				
			case 4:
				printf("... ALTERAR CADASTRO ...\n");
				alteraLogin();
				break;
			case 5:
				printf("... EXCLUIR LOGIN...\n");
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

// Funcao Exibir Menu da Login
void exibeMenuLogin(void){
	printf("\n  ..:: LOGIN ::..\n\n");
	printf("  1 - CADASTRAR \n");
	printf("  2 - LISTAR\n");
	printf("  3 - CONSULTAR POR CODIGO\n");
	printf("  4 - ALTERAÇÃO DO CADASTRO\n");
	printf("  5 - EXCLUIR DO CADASTRO\n");
	printf("  6 - EXPORTAR\n");
	printf("  0 - VOLTAR\n"); 
	printf("\n\n  ESCOLHA UMA OPÇÃO: ");	
}

// Gerando codigo aleatorio do login (chave primaria)
void exibeLogin(int cod){
	printf("\n...:: LOGIN - %d ::... \n", cod);
}

// Funcao Validar opcao do MENU
int validaOpcaoMenuLogin(void){
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
void recebeDadosLogin(struct tLogin *cl){
	exibeLogin(cl->codigo);
	printf("\nUsuário: ");
	leValidaStringLogin (cl->usuario);
	printf("\nSenha: ");
	getsSenha (cl->senha);
	
}

// incrementando codigo sequencial
int incrementaCodigoLogin(void){
	int cod = 1;
	struct tLogin login;
	FILE *arquivoLogin;
	arquivoLogin = fopen("login.bin", "rb");
	if (arquivoLogin == NULL)	
		return cod;		
	while(fread(&login, sizeof(login), 1, arquivoLogin))	
		cod = login.codigo;			
	fclose(arquivoLogin);			
	return ++cod;
}

// Funcao que valida variaveis do tipo STRING 
void leValidaStringLogin (char *string){
	do{
		fflush(stdin);
		gets(string);
		  if(strlen(string)==0){
			printf("\n-> Digite algo:");
		} 		
	} while(strlen(string)==0);
}

/* cadastrando novo login */
void cadastraLogin(struct tLogin cl){
	FILE *arquivoLogin;
	
	arquivoLogin = fopen("login.bin", "ab");
	
	if (arquivoLogin == NULL)	
		mensagemErroArquivo();
	else {
		fwrite(&cl, sizeof(cl), 1, arquivoLogin);
	}
	fclose(arquivoLogin);
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

// listagem de logins que nao estao excluidos
void listaLogin(void){
	struct tLogin login;
	FILE *arquivoLogin;
	arquivoLogin=fopen("login.bin", "rb");
	if(arquivoLogin==NULL)
		mensagemErroArquivo();
	else {
		printf("COD. | USUÁRIO                 | SENHA \n");
		while(fread(&login, sizeof(login), 1, arquivoLogin))
		if(login.flag!='*')
			printf("%c%4d%18s%19s\n", login.flag, login.codigo, login.usuario, login.senha);
		
		mensagemContinuar();
	}
	fclose(arquivoLogin);
	
} 

// mostrando dados do login - funcoa usada dentro de outras funcoes 
// nao mexer!.
void mostrarDadosLogin(struct tLogin cl){
	printf("\nExibindo dados encontrados...\n");
	exibeLogin(cl.codigo);
	printf("\n  Usuário: %s", cl.usuario);
	printf("\n  Senha: %s", cl.senha);
}

// recebendo codigo
int recebeCodigoLogin(void){
	int cod;
	printf("\nDigite o codigo para ser consultado:");
	scanf("%d", &cod);
	return cod;
}

// consultando login nos arquivos e registros
void consultaLogin(void){
	int cod, achei=0;
	struct tLogin login;
	FILE *arquivoLogin;
	arquivoLogin=fopen("login.bin", "rb");
	if(arquivoLogin==NULL)
		mensagemErroArquivo();
	
	else {
		cod=recebeCodigoLogin();
		while(fread(&login, sizeof(login), 1, arquivoLogin))
			if(cod == login.codigo){
				mostrarDadosLogin(login);
				achei=1;
				
			}
		if(!achei)
			printf("ERRO: Login não encontrado. \n");
			
		mensagemContinuar();
	}
}

// fazendo alteracao do cadastro do login buscado
void alteraLogin(void){
	int cod, achei=0;
	struct tLogin login;
	FILE *arquivoLogin;
	arquivoLogin=fopen("login.bin", "r+b");
	if(arquivoLogin==NULL)
		mensagemErroArquivo();
	else {
		cod=recebeCodigoLogin();
		while(fread(&login, sizeof(login), 1, arquivoLogin))
			if(cod==login.codigo){
				mostrarDadosLogin(login);
				printf("\n\n*** ATENCAO: CODIGO NAO PODERA SER ALTERADO!. ***\n\n");
				printf("\nDigite os novos dados: ");
				recebeDadosLogin(&login);
				achei=1;
				fseek(arquivoLogin, -sizeof(login), SEEK_CUR); // posicionando ponteiro no registro
				fwrite(&login, sizeof(login), 1, arquivoLogin);
				fseek(arquivoLogin, 0, SEEK_CUR); // fixando ponteiro
			}
			if(!achei)
				printf("ERRO: Login não encontrado.\n");
			
			mensagemContinuar();
			
	}
		
	fclose(arquivoLogin);
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
		excluirLoginPermanente();
	if(opcao==2)
		excluirLoginTemp();
	
}

// mensagem de warning 
char mensagemExcluirLogin(void){
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

void excluirLoginTemp(void){
	int cod, achei=0;
	struct tLogin login;
	FILE *arquivoLogin;
	arquivoLogin=fopen("login.bin", "r+b");
	if (arquivoLogin==NULL)
		mensagemErroArquivo();
	else {
		cod = recebeCodigoLogin ();
		while (fread(&login, sizeof(login), 1, arquivoLogin))
			if(cod == login.codigo && login.flag!='*'){
				mostrarDadosLogin(login);
				achei=1;
				if(mensagemExcluirLogin()=='S'){
					login.flag = '*'; 
					fseek(arquivoLogin, -sizeof(login), SEEK_CUR);
					fwrite(&login, sizeof(login), 1, arquivoLogin);
					fseek(arquivoLogin, 0, SEEK_CUR);
					
				}
			}
			if(!achei)
				printf("\n ERRO: Login não encontrado. \n");
				mensagemContinuar();
	}
	fclose(arquivoLogin);
	
}

// exclusao do arquivo todo

void excluirLoginPermanente(void){
	struct tLogin login;
	FILE *arquivoLogin;
	FILE *arquivoLoginTemp;
	arquivoLogin=fopen("login.bin", "r+b");
	arquivoLoginTemp=fopen("loginTemp.bin", "wb");
	if(arquivoLogin==NULL)
		mensagemErroArquivo();
	else {
		if(mensagemExcluirLogin()=='S'){
			while(fread(&login, sizeof(login), 1, arquivoLogin))
				if(login.flag!='*')
					fwrite(&login, sizeof(login), 1, arquivoLoginTemp);
				fclose(arquivoLogin);
				fclose(arquivoLoginTemp);
				remove(arquivoLogin);
				rename(arquivoLoginTemp, arquivoLogin); //erro aqui 
				
		}
	}
}

// exportacao em arquivo de valores
void exportarExcel(void){
	struct tLogin login;
	FILE *arquivoLoginBin;
	FILE *arquivoLoginTxt;
	arquivoLoginBin=fopen("login.bin", "rb");
	arquivoLoginTxt=fopen("login.csv", "w");
	if(arquivoLoginBin==NULL || arquivoLoginTxt==NULL)
		mensagemErroArquivo();
	
	else{
		fprintf(arquivoLoginTxt, "COD;USUÁRIO;SENHA;\n");
		while (fread(&login, sizeof(login), 1, arquivoLoginBin)){
			// adicionar flag aqui
			fprintf(arquivoLoginTxt, "%d;%s;%s\n", login.codigo, login.usuario, login.senha);
		}
		fclose(arquivoLoginBin);
		fclose(arquivoLoginTxt);
		printf(" *** ABRINDO EXCEL.... *** \n");
		system(arquivoLoginTxt); //erro aqui 
	}
	
	mensagemContinuar();
}

//Valida senha
void getsSenha(char *string){
	int pos=0;
	
	do{
		string[pos] = getch();
			if(string[pos]!=13)
				printf("*");
	}while(string[pos++]!=13);
	
	string[pos-1]='\0';
}
