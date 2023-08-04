#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int number = 2100;
    printf("original: %d", number);
    number = number << 6&255;
    printf("test: %d", number);
    return 0;
}