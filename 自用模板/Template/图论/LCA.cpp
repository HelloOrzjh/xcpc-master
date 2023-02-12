int n, m, dep[MAXN], vis[MAXN], lca[MAXN][25];
vector<int> G[MAXN];

void DFS(int u, int ftr) {
	dep[u] = dep[ftr] + 1;
	vis[u] = 1;
	lca[u][0] = ftr;
	for(int i = 1; i <= 20; i++) {
		if(dep[u] < (1 << i)) break;
		lca[u][i] = lca[lca[u][i - 1]][i - 1];
	}
	for(int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if(vis[v]) continue;
		DFS(v, u);
	}
}

int LCA(int x, int y) {
	int u = x, v = y;
	if(dep[u] > dep[v]) swap(u, v); //dep[u] <= dep[v]
	for(int i = 20; i >= 0; i--) {
		if((1 << i) & (dep[v] - dep[u])) v = lca[v][i];
	}
	for(int i = 20; i >= 0; i--) {
		if(lca[u][i] != lca[v][i]) {
			u = lca[u][i];
			v = lca[v][i];
		}
	}
	return u == v ? u : lca[u][0];
}


