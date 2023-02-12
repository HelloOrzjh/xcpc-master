#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = (int)1e5 + 5;
const int MAXM = (int)2e5 + 5;
struct Node {
	int u, w;
	bool operator < (const Node &a) const { return w > a.w; } 
};
struct Edge {
	int v, w, nxt;
}e[MAXM];
int n, m, s, cnt = 0, head[MAXN], vis[MAXN], dist[MAXN];
priority_queue<Node> Q;

void Add(int u, int v, int w) {
	e[++cnt].v = v;
	e[cnt].w = w;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}

void Dijkstra(int s) {
	for(int i = 1; i <= n; i++) vis[i] = 0, dist[i] = INF;
	dist[s] = 0;
	Q.push((Node){s, 0});
	while(!Q.empty()) {
		Node now = Q.top();
		int u = now.u, w = now.w;
		Q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(int i = head[u]; i != -1; i = e[i].nxt) {
			if(dist[e[i].v] > dist[u] + e[i].w) {
				dist[e[i].v] = dist[u] + e[i].w;
				Q.push((Node){e[i].v, dist[e[i].v]});
			}
		}
	}
}

int main(){
	scanf("%d%d%d", &n, &m, &s);
	memset(head, -1, sizeof(head));
	for(int i = 1; i <= m; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		Add(u, v, w);
	}
	Dijkstra(s);
	for(int i = 1; i <= n; i++) printf("%d ", dist[i]);
	return 0;
}
