#include <stdio.h>
int main() {
    int tests;
    scanf("%d", &tests);
    for(tests; tests > 0; tests--) {
        long long int cartas_test;
        scanf("%lld", &cartas_test);
        while (cartas_test >= 2) {
		long long int inf = 1;
		long long int sup = (cartas_test < 81650) ? cartas_test : 81650;
		long long int m = (inf + sup) / 2;
		while (inf + 1 < sup) {
			if ((long long int) m*(3*m + 1)/2 > cartas_test) sup = m;
			else inf = m;
			m = (inf + sup) / 2;
		}
		cartas_test -= (long long int) m*(3*inf + 1)/2;
		printf((cartas_test<2)?"%lld":"%lld ", inf);
        }
        printf("\n");
    }
    return 0;
}
