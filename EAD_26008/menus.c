#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "secondary.h"

#pragma region menus

/// Ambos os menus funcionam da mesma maneira; 
/// Apresenta as op��es ao utilizador e quando o utilizador escolher uma op��o v�lida vai executar as fun��es para realizar essa a��o

/// O menu de gestor permite realizar mais a��es do que o menu de clientes
int menuGestor(int utilizadorAtual, char* nomeAtual) {

	Utilizador* utilizadores = NULL;
	Meio* meios = NULL;
	Aluguer* alugueres = NULL;
	Grafo* locais = NULL;
	Distancia* dists = NULL;
	int sucesso = 0, existe;

	//Dados introduzidos pelo utilizador
	int opcao, opcaoList, codigo, NIF, gestor, historico, resp, posicao, raio, origem, destino, distancia;
	char utilizador[11], nome[41], password[11], morada[31], tipo[21], nomeLocal[LOC_SIZE];
	float saldo, precoBase, precoAdicional;
	Data dataNascimento;
	Estado estado;

	system("cls");
	while (sucesso != 1) {
		printf(" %s -- Menu de Gestor:\n\n", nomeAtual);
		printf("1. Alterar Dados Pessoais\n\n --- Meios\n2. Listar Meios\n3. Adicionar Meio\n4. Editar Meio\n5. Remover Meio\n\n --- Utilizadores\n6. Listar Utilizadores\n7. Adicionar Utilizador\n8. Editar Utilizador\n9. Remover Utilizador\n\n --- Alugueres\n10. Listar Alugueres\n\n --- Grafo\n11. Listar Locais\n12. Adicionar Local\n13. Adicionar Caminho\n\n0. Sair\n\n-> ");

		scanf("%d", &opcao);
		getchar();
		switch (opcao)
		{
		case 0:
			sucesso = 1;
			break;
		case 1:
			system("cls");
			utilizadores = lerUtilizadores();
			listarUtilizadorSimples(utilizadores, utilizadorAtual, NULL);
			freeUtilizador(utilizadores);
			utilizadores = NULL;

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
			resp = mG1(utilizadores, utilizadorAtual, nome, password, saldo, dataNascimento, NIF, morada, gestor);

			if (resp == 1)
			{
				printf("\n--- Utilizador alterado com sucesso ---\n\n");
				sucesso = 1;
			}
			else
				printf("\n--- Erro ao alterar o utilizador ---\n\n");
			break;
		case 2:
			system("cls");
			existe = 1;
			while (existe)
			{
				printf("\n1. Listar Meios\n2. Listar Meios por Autonomia\n3. Listar Meios numa Localizacao\n4. Listar Meios numa Area\n\n0. Sair\n\n-> ");
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
					mG2(alugueres, opcaoList, NULL, NULL, NULL);
					existe = 0;
					break;
				case 3:
					system("cls");
					locais = lerLocais();
					listarLocaisSimples(locais);
					existe = 0;
					while (!existe) {
						printf("Localizacao: (codigo)\n");
						scanf("%d", &posicao);
						getchar();

						existe = existeLocalCodigo(locais, posicao);
					}
					freeLocais(locais);
					locais = NULL;

					system("cls");
					mG2(alugueres, opcaoList, posicao, NULL, NULL);
					existe = 0;
					break;
				case 4:
					system("cls");
					locais = lerLocais();
					listarLocaisSimples(locais);
					existe = 0;
					while (!existe) {
						printf("Localizacao atual: (codigo)\n");
						scanf("%d", &posicao);
						getchar();

						existe = existeLocalCodigo(locais, posicao);
					}
					freeLocais(locais);
					locais = NULL;

					printf("Tipo do meio:\n");
					scanf("%[^\n]20s", tipo);
					getchar();

					printf("Distancia maxima do meio:\n");
					scanf("%d", &raio);
					getchar();

					system("cls");
					mG2(alugueres, opcaoList, posicao, raio, tipo);
					
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
			freeMeio(meios);
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

			locais = lerLocais();
			listarLocaisSimples(locais);
			existe = 0;
			while (!existe) {
				printf("Localizacao: (codigo)\n");
				scanf("%d", &estado.posicao);
				getchar();

				existe = existeLocalCodigo(locais, estado.posicao);
			}
			freeLocais(locais);
			locais = NULL;

			printf("Preco Base:\n");
			scanf("%f", &precoBase);
			getchar();

			printf("Preco por minuto:\n");
			scanf("%f", &precoAdicional);
			getchar();

			system("cls");
			resp = mG3(meios, codigo, tipo, estado, precoBase, precoAdicional);
			if (resp == 1)
				printf("\n--- Meio adicionado com sucesso ---\n\n");
			else
				printf("\n--- Erro ao adicionar o meio ---\n\n");
			break;
		case 4:
			system("cls");
			existe = 0;
			while (!existe)
			{
				printf("Codigo do meio a editar:\n");
				scanf("%d", &codigo);
				getchar();

				meios = lerMeios();
				existe = existeMeio(meios, codigo);

				if (!existe) {
					system("cls");
					printf("\n--- Erro, o meio introduzido nao existe ---\n\n");
				}
			}
			listarMeioSimples(meios, codigo);
			freeMeio(meios);
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

			locais = lerLocais();
			listarLocaisSimples(locais);
			existe = 0;
			while (!existe) {
				printf("Localizacao: (codigo)\n");
				scanf("%d", &estado.posicao);
				getchar();

				existe = existeLocalCodigo(locais, estado.posicao);
			}
			freeLocais(locais);
			locais = NULL;

			printf("Preco Base:\n");
			scanf("%f", &precoBase);
			getchar();

			printf("Preco por minuto:\n");
			scanf("%f", &precoAdicional);
			getchar();

			system("cls");
			resp = mG4(meios, codigo, tipo, estado, precoBase, precoAdicional);
			freeMeio(meios);
			if (resp == 1)
				printf("\n--- Meio alterado com sucesso ---\n\n");
			else
				printf("\n--- Erro ao alterar o meio ---\n\n");
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
				freeMeio(meios);
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

			existe = 1;
			while (existe)
			{
				printf("Utilizador:\n");
				scanf("%10s", utilizador);
				getchar();
				existe = existeUser(utilizadores, utilizador);

				if (existe) {
					system("cls");
					printf("\n--- Erro, o utilizador introduzido ja existe ---\n\n");
				}
			}
			freeUtilizador(utilizadores);
			utilizadores = NULL;

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
			freeUtilizador(utilizadores);
			if (resp == 1)
				printf("\n--- Utilizador adicionado com sucesso ---\n\n");
			else
				printf("\n--- Erro ao adicionar o utilizador ---\n\n");
			break;
		case 8:
			system("cls");
			utilizadores = lerUtilizadores();

			existe = 0;
			while (!existe)
			{
				printf("Codigo do utilizador a editar:\n");
				scanf("%d", &codigo);
				getchar();

				existe = existeUtilizadorAtivo(utilizadores, codigo);

				if (!existe) {
					system("cls");
					printf("\n--- Erro, nao e possivel editar o utilizador introduzido ---\n\n");
				}
			}
			system("cls");
			listarUtilizadorSimples(utilizadores, codigo, NULL);
			freeUtilizador(utilizadores);
			utilizadores = NULL;

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
			resp = mG8(utilizadores, codigo, nome, password, saldo, dataNascimento, NIF, morada, gestor);

			if (resp == 1) {
				printf("\n--- Utilizador alterado com sucesso ---\n\n");
				if (codigo == utilizadorAtual)
					sucesso = 1;
			}
			else
				printf("\n--- Erro ao alterar o utilizador ---\n\n");
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
				freeUtilizador(utilizadores);
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
			system("cls");
			mG11(locais);
			break;
		case 12:
			system("cls");

			locais = lerLocais();
			codigo = obterUltimoLocal(locais) + 1;
			existe = 1;
			while (existe) {
				printf("Localizacao: (Palava1.Palavra2.Palavra3)\n");
				scanf("%[^\n]56s", nomeLocal);
				getchar();

				existe = existeLocal(locais, nomeLocal);
			}
			freeLocais(locais);
			locais = NULL;

			system("cls");
			resp = mG12(locais, codigo, nomeLocal);
			if (resp == 1)
				printf("\n--- Local criado com sucesso ---\n\n");
			else
				printf("\n--- Erro ao criar o local ---\n\n");
			break;
		case 13:
			system("cls");

			locais = lerLocais();
			existe = 0;
			while (!existe) {
				printf("Local Origem: (Codigo)\n");
				scanf("%d", &origem);
				getchar();

				existe = existeLocalCodigo(locais, origem);
			}
			existe = 0;
			while (!existe) {
				printf("Local Destino: (Codigo)\n");
				scanf("%d", &destino);
				getchar();

				existe = existeLocalCodigo(locais, destino);
			}
			freeLocais(locais);
			locais = NULL;

			printf("Distancia:\n");
			scanf("%d", &distancia);
			getchar();

			system("cls");
			resp = mG13(origem, destino, distancia);
			if (resp == 1)
				printf("\n--- Caminho criado com sucesso ---\n\n");
			else
				printf("\n--- Erro ao criar o caminho ---\n\n");
			break;
		default:
			system("cls");
			printf("\n--- Valor invalido, tente novamente ---\n\n");
			break;
		}
	}
	return 0;
}

/// O menu de cliente tem menos op��es do que o menu de gestor, mas permite alugar um meio
int menu(int utilizadorAtual, char* nomeAtual) {

	Utilizador* utilizadores = NULL;
	Meio* meios = NULL;
	Aluguer* alugueres = NULL;
	Distancia* dists = NULL;
	Grafo* locais = NULL;

	int opcao, sucesso = 0, existe, codigo, codigoMeio, codigoAluguer, NIF, opcaoList, resp, posicao, raio;
	char nome[41], password[11], morada[31], tipo[21];
	float custo, saldo;
	Data dataNascimento;

	system("cls");
	while (sucesso != 1) {
		printf(" %s -- Menu:\n\n", nomeAtual);
		printf("1. Alterar Dados Pessoais\n2. Listar Meios Disponiveis\n3. Alugar Meio\n4. Terminar Aluguer\n5. Historico\n\n0. Sair\n\n-> ");

		scanf("%d", &opcao);
		scanf("%*c");
		switch (opcao)
		{
		case 0:
			sucesso = 1;
			break;
		case 1:
			system("cls");
			utilizadores = lerUtilizadores();
			listarUtilizadorSimples(utilizadores, utilizadorAtual, &saldo);
			freeUtilizador(utilizadores);
			utilizadores = NULL;

			printf("Nome:\n");
			scanf("%[^\n]40s", nome);
			getchar();

			printf("Password:\n");
			scanf("%[^\n]10s", password);
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

			system("cls");
			resp = m1(utilizadores, utilizadorAtual, nome, password, saldo, dataNascimento, NIF, morada, 0);

			if (resp == 1)
			{
				printf("\n--- Utilizador alterado com sucesso ---\n\n");
				sucesso = 1;
			}
			else
				printf("\n--- Erro ao alterar o utilizador ---\n\n");
			break;
		case 2:
			existe = 1;
			while (existe)
			{
				printf("1. Listar Meios\n2. Listar Meios por Autonomia\n3. Listar Meios numa Localizacao\n4. Listar Meios numa Area\n\n0. Sair\n\n-> ");
				scanf("%d", &opcaoList);
				getchar();
				switch (opcaoList) {
				case 0:
					existe = 0;
					break;
				case 1:
				case 2:
					m2(alugueres, meios, opcaoList, NULL, NULL, NULL);
					existe = 0;
					break;
				case 3:
					printf("Localizacao: (codigo)\n");
					scanf("%d", &posicao);
					getchar();
					m2(alugueres, meios, opcaoList, posicao, NULL, NULL);
					existe = 0;
					break;
				case 4:
					system("cls");
					locais = lerLocais();
					listarLocaisSimples(locais);
					existe = 0;
					while (!existe) {
						printf("Localizacao atual: (codigo)\n");
						scanf("%d", &posicao);
						getchar();

						existe = existeLocalCodigo(locais, posicao);
					}
					freeLocais(locais);
					locais = NULL;

					printf("Tipo do meio:\n");
					scanf("%[^\n]20s", tipo);
					getchar();

					printf("Distancia maxima do meio:\n");
					scanf("%d", &raio);
					getchar();

					system("cls");
					m2(alugueres, meios, opcaoList, posicao, raio, tipo);

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
			existe = existeAluguerAtivo(alugueres, utilizadorAtual, NULL);

			if (!existe) {
				codigo = obterUltimoAluguer(alugueres) + 1;

				existe = 1;
				while (existe)
				{
					printf("Codigo do Meio:\n");
					scanf("%d", &codigoMeio);
					getchar();

					meios = lerMeios();
					existe = (existeMeio(meios, codigoMeio) && existeAluguerMeio(alugueres, codigoMeio));

					freeMeio(meios);
					meios = NULL;

					if (existe) {
						system("cls");
						printf("\n--- Erro, nao e possivel alugar o meio introduzido ---\n\n");
					}
				}

				freeAluguer(alugueres);
				alugueres = NULL;

				resp = m3(utilizadores, alugueres, codigo, utilizadorAtual, codigoMeio);
				if (resp == 1)
					printf("\n--- Meio alugado com sucesso ---\n\n");
				else
					printf("\n--- Erro ao alugar o meio ---\n\n");
			}
			else {
				freeAluguer(alugueres);
				alugueres = NULL;
				printf("\n--- Nao pode alugar outro meio enquanto tiver um aluguer ativo ---\n\n");
			}
			break;
		case 4:
			system("cls");
			alugueres = lerAlugueres();
			existe = existeAluguerAtivo(alugueres, utilizadorAtual, &codigoAluguer);
			if (existe) {

				utilizadores = lerUtilizadores();
				meios = lerMeios();
				resp = m4(utilizadores, alugueres, meios, codigoAluguer);
				if (resp == 1)
					printf("\n--- Aluguer terminado com sucesso ---\n\n");
				else
					printf("\n--- Erro ao terminar o aluguer ---\n\n");

				freeUtilizador(utilizadores);
				utilizadores = NULL;
				freeMeio(meios);
				meios = NULL;
			}
			else
			{
				printf("\n--- Nao tem um aluguer ativo ---\n\n");
			}
			freeAluguer(alugueres);
			alugueres = NULL;
			
			break;
		case 5:
			system("cls");
			m5(utilizadores, alugueres, meios, utilizadorAtual);
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

/// Atrav�s dos dados obtidos escolhe o menu de gestor ou o menu de clientes
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