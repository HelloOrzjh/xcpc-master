//#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define int long long
#define pir make_pair
#define pii pair<int, int>
#define fi first
#define se second
using namespace std;
const int MAXN = 40005;
const int MAXS = 205;
const int MOD = 1e9 + 7;

int n, m, s, a[MAXN], val[MAXN], id[MAXN], l[MAXS], r[MAXS], c[MAXN], vis[MAXN], sum[MAXS][MAXN], ans[MAXS][MAXS];
map<int, int> Map;

void Init() {
	int cnt = 0;
	for(auto &i : Map) i.se = ++cnt, val[i.se] = i.fi;
	for(int i = 1; i <= n; i++) a[i] = Map[ a[i] ];

	s = sqrt(n);
	for(int i = 1; i <= n; i++) id[i] = (i - 1) / s + 1, r[ id[i] ] = i;
	for(int i = n; i >= 1; i--) l[ id[i] ] = i;
	
	for(int i = 1; i <= n; i++) sum[ id[i] ][ a[i] ]++;
	for(int i = 1; i <= id[n]; i++) for(int j = 1; j <= n; j++) sum[i][j] += sum[i - 1][j];	
	
	for(int i = 1; i <= id[n]; i++) {
		int res = 0;
		for(int j = i; j >= 1; j--) {
			for(int k = l[j]; k <= r[j]; k++) {
				c[ a[k] ]++;
				if(c[ a[k] ] > c[res] || (c[ a[k] ] == c[res] && a[k] < res) ) res = a[k];
			}
			ans[j][i] = res;
		}
		for(int j = 1; j <= n; j++) c[j] = 0;
	}
}

int Query(int L, int R) {
	int lid = id[L], rid = id[R], res = 0;
	if(rid - lid + 1 <= 2) {
		res = 0;
		for(int i = L; i <= R; i++) {
			c[ a[i] ]++;
			if(c[ a[i] ] > c[res] || (c[ a[i] ] == c[res] && a[i] < res) ) res = a[i];
		}
		for(int i = L; i <= R; i++) c[ a[i] ] = 0;
	} else {
		res = ans[lid + 1][rid - 1];
		c[res] += sum[rid - 1][res] - sum[lid][res];
		vis[res] = 1;
		
		for(int i = L; i <= r[lid]; i++) c[ a[i] ]++;
		for(int i = l[rid]; i <= R; i++) c[ a[i] ]++;
		
		for(int i = L; i <= r[lid]; i++) {
			if(!vis[ a[i] ]) {
				c[ a[i] ] += sum[rid - 1][ a[i] ] - sum[lid][ a[i] ];
				vis[ a[i] ] = 1;
				if(c[ a[i] ] > c[res] || (c[ a[i] ] == c[res] && a[i] < res) ) res = a[i];
			}
		}
		for(int i = l[rid]; i <= R; i++) {
			if(!vis[ a[i] ]) {
				c[ a[i] ] += sum[rid - 1][ a[i] ] - sum[lid][ a[i] ];
				vis[ a[i] ] = 1;
				if(c[ a[i] ] > c[res] || (c[ a[i] ] == c[res] && a[i] < res) ) res = a[i];
			}
		}
		
		for(int i = L; i <= r[lid]; i++) c[ a[i] ] = vis[ a[i] ] = 0;
		for(int i = l[rid]; i <= R; i++) c[ a[i] ] = vis[ a[i] ] = 0;
		c[ ans[lid + 1][rid - 1] ] = vis[ ans[lid + 1][rid - 1] ] = 0;
	}
	return res;
}

signed main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i], Map[ a[i] ] = 1;
	Init();
	
	int x = 0;
	while(m--) {
		int l, r; cin >> l >> r;
		l = (l + x - 1) % n + 1, r = (r + x - 1) % n + 1;
		if(l > r) swap(l, r);
		x = val[ Query(l, r) ];
		cout << x << "\n";
	}
	return 0;
}

