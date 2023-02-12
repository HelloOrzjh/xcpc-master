#include<bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 205;
const int MAXM = 5005;

struct Edge {
	int v, w, nxt;
}e[MAXM << 1];

int n, m, s, t, cnt = 1, dep[MAXN], head[MAXN];

void Add(int u, int v, int w) {
	e[++cnt].v = v;
	e[cnt].w = w;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}

bool BFS() {
	for(int i = 1; i <= n + 1; i++) dep[i] = 0;
	dep[s] = 1;
	queue<int> Q;
	Q.push(s);
	while(!Q.empty()) {
		int u = Q.front(); Q.pop();
		for(int i = head[u]; i != -1; i = e[i].nxt) {
			int v = e[i].v;
			if(dep[v] == 0 && e[i].w > 0) {
				dep[v] = dep[u] + 1;
				Q.push(v);
			}
		}
	}
	return (bool)dep[t];
}

int DFS(int u, int in) {
	if(u == t) return in;
	int out = 0;
	for(int i = head[u]; i != -1 && in > 0; i = e[i].nxt) {
		int v = e[i].v;
		if(dep[v] == dep[u] + 1 && e[i].w > 0) {
			int res = DFS(v, min(e[i].w, in));
			e[i].w -= res;
			e[i ^ 1].w += res;	// ·´Ïò±ß(²ĞÁ¿ÍøÂç)
			in -= res;
			out += res; 
		}
	}
	if(out == 0) dep[u] = 0;
	return out;
}

signed main()
{
	memset(head, -1, sizeof(head));
	scanf("%lld%lld%lld%lld", &n, &m, &s, &t);
	for(int i = 1; i <= m; i++) {
		int u, v, w; scanf("%lld%lld%lld", &u, &v, &w);
		Add(u, v, w); Add(v, u, 0);
	}
	int ans = 0;
	while(BFS()) { ans += DFS(s, 1e18); }
	printf("%lld", ans);
	return 0;
}

