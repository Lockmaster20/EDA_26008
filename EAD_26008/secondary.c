#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "secondary.h"

///
///	Recebe um int
///	Se for 1 devolve "sim", se for 0 devolve "nao"
///
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

/// Funções para libertar a memória utilizada pelas ligas ligadas; 
/// Recebe a lista ligada, enquanto a lista não estiver vazia, liberta a memória da "atual" e passa para a seguinte

/// Liberta a memória utilizada pela lista de utilizadores
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

/// Liberta a memória utilizada pela lista de meios
void freeMeio(Meio* inicio) {
	Meio* aux;

	while (inicio != NULL)
	{
		aux = inicio;
		inicio = inicio->seguinte;
		free(aux);
	}
}

/// Liberta a memória utilizada pela lista de alugueres
void freeAluguer(Aluguer* inicio) {
	Aluguer* aux;

	while (inicio != NULL)
	{
		aux = inicio;
		inicio = inicio->seguinte;
		free(aux);
	}
}

#pragma endregion

#pragma region ordenarDados

///
///	Função para trocar os dados de uma lista de utilizadores para outra
///	Recebe dados de duas listas, copia os dados da primeira lista para uma lista auxiliar
///	Depois copia os dados da lista seguinte para a primeira lista
///	Por fim copia os dados da lista auxiliar para a segunda lista
///
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

///
///	Função para ordenar os utilizadores
///	Recebe a lista, se não estiver vazia verifica se o código do utilizador seguinte é menor
///	Se se verificar, executa a função para trocar as posições e marca que houve uma troca
/// 
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

///
///	Função para trocar os dados de uma lista de meios para outra
///	Recebe dados de duas listas, copia os dados da primeira lista para uma lista auxiliar
///	Depois copia os dados da lista seguinte para a primeira lista
///	Por fim copia os dados da lista auxiliar para a segunda lista
///
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

///
///	Função para ordenar os meios
///	Recebe a lista e a opção de ordenação
///	Se não estiver vazia verifica vai executar o código da opção introduzida
///	Se a opção for 1 vai ordenar por código, se for 2 vai ordenar por ordem decrescente de autonomia
///
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

///
///	Função para trocar os dados de uma lista de alugueres para outra
///	Recebe dados de duas listas, copia os dados da primeira lista para uma lista auxiliar
///	Depois copia os dados da lista seguinte para a primeira lista
///	Por fim copia os dados da lista auxiliar para a segunda lista
///
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

///
///	Função para ordenar os alugueres
///	Recebe a lista, se não estiver vazia verifica se o código do aluguer seguinte é menor
///	Se se verificar, executa a função para trocar as posições e marca que houve uma troca
///
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

/// Insere um novo registo na lista dos utilizadores
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

/// Insere um novo registo na lista dos meios
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

/// Insere um novo registo na lista dos alugueres
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

///
///	Função para ler os dados do ficheiro 'utilizadores.txt'
///	Para cada linha lê os dados e verifica se tem o número certo de dados
///	Se se verificar envia os dados para a função 'carregarUtilizador'
///
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

///
///	Função para ler os dados do ficheiro 'meios.txt'
///	Para cada linha lê os dados e verifica se tem o número certo de dados
///	Se se verificar envia os dados para a função 'carregarMeio'
///
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

///
///	Função para ler os dados do ficheiro 'alugueres.txt'
///	Para cada linha lê os dados e verifica se tem o número certo de dados
///	Se se verificar envia os dados para a função 'carregarAlugueres'
///
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

///
///	Função para listar os dados de uma lista de utilizadores
///	Recebe a lista, imprime a estrutura da lista e depois, para cada item da lista imprime os dados
///
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
	printf("==================================================================================================================================================\n\n");
}

/// Imprime os dados correspondentes ao codigo do utilizador recebido e altera o valor do saldo recebido
void listarUtilizadorSimples(Utilizador* inicio, int codigo, float* saldo)
{
	printf("==============================================\n");
	printf("\tDados Atuais\n");
	printf("==============================================\n");
	while (inicio != NULL)
	{
		if (inicio->codigo == codigo) {
			printf("Codigo: %d\nUtilizador: %s\nPassword: %s\nNome: %s\nMorada: %s\nData de Nascimento: %d-%d-%d\nNIF: %d\nSaldo: %.2f\nGestor: %s\n", 
				inicio->codigo, inicio->utilizador, inicio->password, inicio->nome, inicio->morada,
				inicio->dataNascimento.dia, inicio->dataNascimento.mes, inicio->dataNascimento.ano,
				inicio->NIF, inicio->saldo, checkSN(inicio->gestor));
			if (saldo != NULL)
				*saldo = inicio->saldo;
		}

		inicio = inicio->seguinte;
	}
	printf("==============================================\n");
}

///
///	Função para listar os dados de uma lista de meios
///	Recebe a lista de meios, um int para verificar se o utilizador é gestor e outro para a escolha do utilizador, e uma string para filtrar a localização 
///	Imprime a estrutura da lista de acordo com o tipo de utilizador
///	Para os gestores vai mostrar os meios todos e para os clientes só mostra os meios que não lê como histórico
///	Depois verifica a opção do utilizador para que, caso seja 3, só liste os meios na localização especificada
///
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

/// Imprime os dados correspondentes ao codigo do meio recebido
void listarMeioSimples(Meio* inicio, int codigo)
{
	printf("=====================================================================\n");
	printf("\tDados Atuais\n");
	printf("=====================================================================\n");
	while (inicio != NULL)
	{
		if (inicio->codigo == codigo) {
			printf("Codigo: %d\nTipo: %s\nBateria: %.2f\nAutonomia: %.2f\nLocalizacao: %s\nPreco: %.2f\n",
				inicio->codigo, inicio->tipo, inicio->estado.bateria, inicio->estado.autonomia,
				inicio->estado.posicao.palavras, inicio->preco);
		}

		inicio = inicio->seguinte;
	}
	printf("=====================================================================\n");
}

///
///	Função para listar os dados de uma lista de alugueres
///	Recebe 3 listas(alugueres, utilizadores e meios), um int para o código do utilizador atual e outro para verificar se é gestor
///	Imprime a estrutura da lista
///	Para cada aluguer vai obter o utilizador e meio correspondente
///	Depois imprime os alugueres todos, caso seja utiizador, ou apenas os do utilizador, caso seja cliente
///
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

/// Na lista, passa o utilizador especificado para histórico
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

///
///	Devolve 0 caso o utilizador não tenha saldo suficiente para o aluguer
///	Se puder realizar a ação, na lista, vai alterar o saldo do utilizador
///
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

/// Na lista, altera os dados do utilizador especificado, para os novos dados recebidos
int alterarUtilizador(Utilizador* inicio, int codigo, char* nome, char* password, float saldo, Data dataNascimento, int NIF, char* morada, int gestor)
{
	while (inicio != NULL)
	{
		if ((inicio->codigo == codigo)) {
			strcpy(inicio->nome, nome);
			strcpy(inicio->password, password);
			inicio->saldo = saldo;

			inicio->dataNascimento = dataNascimento;

			inicio->NIF = NIF;
			strcpy(inicio->morada, morada);
			inicio->gestor = gestor;
		}

		inicio = inicio->seguinte;
	}
	return;
}

///
///	Para cada meio, vai verificar se existe algum aluguer ativo com esse meio
///	Caso se verificar passa o meio para histórico na lista de meios recebida
///
int removerMeioAtivo(Meio* inicio, Aluguer* alugueres)
{
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
		inicio = inicio->seguinte;
	}
	return (1);
}

/// Na lista, passa o meio especificado para histórico
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

/// Na lista, altera os dados do meio especificado, para os novos dados recebidos
int alterarMeio(Meio* inicio, int codigo, char* tipo, Estado estado, float preco)
{
	while (inicio != NULL)
	{
		if ((inicio->codigo == codigo)) {
			strcpy(inicio->tipo, tipo);
			inicio->estado.bateria = estado.bateria;
			inicio->estado.autonomia = estado.autonomia;
			strcpy(inicio->estado.posicao.palavras, estado.posicao.palavras);

			inicio->preco = preco;
		}

		inicio = inicio->seguinte;
	}
	return;
}

/// Na lista, passa o aluguer especificado para não ativo
int terminarAluguer(Aluguer* inicio, int codigo) {
	while (inicio != NULL)
	{
		if ((inicio->codigo == codigo)) {
			inicio->ativo = 0;
		}

		inicio = inicio->seguinte;
	}
	return;
}

#pragma endregion

#pragma region adicionarDadosDocumentos

/// Adiciona os dados do utilizador da lista recebida no fim do documento
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

/// Adiciona os dados do meio da lista recebida no fim do documento
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

/// Adiciona os dados do aluguer da lista recebida no fim do documento
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

/// Escreve os dados do utilizador da lista recebida no documento
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

/// Escreve os dados do meio da lista recebida no documento
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

/// Escreve os dados do aluguer da lista recebida no documento
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

/// Verifica se, na lista, existe um utilizador com o código igual ao código recebido
int existeUtilizador(Utilizador* inicio, int codigo)
{
	while (inicio != NULL)
	{
		if (inicio->codigo == codigo) return(1);
		inicio = inicio->seguinte;
	}
	return(0);
}

/// Verifica se, na lista, existe um utilizador com o código igual ao código recebido e que esteja ativo
int existeUtilizadorAtivo(Utilizador* inicio, int codigo)
{
	while (inicio != NULL)
	{
		if (inicio->codigo == codigo && inicio->historico == 0) return(1);
		inicio = inicio->seguinte;
	}
	return(0);
}

/// Verifica se, na lista, existe um utilizador com o 'username' igual ao 'username' recebido
int existeUser(Utilizador* inicio, char* utilizador)
{
	while (inicio != NULL)
	{
		if (!strcmp(inicio->utilizador, utilizador) && inicio->historico == 0) return(1);
		inicio = inicio->seguinte;
	}
	return(0);
}

/// Verifica se, na lista, existe um meio com o código igual ao código recebido
int existeMeio(Meio* inicio, int codigo)
{
	while (inicio != NULL)
	{
		if (inicio->codigo == codigo) return(1);
		inicio = inicio->seguinte;
	}
	return(0);
}

/// Verifica se, na lista, existe um aluguer com o código igual ao código recebido
int existeAluguer(Aluguer* inicio, int codigo)
{
	while (inicio != NULL)
	{
		if (inicio->codigo == codigo) return(1);
		inicio = inicio->seguinte;
	}
	return(0);
}

/// Verifica se, na lista, existe um aluguer ativo com o código de meio igual ao código recebido
int existeAluguerMeio(Aluguer* inicio, int codigo)
{
	while (inicio != NULL)
	{
		if ((inicio->codigoMeio == codigo) && (inicio->ativo == 1)) return(1);
		inicio = inicio->seguinte;
	}
	return(0);
}

/// Verifica se, na lista, existe um aluguer ativo com o código de utilizador igual ao código recebido e altera o valor guardado no codigo de aluguer
int existeAluguerAtivo(Aluguer* inicio, int codigo, int* codigoAluguer)
{
	while (inicio != NULL)
	{
		if ((inicio->codigoUtilizador == codigo) && (inicio->ativo == 1)) {
			if (codigoAluguer != NULL)
				*codigoAluguer = inicio->codigo;
			return(1);
		} 
		inicio = inicio->seguinte;
	}
	return(0);
}

#pragma endregion

#pragma region obterUltimoCodigo

/// Passa por todos os utilizadores e devolve o código mais alto, devolvendo 0 se a lista estiver vazia
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

/// Passa por todos os meios e devolve o código mais alto, devolvendo 0 se a lista estiver vazia
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

/// Passa por todos os alugueres e devolve o código mais alto, devolvendo 0 se a lista estiver vazia
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

///
///	Função da 1a opção do menu de gestores
///	Recebe uma lista vazia e os dados introduzidos pelo utilizador
///	Carrega os utilizadores através dos documentos
///	Passa a lista e os dados para a função 'alterarUtilizador'
///	Depois de alterar os dados vai ordenar a lista por código e tenta guardar a lista ordenada no documento
///
int mG1(Utilizador* utilizadores, int codigo, char* nome, char* password, float saldo, Data dataNascimento, int NIF, char* morada, int gestor) {
	utilizadores = lerUtilizadores(utilizadores);
	alterarUtilizador(utilizadores, codigo, nome, password, saldo, dataNascimento, NIF, morada, gestor);
	ordenarUtilizadores(utilizadores);
	int resp = guardarUtilizadores(utilizadores);
	return resp;
}

///
///	Função para listar os meios de acordo com a opção escolhida pelo utilizador
///	Carrega os dados dos meios e ordena de acordo com a opção e depois lista os meios
///
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
	freeMeio(meios);
	meios = NULL;

	return 1;
}

///
///	Função para a 3a opção do menu de gestores
///	Recebe uma lista dos meios vazia e os dados introduidos pelo utilizador para o novo meio
///	Carrega um meio com os novos dados e passa para a função 'adicionarMeios'
///
int mG3(Meio* meios, int codigo, char* tipo, Estado estado, float preco) {
	meios = carregarMeio(meios, codigo, tipo, estado, preco, 0);

	int resp = adicionarMeios(meios);

	freeMeio(meios);
	meios = NULL;
	return resp;
}

///
///	Carrega os meios para uma lista vazia
///	Altera os dados do meio escolhido pelo utilizador através da função 'alterarMeio'
///	Ordena a lista dos meios e tenta guardar os dados no documento
///
int mG4(Meio* meios, int codigo, char* tipo, Estado estado, float preco) {
	meios = lerMeios(meios);
	alterarMeio(meios, codigo, tipo, estado, preco);
	ordenarMeios(meios, 1);
	int resp = guardarMeios(meios);
	return resp;
}

///
///	Função para "apagar" meio
///	Carrega os meios para uma lista e verifica se o meio existe
///	Se se verificar passa o meio para histórico, ordena a lista e tenta guardar os dados da lista no documento
///
int mG5(Meio* meios, int codigo) {
	int resp = 0;
	meios = lerMeios(meios);
	if (existeMeio(meios, codigo)) {
		apagarMeio(meios, codigo);
		ordenarMeios(meios, 1);
		resp = guardarMeios(meios);
	}
	freeMeio(meios);
	meios = NULL;

	return resp;
}

///
///	Função para listar os utilizadores
///	Carrega os dados dos utilizadores e ordena por código e depois lista os utilizadores
///
int mG6(Utilizador* utilizadores) {
	utilizadores = lerUtilizadores();
	ordenarUtilizadores(utilizadores);
	listarUtilizador(utilizadores);
	freeUtilizador(utilizadores);
	utilizadores = NULL;

	return 1;
}

///
///	Função para a 7a opção do menu de gestores
///	Recebe uma lista dos utilizadore vazia e os dados introduidos pelo utilizador para o novo utilizador
///	Carrega um utilizador com os novos dados e passa para a função 'adicionarUtilizadores'
///
int mG7(Utilizador* utilizadores, int codigo, char* utilizador, char* nome, char* password, float saldo, Data dataNascimento, int NIF, char* morada, int gestor) {
	
	utilizadores = carregarUtilizador(utilizadores, codigo, utilizador, nome, password, saldo, dataNascimento, NIF, morada, gestor, 0);

	int resp = adicionarUtilizadores(utilizadores);

	freeUtilizador(utilizadores);
	utilizadores = NULL;
	return resp;
}

///
///	Carrega os utilizadores para uma lista vazia
///	Altera os dados do utilizador escolhido pelo utilizador atual através da função 'alterarUtilizador'
///	Ordena a lista dos utilizadores e tenta guardar os dados no documento
///
int mG8(Utilizador* utilizadores, int codigo, char* nome, char* password, float saldo, Data dataNascimento, int NIF, char* morada, int gestor) {
	utilizadores = lerUtilizadores(utilizadores);
	alterarUtilizador(utilizadores, codigo, nome, password, saldo, dataNascimento, NIF, morada, gestor);
	ordenarUtilizadores(utilizadores);
	int resp = guardarUtilizadores(utilizadores);
	return resp;
}

///
///	Função para "apagar" um utilizador
///	Carrega os utilizadores para uma lista e verifica se o utilizador existe
///	Se se verificar passa o utilizador para histórico, ordena a lista e tenta guardar os dados da lista no documento
///
int mG9(Utilizador* utilizadores, int codigo) {
	int resp = 0;
	utilizadores = lerUtilizadores(utilizadores);
	if (existeUtilizador(utilizadores, codigo)) {
		apagarUtilizador(utilizadores, codigo);
		ordenarUtilizadores(utilizadores);
		resp = guardarUtilizadores(utilizadores);
	}
	freeUtilizador(utilizadores);
	utilizadores = NULL;

	return resp;
}

///
///	Função para listar os alugueres
///	Carrega os dados dos alugueres, utilizadores e meos, ordena por os alugueres por código e depois lista os alugueres com alguns dados das outras listas
///
int mG10(Utilizador* utilizadores, Aluguer* alugueres, Meio* meios, int utilizadorAtual) {
	meios = lerMeios();
	utilizadores = lerUtilizadores();
	alugueres = lerAlugueres();
	ordenarAlugueres(alugueres);
	listarAluguer(alugueres, utilizadores, meios, utilizadorAtual, 1);

	freeUtilizador(utilizadores);
	freeMeio(meios);
	freeAluguer(alugueres);

	utilizadores = NULL;
	meios = NULL;
	alugueres = NULL;

	return 1;
}

#pragma endregion

#pragma region opcoesCliente

///
///	Função da 1a opção do menu de clientes
///	Recebe uma lista vazia e os dados introduzidos pelo utilizador
///	Carrega os utilizadores através dos documentos
///	Passa a lista e os dados para a função 'alterarUtilizador'
///	Depois de alterar os dados vai ordenar a lista por código e tenta guardar a lista ordenada no documento
///
int m1(Utilizador* utilizadores, int codigo, char* nome, char* password, float saldo, Data dataNascimento, int NIF, char* morada, int gestor) {
	utilizadores = lerUtilizadores(utilizadores);
	alterarUtilizador(utilizadores, codigo, nome, password, saldo, dataNascimento, NIF, morada, gestor);
	ordenarUtilizadores(utilizadores);
	int resp = guardarUtilizadores(utilizadores);
	return resp;
}

///
///	Função para listar os meios disponíveis de acordo com a opção escolhida pelo utilizador
///	Carrega os dados dos meios e dos alugueres e envia as listas para a função 'removerMeioAtivo'
///	Ordena os meios de acordo com a opção e depois lista os meios disponíveis
///
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

	freeAluguer(alugueres);
	freeMeio(meios);

	meios = NULL;
	alugueres = NULL;

	return 1;
}

///
///	Função para alugar um meio
///	Recebe a lista dos alugueres e os dados introduzidos pelo utilizador
///	Carrega os utilizadores e verifica se posde alugar o meio
///	Se o puder realizar, atualiza o saldo e cria o aluguer
///
int m3(Utilizador* utilizadores, Aluguer* alugueres, int codigo, int codigoUtilizador, int codigoMeio, float custo) {
	int resp = 0;
	// Verificar se o saldo permite o aluguer e remover o custo do saldo.
	utilizadores = lerUtilizadores();
	if (atualizarSaldo(utilizadores, codigoUtilizador, custo)){

		ordenarUtilizadores(utilizadores);
		guardarUtilizadores(utilizadores);

		alugueres = carregarAluguer(alugueres, codigo, codigoUtilizador, codigoMeio, 1, custo);
		resp = adicionarAlugueres(alugueres);
		freeAluguer(alugueres);
		alugueres = NULL;
	}
	freeUtilizador(utilizadores);
	utilizadores = NULL;
	return resp;
}

/// Recebe a lista com os alugueres e o código do utilizador, executa a função 'terminarAluguer', ordena a lista e tenta guardar a lista ordenada no documento
int m4(Aluguer* alugueres, int codigo) {
	int resp = 0;
	terminarAluguer(alugueres, codigo);

	ordenarAlugueres(alugueres);
	resp = guardarAlugueres(alugueres);

	return resp;
}

///
///	Função para mostrar os alugueres realizados pelo utilizador
///	Carrega os dados para as listas correspondentes, e depois lista os alugueres do utilizador da sessão
///
int m5(Utilizador* utilizadores, Aluguer* alugueres, Meio* meios, int utilizadorAtual) {
	meios = lerMeios();
	utilizadores = lerUtilizadores();
	alugueres = lerAlugueres();
	ordenarAlugueres(alugueres);
	listarAluguer(alugueres, utilizadores, meios, utilizadorAtual, 0);

	freeUtilizador(utilizadores);
	freeMeio(meios);
	freeAluguer(alugueres);

	utilizadores = NULL;
	meios = NULL;
	alugueres = NULL;
	return 1;
}

#pragma endregion

#pragma endregion