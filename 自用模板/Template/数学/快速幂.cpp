// 快速乘 适用正数 
int qmul(int a, int b, int MOD) {
	int ans = 0;
	while(b > 0) {
		if(b & 1) ans = (ans + a) % MOD;
		b >>= 1;
		a = (a << 1) % MOD;
	}
	return ans;
}

// 快速幂 
int qpow(int a, int p, int MOD) {
	int ans = 1;
	while(p > 0) {
		if(p & 1) ans = ans * a % MOD;
		p >>= 1;
		a = a * a % MOD;
	}
	return ans;
}

// 矩阵快速幂 
struct Martix {
	long long c[MAXN][MAXN];
}A, E;

Martix operator * (const Martix &a, const Martix &b) {
	Martix Ans;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) Ans.c[i][j] = 0;
	for(int k = 1; k <= n; k++) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) Ans.c[i][j] = (Ans.c[i][j] + a.c[i][k] * b.c[k][j] % MOD) % MOD;
		}
	}
	return Ans;
}

Martix MartixQuickPow(Martix A, int k) {
	Martix ans, now;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) ans.c[i][j] = 0;
		ans.c[i][i] = 1;
	}
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) now.c[i][j] = A.c[i][j];
	while(k > 0) {
		if(1 & k) ans = ans * now;
		now = now * now; 
		k = k >> 1;
	}
	return ans;
}
