/*
对于节点u 其子树范围 [ dfn[u], dfn[u] + sze[u] - 1 ] 
可用线段树等数据结构维护 
*/

void DFS(int u, int fa) {
	dfn[u] = ++cnt;
	sze[u] = 1;
	for(auto v : G[u]) {
		if(v == fa) continue;
		DFS(v, u);
		sze[u] += sze[v];
	}
}
