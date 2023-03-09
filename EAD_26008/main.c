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



Utilizador* inserirUtilizador(Utilizador* inicio, int codigo, char utilizador[], char nome[], char password[], float saldo, Data dataNascimento, int NIF, char morada[], int gestor) {
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
				aux = inserirUtilizador(aux, fcodigo, futilizador, fnome, fpassword, fsaldo, fdataNascimento, fNIF, fmorada, fgestor);
			}
		}
		fclose(fp);
	}
	return(aux);
}

void listarUtilizador(Utilizador* inicio)
{
	while (inicio != NULL)
	{
		printf("%d %s %.2f %d-%d-%d\n", inicio->codigo, inicio->nome, inicio->saldo, inicio->dataNascimento.dia, inicio->dataNascimento.mes, inicio->dataNascimento.ano);
		printf("////////////////////////////////////////////////////////////////\n");
		inicio = inicio->seguinte;
	}
}


int login(Utilizador* inicio, int *utilizadorAtual, char *nomeAtual, int* gestor) {

	int sucesso=0;
	char utilizador[20], password[4];

	while(!sucesso){

		printf("Utilizador:\n");
		scanf("%[^\n]s", utilizador);
		scanf("%*c");					// !!! Se possível ver outra solução para não passar à frente !!!
		printf("Password:\n");
		scanf("%3s", password);			// !!! A ler os primeiros 3 caracteres da passe introduzida alterar na versão final !!!
		scanf("%*c");

		while (inicio != NULL)
		{
			int a = 0;
			if (!strcmp(utilizador, inicio->utilizador) && !strcmp(password, inicio->password))
			{
				*gestor = inicio->gestor;
				*utilizadorAtual = inicio->codigo;

				strcpy(nomeAtual, inicio->nome);
				sucesso = 1;
			}
			inicio = inicio->seguinte;
		}
		system("cls");
		if (sucesso == 0)
			printf("\n------ERRO------\n\n");
	}

	printf("\n------LOGIN------\n\n");

	return 1;
}

main() {
	//Fazer com listas ligadas porque ocupam menos espaço na memória, porque não é necessário dedicar memória ao definir a sruct
	//cada "meio" regista o endereço do próximo "meio"

	//Carregar utilizadores
	//Fazer login
	//Carregar

	Utilizador* utilizadores = NULL;			// Lista ligada vazia 
	int utilizadorAtual = 0, gestor = 0;		//Dados da sessão
	char nomeAtual[50] = {'t', 'e', 's', 't', 'e', '\0'};

	utilizadores = lerUtilizadores();
	login(utilizadores, &utilizadorAtual, &nomeAtual, &gestor);

	printf("\nNome : %s\n\n", nomeAtual);

	//listarUtilizador(utilizadores);



	/*int utilizadorAtual = 0;
	int checkGestor = login(utilizadorAtual);
	menu(checkGestor, utilizadorAtual);*/
}

int menu(int checkGestor, int utilizadorAtual) {
	switch (checkGestor)
	{
	case 1:
		printf("\n\nOperação específica\n\n");
	default:
		printf("\n\nOperação geral\n\n");
		break;
	}
	
	printf("\n\nUtilizador: %d\n\n", utilizadorAtual);

	return 0;
}