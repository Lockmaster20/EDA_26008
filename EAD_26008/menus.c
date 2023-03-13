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

	int codigo, NIF, gestor, historico, opcaoList, resp;
	char utilizador[11], nome[41], password[11], morada[31], tipo[21], posicao[57];
	float saldo, preco;
	Data dataNascimento;
	Estado estado;

	system("cls");
	while (sucesso != 1) {
		printf(" %s -- Menu de Gestor:\n\n", nomeAtual);
		printf("1. Alterar Dados Pessoais\n\n --- Meios\n2. Listar Meios\n3. Adicionar Meio\n4. Editar Meio\n5. Remover Meio\n\n --- Utilizadores\n6. Listar Utilizadores\n7. Adicionar Utilizador\n8. Editar Utilizador\n9. Remover Utilizador\n\n --- Alugueres\n10. Listar Alugueres\n11. Editar Aluguer\n\n0. Sair\n\n-> ");

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
			system("cls");
			existe = 1;
			while (existe)
			{
				printf("\n1. Listar Meios\n2. Listar Meios por Autonomia\n3. Listar Meios numa Localizacao\n\n0. Sair\n\n-> ");
				scanf("%d", &opcaoList);
				getchar();
				switch (opcaoList) {
				case 0:
					existe = 0;
					system("cls");
					break;
				case 1:
				case 2:
					system("cls");
					mG2(alugueres, opcaoList, NULL);
					existe = 0;
					break;
				case 3:
					printf("Localizacao: (palavra1.palavra2.palavra3)\n");
					scanf("%[^\n]56s", &posicao);
					getchar();
					system("cls");
					mG2(alugueres, opcaoList, posicao);
					existe = 0;
					break;
				default:
					system("cls");
					printf("\n--- Valor invalido, tente novamente ---\n\n");
					break;
				}
			}
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

			system("cls");
			resp = mG3(meios, codigo, tipo, estado, preco);
			if (resp == 1)
				printf("\n--- Meio adicionado com sucesso ---\n\n");
			else
				printf("\n--- Erro ao adicionar o meio ---\n\n");
			break;
		case 4:
			mG4();
			break;
		case 5:
			system("cls");
			existe = 0;
			while (!existe)
			{
				printf("Codigo do meio a remover?\n");
				scanf("%d", &codigo);
				getchar();

				meios = lerMeios();
				existe = existeMeio(meios, codigo);
				free(meios);
				meios = NULL;

				if (!existe) {
					system("cls");
					printf("\n--- Erro, o meio introduzido nao existe ---\n\n");
				}
			}
			system("cls");
			resp = mG5(meios, codigo);
			if (resp == 1)
				printf("\n--- Meio removido com sucesso ---\n\n");
			else
				printf("\n--- Erro ao remover o meio ---\n\n");
			break;
		case 6:
			system("cls");
			mG6(utilizadores);
			break;
		case 7:
			system("cls");
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

				if (existe) {
					system("cls");
					printf("\n--- Erro, o utilizador introduzido ja existe ---\n\n");
				}
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

			printf("Gestor: (1 | 0)\n");
			scanf("%d", &gestor);
			getchar();

			system("cls");
			resp = mG7(utilizadores, codigo, utilizador, nome, password, saldo, dataNascimento, NIF, morada, gestor);

			if (resp == 1)
				printf("\n--- Utilizador adicionado com sucesso ---\n\n");
			else
				printf("\n--- Erro ao adicionar o utilizador ---\n\n");
			break;
		case 8:
			mG8();
			break;
		case 9:
			system("cls");
			existe = 0;
			while (!existe)
			{
				printf("Codigo do utilizador a remover?\n");
				scanf("%d", &codigo);
				getchar();

				utilizadores = lerUtilizadores();
				existe = existeUtilizador(utilizadores, codigo);
				free(utilizadores);
				utilizadores = NULL;

				if (!existe) {
					system("cls");
					printf("\n--- Erro, o utilizador introduzido nao existe ---\n\n");
				}
			}
			system("cls");
			resp = mG9(utilizadores, codigo);
			if (resp == 1)
				printf("\n--- Utilizador removido com sucesso ---\n\n");
			else
				printf("\n--- Erro ao remover o utilizador ---\n\n");
			break;
		case 10:
			system("cls");
			mG10(utilizadores, alugueres, meios, utilizadorAtual);
			break;
		case 11:
			mG11();
			break;
		default:
			system("cls");
			printf("\n--- Valor invalido, tente novamente ---\n\n");
			break;
		}
	}
	return 0;
}

int menu(int utilizadorAtual, char* nomeAtual) {

	Utilizador* utilizadores = NULL;
	Meio* meios = NULL;
	Aluguer* alugueres = NULL;
	int opcao, sucesso = 0, existe, codigo, codigoMeio, opcaoList, resp;
	char posicao[57];
	float custo;

	system("cls");
	while (sucesso != 1) {
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
					printf("Localizacao: (palavra1.palavra2.palavra3)\n");
					scanf("%[^\n]56s", &posicao);
					getchar();
					m2(alugueres, meios, opcaoList, posicao);
					existe = 0;
					break;
				default:
					system("cls");
					printf("\n--- Valor invalido, tente novamente ---\n\n");
					break;
				}
			}
			break;
		case 3:
			system("cls");
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

					if (existe) {
						system("cls");
						printf("\n--- Erro, nao e possivel alugar o meio introduzido ---\n\n");
					}
				}

				// !!! Opção temporária, depois calcular o custo pelo preço do meio
				printf("Custo:\n");
				scanf("%f", &custo);
				getchar();

				resp = m3(utilizadores, alugueres, codigo, utilizadorAtual, codigoMeio, custo);
				if (resp == 1)
					printf("\n--- Meio alugado com sucesso ---\n\n");
				else
					printf("\n--- Erro ao alugar o meio ---\n\n");
			}
			else {
				printf("\n--- Nao pode alugar outro meio enquanto tiver um aluguer ativo ---\n\n");
			}
			break;
		case 4:
			system("cls");
			m4(utilizadores, alugueres, meios, utilizadorAtual);
			break;
		default:
			system("cls");
			printf("\n--- Valor invalido, tente novamente ---\n\n");
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