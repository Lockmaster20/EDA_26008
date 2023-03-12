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

#pragma region menus

int menuGestor(int utilizadorAtual, char* nomeAtual) {

	Utilizador* utilizadores = NULL;
	Meio* meios = NULL;
	Aluguer* alugueres = NULL;
	int opcao, sucesso = 0, existe;

	//Dados scanf adicionar/alterar

	int codigo, NIF, gestor, historico;
	char utilizador[11], nome[41], password[11], morada[31], tipo[21];
	float saldo, preco;
	Data dataNascimento;
	Estado estado;

	while (sucesso != 1) {
		system("cls");
		printf(" %s -- Menu de Gestor:\n\n", nomeAtual);
		printf("1. Alterar Dados Pessoais\n\n --- Meios\n2. Listar Meios\n3. Adicionar Meio\n4. Editar Meio\n5. Apagar Meio\n\n --- Utilizadores\n6. Listar Utilizadores\n7. Adicionar Utilizador\n8. Editar Utilizador\n9. Apagar Utilizador\n\n --- Alugueres\n10. Listar Alugueres\n11. Editar Aluguer\n\n0. Sair\n\n-> ");

		scanf("%d", &opcao);
		getchar();
		switch (opcao)
		{
		case 0:
			sucesso = 1;
			break;
		case 1:
			mG1();
			break;
		case 2:
			mG2(meios);
			sucesso = 1;
			break;
		case 3:
			/*existe = 1;
			while (existe)
			{
				printf("Codigo:\n");
				scanf("%d", &codigo);
				getchar();

				meios = lerMeios();
				existe = existeMeio(meios, codigo);

				free(meios);
				meios = NULL;
			}*/
			meios = lerMeios();
			codigo = obterUltimoMeio(meios) + 1;
			free(meios);
			meios = NULL;

			printf("Tipo:\n");
			scanf("%[^\n]20s", tipo);
			getchar();

			printf("Bateria:\n");
			scanf("%f", &estado.bateria);
			getchar();

			printf("Autonomia:\n");
			scanf("%f", &estado.autonomia);
			getchar();

			printf("Localizacao: (palavra1.palavra2.palavra3)\n");
			scanf("%[^\n]56s", &estado.posicao.palavras);
			getchar();

			printf("Preco:\n");
			scanf("%f", &preco);
			getchar();
			
			mG3(meios, codigo, tipo, estado, preco);
			break;
		case 4:
			mG4();
			break;
		case 5:
			printf("Codigo do meio a remover?\n");
			scanf("%d", &codigo);
			mG5(meios, codigo);
			break;
		case 6:
			mG6(utilizadores);
			sucesso = 1;
			break;
		case 7:
			/*existe = 1;
			while (existe)
			{
				printf("Codigo:\n");
				scanf("%d", &codigo);
				getchar();

				utilizadores = lerUtilizadores();
				existe = existeUtilizador(utilizadores, codigo);

				free(utilizadores);
				utilizadores = NULL;
			}*/
			utilizadores = lerUtilizadores();
			codigo = obterUltimoUtilizador(utilizadores) + 1;
			free(utilizadores);
			utilizadores = NULL;

			existe = 1;
			while (existe)
			{
				printf("Utilizador:\n");
				scanf("%10s", utilizador);
				getchar();

				utilizadores = lerUtilizadores();
				existe = existeUser(utilizadores, utilizador);

				free(utilizadores);
				utilizadores = NULL;
			}
			printf("Nome:\n");
			scanf("%[^\n]40s", nome);
			getchar();

			printf("Password:\n");
			scanf("%[^\n]10s", password);
			getchar();

			printf("Saldo:\n");
			scanf("%f", &saldo);
			getchar();

			printf("Data de Nascimento: (d-m-aaaa)\n");
			scanf("%d-%d-%d", &dataNascimento.dia, &dataNascimento.mes, &dataNascimento.ano);
			getchar();

			printf("NIF:\n");
			scanf("%d", &NIF);
			getchar();

			printf("Morada:\n");
			scanf("%[^\n]30s", morada);
			getchar();
			
			printf("Gestor: (1 || 0)\n");
			scanf("%d", &gestor);
			getchar();
			mG7(utilizadores, codigo, utilizador, nome, password, saldo, dataNascimento, NIF, morada, gestor);
			sucesso = 1;
			break;
		case 8:
			mG8();
			break;
		case 9:
			printf("Codigo do utilizador a remover?\n");
			scanf("%d", &codigo);
			mG9(utilizadores, codigo);
			break;
		case 10:
			mG10(utilizadores, alugueres, meios, utilizadorAtual);
			sucesso = 1;
			break;
		case 11:
			mG11();
			break;
		}
	}
	return 0;
}

int menu(int utilizadorAtual, char* nomeAtual) {

	Utilizador* utilizadores = NULL;
	Meio* meios = NULL;
	Aluguer* alugueres = NULL;
	int opcao, sucesso = 0, existe, codigo, codigoMeio;
	float custo;

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
			m1();
			break;
		case 2:
			m2(alugueres, meios);
			sucesso = 1;
			break;
		case 3:
			alugueres = lerAlugueres();
			existe = existeAluguerAtivo(alugueres, utilizadorAtual);

			free(alugueres);
			alugueres = NULL;

			if (!existe) {
				alugueres = lerAlugueres();
				codigo = obterUltimoAluguer(alugueres) + 1;
				free(alugueres);
				alugueres = NULL;

				existe = 1;
				while (existe)
				{
					printf("Codigo do Meio:\n");
					scanf("%d", &codigoMeio);
					getchar();

					meios = lerMeios();
					alugueres = lerAlugueres();
					existe = (existeMeio(meios, codigo) && existeAluguerMeio(alugueres, codigo));

					free(meios);
					meios = NULL;
					free(alugueres);
					alugueres = NULL;
				}

				// !!! Opção temporária, depois calcular o custo pelo preço do meio
				printf("Custo:\n");
				scanf("%f", &custo);
				getchar();

				m3(utilizadores, alugueres, codigo, utilizadorAtual, codigoMeio, custo);
			}
			break;
		case 4:
			m4(utilizadores, alugueres, meios, utilizadorAtual);
			sucesso = 1;
			break;
		}
	}

	return 0;
}

#pragma endregion

main() {

	Utilizador* utilizadores = NULL, * aux;			// Lista ligada vazia 
	int utilizadorAtual = 0, gestor = 0;			//Dados da sessão
	char nomeAtual[41];

	utilizadores = lerUtilizadores();
	if (utilizadores != NULL && 1 == 1) {
		login(utilizadores, &utilizadorAtual, &gestor, &nomeAtual);
		free(utilizadores);
		utilizadores = NULL;

		if (utilizadorAtual) {
			if (gestor == 1) {
				menuGestor(utilizadorAtual, nomeAtual);
			}
			else {
				menu(utilizadorAtual, nomeAtual);
			}
		}
	}
}