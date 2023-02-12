#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = (int)1e5 + 5;
const int MAXM = (int)3e5 + 5;
struct Node {
	int u, v, w, flag;
}e[MAXM];
int lca[MAXN][30], maxx1[MAXN][30], maxx2[MAXN][30], dep[MAXN], n, m, f[MAXN], ans, vis[MAXN];
vector< pair<int, int> > G[MAXN];

bool cmp(Node &a, Node &b) { return a.w < b.w; }
int find(int x) { return ( x == f[x] ? x : ( f[x] = find(f[x]) ) ); }

void Kruskal() {
	for(int i = 1; i <= n; i++) f[i] = i;
	sort(e + 1, e + 1 + m, cmp);
	
	ans = 0;
	for(int i = 1; i <= m; i++) {
		int fu = find(e[i].u), fv = find(e[i].v);
		if(fu == fv) continue;
		if(fu > fv) swap(fu, fv);
		f[fv] = fu;
		ans += e[i].w;
		e[i].flag = 1;
		G[ e[i].u ].push_back( make_pair(e[i].v, e[i].w) ), G[ e[i].v ].push_back( make_pair(e[i].u, e[i].w) );
	}
}

void DFS(int u, int ftr) {
	// maxx1维护最大值 maxx2维护次大值 
	dep[u] = dep[ftr] + 1;
	vis[u] = 1;
	for(int i = 1; i <= 20; i++) {
		lca[u][i] = lca[ lca[u][i - 1] ][i - 1];
		maxx1[u][i] = max( maxx1[u][i - 1], maxx1[ lca[u][i - 1] ][i - 1] ); 
		if(maxx1[u][i - 1] == maxx1[ lca[u][i - 1] ][i - 1]) 
			maxx2[u][i] = max( maxx2[u][i - 1], maxx2[ lca[u][i - 1] ][i - 1] );
		else 
			maxx2[u][i] = max( min( maxx1[u][i - 1], maxx1[ lca[u][i - 1] ][i - 1] ), max( maxx2[u][i - 1], maxx2[ lca[u][i - 1] ][i - 1] ) );
	}
	
	for(auto i : G[u]) {
		int v = i.first, w = i.second;
		if(vis[v]) continue;
		lca[v][0] = u; maxx1[v][0] = w; maxx2[v][0] = 0;
		DFS(v, u);
	}
}

int LCA(int u, int v) {
	if(dep[u] < dep[v]) swap(u, v);
	for(int i = 20; i >= 0; i--) {
		if((1 << i) & (dep[u] - dep[v])) u = lca[u][i];
	}
	for(int i = 20; i >= 0; i--) {
		if(lca[u][i] != lca[v][i]) {
			u = lca[u][i];
			v = lca[v][i];
		}
	}
	return u == v ? u : lca[u][0];
}

int Work(int u, int l, int w) {
	int max1 = 0, max2 = 0;
	for(int i = 20; i >= 0; i--) {
		if((1 << i) & (dep[u] - dep[l])) {
			max1 = max(max1, maxx1[u][i]);
			max2 = max(max2, maxx2[u][i]);
			u = lca[u][i]; 
		}
	}
	if(w - max1 == 0) return w - max2;
	return w - max1;
}

signed main()
{
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= m; i++) {
		int u, v, w;
		scanf("%lld%lld%lld", &u, &v, &w);
		e[i].u = u, e[i].v = v, e[i].w = w, e[i].flag = 0;
	}
	Kruskal();
	DFS(1, 0);
	
	int d = 1e14;
	for(int i = 1; i <= m; i++) {
		if(e[i].flag) continue;
		int u = e[i].u, v = e[i].v, w = e[i].w;
		int l = LCA(u, v);
		d = min(d, Work(u, l, w) );
		d = min(d, Work(v, l, w) );
	}
	printf("%lld", ans + d);
	return 0;
}


