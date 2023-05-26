#include <stdio.h>

int main() {
	int testing_number;
	scanf("%d",&testing_number);
	int output = (testing_number < 10) ? testing_number : 10;
	printf("%d",output);
	return 0;
}
