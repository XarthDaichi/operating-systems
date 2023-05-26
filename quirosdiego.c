#include <stdio.h>
int main() {
	int tests;
	for(scanf("%d",&tests); tests > 0; tests--) {
		long long int test_cards;
		scanf("%lld", &test_cards);
		while(test_cards >= 2) {
			long long int inf = 1;
			long long int sup = (test_cards < 81650) ? test_cards : 81650; // 81649 is the highest level you can reach before using 10^10 cards
			while (inf + 1 < sup) {
				long long int m = (inf + sup)/2;
				if ((long long int) m*(3*m+1)/2 > test_cards) sup = m;
				else inf = m;
			}
			test_cards -= (long long int) inf*(3*inf +1)/2;
			printf("%lld ", inf);
		}
		printf("\n");
	}
	return 0;
}
