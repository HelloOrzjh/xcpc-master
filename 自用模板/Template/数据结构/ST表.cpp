void Prework() {
	for(int k = 1; (1 << k) <= n; k++) {
		for(int i = 1; i <= n; i++) {
			st[i][k] = max(st[i][k - 1], st[i + (1 << (k - 1) )][k - 1]);
		}
	}
}

int Query(int l, int r) {
	int t = floor(log2(r - l + 1));
	return max(st[l][t], st[r - (1 << t) + 1][t]);
}
