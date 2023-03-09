#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct registoData {
	int ano, mes, dia;
} Data;

typedef struct registoPosicao {
	char palavra1[19], palavra2[19], palavra3[19];
} Posicao;

typedef struct registoContacto {
	char tipoContacto[10];
	char contacto[30];
} Contacto;

typedef struct registoEstado {
	float bateria;
	float autonomia;
	//Posicao posicao;				// posição do meio através de 3 palavras (what3words.com)
} Estado;

typedef struct registoMeio {
	int codigo;
	char tipo[50];
	//Estado estado;
	struct registoMeio* seguinte;	// endereço de memória para uma struct
} Meio;

typedef struct registoUtilizador {
	int codigo;
	char utilizador[20];			// Nome para iniciar sessão
	char nome[50];					// Nome normal
	char password[4];				// !!!! Tamanho temporário alterar depois de testes !!!! Ex: "123" + \n
	float saldo;
	Data dataNascimento;
	int NIF;
	char morada[50];
	//Contacto contacto[3];			// máximo de 3 contactos por cliente
	int gestor;
	struct registoUtilizador* seguinte;
} Utilizador;

typedef struct registoAluguer {
	int codigo;
	int codigoUtilizador;
	int codigoMeio;
	//Data dataInicio, dataFim;
	//Estado estadoInicial, estadoFinal;
	int ativo;
	float custo;
	struct registoAluguer* seguinte;
} Aluguer;



Utilizador* carregarUtilizador(Utilizador* inicio, int codigo, char utilizador[], char nome[], char password[], float saldo, Data dataNascimento, int NIF, char morada[], int gestor) {
	int i0 = 0;
	int a = dataNascimento.ano;
	int i1 = 1; 
	
	Utilizador* novo = malloc(sizeof(struct registoUtilizador));
	if (novo != NULL)
	{
		novo->codigo = codigo;
		strcpy(novo->utilizador, utilizador);
		strcpy(novo->nome, nome);
		strcpy(novo->password, password);
		novo->saldo = saldo;
		novo->dataNascimento.ano = dataNascimento.ano;
		novo->dataNascimento.mes = dataNascimento.mes;
		novo->dataNascimento.dia = dataNascimento.dia;
		novo->NIF = NIF;
		strcpy(novo->morada, morada);
		novo->gestor = gestor;
		novo->seguinte = inicio;
		return(novo);
	}

}

Utilizador* lerUtilizadores()
{
	FILE* fp;
	int fcodigo;
	char futilizador[20];
	char fnome[50];
	char fpassword[4];
	float fsaldo;
	Data fdataNascimento;
	int fNIF;
	char fmorada[50];
	int fgestor;

	Utilizador* aux = NULL;

	fp = fopen("dados/utilizadores.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			int check = fscanf(fp, "%d;%[^;];%[^;];%[^;];%f;%d-%d-%d;%d;%[^;];%d\n", &fcodigo, futilizador, fnome, fpassword, &fsaldo, &fdataNascimento.ano, &fdataNascimento.mes, &fdataNascimento.dia, &fNIF, fmorada, &fgestor);
			if (check != 11) {
				printf("\n\n\n////////////////// ERRO //////////////////\n\n\n");
				return NULL;
			}
			else {
				aux = carregarUtilizador(aux, fcodigo, futilizador, fnome, fpassword, fsaldo, fdataNascimento, fNIF, fmorada, fgestor);
			}
		}
		fclose(fp);
	}
	return(aux);
}

#pragma region FreeRegion

void freeUtilizador(Utilizador* inicio) {
	Utilizador* aux;

	while (inicio != NULL)
	{
		aux = inicio;
		inicio = inicio->seguinte;
		free(aux);
	}
}

void freeMeio(Meio* inicio) {
	Meio* aux;

	while (inicio != NULL)
	{
		aux = inicio;
		inicio = inicio->seguinte;
		free(aux);
	}
}

void freeAluguer(Aluguer* inicio) {
	Aluguer* aux;

	while (inicio != NULL)
	{
		aux = inicio;
		inicio = inicio->seguinte;
		free(aux);
	}
}

#pragma endregion

void listarUtilizador(Utilizador* inicio)
{
	while (inicio != NULL)
	{
		printf("%d %s %.2f %d-%d-%d\n", inicio->codigo, inicio->nome, inicio->saldo, inicio->dataNascimento.dia, inicio->dataNascimento.mes, inicio->dataNascimento.ano);
		printf("////////////////////////////////////////////////////////////////\n");
		inicio = inicio->seguinte;
	}
}


int login(Utilizador* inicio, int *utilizadorAtual, int* gestor, char* nomeAtual) {
	
	Utilizador* aux;
	int sucesso=0;
	char utilizador[20], password[4];

	while(!sucesso){

		printf("Utilizador:\n");
		scanf("%[^\n]s", utilizador);
		scanf("%*c");					// !!! Se possível ver outra solução para não passar à frente !!!
		printf("Password:\n");
		scanf("%3s", password);			// !!! A ler os primeiros 3 caracteres da passe introduzida alterar na versão final !!!
		scanf("%*c");

		aux = inicio;
		while (aux != NULL)
		{
			int a = 0;
			if (!strcmp(utilizador, aux->utilizador) && !strcmp(password, aux->password))
			{
				*utilizadorAtual = aux->codigo;
				*gestor = aux->gestor;
				strcpy(nomeAtual, aux->nome);

				sucesso = 1;
				aux = NULL;
			}
			else {
				aux = aux->seguinte;
			}
		}
		system("cls");
		if (sucesso == 0)
			printf("\n------ERRO------\n\n");
	}

	return 1;
}

int menuGestor(int utilizadorAtual, char* nomeAtual) {

	Utilizador* utilizadores = NULL;
	int opcao, sucesso = 0;

	while (sucesso != 1) {
		system("cls");
		printf(" %s -- Menu de Gestor:\n\n", nomeAtual);
		printf("1. Alterar Dados Pessoais\n\n --- Meios\n2. Listar Meios\n3. Editar Meio\n4. Apagar Meio\n\n --- Utilizadores\n5. Listar Utilizadores\n6. Adicionar Utilizador\n7. Editar Utilizador\n8. Apagar Utilizador\n\n --- Alugueres\n9. Listar Alugueres\n\n10. Sair\n\n-> ");

		scanf("%d", &opcao);
		scanf("%*c");
		switch (opcao)
		{
		case 1:
			printf("\n\nOperação específica\n\n");
			break;
		case 2:
			printf("\n\nOperação específica\n\n");
			break;
		case 3:
			printf("\n\nOperação específica\n\n");
			break;
		case 4:
			printf("\n\nOperação específica\n\n");
			break;
		case 5:
			utilizadores = lerUtilizadores();
			listarUtilizador(utilizadores);
			sucesso = 1;
			break;
		case 6:
			printf("\n\nOperação específica\n\n");
			break;
		case 7:
			printf("\n\nOperação específica\n\n");
			break;
		case 8:
			printf("\n\nOperação específica\n\n");
			break;
		case 9:
			printf("\n\nOperação específica\n\n");
			break;
		case 10:
			sucesso = 1;
			break;
		}
	}


	return 0;
}

int menu(int utilizadorAtual, char* nomeAtual) {

	printf(" %s -- Menu:\n\n", nomeAtual);
	printf("1. Alterar Dados Pessoais\n2. Listar Meios Disponiveis\n3. Alugar Meio\n\n0. Sair");
	//scanf();

	/*switch (utilizadorAtual)
	{
	case 1:
		printf("\n\nOperação específica\n\n");
	default:
		printf("\n\nOperação geral\n\n");
		break;
	}*/

	return 0;
}

main() {

	Utilizador* utilizadores = NULL, *aux;			// Lista ligada vazia 
	int utilizadorAtual = 0, gestor = 0;		//Dados da sessão
	char nomeAtual[50];

	utilizadores = lerUtilizadores();
	//login(utilizadores, &utilizadorAtual, &nomeAtual, &gestor);
	login(utilizadores, &utilizadorAtual, &gestor, &nomeAtual);
	freeUtilizador(utilizadores);

	if (utilizadorAtual) {
		if (gestor == 1) {
			menuGestor(utilizadorAtual, nomeAtual);
		}
		else {
			menu(utilizadorAtual, nomeAtual);
		}
	}

	//listarUtilizador(utilizadores);
}