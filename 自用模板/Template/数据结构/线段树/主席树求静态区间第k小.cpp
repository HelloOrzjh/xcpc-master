/*
对权值线段树可持久化 再通过树上二分的方式找到[l,r]内第k小值 
*/
#include<bits/stdc++.h>
using namespace std;
const int MAXN = (int)2e5 + 5;

struct Query {
	int x, y, l, r, k;
}q[MAXN];

void Init() {	// 离散化 
	sort(b + 1, b + 1 + tot);
	int cnt = 0;
	a[0].val = -0x3f3f3f3f;	// significant 
	for(int i = 1; i <= n; i++) {
		if(a[i].val != a[i - 1].val) ++cnt;
		a[i].hval = cnt;
		Hash[cnt] = a[i].val;
	}
	sort(a + 1, a + 1 + n, cmp2);
}

int Build(int l, int r) {
	int dir = ++cnt;
	tree[dir].val = 0;
	if(l == r) return dir;
	int mid = l + r >> 1;
	tree[dir].ls = Build(l, mid);
	tree[dir].rs = Build(mid + 1, r);
	return dir;
}

int Modify(int p, int l, int r, int loc) {
	int dir = ++cnt;
	tree[dir] = tree[p];
	tree[dir].val++;
	if(l == r) return dir;
	int mid = l + r >> 1;
	if(loc <= mid) tree[dir].ls = Modify(tree[dir].ls, l, mid, loc); 
	if(loc > mid) tree[dir].rs = Modify(tree[dir].rs, mid + 1, r, loc);
	return dir;
}

int Query(int dl, int dr, int l, int r, int k) { 
	if(l == r) return l;
	int mid = l + r >> 1;
	int x = tree[ tree[dr].ls ].val - tree[ tree[dl].ls ].val;
	if(x >= k) return Query(tree[dl].ls, tree[dr].ls, l, mid, k);
	else return Query(tree[dl].rs, tree[dr].rs, mid + 1, r, k - x);
}

signed main()
{
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i], b[++tot] = a[i];
	for(int i = 1; i <= m; i++) {
		char ch = getchar();
		if(ch == 'Q') cin >> q[i].l >> q[i].r >> q[i].k;
		else cin >> q[i].x >> q[i].y, b[++tot] = q[i].y;
	}
	Init();
	
	return 0;
}

