/*
���ڽڵ�u ��������Χ [ dfn[u], dfn[u] + sze[u] - 1 ] 
�����߶��������ݽṹά�� 
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
