bool Match(int x) {
	for(int i = 1; i <= m; i++) {
		if(G[x][i] && !vis[i]) {
			vis[i] = 1;
			if(!a[i] || Match(a[i])) {
				a[i] = x;
				return true;
			}
		}
	}
	return false;
}

int main() {
	scanf("%d%d%d", &n, &m, &e);
	for(int i = 1; i <= e; i++) {
		int u, v; scanf("%d%d", &u, &v);
		G[u][v] = 1;
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));
		if(Match(i)) ans++;
	}
	printf("%d", ans);
	return 0;
}
