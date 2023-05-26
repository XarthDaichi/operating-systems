// int suma_factores_propios(int n) {
// 	int s = 1;
// 	for (int i = 2; i * i <= n; i++) {
// 		if (i * i == n) s += i;
// 		else if ( n % i == 0)
// 			s += n/i + 1;
// 	}
// 	return s;
// }




// si se vuelan n papeles y se agarran n-1 papeles, cual falta? manera eficiente

int papeles (int n, int* a) {
	int r = 0;
	for (int i = 0; i < n; i++)
		r ^= (i + 1) ^ a[i];
	return r;
}