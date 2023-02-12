#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define pir make_pair
#define reg register
#define pdi pair<double, int>
using namespace std;
const int MAXN = 100005;
const int INF = 0x7fffffff;
const int MOD1 = 39989;
const int MOD2 = (int)1e9;

struct Tree {
	int l, r, id;
}tree[MAXN << 2];
struct Seg {
	double k, b;
	double f(int x) { return 1.0 * k * x + b; }
	Seg() {}
	Seg(int x0, int y0, int x1, int y1) {
		if(x0 == x1) k = 0, b = max(y0, y1);
		else {
			k = 1.0 * (y0 - y1) / (x0 - x1);
			b = y0 - 1.0 * k * x0;
		}
	}
}s[MAXN];
int n;

inline int ls(int x) { return x << 1; }
inline int rs(int x) { return x << 1 | 1; }
pdi Max(pdi u, pdi v) {
	if(u.fi > v.fi) return u;
	else if(u.fi < v.fi) return v;
	else {
		if(u.se < v.se) return u;
		else return v;
	}
}

void Build(int l, int r, int p) {
	tree[p].l = l;
	tree[p].r = r;
	tree[p].id = 0;
	if(l == r) return ;
	int mid = l + r >> 1;
	Build(l, mid, ls(p));
	Build(mid + 1, r, rs(p));
}

void Modify(int u, int nl, int nr, int p) {
	int l = tree[p].l, r = tree[p].r, v = tree[p].id, mid = l + r >> 1;
	double fu = s[u].f(mid), fv = s[v].f(mid);
	if(nl <= l && nr >= r) {
		if(l == r) {
			if(fu > fv) tree[p].id = u;
			return ;
		}
		if(s[u].k > s[v].k) {
			if(fu > fv) tree[p].id = u, Modify(v, nl, nr, ls(p));
			else Modify(u, nl, nr, rs(p));
		} else if(s[u].k < s[v].k) {
			if(fu > fv) tree[p].id = u, Modify(v, nl, nr, rs(p));
			else Modify(u, nl, nr, ls(p));			
		} else {
			if(s[u].b > s[v].b) tree[p].id = u;
		}
		return ;
	}
	if(nl <= mid) Modify(u, nl, nr, ls(p));
	if(nr > mid) Modify(u, nl, nr, rs(p));
}

pdi Query(int loc, int p) {
	int l = tree[p].l, r = tree[p].r, id = tree[p].id;
	if(l == r) return pir(s[id].f(loc), id);
	int mid = l + r >> 1;
	pdi u = pir(s[id].f(loc), id), v;
	if(loc <= mid) v = Query(loc, ls(p));
	else v = Query(loc, rs(p));
	return Max(u, v);
}

void Modify(int x0, int y0, int x1, int y1, int id) {
	s[id] = Seg(x0, y0, x1, y1);
	Modify(id, x0, x1, 1);
}

signed main()
{
	scanf("%lld", &n);
	Build(1, MOD1, 1);
	int last = 0, cnt = 0;
	for(int i = 1; i <= n; i++) {
		int op, k, x0, y0, x1, y1;
		scanf("%lld", &op);
		if(op == 0) {
			scanf("%lld", &k);
			k = (k + last - 1 + MOD1) % MOD1 + 1;
			last = Query(k, 1).se;
			printf("%lld\n", last);
		} else {
			scanf("%lld%lld%lld%lld", &x0, &y0, &x1, &y1);
			x0 = (x0 + last - 1 + MOD1) % MOD1 + 1;
			x1 = (x1 + last - 1 + MOD1) % MOD1 + 1;
			y0 = (y0 + last - 1 + MOD2) % MOD2 + 1;
			y1 = (y1 + last - 1 + MOD2) % MOD2 + 1;
			if(x0 > x1) swap(x0, x1), swap(y0, y1);
			Modify(x0, y0, x1, y1, ++cnt);
		}
	}
	return 0;
}
