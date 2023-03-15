#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "secondary.h"

void login(Utilizador* inicio, int* utilizadorAtual, int* gestor, char* nomeAtual) {

	Utilizador* aux;
	int sucesso = 0;
	char utilizador[16], password[11];

	while (!sucesso) {

		printf("Utilizador:\n");
		scanf("%15s", utilizador);
		getchar();
		printf("Password:\n");
		scanf("%10s", password);
		getchar();

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

main() {

	Utilizador* utilizadores = NULL;			// Lista ligada vazia 
	int utilizadorAtual = 0, gestor = 0;			//Dados da sessão
	char nomeAtual[41];

	utilizadores = lerUtilizadores();
	if (utilizadores != NULL && 1 == 1) {		// !!! Apagar a condição para testes
		login(utilizadores, &utilizadorAtual, &gestor, &nomeAtual);
		freeUtilizador(utilizadores);
		utilizadores = NULL;

		if (utilizadorAtual) {
			escolherMenu(utilizadorAtual, nomeAtual, gestor);
		}
	}
}