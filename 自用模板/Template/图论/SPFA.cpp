int n;	// �ܵ��� 
int h[N], w[N], e[N], ne[N], idx;	// �ڽӱ��� 
int dist[N];	// �洢ÿ���㵽1�ŵ����̾��� 
bool st[N];	// �洢ÿ�����Ƿ��ڶ����� 

// ��1�ŵ㵽n�ŵ����̾��룬����޷����ﷵ��-1 
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

