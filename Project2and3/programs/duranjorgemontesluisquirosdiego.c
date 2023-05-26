/*
    Jorge Durán Campos
    Luis Montes de Oca Ruiz
    Diego Quirós Artiñano
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>

#define BUFFERLEN 1000

static pthread_mutex_t solution_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER;

static pthread_cond_t read_condition = PTHREAD_COND_INITIALIZER;
static pthread_cond_t consumed_condition = PTHREAD_COND_INITIALIZER;

static unsigned char buffer[BUFFERLEN];
static long pos_p = 0;
static long pos_c = 0;

int flag = 1;

static int solution_array[256] = {0};
static int solution_aux[256];

static int producers_num;
static int consumers_num;

static char *filepath;
static long filelen;
static long consumers_final_pos;

void merge(int arr1[], int arr2[], int left1[], int left2[], int left_size, int right1[], int right2[], int right_size) {
	int i = 0, j = 0, k = 0;
	while (i < left_size && j < right_size) {
		if (left1[i] >= right1[j]) {
			arr1[k] = left1[i];
			arr2[k] = left2[i];
			i++;
		}
		else {
			arr1[k] = right1[j];
			arr2[k] = right2[j];
			j++;
		}
		k++;
	}
	
	while (i < left_size) {
		arr1[k] = left1[i];
		arr2[k] = left2[i];
		i++;
		k++;
	}
	
	while (j < right_size) {
		arr1[k] = right1[j];
		arr2[k] = right2[j];
		j++;
		k++;
	}
}

void mergesort(int arr1[], int arr2[], int size) {
	if (size < 2)
		return;
	
	int mid = size / 2;
	int *left1 = (int*) malloc(mid * sizeof(int));
	int *left2 = (int*) malloc(mid * sizeof(int));
	int *right1 = (int*) malloc((size - mid) * sizeof(int));
	int *right2 = (int*) malloc((size - mid) * sizeof(int));
	
	for (int i = 0; i < mid; i++) {
		left1[i] = arr1[i];
		left2[i] = arr2[i];
	}
	
	for (int i = mid; i < size; i++) {
		right1[i - mid] = arr1[i];
		right2[i - mid] = arr2[i];
	}
	
	mergesort(left1, left2, mid);
	mergesort(right1, right2, size - mid);
	merge(arr1, arr2, left1, left2, mid, right1, right2, size - mid);
	
	free(left1);
	free(left2);
	free(right1);
	free(right2);
}

void *reading_file() {
    FILE *fileptr;
    fileptr = fopen(filepath, "rb");
    while(!feof(fileptr)) {
        pthread_mutex_lock(&buffer_mutex);
        if (feof(fileptr)) {
            flag = 0;
            pthread_mutex_unlock(&buffer_mutex);
            pthread_exit((void*)0);
        }
        fseek(fileptr, pos_p, SEEK_SET);
        fread(buffer+(pos_p%BUFFERLEN), 1, 1, fileptr);
        if (pos_p >= BUFFERLEN) {
            while((pos_p+1) % BUFFERLEN == pos_c % BUFFERLEN) {
                pthread_cond_wait(&consumed_condition, &buffer_mutex);
            }
        }
        pos_p++;
        if (feof(fileptr)) flag = 0;
        pthread_mutex_unlock(&buffer_mutex);
        pthread_cond_broadcast(&read_condition);
    }
    fclose(fileptr);
    flag = 0;
    pthread_exit((void*)0);
}

void *adding_to_array() {
    while(filelen) {
        pthread_mutex_lock(&solution_mutex);
        if(!filelen) {
            pthread_mutex_unlock(&solution_mutex);
            pthread_exit((void*)0);
        }
        while(pos_c >= pos_p && flag) {
            pthread_cond_wait(&read_condition, &solution_mutex);
        }
        if(!filelen) {
            pthread_mutex_unlock(&solution_mutex);
            pthread_exit((void*)0);
        }
        solution_array[buffer[pos_c%BUFFERLEN]]++;
        pos_c++;
        filelen--;
        pthread_mutex_unlock(&solution_mutex);
        pthread_cond_broadcast(&consumed_condition);
    }
    pthread_exit((void*)0);
}

int main(int argc, char *argv[]) {
    for (int i = 0; i < 256; i++) solution_aux[i] = i;
    
    if (argc > 1) producers_num = atoi(argv[1]);
    else {
        printf("Falta el numero de productores");
        return -1;
    }

    if (argc > 2) consumers_num = atoi(argv[2]);
    else {
        printf("Falta el numero de consumidores");
        return -1;
    }

    if (argc > 3) filepath = (argv[3]);
    else {
        printf("Falta la dirección del archivo");
        return -1;
    }

    pthread_t producers[producers_num];
    pthread_t consumers[consumers_num];

    FILE *fileptr;
    fileptr = fopen(filepath, "rb");
    if (fileptr == NULL) {
        printf("Fallo la apertura del documento");
        return -1;
    }
    fseek(fileptr, 0, SEEK_END);
    filelen = ftell(fileptr);
    rewind(fileptr);
    fclose(fileptr);
    for (int i = 0; i < producers_num; i++) {
        if (pthread_create(&producers[i], NULL, reading_file, NULL) != 0) {
            printf("No se pudo crear el hilo de productores");
            return -1;
        }
    }

    for (int i = 0; i < consumers_num; i++) {
        if (pthread_create(&consumers[i], NULL, adding_to_array, NULL) != 0) {
            printf("No se pudo crear el hilo de consumidores");
            return -1;
        }
    }

    for (int i = 0; i < producers_num; i++) {
        if (pthread_join(producers[i], NULL)) {
            printf("No se pudo unir el hilo de productores");
            return -1;
        }
    }

    for (int i = 0; i < consumers_num; i++) {
        if (pthread_join(consumers[i], NULL)) {
            printf("No se pudo unir el hilo de consumidores");
            return -1;
        }
    }

    mergesort(solution_array, solution_aux, 256);

    for (int i = 0; i < 256; i++) {
        if (solution_array[i] != 0) printf("%d aparece %d veces\n", solution_aux[i], solution_array[i]);
    }

    pthread_mutex_destroy(&solution_mutex);
    pthread_mutex_destroy(&buffer_mutex);
    pthread_cond_destroy(&consumed_condition);
    pthread_cond_destroy(&read_condition);
    return 0;
}