int n;	// 总点数 
int h[N], w[N], e[N], ne[N], idx;	// 邻接表存边 
int dist[N];	// 存储每个点到1号点的最短距离 
bool st[N];	// 存储每个点是否在队列中 

// 求1号点到n号点的最短距离，如果无法到达返回-1 
int SPFA() {
	memset(dist, 0x3f, sizeof dist);
	queue<int> q;
	q.push(1);
	dist[1] = 0, st[1] = true;
	while(!q.empty()) {
		auto t = q.front(); q.pop();
		st[t] = false;
		for(int i = h[t]; i != -1; i = ne[i]) {
			int j = e[i];
			if(dist[j] > dist[t] + w[i]) {
				dist[j] = dist[t] + w[i];
				if(!st[j]) q.push(j), st[j] = true;
			}
		}
	}
	if(dist[n] >= 0x3f3f3f3f) return -1;
	return dist[n];
}

