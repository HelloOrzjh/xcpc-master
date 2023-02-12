int Prim() {
	memset(dist, 0x3f, sizeof(dist));
	int res = 0;
	for(int i = 0; i < n; i++) {
		int t = -1;
		for(int j = 1; j <= n; j++) {
			if(!st[j] && (t == -1 || dist[t] > dist[j])) t = j;
		}
		if(i && dist[t] == INF) return INF;	// 无解 
		
		if(i) res += dist[t];
		st[t] = true;
		
		for(int j = 1; j <= n; j++) dist[j] = min(dist[j], G[t][j]);
	}
	return res;
}

int Kruskal() {
	for(int i = 1; i <= n; i++) f[i] = i;
	sort(e + 1, e + 1 + m, cmp); // 按边权排序
	ans = 0;
	for(int i = 1; i <= m; i++) {
		int fu = find(e[i].u), fv = find(e[i].v);
		if(fu == fv) continue;
		if(fu > fv) swap(fu, fv);
		f[fv] = fu;
		ans += e[i].w;
		e[i].flag = 1;
		G[ e[i].u ].push_back( make_pair(e[i].v, e[i].w) );
		G[ e[i].v ].push_back( make_pair(e[i].u, e[i].w) );
	}
	return ans;
}
