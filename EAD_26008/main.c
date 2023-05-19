#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "secondary.h"





// Function to find the shortest path in the graph using Dijkstra's algorithm
/*
int testeDistancia (Grafo* graph, int src, int dest, int V) {
	int* distance = (int*)malloc(V * sizeof(int));
	int* parent = (int*)malloc(V * sizeof(int));
	bool* visited = (bool*)malloc(V * sizeof(bool));

	// Initialize distance, parent, and visited arrays
	for (int i = 0; i < V; ++i) {
		distance[i] = INF;
		parent[i] = -1;
		visited[i] = false;
	}

	// Distance of source vertex from itself is 0
	distance[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < V - 1; ++count) {
		int u = findMinDistance(distance, visited, V);
		visited[u] = true;

		Grafo* aux = graph;
		while (aux->codigoLocal_h = !u) aux = aux->seguinte;
		Caminho currNode = aux->caminhos;

		while (currNode != NULL) {
			int v = currNode->codigoLocal;
			int weight = currNode->distancia;

			if (!visited[v] && distance[u] + weight < distance[v]) {
				distance[v] = distance[u] + weight;
				parent[v] = u;
			}

			currNode = currNode->seguinte;
		}
	}

	// Print the shortest path
	printf("Shortest path from %d to %d: ", src, dest);
	printf("\n");

	// Print the distance
	printf("Shortest distance from %d to %d: %d\n", src, dest, distance[dest]);

	// Free allocated memory
	free(distance);
	free(parent);
	free(visited);
	return 1;
}
*/


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


int testeDistancia(Grafo* graph, int src, int dest, int V) {
	return V;
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
	int nCaminhos = contaLocais(grafo);

	
	//int funcionou = dijkstra(grafo, "lisp.rival.gracious", nCaminhos);

	int tstttt = 1;

	int source = 1;
	int destination = 5;

	int res = testeDistancia(grafo, source, destination, nCaminhos);
	printf("\n\n//////////////////////////////\n%d\n//////////////////////////////\n\n");

	int abc = 0;
}

int contaLocais(Grafo* inicio) {
	int count = 0;
	while (inicio != NULL)
	{
		count++;
		inicio = inicio->seguinte;
	}
	return(count);
}