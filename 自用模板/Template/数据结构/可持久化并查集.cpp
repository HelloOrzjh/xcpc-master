//#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
const int MOD = 1e9 + 7;

struct Node {
	int fa, dep, ls, rs;
}tree[MAXN * 40];

int cnt, n, m, root[MAXN];

int Build(int l, int r) {
	int dir = ++cnt;
	if(l == r) { tree[dir].fa = l; return dir; }
	int mid = l + r >> 1; 
	tree[dir].ls = Build(l, mid);
	tree[dir].rs = Build(mid + 1, r);
	return dir;
}

int ModifyDep(int rt, int l, int r, int loc, int val) {
	int dir = ++cnt;
	tree[dir] = tree[rt];
	if(l == r) { tree[dir].dep += val; return dir; }
	int mid = (l + r) >> 1;
	if(loc <= mid) tree[dir].ls = ModifyDep(tree[dir].ls, l, mid, loc, val);
	if(loc > mid) tree[dir].rs = ModifyDep(tree[dir].rs, mid + 1, r, loc, val); 
	return dir;
}

int ModifyFa(int rt, int l, int r, int loc, int val) {
	int dir = ++cnt;
	tree[dir] = tree[rt];
	if(l == r) { tree[dir].fa = val; return dir; }
	int mid = (l + r) >> 1;
	if(loc <= mid) tree[dir].ls = ModifyFa(tree[dir].ls, l, mid, loc, val);
	if(loc > mid) tree[dir].rs = ModifyFa(tree[dir].rs, mid + 1, r, loc, val); 
	return dir;
}

int QueryNode(int rt, int l, int r, int loc) {
	if(l == r) return rt;
	int mid = (l + r) >> 1;
	if(loc <= mid) return QueryNode(tree[rt].ls, l, mid, loc);
	if(loc > mid) return QueryNode(tree[rt].rs, mid + 1, r, loc);
}

int Find(int rt, int u) {	// 返回值为祖先节点在主席树上对应节点编号
	int cur = QueryNode(rt, 1, n, u);
	if(u == tree[cur].fa) return cur;
	return Find(rt, tree[cur].fa); 
}

void Union(int p, int u, int v) {	// 按秩合并
	u = Find(root[p], u), v = Find(root[p], v);
	if(u == v) return ;
	if(tree[u].dep > tree[v].dep) swap(u, v);
	root[p] = ModifyFa(root[p], 1, n, tree[u].fa, tree[v].fa);
	if(tree[u].dep == tree[v].dep) root[p] = ModifyDep(root[p], 1, n, tree[v].fa, 1);
}

signed main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m; root[0] = Build(1, n);
	for(int i = 1; i <= m; i++) {
		root[i] = root[i - 1];
		int op, a, b, k; cin >> op;
		if(op == 1) cin >> a >> b, Union(i, a, b);
		else if(op == 2) cin >> k, root[i] = root[k];
		else cin >> a >> b, cout << (tree[ Find(root[i], a) ].fa == tree[ Find(root[i], b) ].fa) << "\n";
	}
	return 0;
}