#include<bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = (int)1e5 + 5;

struct Node {
	int v, nxt;
}e[MAXN << 1];

int sum[MAXN << 2], tag[MAXN << 2];
int n, m, r, MOD, cnt, e_cnt, v[MAXN];
int head[MAXN], vis[MAXN], fa[MAXN], sze[MAXN], son[MAXN], dep[MAXN];
int idx[MAXN], a[MAXN], top[MAXN];

int ls(int x) { return x << 1; }
int rs(int x) { return x << 1 | 1; }

void F(int l, int r, int p, int k) {
	tag[p] += k; tag[p] %= MOD;
	sum[p] += (r - l + 1) * k; sum[p] %= MOD;
}

void PushUp(int p) {
	sum[p] = sum[ls(p)] + sum[rs(p)];
	sum[p] %= MOD;
}

void PushDown(int l, int r, int p) {
	int mid = (l + r) >> 1;
	F(l, mid, ls(p), tag[p]);
	F(mid + 1, r, rs(p), tag[p]);
	PushUp(p);
	tag[p] = 0;
}

void Build(int l, int r, int p) {
	if(l == r) {
		sum[p] = a[l];
		tag[p] = 0;
		return ;
	}
	int mid = (l + r) >> 1;
	Build(l, mid, ls(p));
	Build(mid + 1, r, rs(p));
	PushUp(p);
}

void SegmentTreeModify(int nl, int nr, int l, int r, int p, int k) {
	if(nl <= l && nr >= r) {
		tag[p] += k; tag[p] %= MOD;
		sum[p] += (r - l + 1) * k; sum[p] %= MOD;
		return ;
	}
	PushDown(l, r, p);
	int mid = (l + r) >> 1;
	if(nl <= mid) SegmentTreeModify(nl, nr, l, mid, ls(p), k);
	if(nr > mid) SegmentTreeModify(nl, nr, mid + 1, r, rs(p), k);
	PushUp(p);
	return ;
}

int SegmentTreeQuery(int nl, int nr, int l, int r, int p) {
	if(nl <= l && nr >= r) {
		return sum[p];
	}
	PushDown(l, r, p);
	int res = 0;
	int mid = (l + r) >> 1;
	if(nl <= mid) res += SegmentTreeQuery(nl, nr, l, mid, ls(p)), res %= MOD; 
	if(nr > mid) res += SegmentTreeQuery(nl, nr, mid + 1, r, rs(p)), res %= MOD;
	return res;
}

void Add(int u, int v) {
	e[++e_cnt].v = v;
	e[e_cnt].nxt = head[u];
	head[u] = e_cnt;
}

void DFS1(int u, int ftr) {
	fa[u] = ftr;
	sze[u] = 1;
	dep[u] = dep[ftr] + 1;
	vis[u] = 1;
	int maxsize = -1;
	for(int i = head[u]; i != -1; i = e[i].nxt) {
		int v = e[i].v;
		if(vis[v]) continue;
		DFS1(v, u);
		sze[u] += sze[v];
		if(sze[v] > maxsize) {
			son[u] = v;
			maxsize = sze[v];
		}
	}
}

void DFS2(int u, int top_u) {
	idx[u] = ++cnt;
	a[cnt] = v[u];
	top[u] = top_u;
	if(son[u] == 0) return ;
	DFS2(son[u], top_u);
	for(int i = head[u]; i != -1; i = e[i].nxt) {
		int v = e[i].v;
		if(v == fa[u] || v == son[u]) continue;
		DFS2(v, v);
	}
}

void Modify(int u, int v, int w) {
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		SegmentTreeModify(idx[top[u]], idx[u], 1, n, 1, w);
		u = fa[top[u]];
	}
	if(idx[u] > idx[v]) swap(u, v);
	SegmentTreeModify(idx[u], idx[v], 1, n, 1, w);
}

int Query(int u, int v) {
	int res = 0;
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		res += SegmentTreeQuery(idx[top[u]], idx[u], 1, n, 1);
		res %= MOD;
		u = fa[top[u]];
	}
	if(idx[u] > idx[v]) swap(u, v);
	res += SegmentTreeQuery(idx[u], idx[v], 1, n, 1);
	return res % MOD;
}

signed main()
{
	scanf("%lld%lld%lld%lld", &n, &m, &r, &MOD);
	cnt = 0, e_cnt = 0;
	memset(head, -1, sizeof(head));
	for(int i = 1; i <= n; i++) {
		scanf("%lld", &v[i]);
	} 
	for(int i = 1; i < n; i++) {
		int u, v;
		scanf("%lld%lld", &u, &v);
		Add(u, v);
		Add(v, u);
	}
	DFS1(r, 0);
	DFS2(r, r);
	Build(1, n, 1);
	while(m--) {
		int opt, x, y, z;
		scanf("%lld", &opt);
		if(opt == 1) {
			scanf("%lld%lld%lld", &x, &y, &z);
			Modify(x, y, z);	
		} else if(opt == 2) {
			scanf("%lld%lld", &x, &y);
			printf("%lld\n", Query(x, y));
		} else if(opt == 3) {
			scanf("%lld%lld", &x, &z);
			SegmentTreeModify(idx[x], idx[x] + sze[x] - 1, 1, n, 1, z);
		} else {
			scanf("%lld", &x);
			printf("%lld\n", SegmentTreeQuery(idx[x], idx[x] + sze[x] - 1, 1, n, 1) % MOD);
		}
	}
	return 0;
}

/*
input:
5 5 2 24
7 3 7 8 0 
1 2
1 5
3 1
4 1
3 4 2
3 2 2
4 5
1 5 1 3
2 1 3

output:
2
21
*/
