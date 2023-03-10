#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct registoData {
	int ano, mes, dia;
} Data;

typedef struct registoPosicao {
	char palavras[57];
} Posicao;

typedef struct registoContacto {
	char tipoContacto[10];
	char contacto[30];
} Contacto;

typedef struct registoEstado {
	float bateria;
	float autonomia;
	Posicao posicao;				// posição do meio através de 3 palavras (what3words.com)
} Estado;

typedef struct registoMeio {
	int codigo;
	char tipo[21];
	Estado estado;
	float preco;					// preco por minuto
	int historico;
	struct registoMeio* seguinte;	// endereço de memória para uma struct
} Meio;

typedef struct registoUtilizador {
	int codigo;
	char utilizador[11];			// Nome para iniciar sessão
	char nome[41];					// Nome normal
	char password[11];				// Ex: "12ab567890" + \n
	float saldo;
	Data dataNascimento;
	int NIF;
	char morada[31];
	//Contacto contacto[3];			// máximo de 3 contactos por cliente
	int gestor;
	int historico;					// verifica se foi "eliminado"
	struct registoUtilizador* seguinte;
} Utilizador;

typedef struct registoAluguer {
	int codigo;
	int codigoUtilizador;
	int codigoMeio;
	//Data dataInicio, dataFim;
	//Estado estadoInicial, estadoFinal;
	int ativo;
	float custo;					// preço total do aluguer
	struct registoAluguer* seguinte;
} Aluguer;

const char* checkSN(int i) {

	switch (i)
	{
	case 1:
		return "Sim";
	case 0:
		return "Nao";
	}
}

#pragma region libertarMemoria

void freeUtilizador(Utilizador* inicio) {
	Utilizador* aux;

	while (inicio != NULL)
	{
		aux = inicio;
		inicio = inicio->seguinte;
		free(aux);
	}
	inicio = NULL;
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

#pragma region carregarDados

Utilizador* carregarUtilizador(Utilizador* inicio, int codigo, char utilizador[], char nome[], char password[], float saldo, Data dataNascimento, int NIF, char morada[], int gestor, int historico) {
	
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
		novo->historico = historico;

		novo->seguinte = inicio;
		return(novo);
	}
}

Meio* carregarMeio(Meio* inicio, int codigo, char tipo[], Estado estado, float preco, int historico) {

	Meio* novo = malloc(sizeof(struct registoMeio));

	if (novo != NULL)
	{
		novo->codigo = codigo;
		strcpy(novo->tipo, tipo);
		novo->estado.bateria = estado.bateria;
		novo->estado.autonomia = estado.autonomia;
		strcpy(novo->estado.posicao.palavras, estado.posicao.palavras);
		novo->preco = preco;
		novo->historico = historico;

		novo->seguinte = inicio;
		return(novo);
	}
}

Aluguer* carregarAluguer(Aluguer* inicio, int codigo, int codigoUtilizador, int codigoMeio, int ativo, float custo) {

	Aluguer* novo = malloc(sizeof(struct registoAluguer));

	if (novo != NULL)
	{
		novo->codigo = codigo;
		novo->codigoUtilizador = codigoUtilizador;
		novo->codigoMeio = codigoMeio;
		novo->ativo = ativo;
		novo->custo = custo;

		novo->seguinte = inicio;
		return(novo);
	}
}

#pragma endregion

#pragma region lerDocumentos

Utilizador* lerUtilizadores()
{
	FILE* fp;

	int codigo, NIF, gestor, historico;
	char utilizador[11], nome[41], password[11], morada[31];
	float saldo;
	Data dataNascimento;

	Utilizador* aux = NULL;

	fp = fopen("dados/utilizadores.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			int check = fscanf(fp, "%d;%[^;];%[^;];%[^;];%f;%d-%d-%d;%d;%[^;];%d;%d\n", &codigo, utilizador, nome, password, &saldo, &dataNascimento.ano, &dataNascimento.mes, &dataNascimento.dia, &NIF, morada, &gestor, &historico);
			if (check != 12) {
				printf("\n\n\nErro a carregar dados dos utilizadores\n\n\n");
				return NULL;
			}
			else {
				aux = carregarUtilizador(aux, codigo, utilizador, nome, password, saldo, dataNascimento, NIF, morada, gestor, historico);
			}
		}
		fclose(fp);
	}
	return(aux);
}

Meio* lerMeios()
{
	FILE* fp;

	int codigo, historico;
	char tipo[21];
	float preco;
	Estado estado;

	Meio* aux = NULL;

	fp = fopen("dados/meios.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			int check = fscanf(fp, "%d;%[^;];%f;%f;%[^;];%f;%d\n", 
				&codigo, tipo, &estado.bateria, &estado.autonomia, 
				&estado.posicao.palavras, 
				&preco, &historico);
			
			if (check != 7) {
				printf("\n\n\nErro a carregar dados dos meios\n\n\n");
				return NULL;
			}
			else {
				aux = carregarMeio(aux, codigo, tipo, estado, preco, historico);
			}
		}
		fclose(fp);
	}
	return(aux);
}

Aluguer* lerAlugueres()
{
	FILE* fp;

	int codigo, codigoUtilizador, codigoMeio, ativo;
	float custo;

	Aluguer* aux = NULL;

	fp = fopen("dados/alugueres.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			int check = fscanf(fp, "%d;%d;%d;%d;%f\n",
				&codigo, &codigoUtilizador, &codigoMeio, &ativo, &custo);

			if (check != 5) {
				printf("\n\n\nErro a carregar dados dos alugueres\n\n\n");
				return NULL;
			}
			else {
				aux = carregarAluguer(aux, codigo, codigoUtilizador, codigoMeio, ativo, custo);
			}
		}
		fclose(fp);
	}
	return(aux);
}

#pragma endregion

#pragma region listarDados

void listarUtilizador(Utilizador* inicio)
{
	printf("==================================================================================================================================================\n");
	printf("Codigo | Utilizador | Nome                                     | Morada                         | Data Nasc. | NIF       | Saldo  | Gestor | Hist.\n");
	printf("=======|============|==========================================|================================|============|===========|========|========|======\n");

	while (inicio != NULL)
	{
		printf("%6d | %-10s | %-40s | %-30s | %2d-%2d-%4d | %9d | %6.2f | %-6s | %-5s\n", 
			inicio->codigo, inicio->utilizador, inicio->nome, inicio->morada, 
			inicio->dataNascimento.dia, inicio->dataNascimento.mes, inicio->dataNascimento.ano, 
			inicio->NIF, inicio->saldo, checkSN(inicio->gestor), checkSN(inicio->historico));
		inicio = inicio->seguinte;
	}
	printf("==================================================================================================================================================\n");
}

void listarMeio(Meio* inicio, int gestor)
{
	if (gestor == 1) {
		printf("==============================================================================================================================\n");
		printf("Codigo | Tipo                 | Bateria | Autonomia | Localizacao                                              | Preco | Hist.\n");
		printf("=======|======================|=========|===========|==========================================================|=======|======\n");

		while (inicio != NULL)
		{
			printf("%6d | %-20s | %7.2f | %9.2f | %-56s | %5.2f | %-5s\n",
				inicio->codigo, inicio->tipo, inicio->estado.bateria, inicio->estado.bateria,
				inicio->estado.posicao.palavras,
				inicio->preco, checkSN(inicio->historico));
			inicio = inicio->seguinte;
		}
		printf("==============================================================================================================================\n");
	}
	else {
		printf("======================================================================================================================\n");
		printf("Codigo | Tipo                 | Bateria | Autonomia | Localizacao                                              | Preco\n");
		printf("=======|======================|=========|===========|==========================================================|======\n");

		while (inicio != NULL)
		{
			if (inicio->historico == 0) {
				printf("%6d | %-20s | %7.2f | %9.2f | %-56s | %5.2f\n",
					inicio->codigo, inicio->tipo, inicio->estado.bateria, inicio->estado.bateria,
					inicio->estado.posicao.palavras,
					inicio->preco);
			}
			inicio = inicio->seguinte;
		}
		printf("======================================================================================================================\n");

	}
}

void listarAluguer(Aluguer* inicio, Utilizador* utilizadores, Meio* meios, int utilizadorAtual, int gestor)
{
	char utilizador[11], tipo[21];

	printf("=============================================================================\n");
	printf("Codigo | Utilizador | C. Ut. | Tipo de Meio         | C. Me. | Ativo | Custo \n");
	printf("=======|============|========|======================|========|=======|=======\n");

	while (inicio != NULL)
	{
		while (utilizadores != NULL){
				if (inicio->codigoUtilizador == utilizadores->codigo) {
					strcpy(utilizador, utilizadores->utilizador);
					utilizadores = NULL;
				}
				else {
					utilizadores = utilizadores->seguinte;
				}
			}
		while (meios != NULL){
				if (inicio->codigoMeio == meios->codigo) {
					strcpy(tipo, meios->tipo);
					meios = NULL;
				}
				else {
					meios = meios->seguinte;
				}
			}

		if (gestor == 1) {
			printf("%6d | %-10s | %6d | %-20s | %6d | %5s | %6.2f\n",
				inicio->codigo, utilizador, inicio->codigoUtilizador, tipo, inicio->codigoMeio,
				checkSN(inicio->ativo), inicio->custo);
		}
		else {
			if (inicio->codigoUtilizador == utilizadorAtual) {
				printf("%6d | %-10s | %6d | %-20s | %6d | %5s | %6.2f\n",
					inicio->codigo, utilizador, inicio->codigoUtilizador, tipo, inicio->codigoMeio,
					checkSN(inicio->ativo), inicio->custo);
			}
		}
		inicio = inicio->seguinte;
	}
	printf("=============================================================================\n");
}

#pragma endregion

void login(Utilizador* inicio, int *utilizadorAtual, int* gestor, char* nomeAtual) {
	
	Utilizador* aux;
	int sucesso=0;
	char utilizador[16], password[11];

	while(!sucesso){

		printf("Utilizador:\n");
		scanf("%15s", utilizador);
		scanf("%*c");					// !!! Se possível ver outra solução para não passar à frente !!!
		printf("Password:\n");
		scanf("%10s", password);			// !!! A ler os primeiros 3 caracteres da passe introduzida alterar na versão final !!!
		scanf("%*c");

		aux = inicio;
		while (aux != NULL)
		{
			if (!strcmp(utilizador, aux->utilizador) && !strcmp(password, aux->password) && aux->historico == 0)
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

	return;
}

int menuGestor(int utilizadorAtual, char* nomeAtual) {

	Utilizador* utilizadores = NULL;
	Meio* meios = NULL;
	Aluguer* alugueres = NULL;
	int opcao, sucesso = 0;

	while (sucesso != 1) {
		system("cls");
		printf(" %s -- Menu de Gestor:\n\n", nomeAtual);
		printf("1. Alterar Dados Pessoais\n\n --- Meios\n2. Listar Meios\n3. Adicionar Meio\n4. Editar Meio\n5. Apagar Meio\n\n --- Utilizadores\n6. Listar Utilizadores\n7. Adicionar Utilizador\n8. Editar Utilizador\n9. Apagar Utilizador\n\n --- Alugueres\n10. Listar Alugueres\n11. Editar Aluguer\n\n0. Sair\n\n-> ");

		scanf("%d", &opcao);
		scanf("%*c");
		switch (opcao)
		{
		case 0:
			sucesso = 1;
			break;
		case 1:
			printf("\n\nOperação específica\n\n");
			break;
		case 2:
			meios = lerMeios();
			listarMeio(meios, 1);
			freeMeio(meios);
			meios = NULL;
			sucesso = 1;
			break;
		case 3:
			printf("\n\nOperação específica\n\n");
			break;
		case 4:
			printf("\n\nOperação específica\n\n");
			break;
		case 5:
			printf("\n\nOperação específica\n\n");
			break;
		case 6:
			utilizadores = lerUtilizadores();
			listarUtilizador(utilizadores);
			freeUtilizador(utilizadores);
			utilizadores = NULL;
			sucesso = 1;
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
			meios = lerMeios();
			utilizadores = lerUtilizadores();
			alugueres = lerAlugueres();
			listarAluguer(alugueres, utilizadores, meios, utilizadorAtual, 1);

			freeUtilizador(utilizadores);
			freeMeio(meios);
			freeAluguer(alugueres);
			utilizadores = NULL;
			meios = NULL;
			alugueres = NULL;

			sucesso = 1;
			break;
		case 11:
			printf("\n\nOperação específica\n\n");
			break;
		}
	}
	return 0;
}

int menu(int utilizadorAtual, char* nomeAtual) {

	Utilizador* utilizadores = NULL;
	Meio* meios = NULL;
	Aluguer* alugueres = NULL;
	int opcao, sucesso = 0;

	while (sucesso != 1) {
		system("cls");
		printf(" %s -- Menu:\n\n", nomeAtual);
		printf("1. Alterar Dados Pessoais\n2. Listar Meios Disponiveis\n3. Alugar Meio\n4. Historico\n\n0. Sair\n\n-> ");

		scanf("%d", &opcao);
		scanf("%*c");
		switch (opcao)
		{
		case 0:
			sucesso = 1;
			break;
		case 1:
			printf("\n\nOperação específica\n\n");
			break;
		case 2:
			meios = lerMeios();
			listarMeio(meios, 1);
			freeMeio(meios);
			meios = NULL;
			sucesso = 1;
			break;
		case 4:
			meios = lerMeios();
			utilizadores = lerUtilizadores();
			alugueres = lerAlugueres();
			listarAluguer(alugueres, utilizadores, meios, utilizadorAtual, 1);

			freeUtilizador(utilizadores);
			freeMeio(meios);
			freeAluguer(alugueres);
			utilizadores = NULL;
			meios = NULL;
			alugueres = NULL;

			sucesso = 1;
			break;
		}
	}

	return 0;
}

main() {

	Utilizador* utilizadores = NULL, *aux;			// Lista ligada vazia 
	int utilizadorAtual = 0, gestor = 0;			//Dados da sessão
	char nomeAtual[41];

	utilizadores = lerUtilizadores();
	if (utilizadores != NULL && 1 == 0) {
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
	}

	//testes

	utilizadorAtual = 5;
	gestor = 0;

	//listarUtilizador(utilizadores);

	Meio* meios = NULL;
	meios = lerMeios();
	Aluguer* alugueres = NULL;
	alugueres = lerAlugueres();
	listarAluguer(alugueres, utilizadores, meios, utilizadorAtual, gestor);
	//int aaaa = 0;
}