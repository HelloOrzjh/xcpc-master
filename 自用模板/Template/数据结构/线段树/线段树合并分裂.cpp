#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define int long long
#define pir make_pair
#define pii pair<int, int>
#define fi first
#define se second
using namespace std;
const int MAXN = 1e5 + 5;
const int MOD = 1e9 + 7;

int n, m, Op[MAXN];
set<int> Set;

struct Node {
	int ltype, rtype, ans, sze;
	friend Node operator + (Node a, Node b) {
		if(!a.sze) return b;
		if(!b.sze) return a;
		Node res;
		res.ans = a.ans + b.ans + (a.rtype ^ b.ltype);
		res.ltype = a.ltype;
		res.rtype = b.rtype;
		res.sze = a.sze + b.sze;
		return res;
	}
}tree[MAXN << 2];

struct Segment_Tree {
	int root[MAXN * 40], son[MAXN * 40][3];
	Node sum[MAXN * 40];
	int pool[MAXN * 40], delcnt = 0, cnt = 0;
	
	void PushUp(int p) { sum[p] = sum[ son[p][0] ] + sum[ son[p][1] ]; }
	
	int NewNode() { return delcnt ? pool[delcnt--] : ++cnt; }
	
	void DelNode(int p) {
		pool[++delcnt] = p;
		sum[p] = {0, 0, 0, 0};
		son[p][0] = son[p][1] = 0;
	}
	
	void Insert(int& p, int l, int r, int loc) {
		if(!p) p = NewNode();
		if(l == r) {
			sum[p].ltype = sum[p].rtype = (loc & 1);
			sum[p].ans = 0, sum[p].sze = 1;
			return ;
		}
		int mid = l + r >> 1;
		if(loc <= mid) Insert(son[p][0], l, mid, loc);
		else Insert(son[p][1], mid + 1, r, loc);
		PushUp(p);
	}
	
	int Merge(int u, int v, int l = 1, int r = n) {
		if(!u || !v) return u + v;
		if(l == r) {
			sum[u] = sum[u] + sum[v];
			DelNode(v); 
			return u;
		}
		int mid = l + r >> 1;
		son[u][0] = Merge(son[u][0], son[v][0], l, mid);
		son[u][1] = Merge(son[u][1], son[v][1], mid + 1, r);
		DelNode(v);
		PushUp(u);
		return u;
	}
	
	void Split(int u, int& v, int k, int flag) {	//把u节点分裂，得到新的放到v里面，分裂前k个数的节点
		if(!k) return ;
		v = NewNode();
		if(k >= sum[ son[u][flag] ].sze) {
			Split(son[u][flag ^ 1], son[v][flag ^ 1], k - sum[ son[u][flag] ].sze, flag);
			swap(son[u][flag], son[v][flag]);
		} else Split(son[u][flag], son[v][flag], k, flag);
		PushUp(u), PushUp(v);
	}
}S;

void Modify(int loc, int l, int r, int p) {
	if(l == r) {
		tree[p] = S.sum[ S.root[loc] ];
		if(Op[loc]) swap(tree[p].ltype, tree[p].rtype);
		return ;
	}
	int mid = l + r >> 1;
	if(loc <= mid) Modify(loc, l, mid, p << 1);
	else Modify(loc, mid + 1, r, p << 1 | 1);
	tree[p] = tree[p << 1] + tree[p << 1 | 1];
}

Node Query(int nl, int nr, int l, int r, int p) {
	if(nl <= l && nr >= r) return tree[p];
	int mid = l + r >> 1;
	if(nl > mid) return Query(nl, nr, mid + 1, r, p << 1 | 1);
	else if(nr <= mid) return Query(nl, nr, l, mid, p << 1);
	else return Query(nl, nr, l, mid, p << 1) + Query(nl, nr, mid + 1, r, p << 1 | 1);
}

set<int>::iterator Split(int x) {
	auto pos = Set.lower_bound(x), tmp = pos;
	if(*pos == x) return pos;
	pos--;
	S.Split(S.root[*pos], S.root[x], *tmp - x, Op[*pos] ^ 1);
	Modify(*pos, 1, n, 1);
	Op[x] = Op[*pos];
	Modify(x, 1, n, 1);
	Set.insert(x);
	return Set.lower_bound(x);
}

signed main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m; Set.insert(n + 1);
	for(int i = 1; i <= n; i++) {
		int x; cin >> x;
		Set.insert(i);
		S.Insert(S.root[i], 1, n, x);
		Modify(i, 1, n, 1);
	}
	while(m--) {
		int op, l, r; cin >> op >> l >> r;
		auto pl = Split(l), pr = Split(r + 1);
		if(op == 3) {
			cout << Query(l, r, 1, n, 1).ans + 1 << "\n";
		} else {
			
			for(auto i = ++pl; i != pr; i++) {
				S.Merge(S.root[l], S.root[*i]);
				S.root[*i] = 0;
				Modify(*i, 1, n, 1);
			}
			Set.erase(pl, pr);
			Op[l] = op - 1;
			Modify(l, 1, n, 1);
		}
	}
	return 0;
}
