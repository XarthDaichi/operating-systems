#include <stdio.h>
#include <stdlib.h>

//Siempre van a ser menos de 40000 vectores...
int vectoresTridimensionales[40000][3];

int CANT;

int relacion(int a, int b) {
    return (a < b) ? 1 : 0;
}

int* quicksort(int * vec, int len) {
    if (len == 0) return vec;
    int * Vic = (int *) malloc(len * 3 * sizeof(int));

    int * Per = (int *) malloc(len * 3 * sizeof(int));
    int lastVic = 0; int lastPer = 0;
    for (int i = 1; i < len; i++) {
        if (relacion(vec[i * 3 + 0], vec[0])) {
            Vic[lastVic * 3 + 0] = vec[i * 3 + 0];
            Vic[lastVic * 3 + 1] = vec[i * 3 + 1];
            Vic[lastVic * 3 + 2] = vec[i * 3 + 2];
            lastVic++;
            continue;
        } else if (vec[i * 3 + 0] == vec[0]) {
            if (relacion(vec[i * 3 + 1], vec[0*3 +1])) {
                Vic[lastVic * 3 + 0] = vec[i * 3 + 0];
                Vic[lastVic * 3 + 1] = vec[i * 3 + 1];
                Vic[lastVic * 3 + 2] = vec[i * 3 + 2];
                lastVic++;
                continue;
            } else if (vec[i * 3 + 1] == vec[1]) {
                if (relacion(vec[i * 3 + 2], vec[0*3 +2])) {
                    Vic[lastVic * 3 + 0] = vec[i * 3 + 0];
                    Vic[lastVic * 3 + 1] = vec[i * 3 + 1];
                    Vic[lastVic * 3 + 2] = vec[i * 3 + 2];
                    lastVic++;
                    continue;
                }
            }
        }
        Per[lastPer * 3 + 0] = vec[i * 3 + 0];
        Per[lastPer * 3 + 1] = vec[i * 3 + 1];
        Per[lastPer * 3 + 2] = vec[i * 3 + 2];
        lastPer++;
    }

    Vic = quicksort(Vic, lastVic);
    Per = quicksort(Per, lastPer);
    int vec0[3];
    for (int i = 0; i < 3; i++) vec0[i] = vec[i];

    for (int i = 0; i < lastVic; i++) {
        for (int j = 0; j < 3; j++) {
            vec[i * 3 + j] = Vic[i * 3 + j];
        }
    }
    for (int i = 0; i < 3; i++) vec[lastVic * 3 + i] = vec0[i];
    for (int i = 0; i < lastPer; i++) {
        for (int j = 0; j < 3; j++) {
            vec[(i+lastVic+1) * 3 + j] = Per[i * 3 + j];
        }
    }
    return vec;
}

void ordenar(){
	int* tempVectoresTridimensionales = quicksort(vectoresTridimensionales, CANT);
    for (int i = 0; i < CANT; i++)
        for (int j = 0; j < 3; j++)
            vectoresTridimensionales[i][j] = tempVectoresTridimensionales[i * 3 + j];
    return;
}

void leerVectores(){
	scanf("%d",&CANT);
	int i = CANT;
	while(i--){
		scanf("%d %d %d",&vectoresTridimensionales[CANT-i-1][0],
				 &vectoresTridimensionales[CANT-i-1][1],
				 &vectoresTridimensionales[CANT-i-1][2]);
	}
}

void escribirVector(){
	for(int i = 0; i<CANT;i++)
		printf("%d %d %d\n", vectoresTridimensionales[i][0],
				     vectoresTridimensionales[i][1],
				     vectoresTridimensionales[i][2]);
}


int main(){
	leerVectores();
	ordenar();
	escribirVector();
	return 0;
}

