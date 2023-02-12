int inv(int x, int MOD) {	// ÇóÄæÔª 
	return qpow(x, MOD - 2, MOD);
}

void Init() {
	fact[0] = 1;
	for(int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD;

	inv[n] = inv(fact[n], MOD);
	for(int i = n - 1; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % MOD;
}

int C(int n, int m) {
	if(m > n) return 0;
	return fact[n] * inv[m] % MOD * inv[n - m] % MOD;
}

int Lucas(int n, int m) {
	if(m == 0) return 1;
	return C(n % MOD, m % MOD) * Lucas(n / MOD, m / MOD) % MOD;
}
