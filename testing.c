#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[]) {
	char test;
	if (argc > 1) test = *argv[1];
	printf("%d", test);
	return 0;
}
