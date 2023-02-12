const int N;

int dfn[N], low[N], s[N], vis[N], color[N], top = 0, sum = 0, dep = 0;
int n, m;
vector<int> G[N];

// 求强连通分量 复杂度O(E+V)
void Tarjan(int u) {
	dfn[u] = low[u] = ++dep;
	vis[u] = 1;
	s[++top] = u;
	
	for(int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if(!dfn[v]) Tarjan(v), low[u] = min(low[u], low[v]);
		else if(vis[v]) low[u] = min(low[u], low[v]);
	}
	
	if(dfn[u] == low[u]) {
		color[u] = ++sum;
		vis[u] = 0;
		while(s[top] != u) {
			color[ s[top] ] = sum;
			vis[ s[top] ] = 0;
			top--;
		}
		top--;
	}
}

// 求割点
vector<int> cut; // 存储所有割点
void Tarjan(int u, bool root = true) {
	int tot = 0;
	low[u] = dfn[u] = ++dep;
	for(auto v : G[u]) {
		if(!dfn[v]) {
			Tarjan(v, false);
			low[u] = min(low[u], low[v]);
			tot += (low[v] >= dfn[u]); // 统计满足low[v] >= dfn[u]的子节点数目
		} else low[u] = min(low[u], dfn[v]);
	}
	if (tot > root) // 如果是根，tot需要大于1；否则只需大于0
        cut.push_back(u);
}

// 求割桥
vector<pair<int, int>> bridges;	// 存割桥
void Tarjan(int u) {
	low[u] = dfn[u] = ++dep;
	for(auto v : G[u]) {
		if(!dfn[v]) {
			fa[v] = u;	// 记录父节点
			Tarjan(v);
			low[u] = min(low[u], low[v]);
			if(low[v] > dfn[u]) bridges.emplace_back(u, v);
		} else if (fa[u] != v) // 排除父节点
            low[u] = min(low[u], dfn[v]);
	}
}

void Solve() {
	for(int i = 1; i <= n; i++) if(!dfn[i]) {
		Tarjan(i);
		Tarjan(i, true);
	}
}