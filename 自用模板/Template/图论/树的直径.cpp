int n, d1[MAXN], d2[MAXN], d = 0;
vector<int> G[MAXN];

void DFS(int u, int fa) {
	d1[u] = d2[u] = 0;
	for(auto v : G[u]) {
		if(v == fa) continue;
		DFS(v, u);
		int cur = d1[v] + 1;
		if(cur > d1[u]) d2[u] = d1[u], d1[u] = cur;
		else if(cur > d2[u]) d2[u] = cur;
	} 
	d = max(d, d1[u] + d2[u]);
}
