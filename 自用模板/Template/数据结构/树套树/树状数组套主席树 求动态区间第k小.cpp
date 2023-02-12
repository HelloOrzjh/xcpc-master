#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100000 + 5;
const int INF = 0x7fffffff; 

struct Query {
	int l, r, k, x, y;
}q[MAXN];

map<int, int> Map;
vector<int> lRoot, rRoot;
int n, m, a[MAXN], cnt = 0, num[MAXN << 1], root[MAXN];
int tot, sum[MAXN << 7], ls[MAXN << 7], rs[MAXN << 7];

void Modify(int &rt, int l, int r, int loc, int val) {
	if(!rt) rt = ++tot;
	sum[rt] += val;
	if(l == r) return ;
	int mid = l + r >> 1;
	if(loc <= mid) Modify(ls[rt], l, mid, loc, val);
	else Modify(rs[rt], mid + 1, r, loc, val);
}

int QueryKth(int l, int r, int k) {
	if(l == r) return l;
	int mid = l + r >> 1, res = 0;
	for(auto i : rRoot) res += sum[ ls[i] ];
	for(auto i : lRoot) res -= sum[ ls[i] ];
	if(res >= k) {
		for(auto &i : lRoot) i = ls[i];
		for(auto &i : rRoot) i = ls[i];
		return QueryKth(l, mid, k);
	} else {
		for(auto &i : lRoot) i = rs[i];
		for(auto &i : rRoot) i = rs[i];		
		return QueryKth(mid + 1, r, k - res);
	}
}

void Modify(int pos, int val) {
	int loc = Map[ a[pos] ];
	for( ; pos <= n; pos += (pos & (-pos))) Modify(root[pos], 1, cnt, loc, val);
}

int Query(int l, int r, int k) {
	lRoot.clear(), rRoot.clear();
	for(int pos = l - 1; pos; pos -= (pos & (-pos))) lRoot.push_back(root[pos]);
	for(int pos = r; pos; pos -= (pos & (-pos))) rRoot.push_back(root[pos]);
	return QueryKth(1, cnt, k);
}

signed main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i], Map[ a[i] ] = 1;
	for(int i = 1; i <= m; i++) {
		char ch; cin >> ch;
		if(ch == 'Q') cin >> q[i].l >> q[i].r >> q[i].k;
		else cin >> q[i].x >> q[i].y, Map[ q[i].y ] = 1;
	}
	for(auto &i : Map) i.second = ++cnt, num[cnt] = i.first;
	for(int i = 1; i <= n; i++) Modify(i, 1);
	for(int i = 1; i <= m; i++) {
		if(q[i].l) cout << num[ Query(q[i].l, q[i].r, q[i].k) ] << "\n";
		else {
			Modify(q[i].x, -1);
			a[ q[i].x ] = q[i].y;
			Modify(q[i].x, 1);
		}
	}
	return 0;
}

