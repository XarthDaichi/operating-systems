#include <stdio.h>
#include <stdlib.h>

//int relacion(int a, int b) {
//    return (a < b) ? 1 : 0;
//}
//
//void burbuja(int *L, int len) {
//    int hayCambios = 1;
//    while (hayCambios) {
//        hayCambios = 0;
//        for (int i = 0; i < len -1; i++) {
//            if (relacion(L[i+1], L[i])) {
//                int T = L[i];
//                L[i] = L[i+1];
//                L[i+1] = T;
//                hayCambios += 1;
//            }
//        }
//    }
//}

/*void insercion(int *L, int len) {
     if (len == 0) return;
     int LTemp[len];
     for (int i = 1; i < len; i++) LTemp[i-1] = L[i];
     static int L0;
     insercion(LTemp, len-1);
     for (int i = 0; i < len -1; i++) {
         if (relacion(L[0], L0[i])) {
             L0[i] = L[0];
             for (int j = 0; j < len; j++) printf("%d ", L0[j]);
             printf(" <---- I returned this, not full\n");
             return;
         }
     }
     L0[len] = L[0];
     for (int i = 0; i < len; i++) printf("%d ", L0[i]);
     printf("<---- I returned this, full\n");
 }*/

//int * quicksort(int * L, int len) {
//    if (len == 0) return L;
//    int * Vic = malloc(sizeof(int) * len);
//    int * Per = malloc(sizeof(int) * len);
//    int lastVic = 0, lastPer = 0;
//    for (int i = 1; i < len; i++) {
//        if (relacion(L[i], L[0])) Vic[lastVic++] = L[i];
//        else Per[lastPer++] = L[i];
//    }
//    Vic = quicksort(Vic, lastVic);
//    Per = quicksort(Per, lastPer);
//    int L0 = L[0];
//    for (int i = 0; i < lastVic; i++) L[i] = Vic[i];
//    L[lastVic] = L0;
//    for (int i = 0; i < lastPer; i++) L[i+lastVic + 1] = Per[i];
//    return L;
//}

//int main() {
//    int Lista[7] = {3,1,-5,7,3,9,-3};
//    int len = sizeof(Lista)/sizeof(Lista[0]);
//
//    // burbuja(Lista, len);
//    // insercion(Lista, len);
//    int * returnList = malloc(sizeof(int) * (sizeof(Lista)/sizeof(Lista[0])));
//    returnList = quicksort(Lista, len);
//
//    for(int i = 0; i < 7; i++) {
//        if (returnList[i] && i != 6) {
//            printf("%d,", returnList[i]);
//        } else if (returnList[i] && i == 6) {
//            printf("%d", returnList[i]);
//        }
//    }
//}
