```c
long long int pow(int a, int n) {
	if (!n) return 1;
	long long int r = pow(a, n>>1);
	r *= r;
	if (n % 2) r *= a;
	return r;
} //  Si a = 2 puede hacer 1 << n (queda en O(1);
```


```c
static int M[2][2] = {{0,1}, {1,1}};




int main() {
	
	return 0;
}
```