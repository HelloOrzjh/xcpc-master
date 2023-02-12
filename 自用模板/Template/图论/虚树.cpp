//#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define int long long
#define pir make_pair
#define pii pair<int, int>
#define fi first
#define se second
using namespace std;
const int MAXN = 1e6 + 5;
const int INF = 0x3f3f3f3f;

int n, m, cnt, dfn[MAXN], dep[MAXN], top, s[MAXN], vis[MAXN], lca[MAXN][25];
vector<pii> VG[MAXN], vec;
vector<int> G[MAXN];
unordered_map<int, int> Map;

void DFS(int u, int fa) {
	dfn[u] = ++cnt; dep[u] = dep[fa] + 1;
	lca[u][0] = fa;
	for(int i = 1; i <= 20; i++) lca[u][i] = lca[ lca[u][i - 1] ][i - 1];
	for(auto i : G[u]) if(i != fa) DFS(i, u);
}

int LCA(int u, int v) {
	if(dep[u] > dep[v]) swap(u, v);
	for(int i = 20; i >= 0; i--) if((1 << i) & (dep[v] - dep[u])) v = lca[v][i];
	for(int i = 20; i >= 0; i--) if(lca[u][i] != lca[v][i]) u = lca[u][i], v = lca[v][i];
	return u == v ? u : lca[u][0];
}

int Dist(int u, int v) {

}

void Add(int u, int v) {
	int w = Dist(u, v);
	VG[u].push_back( pir(v, w) );
	VG[v].push_back( pir(u, w) );
	if(!Map[u]) Map[u] = ++cnt;
	if(!Map[v]) Map[v] = ++cnt;
}

void VirtualTreeInsert(int u) {
	if(!top) return void(s[++top] = u);
	int l = LCA(s[top], u);
	while(top > 1 && dep[l] < dep[ s[top - 1] ]) Add(s[top - 1], s[top]), --top;
	if(dep[l] < dep[ s[top] ]) Add(l, s[top]), --top;
	if(!top || s[top] != l) s[++top] = l;
	if(s[top] != u) s[++top] = u;
}

void BuildVirtualTree(vector<pii> vec, int k) {
	sort(vec.begin(), vec.end());
	for(auto i : Map) VG[i.fi].clear();
	top = cnt = 0; Map.clear(); 
	s[++top] = 1, Map[1] = ++cnt;
	for(auto i : vec) VirtualTreeInsert(i.se);
	for(int i = 1; i < top; i++) Add(s[i], s[i + 1]);
}

signed main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		G[u].push_back(v), G[v].push_back(u);
	}
	DFS(1, 0); cnt = 0;
	cin >> m;
	while(m--) {
		int k; cin >> k; vec.clear();
		for(int i = 1; i <= k; i++) {
			int cur; cin >> cur;
			vec.push_back( pir(dfn[cur], cur) );
		}
		BuildVirtualTree(vec, k);
	}
	return 0;
}

