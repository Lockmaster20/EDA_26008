#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "secondary.h"


void listarMeioLocais(Meio* inicio, int gestor, Distancia * distancias)
{
	if (gestor == 1) {
		printf("==============================================================================================================================\n");
		printf("Codigo | Tipo                 | Bateria | Autonomia | Localizacao                                              | Preco | Hist.\n");
		printf("=======|======================|=========|===========|==========================================================|=======|======\n");

		while (inicio != NULL)
		{
			while (distancias->codigoLocal =! NULL)
			printf("%6d | %-20s | %7.2f | %9.2f | %-56s | %5.2f | %-5s\n",
				inicio->codigo, inicio->tipo, inicio->estado.bateria, inicio->estado.autonomia,
				inicio->estado.posicao.palavras,
				inicio->preco.precoBase, checkSN(inicio->historico));
			
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
				if (opcao == 1 || opcao == 2 || ((opcao == 3) && (!strcmp(inicio->estado.posicao.palavras, posicao)))) {
					printf("%6d | %-20s | %7.2f | %9.2f | %-56s | %5.2f\n",
						inicio->codigo, inicio->tipo, inicio->estado.bateria, inicio->estado.autonomia,
						inicio->estado.posicao.palavras,
						inicio->preco.precoBase);
				}
			}
			inicio = inicio->seguinte;
		}
		printf("======================================================================================================================\n");

	}
}



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

	/*
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
	*/


	Grafo* grafo = lerLocais();
	int teste = lerCaminhos(grafo);
	int existe = existeLocal(grafo, "tile.research.goggles");
	int nLocais = contaLocais(grafo);

	listarLocais(grafo);

	freeLocais(grafo);
	grafo = NULL;


	// int localPartida = 6;
	// int limite = 500;

	// Distancia* dddddddd = calcularDistancia(grafo, localPartida, limite, nLocais);

	int abc = 0;
}
