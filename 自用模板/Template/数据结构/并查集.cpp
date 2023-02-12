struct DSU {    // 按秩合并 可撤销
	struct Node {
	    int u, v, val;
    };
    
    int f[MAXN], dep[MAXN], top = 0;
	Node s[MAXN];
	
	void Init(int n) { for(int i = 1; i <= n; i++) f[i] = i, dep[i] = 0; }
	
	int Find(int u) { return u == f[u] ? u : Find(f[u]); }
	
	void Union(int u, int v) {  // 按秩合并
		u = Find(u), v = Find(v);
		if(u == v) return ;
		if(dep[u] > dep[v]) swap(u, v);
		int val = (dep[u] == dep[v]);
		s[++top] = (Node){u, v, val};
		f[u] = v, dep[v] += val;
	}
	
	bool Same(int u, int v) { return Find(u) == Find(v); }
	
	void Undo(int cur) {
		while(top > cur) {
			int u = s[top].u, v = s[top].v, val = s[top].val;	// dep[u] <= dep[v]
			f[u] = u, dep[v] -= val, top--;
		}
	}
}dsu;