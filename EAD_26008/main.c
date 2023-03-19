#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "secondary.h"

/// Pede dados de login ao utilizador, 
/// verifica os dados introduzidos, 
/// ao validar os dados introduzidos, altera os dados da sess�o atual e devolve 1
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
			printf("\n--- Dados invalidos, tente novamente ---\n\n");
	}

	return;
}

/// Carrega os dados dos utilizadores em "utilizadores.txt", 
/// se tiver dados executa a fun��o login, 
/// depois de fazer login liberta a mem�ria utilizada e passa para a fun��o de escolher o menu
main() {

	Utilizador* utilizadores = NULL;
	// Dados da sess�o
	int utilizadorAtual = 0, gestor = 0;
	char nomeAtual[41];

	utilizadores = lerUtilizadores();
	if (utilizadores != NULL) {
		login(utilizadores, &utilizadorAtual, &gestor, &nomeAtual);
		freeUtilizador(utilizadores);
		utilizadores = NULL;

		if (utilizadorAtual) {
			escolherMenu(utilizadorAtual, nomeAtual, gestor);
		}
	}
}