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

int login() {
	char utilizador[20], password[4];

	printf("Utilizador:\n");
	scanf("%[^\n]s", utilizador);
	scanf("%*c");					// !!! Se possível ver outra solução para não passar à frente !!!
	printf("Password:\n");
	scanf("%[^\n]s", password);
	scanf("%*c"); 
	
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

	fp = fopen("dados/utilizadores.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			int check = fscanf(fp, "%d;%[^;];%[^;];%[^;];%f;%d-%d-%d;%d;%[^;];%d\n", &fcodigo, futilizador, fnome, fpassword, &fsaldo, &fdataNascimento.ano, &fdataNascimento.mes, &fdataNascimento.dia, &fNIF, fmorada, &fgestor);
			if (check != 11) {
				printf("\n\n\n////////////////// ERRO //////////////////\n\n\n");
				return 0;
			}

			int a = 0;
		}
		fclose(fp);
	}

	if (!strcmp(utilizador, futilizador) && !strcmp(password, fpassword))
	{
		return 1;
	}

	int a = 0;

	return 0;
}

main() {
	//Fazer com listas ligadas porque ocupam menos espaço na memória, porque não é necessário dedicar memória ao definir a sruct
	//cada "meio" regista o endereço do próximo "meio"

	//Meio m;

	//int a = m.codigo;
	printf("\n\nLogin? %d\n", login());
}