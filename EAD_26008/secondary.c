#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "secondary.h"

const char* checkSN(int i) {

	switch (i)
	{
	case 1:
		return "Sim";
	case 0:
		return "Nao";
	}
}

#pragma region libertarMemoria
/*
void freeUtilizador(Utilizador* inicio) {
	Utilizador* aux;

	while (inicio != NULL)
	{
		aux = inicio;
		inicio = inicio->seguinte;
		free(aux);
	}
	inicio = NULL;
}

void freeMeio(Meio* inicio) {
	Meio* aux;

	while (inicio != NULL)
	{
		aux = inicio;
		inicio = inicio->seguinte;
		free(aux);
	}
}

void freeAluguer(Aluguer* inicio) {
	Aluguer* aux;

	while (inicio != NULL)
	{
		aux = inicio;
		inicio = inicio->seguinte;
		free(aux);
	}
}
*/
#pragma endregion

#pragma region ordenarDados

void trocarUtilizadores(Utilizador* inicio, Utilizador* seg) {

	Utilizador aux;

	aux.codigo = inicio->codigo;
	strcpy(aux.utilizador, inicio->utilizador);
	strcpy(aux.nome, inicio->nome);
	strcpy(aux.password, inicio->password);
	aux.saldo = inicio->saldo;
	aux.dataNascimento = inicio->dataNascimento;
	aux.NIF = inicio->NIF;
	strcpy(aux.morada, inicio->morada);
	aux.gestor = inicio->gestor;
	aux.historico = inicio->historico;

	inicio->codigo = seg->codigo;
	strcpy(inicio->utilizador, seg->utilizador);
	strcpy(inicio->nome, seg->nome);
	strcpy(inicio->password, seg->password);
	inicio->saldo = seg->saldo;
	inicio->dataNascimento = seg->dataNascimento;
	inicio->NIF = seg->NIF;
	strcpy(inicio->morada, seg->morada);
	inicio->gestor = seg->gestor;
	inicio->historico = seg->historico;

	seg->codigo = aux.codigo;
	strcpy(seg->utilizador, aux.utilizador);
	strcpy(seg->nome, aux.nome);
	strcpy(seg->password, aux.password);
	seg->saldo = aux.saldo;
	seg->dataNascimento = aux.dataNascimento;
	seg->NIF = aux.NIF;
	strcpy(seg->morada, aux.morada);
	seg->gestor = aux.gestor;
	seg->historico = aux.historico;

	return;
}

void ordenarUtilizadores(Utilizador* inicio) {
	int trocou = 1;
	Utilizador* aux;

	if (inicio == NULL) return;

	while (trocou) {
		trocou = 0;
		aux = inicio;

		while (aux->seguinte != NULL)
		{
			if (aux->codigo > aux->seguinte->codigo) {
				trocarUtilizadores(aux, aux->seguinte);
				trocou = 1;
			}
			aux = aux->seguinte;
		}
	}
	return;
}

void trocarMeios(Meio* inicio, Meio* seg) {

	Meio aux;

	aux.codigo = inicio->codigo;
	strcpy(aux.tipo, inicio->tipo);
	aux.estado = inicio->estado;
	aux.preco = inicio->preco;
	aux.historico = inicio->historico;

	inicio->codigo = seg->codigo;
	strcpy(inicio->tipo, seg->tipo);
	inicio->estado = seg->estado;
	inicio->preco = seg->preco;
	inicio->historico = seg->historico;

	seg->codigo = aux.codigo;
	strcpy(seg->tipo, aux.tipo);
	seg->estado = aux.estado;
	seg->preco = aux.preco;
	seg->historico = aux.historico;

	return;
}

void ordenarMeios(Meio* inicio, int opcao) {
	int trocou = 1;
	Meio* aux;

	if (inicio == NULL) return;

	while (trocou) {
		trocou = 0;
		aux = inicio;

		while (aux->seguinte != NULL)
		{
			switch (opcao)
			{
			case 1:
				if (aux->codigo > aux->seguinte->codigo) {
					trocarMeios(aux, aux->seguinte);
					trocou = 1;
				}
				break;
			case 2:
				if (aux->estado.autonomia < aux->seguinte->estado.autonomia) {
					trocarMeios(aux, aux->seguinte);
					trocou = 1;
				}
				break;
			}
			aux = aux->seguinte;
		}
	}
	return;
}

void trocarAlugueres(Aluguer* inicio, Aluguer* seg) {

	Aluguer aux;

	aux.codigo = inicio->codigo;
	aux.codigoUtilizador = inicio->codigoUtilizador;
	aux.codigoMeio = inicio->codigoMeio;
	aux.ativo = inicio->ativo;
	aux.custo = inicio->custo;

	inicio->codigo = seg->codigo;
	inicio->codigoUtilizador = seg->codigoUtilizador;
	inicio->codigoMeio = seg->codigoMeio;
	inicio->ativo = seg->ativo;
	inicio->custo = seg->custo;

	seg->codigo = aux.codigo;
	seg->codigoUtilizador = aux.codigoUtilizador;
	seg->codigoMeio = aux.codigoMeio;
	seg->ativo = aux.ativo;
	seg->custo = aux.custo;

	return;
}

void ordenarAlugueres(Aluguer* inicio) {
	int trocou = 1;
	Aluguer* aux;

	if (inicio == NULL) return;

	while (trocou) {
		trocou = 0;
		aux = inicio;

		while (aux->seguinte != NULL)
		{
			if (aux->codigo > aux->seguinte->codigo) {
				trocarAlugueres(aux, aux->seguinte);
				trocou = 1;
			}
			aux = aux->seguinte;
		}
	}
	return;
}

#pragma endregion

#pragma region carregarDados

Utilizador* carregarUtilizador(Utilizador* inicio, int codigo, char* utilizador, char* nome, char* password, float saldo, Data dataNascimento, int NIF, char* morada, int gestor, int historico) {

	Utilizador* novo = malloc(sizeof(struct registoUtilizador));

	if (novo != NULL)
	{
		novo->codigo = codigo;
		strcpy(novo->utilizador, utilizador);
		strcpy(novo->nome, nome);
		strcpy(novo->password, password);
		novo->saldo = saldo;
		novo->dataNascimento.ano = dataNascimento.ano;
		novo->dataNascimento.mes = dataNascimento.mes;
		novo->dataNascimento.dia = dataNascimento.dia;
		novo->NIF = NIF;
		strcpy(novo->morada, morada);
		novo->gestor = gestor;
		novo->historico = historico;

		novo->seguinte = inicio;
		return(novo);
	}
}

Meio* carregarMeio(Meio* inicio, int codigo, char* tipo, Estado estado, float preco, int historico) {

	Meio* novo = malloc(sizeof(struct registoMeio));

	if (novo != NULL)
	{
		novo->codigo = codigo;
		strcpy(novo->tipo, tipo);
		novo->estado.bateria = estado.bateria;
		novo->estado.autonomia = estado.autonomia;
		strcpy(novo->estado.posicao.palavras, estado.posicao.palavras);
		novo->preco = preco;
		novo->historico = historico;

		novo->seguinte = inicio;
		return(novo);
	}
}

Aluguer* carregarAluguer(Aluguer* inicio, int codigo, int codigoUtilizador, int codigoMeio, int ativo, float custo) {

	Aluguer* novo = malloc(sizeof(struct registoAluguer));

	if (novo != NULL)
	{
		novo->codigo = codigo;
		novo->codigoUtilizador = codigoUtilizador;
		novo->codigoMeio = codigoMeio;
		novo->ativo = ativo;
		novo->custo = custo;

		novo->seguinte = inicio;
		return(novo);
	}
}

#pragma endregion

#pragma region lerDocumentos

Utilizador* lerUtilizadores()
{
	FILE* fp;

	int codigo, NIF, gestor, historico;
	char utilizador[11], nome[41], password[11], morada[31];
	float saldo;
	Data dataNascimento;

	Utilizador* aux = NULL;

	fp = fopen("dados/utilizadores.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			int check = fscanf(fp, "%d;%[^;];%[^;];%[^;];%f;%d-%d-%d;%d;%[^;];%d;%d\n", &codigo, utilizador, nome, password, &saldo, &dataNascimento.ano, &dataNascimento.mes, &dataNascimento.dia, &NIF, morada, &gestor, &historico);
			if (check != 12) {
				printf("\n\n\nErro a carregar dados dos utilizadores\n\n\n");
				return NULL;
			}
			else {
				aux = carregarUtilizador(aux, codigo, utilizador, nome, password, saldo, dataNascimento, NIF, morada, gestor, historico);
			}
		}
		fclose(fp);
	}
	return(aux);
}

Meio* lerMeios()
{
	FILE* fp;

	int codigo, historico;
	char tipo[21];
	float preco;
	Estado estado;

	Meio* aux = NULL;

	fp = fopen("dados/meios.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			int check = fscanf(fp, "%d;%[^;];%f;%f;%[^;];%f;%d\n",
				&codigo, tipo, &estado.bateria, &estado.autonomia,
				&estado.posicao.palavras,
				&preco, &historico);

			if (check != 7) {
				printf("\n\n\nErro a carregar dados dos meios\n\n\n");
				return NULL;
			}
			else {
				aux = carregarMeio(aux, codigo, tipo, estado, preco, historico);
			}
		}
		fclose(fp);
	}
	return(aux);
}

Aluguer* lerAlugueres()
{
	FILE* fp;

	int codigo, codigoUtilizador, codigoMeio, ativo;
	float custo;

	Aluguer* aux = NULL;

	fp = fopen("dados/alugueres.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			int check = fscanf(fp, "%d;%d;%d;%d;%f\n",
				&codigo, &codigoUtilizador, &codigoMeio, &ativo, &custo);

			if (check != 5) {
				printf("\n\n\nErro a carregar dados dos alugueres\n\n\n");
				return NULL;
			}
			else {
				aux = carregarAluguer(aux, codigo, codigoUtilizador, codigoMeio, ativo, custo);
			}
		}
		fclose(fp);
	}
	return(aux);
}

#pragma endregion

#pragma region listarDados

void listarUtilizador(Utilizador* inicio)
{
	printf("==================================================================================================================================================\n");
	printf("Codigo | Utilizador | Nome                                     | Morada                         | Data Nasc. | NIF       | Saldo  | Gestor | Hist.\n");
	printf("=======|============|==========================================|================================|============|===========|========|========|======\n");

	while (inicio != NULL)
	{
		printf("%6d | %-10s | %-40s | %-30s | %2d-%2d-%4d | %9d | %6.2f | %-6s | %-5s\n",
			inicio->codigo, inicio->utilizador, inicio->nome, inicio->morada,
			inicio->dataNascimento.dia, inicio->dataNascimento.mes, inicio->dataNascimento.ano,
			inicio->NIF, inicio->saldo, checkSN(inicio->gestor), checkSN(inicio->historico));
		inicio = inicio->seguinte;
	}
	printf("==================================================================================================================================================\n");
}

void listarMeio(Meio* inicio, int gestor, int opcao, char* posicao)
{
	if (gestor == 1) {
		printf("==============================================================================================================================\n");
		printf("Codigo | Tipo                 | Bateria | Autonomia | Localizacao                                              | Preco | Hist.\n");
		printf("=======|======================|=========|===========|==========================================================|=======|======\n");

		while (inicio != NULL)
		{
			if (opcao == 1 || opcao == 2 || ((opcao == 3) && (!strcmp(inicio->estado.posicao.palavras, posicao)))) {
				printf("%6d | %-20s | %7.2f | %9.2f | %-56s | %5.2f | %-5s\n",
					inicio->codigo, inicio->tipo, inicio->estado.bateria, inicio->estado.autonomia,
					inicio->estado.posicao.palavras,
					inicio->preco, checkSN(inicio->historico));
			}
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
						inicio->preco);
				}
			}
			inicio = inicio->seguinte;
		}
		printf("======================================================================================================================\n");

	}
}

void listarAluguer(Aluguer* inicio, Utilizador* utilizadores, Meio* meios, int utilizadorAtual, int gestor)
{
	char utilizador[11], tipo[21];

	printf("=============================================================================\n");
	printf("Codigo | Utilizador | C. Ut. | Tipo de Meio         | C. Me. | Ativo | Custo \n");
	printf("=======|============|========|======================|========|=======|=======\n");

	while (inicio != NULL)
	{
		while (utilizadores != NULL) {
			if (inicio->codigoUtilizador == utilizadores->codigo) {
				strcpy(utilizador, utilizadores->utilizador);
				utilizadores = NULL;
			}
			else {
				utilizadores = utilizadores->seguinte;
			}
		}
		while (meios != NULL) {
			if (inicio->codigoMeio == meios->codigo) {
				strcpy(tipo, meios->tipo);
				meios = NULL;
			}
			else {
				meios = meios->seguinte;
			}
		}

		if (gestor == 1) {
			printf("%6d | %-10s | %6d | %-20s | %6d | %5s | %6.2f\n",
				inicio->codigo, utilizador, inicio->codigoUtilizador, tipo, inicio->codigoMeio,
				checkSN(inicio->ativo), inicio->custo);
		}
		else {
			if (inicio->codigoUtilizador == utilizadorAtual) {
				printf("%6d | %-10s | %6d | %-20s | %6d | %5s | %6.2f\n",
					inicio->codigo, utilizador, inicio->codigoUtilizador, tipo, inicio->codigoMeio,
					checkSN(inicio->ativo), inicio->custo);
			}
		}
		inicio = inicio->seguinte;
	}
	printf("=============================================================================\n");
}

#pragma endregion

#pragma region alterarDados

int removerMeioAtivo(Meio* inicio, Aluguer* alugueres)
{
	//Meio* aux = inicio;
	Aluguer* auxAlugueres = alugueres;
	while (inicio != NULL)
	{
		alugueres = auxAlugueres;
		// Verificar se o meio tem algum aluguer ativo
		while (alugueres != NULL)
		{
			if ((inicio->codigo == alugueres->codigoMeio) && (alugueres->ativo == 1)) {
				inicio->historico = 1;
			}
			alugueres = alugueres->seguinte;
		}
		//aux = aux->seguinte;
		inicio = inicio->seguinte;
	}
	return (1);
}

int apagarUtilizador(Utilizador* inicio, int utilizadorApagar) {

	while (inicio != NULL)
	{
		if ((inicio->codigo == utilizadorApagar)) {
			inicio->historico = 1;
		}

		inicio = inicio->seguinte;
	}
	return (1);
}

void apagarMeio(Meio* inicio, int meioApagar)
{
	while (inicio != NULL)
	{
		if ((inicio->codigo == meioApagar)) {
			inicio->historico = 1;
		}

		inicio = inicio->seguinte;
	}
	return;
}

int atualizarSaldo(Utilizador* inicio, int codigo, float custo) {

	while (inicio != NULL)
	{
		if ((inicio->codigo == codigo) && (inicio->saldo < custo)) {
			return (0);
		}
		else if ((inicio->codigo == codigo))
		{
			inicio->saldo = (inicio->saldo - custo);
			return (1);
		}
		inicio = inicio->seguinte;
	}
	return (1);
}

#pragma endregion

#pragma region adicionarDadosDocumentos

int adicionarUtilizadores(Utilizador* inicio)
{
	FILE* fp;
	fp = fopen("dados/utilizadores.txt", "a");
	if (fp != NULL)
	{
		while (inicio != NULL)
		{
			fprintf(fp, "%d;%s;%s;%s;%.2f;%d-%d-%d;%d;%s;%d;%d\n",
				inicio->codigo, inicio->utilizador, inicio->nome, inicio->password, inicio->saldo,
				inicio->dataNascimento.ano, inicio->dataNascimento.mes, inicio->dataNascimento.dia,
				inicio->NIF, inicio->morada, inicio->gestor, inicio->historico);
			inicio = inicio->seguinte;
		}
		fclose(fp);
		return(1);
	}
	else return(0);
}

int adicionarMeios(Meio* inicio)
{
	FILE* fp;
	fp = fopen("dados/meios.txt", "a");
	if (fp != NULL)
	{
		while (inicio != NULL)
		{
			fprintf(fp, "%d;%s;%.2f;%.2f;%s;%.2f;%d\n",
				inicio->codigo, inicio->tipo, inicio->estado.bateria, inicio->estado.autonomia, inicio->estado.posicao.palavras, inicio->preco, inicio->historico);
			inicio = inicio->seguinte;
		}
		fclose(fp);
		return(1);
	}
	else return(0);
}

int adicionarAlugueres(Aluguer* inicio)
{
	FILE* fp;
	fp = fopen("dados/alugueres.txt", "a");
	if (fp != NULL)
	{
		while (inicio != NULL)
		{
			fprintf(fp, "%d;%d;%d;%d;%.2f\n",
				inicio->codigo, inicio->codigoUtilizador, inicio->codigoMeio, inicio->ativo, inicio->custo);
			inicio = inicio->seguinte;
		}
		fclose(fp);
		return(1);
	}
	else return(0);
}

#pragma endregion

#pragma region guardarDadosDocumentos

int guardarUtilizadores(Utilizador* inicio)
{
	FILE* fp;
	fp = fopen("dados/utilizadores.txt", "w");
	if (fp != NULL)
	{
		while (inicio != NULL)
		{
			fprintf(fp, "%d;%s;%s;%s;%.2f;%d-%d-%d;%d;%s;%d;%d\n",
				inicio->codigo, inicio->utilizador, inicio->nome, inicio->password, inicio->saldo,
				inicio->dataNascimento.ano, inicio->dataNascimento.mes, inicio->dataNascimento.dia,
				inicio->NIF, inicio->morada, inicio->gestor, inicio->historico);
			inicio = inicio->seguinte;
		}
		fclose(fp);
		return(1);
	}
	else return(0);
}

int guardarMeios(Meio* inicio)
{
	FILE* fp;
	fp = fopen("dados/meios.txt", "w");
	if (fp != NULL)
	{
		while (inicio != NULL)
		{
			fprintf(fp, "%d;%s;%.2f;%.2f;%s;%.2f;%d\n",
				inicio->codigo, inicio->tipo, inicio->estado.bateria, inicio->estado.autonomia, inicio->estado.posicao.palavras, inicio->preco, inicio->historico);
			inicio = inicio->seguinte;
		}
		fclose(fp);
		return(1);
	}
	else return(0);
}

int guardarAlugueres(Aluguer* inicio)
{
	FILE* fp;
	fp = fopen("dados/alugueres.txt", "w");
	if (fp != NULL)
	{
		while (inicio != NULL)
		{
			fprintf(fp, "%d;%d;%d;%d;%.2f\n",
				inicio->codigo, inicio->codigoUtilizador, inicio->codigoUtilizador, inicio->ativo, inicio->custo);
			inicio = inicio->seguinte;
		}
		fclose(fp);
		return(1);
	}
	else return(0);
}

#pragma endregion

#pragma region existeDados

int existeUtilizador(Utilizador* inicio, int codigo)
{
	while (inicio != NULL)
	{
		if (inicio->codigo == codigo) return(1);
		inicio = inicio->seguinte;
	}
	return(0);
}

int existeUser(Utilizador* inicio, char* utilizador)
{
	while (inicio != NULL)
	{
		if (!strcmp(inicio->utilizador, utilizador) && inicio->historico == 0) return(1);
		inicio = inicio->seguinte;
	}
	return(0);
}

int existeMeio(Meio* inicio, int codigo)
{
	while (inicio != NULL)
	{
		if (inicio->codigo == codigo) return(1);
		inicio = inicio->seguinte;
	}
	return(0);
}

int existeAluguer(Aluguer* inicio, int codigo)
{
	while (inicio != NULL)
	{
		if (inicio->codigo == codigo) return(1);
		inicio = inicio->seguinte;
	}
	return(0);
}

int existeAluguerMeio(Aluguer* inicio, int codigo)
{
	while (inicio != NULL)
	{
		if ((inicio->codigoMeio == codigo) && (inicio->ativo == 1)) return(1);
		inicio = inicio->seguinte;
	}
	return(0);
}

int existeAluguerAtivo(Aluguer* inicio, int codigo)
{
	while (inicio != NULL)
	{
		if ((inicio->codigoUtilizador == codigo) && (inicio->ativo == 1)) return(1);
		inicio = inicio->seguinte;
	}
	return(0);
}

#pragma endregion

#pragma region obterUltimoCodigo


int obterUltimoUtilizador(Utilizador* inicio) {
	int i = 0;
	while (inicio != NULL) {
		if (i < inicio->codigo) {
			i = inicio->codigo;
		}
		inicio = inicio->seguinte;
	}
	return (i);
}

int obterUltimoMeio(Meio* inicio) {
	int i = 0;
	while (inicio != NULL) {
		if (i < inicio->codigo) {
			i = inicio->codigo;
		}
		inicio = inicio->seguinte;
	}
	return (i);
}

int obterUltimoAluguer(Aluguer* inicio) {
	int i = 0;
	while (inicio != NULL) {
		if (i < inicio->codigo) {
			i = inicio->codigo;
		}
		inicio = inicio->seguinte;
	}
	return (i);
}

#pragma endregion

#pragma region menus

#pragma region opcoesGestor

int mG1() {
	printf("\n\nOperação especifica\n\n");
	return 1;
}

int mG2(Meio* meios, int opcao, char* posicao) {
	meios = lerMeios();
	switch (opcao)
	{
	case 1:
		ordenarMeios(meios, opcao);
		break;
	case 2:
		ordenarMeios(meios, opcao);
		break;
	case 3:
		ordenarMeios(meios, 1);
		break;
	}
	listarMeio(meios, 1, opcao, posicao);
	free(meios);
	meios = NULL;

	return 1;
}

int mG3(Meio* meios, int codigo, char* tipo, Estado estado, float preco) {
	meios = carregarMeio(meios, codigo, tipo, estado, preco, 0);

	int resp = adicionarMeios(meios);

	free(meios);
	meios = NULL;
	return resp;
}

int mG4() {
	printf("\n\nOperação especifica\n\n");
	return 1;
}

int mG5(Meio* meios, int codigo) {
	int resp = 0;
	meios = lerMeios(meios);
	if (existeMeio(meios, codigo)) {
		apagarMeio(meios, codigo);
		ordenarMeios(meios, 1);
		resp = guardarMeios(meios);
	}
	free(meios);
	meios = NULL;

	return resp;
}

int mG6(Utilizador* utilizadores) {
	utilizadores = lerUtilizadores();
	ordenarUtilizadores(utilizadores);
	listarUtilizador(utilizadores);
	free(utilizadores);
	utilizadores = NULL;

	return 1;
}

int mG7(Utilizador* utilizadores, int codigo, char* utilizador, char* nome, char* password, float saldo, Data dataNascimento, int NIF, char* morada, int gestor) {
	
	utilizadores = carregarUtilizador(utilizadores, codigo, utilizador, nome, password, saldo, dataNascimento, NIF, morada, gestor, 0);

	int resp = adicionarUtilizadores(utilizadores);

	free(utilizadores);
	utilizadores = NULL;
	return resp;
}

int mG8() {
	printf("\n\nOperação especifica\n\n");
	return 1;
}

int mG9(Utilizador* utilizadores, int codigo) {
	int resp = 0;
	utilizadores = lerUtilizadores(utilizadores);
	if (existeUtilizador(utilizadores, codigo)) {
		apagarUtilizador(utilizadores, codigo);
		ordenarUtilizadores(utilizadores);
		resp = guardarUtilizadores(utilizadores);
	}
	free(utilizadores);
	utilizadores = NULL;

	return resp;
}

int mG10(Utilizador* utilizadores, Aluguer* alugueres, Meio* meios, int utilizadorAtual) {
	meios = lerMeios();
	utilizadores = lerUtilizadores();
	alugueres = lerAlugueres();
	ordenarAlugueres(alugueres);
	listarAluguer(alugueres, utilizadores, meios, utilizadorAtual, 1);

	free(utilizadores);
	free(meios);
	free(alugueres);

	utilizadores = NULL;
	meios = NULL;
	alugueres = NULL;

	return 1;
}

int mG11() {
	printf("\n\nOperação especifica\n\n");
	return 1;
}

#pragma endregion

#pragma region opcoesCliente

int m1() {
	printf("\n\nOperação geral\n\n");
	return 1;
}

int m2(Aluguer* alugueres, Meio* meios, int opcao, char* posicao) {
	alugueres = lerAlugueres();
	meios = lerMeios();
	removerMeioAtivo(meios, alugueres);
	switch (opcao)
	{
	case 1:
		ordenarMeios(meios, opcao);
		break;
	case 2:
		ordenarMeios(meios, opcao);
		break;
	case 3:
		ordenarMeios(meios, 1);
		break;
	}

	listarMeio(meios, 0, opcao, posicao);

	free(alugueres);
	free(meios);

	meios = NULL;
	alugueres = NULL;

	return 1;
}

int m3(Utilizador* utilizadores, Aluguer* alugueres, int codigo, int codigoUtilizador, int codigoMeio, float custo) {
	int resp = 0;
	// !!! Verificar se o saldo permite o aluguer e remover o custo do saldo.
	utilizadores = lerUtilizadores();
	if (atualizarSaldo(utilizadores, codigoUtilizador, custo)){

		ordenarUtilizadores(utilizadores);
		guardarUtilizadores(utilizadores);

		alugueres = carregarAluguer(alugueres, codigo, codigoUtilizador, codigoMeio, 1, custo);
		resp = adicionarAlugueres(alugueres);
		free(alugueres);
		alugueres = NULL;
	}
	free(utilizadores);
	utilizadores = NULL;
	return resp;
}

int m4(Utilizador* utilizadores, Aluguer* alugueres, Meio* meios, int utilizadorAtual) {
	meios = lerMeios();
	utilizadores = lerUtilizadores();
	alugueres = lerAlugueres();
	ordenarAlugueres(alugueres);
	listarAluguer(alugueres, utilizadores, meios, utilizadorAtual, 0);

	free(utilizadores);
	free(meios);
	free(alugueres);

	utilizadores = NULL;
	meios = NULL;
	alugueres = NULL;
	return 1;
}

#pragma endregion

#pragma endregion