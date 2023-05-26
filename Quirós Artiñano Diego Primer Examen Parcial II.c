#include <stdio.h>
#include <stdlib.h>

//Siempre van a ser menos de 10000 nodos...
int grafo[10000][10000];

int pila[10000]; //por si llegaran a necesitarla
int TOPE = -1; //por si llegaran a necesitar un tope para la pila...
int visitados[10000]; //para algo debe servir

int CANT;

void leerGrafo(){
	scanf("%d",&CANT);
	for(int i = 0; i<CANT; i++)
		for(int j = 0; j<CANT; j++)
			scanf("%d",&grafo[i][j]);
}

void depthFirstTravel(int nodoAhora) {
    visitados[nodoAhora] = 1;
    for (int i = 0; i < CANT; i++) {
        if (grafo[nodoAhora][i] == 1 && visitados[i] == 0) depthFirstTravel(i);
    }
}

int esConexo(){
    depthFirstTravel(0);
    for (int i = 0; i < CANT; i++)
        if (visitados[i] == 0) return 0;
	return 1;
}


int main(){
	leerGrafo();
	if(esConexo())printf("SI\n");
	else printf("NO\n");
	return 0;
}

