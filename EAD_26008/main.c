//#define _CRT_SECURE_NO_WARNINGS
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
	char login[20];					// Nome para iniciar sessão
	char nome[50];					// Nome normal
	char password[4];				// !!!! Tamanho temporário alterar depois de testes !!!!
	float saldo;
	Data dataNascimento;
	int NIF;
	char morada[50];
	//Contacto contacto[5];			// máximo de 5 contactos por cliente
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

main() {
	//Fazer com listas ligadas porque ocupam menos espaço na memória, porque não é necessário dedicar memória ao definir a sruct
	//cada "meio" regista o endereço do próximo "meio"

	//Meio m;

	//int a = m.codigo;
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa\n");
}