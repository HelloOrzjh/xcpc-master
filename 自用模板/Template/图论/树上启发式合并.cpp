// 轻重链剖分
void DFS(int u, int fa) {
	dfn[u] = ++tot, node[tot] = u, sze[u] = 1;
	for(auto v : G[u]) {
		if(v == fa) continue;
		DFS(v, u);
		if(sze[v] > sze[ son[u] ]) son[u] = v;
		sze[u] += sze[v];
	}
}

void add(int pos) { }
void del(int pos) { }
int getAns() { }

void DSU(int u, int fa, bool st) {
	for(auto v : G[u]) if(v != fa && v != son[u]) DSU(v, u, 0);
	if(son[u]) DSU(son[u], u, 1);
	for(auto v : G[u]) {
		if(v == fa || v == son[u]) continue;
		for(int i = dfn[v]; i < dfn[v] + sze[v]; i++) add(node[i]);
	}
	add(u);
	ans[u] = getAns();
	if(!st) for(int i = dfn[u]; i < dfn[u] + sze[u]; i++) del(node[i]);
}

void Solve() {
	DFS(1, 0);
	DSU(1, 0, 0);
}