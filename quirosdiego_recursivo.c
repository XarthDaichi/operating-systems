#include <stdio.h>

void binary_search(long long int cards, long long int inf, long long sup) {
	if (cards < 2) {
		printf("\n");
		return;	
	}
	if (inf + 1 >= sup) {
		printf("%lld ", inf);
		long long int temp_cards = cards - inf*(3*inf+1)/2;
		binary_search(temp_cards, 1, temp_cards);
		return;
	}
	long long int m = (inf + sup) /2;
	if ((long long int) m*(3*m+1)/2 > cards) return binary_search(cards, inf, m);
	return binary_search(cards, m, sup);
}

int main() {
	int test;
	for(scanf("%d",&test); test > 0; test--) {
		long long int test_cards;
		scanf("%lld",&test_cards);
		binary_search(test_cards, 1, (test_cards < 81650) ? test_cards : 81650);
	}
	return 0;
}
