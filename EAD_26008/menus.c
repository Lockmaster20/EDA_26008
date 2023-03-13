#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "secondary.h"

#pragma region menus

int menuGestor(int utilizadorAtual, char* nomeAtual) {

	Utilizador* utilizadores = NULL;
	Meio* meios = NULL;
	Aluguer* alugueres = NULL;
	int opcao, sucesso = 0, existe;

	//Dados scanf adicionar/alterar

	int codigo, NIF, gestor, historico, opcaoList;
	char utilizador[11], nome[41], password[11], morada[31], tipo[21], posicao[57];
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
			existe = 1;
			while (existe)
			{
				printf("1. Listar Meios\n2. Listar Meios por Autonomia\n3. Listar Meios numa Localizacao\n\n0. Sair\n\n-> ");
				scanf("%d", &opcaoList);
				getchar();
				switch (opcaoList) {
				case 0:
					existe = 0;
					break;
				case 1:
				case 2:
					mG2(alugueres, opcaoList, NULL);
					existe = 0;
					break;
				case 3:
					// !!! perguntar posicao
					mG2(alugueres, opcaoList, posicao);
					existe = 0;
					break;
				}
			}
			sucesso = 1;
			break;
		case 3:
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
	int opcao, sucesso = 0, existe, codigo, codigoMeio, opcaoList;
	char posicao[57];
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
			existe = 1;
			while (existe)
			{
				printf("1. Listar Meios\n2. Listar Meios por Autonomia\n3. Listar Meios numa Localizacao\n\n0. Sair\n\n-> ");
				scanf("%d", &opcaoList);
				getchar();
				switch (opcaoList) {
				case 0:
					existe = 0;
					break;
				case 1:
				case 2:
					m2(alugueres, meios, opcaoList, NULL);
					existe = 0;
					break;
				case 3:
					// !!! perguntar posicao
					m2(alugueres, meios, opcaoList, posicao);
					existe = 0;
					break;
				}
			}
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

void escolherMenu(int utilizadorAtual, char* nomeAtual, int gestor) {
	if (utilizadorAtual) {
		if (gestor == 1) {
			menuGestor(utilizadorAtual, nomeAtual);
		}
		else {
			menu(utilizadorAtual, nomeAtual);
		}
	}
	return;
}