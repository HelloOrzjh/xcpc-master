#include<bits/stdc++.h>
#define pir make_pair
#define pii pair<int, int>
#define fi first
#define se second
using namespace std;
const int MAXN = 1e4 + 5;
const int MAXV = 1e7 + 5;
const int MOD = 1e9 + 7;

int n, m, ans[MAXN], val[MAXN], sze[MAXN], vis[MAXN], centroid;
int Map[MAXN], Cur[MAXN], MapVal[MAXV];
vector<pii> G[MAXN];

void GetCentroid(int u, int fa, int n) {
	sze[u] = 1;
	int maxx = 0;
	for(auto i : G[u]) {
		int v = i.fi, w = i.se;
		if(v == fa || vis[v]) continue;
		GetCentroid(v, u, n);
		if(centroid != -1) return ;
		maxx = max(maxx, sze[v]);
		sze[u] += sze[v];
	}
	maxx = max(maxx, n - sze[u]);
	if(maxx <= n / 2) centroid = u, sze[fa] = n - sze[u];
}

void Calc(int u, int fa, int len) {
	if(len > 1e7) return ;
	Cur[ ++Cur[0] ] = len;
	for(auto i : G[u]) {
		int v = i.fi, w = i.se;
		if(vis[v] || v == fa) continue;
		Calc(v, u, len + w);
	}
}

void Calc(int u) {
	Map[ Map[0] = 1 ] = 0, MapVal[0] = 1;
	for(auto i : G[u]) {
		int v = i.fi, w = i.se;
		if(vis[v]) continue;
		Cur[0] = 0; Calc(v, u, w);
		for(int j = 1; j <= Cur[0]; j++) 
			for(int k = 1; k <= m; k++) 
				if(val[k] - Cur[j] >= 0) 
					ans[k] |= MapVal[ val[k] - Cur[j] ];
		for(int j = 1; j <= Cur[0]; j++) MapVal[ Cur[j] ] = 1, Map[ ++Map[0] ] = Cur[j];
	}
	for(int i = 1; i <= Map[0]; i++) MapVal[ Map[i] ] = 0;
}

void Solve(int u) {
	vis[u] = 1; Calc(u);
	for(auto i : G[u]) {
		int v = i.fi, w = i.se;
		if(vis[v]) continue;
		centroid = -1; GetCentroid(v, 0, sze[v]);
		Solve(centroid);
	}
}

signed main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i < n; i++) {
		int u, v, w; cin >> u >> v >> w;
		G[u].push_back( pir(v, w) ), G[v].push_back( pir(u, w) );
	}
	for(int i = 1; i <= m; i++) cin >> val[i];
	centroid = -1;
	GetCentroid(1, 0, n);
	Solve(centroid);
	for(int i = 1; i <= m; i++) cout << (ans[i] ? "AYE" : "NAY") << "\n";
	return 0;
}

