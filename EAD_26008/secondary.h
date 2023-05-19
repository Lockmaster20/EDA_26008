#include <stdio.h>

#define LOC_SIZE 57	// Tamanho máximo das 3 palavras + pontos a separar
#define INF INT_MAX // Define infinito como o valor mais alto possível de int

// !!!!!!!!!!!!!!!!
//int shortestPath(Grafo* graph, int src, int dest, int V);

#pragma region structs

typedef struct registoData {
	int ano, mes, dia;
} Data;

typedef struct registoPosicao {
	char palavras[LOC_SIZE];
} Posicao;

typedef struct registoContacto {
	char tipoContacto[10];
	char contacto[30];
} Contacto;

typedef struct registoEstado {
	float bateria;
	float autonomia;
	Posicao posicao;
} Estado;

typedef struct registoPreco {
	float precoBase;
	float precoAdicional;			// preco por minuto
} Preco;

typedef struct registoMeio {
	int codigo;
	char tipo[21];
	Estado estado;
	Preco preco;
	int historico;
	struct registoMeio* seguinte;	// endereço de memória para uma struct
} Meio;

typedef struct registoUtilizador {
	int codigo;
	char utilizador[11];			// Nome para iniciar sessão
	char nome[41];					// Nome normal
	char password[11];				// Ex: "12ab567890" + \n
	float saldo;
	Data dataNascimento;
	int NIF;
	char morada[31];
	//Contacto contacto[3];			// máximo de 3 contactos por cliente
	int gestor;
	int historico;					// verifica se foi "eliminado"
	struct registoUtilizador* seguinte;
} Utilizador;

typedef struct registoAluguer {
	int codigo;
	int codigoUtilizador;
	int codigoMeio;
	int dataInicio, dataFim;
	//Estado estadoInicial, estadoFinal;
	int ativo;
	float custo;					// preço total do aluguer
	struct registoAluguer* seguinte;
} Aluguer;

typedef struct registoCaminhos
{
	int codigoLocal;
	int distancia;
	struct registoCaminhos* seguinte;
} *Caminho;

typedef struct registoGrafo
{
	int codigoLocal_h;
	char local[LOC_SIZE];
	Caminho caminhos;
	struct registoGrafo* seguinte;
} Grafo;

typedef struct registoDistancia
{
	int codigoLocal;
	char local[LOC_SIZE];
	int distancia;
	struct registoDistancia* seguinte;
} Distancia;

#pragma endregion

#pragma region libertarMemoria

void freeUtilizador(Utilizador* inicio);

void freeMeio(Meio* inicio);

void freeAluguer(Aluguer* inicio);

#pragma endregion

#pragma region lerDocumentos

Utilizador* lerUtilizadores();

Meio* lerMeios();

Aluguer* lerAlugueres();

Grafo* lerLocais(); 

int lerCaminhos(Grafo* grafo);

#pragma endregion

#pragma region listarDados

void listarUtilizadorSimples(Utilizador* inicio, int codigo, float* saldo);

void listarMeioSimples(Meio* inicio, int codigo);

#pragma endregion

#pragma region existeDados

int existeUtilizador(Utilizador* inicio, int codigo);
int existeUtilizadorAtivo(Utilizador* inicio, int codigo);
int existeUser(Utilizador* inicio, char* utilizador);
int existeMeio(Meio* inicio, int codigo);
int existeAluguer(Aluguer* inicio, int codigo);
int existeAluguerMeio(Aluguer* inicio, int codigo);
int existeAluguerAtivo(Aluguer* inicio, int codigo, int* codigoAluguer);
int existeLocal(Grafo* inicio, char* local);

#pragma endregion

#pragma region obterUltimoCodigo

int obterUltimoUtilizador(Utilizador* inicio);
int obterUltimoMeio(Meio* inicio);
int obterUltimoAluguer(Aluguer* inicio);

#pragma endregion

#pragma region menus

void escolherMenu(int utilizadorAtual, char* nomeAtual, int gestor);

#pragma region opcoesGestor

int mG1(Utilizador* utilizadores, int codigo, char* nome, char* password, float saldo, Data dataNascimento, int NIF, char* morada, int gestor);

int mG2(Meio* meios, int opcao, char* posicao);

int mG3(Meio* meios, int codigo, char* tipo, Estado estado, float precoBase, float precoAdicional);

int mG4(Meio* meios, int codigo, char* tipo, Estado estado, float precoBase, float precoAdicional);

int mG5(Meio* meios, int codigo);

int mG6(Utilizador* utilizadores);

int mG7(Utilizador* utilizadores, int codigo, char* utilizador, char* nome, char* password, float saldo, Data dataNascimento, int NIF, char* morada, int gestor);

int mG8(Utilizador* utilizadores, int codigo, char* nome, char* password, float saldo, Data dataNascimento, int NIF, char* morada, int gestor);

int mG9(Utilizador* utilizadores, int codigo);

int mG10(Utilizador* utilizadores, Aluguer* alugueres, Meio* meios, int utilizadorAtual);

#pragma endregion

#pragma region opcoesCliente

int m1(Utilizador* utilizadores, int codigo, char* nome, char* password, float saldo, Data dataNascimento, int NIF, char* morada, int gestor);

int m2(Aluguer* alugueres, Meio* meios, int opcao, char* posicao);

int m3(Utilizador* utilizadores, Aluguer* alugueres, int codigo, int codigoUtilizador, int codigoMeio);

int m4(Utilizador* utilizadores, Aluguer* alugueres, Meio* meios, int codigo);

int m5(Utilizador* utilizadores, Aluguer* alugueres, Meio* meios, int utilizadorAtual);

#pragma endregion

#pragma endregion