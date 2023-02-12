/*
1. 在某个历史版本上修改某一个位置上的值
2. 访问某个历史版本上的某一位置的值 
*/

#include<bits/stdc++.h>
using namespace std;
const int MAXN = (int)1e6 + 5;
struct Node {
	int ls, rs, val;
}tree[MAXN << 5];
int n, m, a[MAXN], cnt, root[MAXN];

int Build(int l, int r) {
	int dir = ++cnt;
	if(l == r) {
		tree[dir].val = a[l];
		return dir;
	}
	int mid = (l + r) >> 1; 
	tree[dir].ls = Build(l, mid);
	tree[dir].rs = Build(mid + 1, r);
	return dir;
}

int Modify(int p, int l, int r, int loc, int val) {
	int dir = ++cnt;
	tree[dir] = tree[p];
	if(l == r) {
		tree[dir].val = val;
		return dir;
	}
	int mid = (l + r) >> 1;
	if(loc <= mid) tree[dir].ls = Modify(tree[dir].ls, l, mid, loc, val);
	if(loc > mid) tree[dir].rs = Modify(tree[dir].rs, mid + 1, r, loc, val); 
	return dir;
}

int Query(int p, int l, int r, int loc) {
	if(l == r) return tree[p].val;
	int mid = (l + r) >> 1;
	if(loc <= mid) return Query(tree[p].ls, l, mid, loc);
	if(loc > mid) return Query(tree[p].rs, mid + 1, r, loc);
}

signed main()
{
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	cnt = 0;
	root[0] = Build(1, n);
	for(int i = 1; i <= m; i++) {
		int v, op, loc, val;
		scanf("%lld%lld%lld", &v, &op, &loc);
		if(op == 1) {
			scanf("%lld", &val);
			root[i] = Modify(root[v], 1, n, loc, val);
		} else {
			printf("%lld\n", Query(root[v], 1, n, loc));
			root[i] = root[v];
		}
	}
	return 0;
}

