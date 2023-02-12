#include<bits/stdc++.h>
using namespace std;

const int MAXN = 5005;
const int INF = 0x3f3f3f3f;

struct Node { int v, w; };

vector<Node> e[MAXN];
int head[MAXN], vis[MAXN], cnt[MAXN], dis[MAXN], n, m, ecnt;
queue<int> Q;

bool SPFA(int s) {
	for(int i = 0; i <= n; i++) dis[i] = INF, vis[i] = cnt[i] = 0;
	dis[s] = 0, vis[s] = 1; Q.push(s);
	while(!Q.empty()) {
		int u = Q.front(); Q.pop();
		vis[u] = 0;
		for(auto i : e[u]) {
			int v = i.v, w = i.w;
			if(dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				cnt[v] = cnt[u] + 1;
				if(cnt[v] >= n + 1) return 0;
				if(!vis[v]) Q.push(v), vis[v] = 1;
			}
		}
	} 
	return 1;
}

signed main()
{
	scanf("%d%d", &n, &m);
	ecnt = 0;
	//x_u - x_v <= w
	for(int i = 1; i <= m; i++) {
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		e[u].push_back((Node){v, w});
	} 
	for(int i = 1; i <= n; i++) Add(0, i, 0);
	if(!SPFA(0)) printf("NO\n");
	else for(int i = 1; i <= n; i++) printf("%d ", dis[i]);
	return 0;
}

