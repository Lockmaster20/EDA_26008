//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct registoPos {
	char word1[19];
	char word2[19];
	char word3[19];
} Posicao;

typedef struct registo {
	int codigo;
	char tipo[50];
	float bateria;
	float autonomia;
	Posicao posicao[1];			// posi��o do meio atrav�s de 3 palavras (what3words.com)
	struct registo* seguinte;	// endere�o de mem�ria para uma strucr registo
} Meio;

main() {
	//Fazer com listas ligadas porque ocupam menos espa�o na mem�ria, porque n�o � necess�rio dedicar mem�ria ao definir a sruct
	//cada "meio" regista o endere�o do pr�ximo "meio"
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa\n");
}

/*

Meio* inserirMeio(Meio* inicio, int cod, char tipo[], float bat, float aut);

int listarMeios(Meio* inicio);

int existeMeio(Meio* inicio, int cod);

Meio* removerMeio(Meio* inicio, int cod);

*/

//Inserir novo registo
Meio* inserirMeio(Meio* inicio, int cod, char tipo[], float bat, float aut) {
	if (!existeMeio(inicio, cod)) {
		Meio* novo = malloc(sizeof(struct registo));
		if (novo != NULL) {
			novo->codigo = cod;
			strcpy(novo->tipo, tipo);
			novo->bateria = bat;
			novo->autonomia = aut;
			novo->seguinte = inicio;
			return(novo);
		}
	}
	else return(inicio);
}

int existeMeio(Meio* inicio, int cod) { 
	while (inicio != NULL) { 
		if (inicio->codigo == cod) return(1); 
		inicio = inicio->seguinte; 
	} 
	return(0);
}

void listarMeios(Meio* inicio){
	while (inicio != NULL) {
		printf("%d %s %.2f %.2f\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia);
		inicio = inicio->seguinte;
	}
}
