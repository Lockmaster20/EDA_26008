#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "secondary.h"


/// Pede dados de login ao utilizador, 
/// verifica os dados introduzidos, 
/// ao validar os dados introduzidos, altera os dados da sessão atual e devolve 1
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
/// se tiver dados executa a função login, 
/// depois de fazer login liberta a memória utilizada e passa para a função de escolher o menu
main() {

	
	Utilizador* utilizadores = NULL;
	// Dados da sessão
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
	
	


	/*
	#pragma region testes
	Grafo* grafo = lerLocais();
	int teste = lerCaminhos(grafo);
	int existe = existeLocal(grafo, "tile.research.goggles");
	int nLocais = contaLocais(grafo);

	int partida = 1;
	int limite = 600;
	char* tipo = "Trotinete";

	Meio* meio = lerMeios();
	//ordenarMeios;
	Distancia* dists = calcularDistancia(grafo, partida, limite, nLocais);

	int tetettes = existeCaminho(grafo, 1, 12);

	ordenarLocais(grafo);
	listarLocais(grafo);
	//listarMeioLocais(meio, 1, dists, tipo);

	freeLocais(grafo);
	grafo = NULL;


	// int localPartida = 6;
	// int limite = 500;

	// Distancia* dddddddd = calcularDistancia(grafo, localPartida, limite, nLocais);

	int abc = 0;
	#pragma endregion
	*/
}
