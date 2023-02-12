/*
区间修改，单点查询的可持久化线段树 
需要利用标记永久化 
*/

#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 100000 + 5;
const int MOD = 998244353;

struct node {
	int s, e, p;
} a[MAXN];

struct treenode {
	int ls, rs, sum = 0, cnt = 0;
} tree[MAXN * 50];

int n, m, tot = 0, root[MAXN];
map<int, int> Map;

int modify(int p, int nl, int nr, int v, int l = 1, int r = n) {
	int dir = ++tot;
	tree[dir] = tree[p];
	if(nl <= l && nr >= r) {
		tree[dir].sum += v;
		tree[dir].cnt += 1;
		return dir;
	}
	int mid = l + r >> 1;
	if(nl <= mid) tree[dir].ls = modify(tree[dir].ls, nl, nr, v, l, mid);
	if(nr > mid) tree[dir].rs = modify(tree[dir].rs, nl, nr, v, mid + 1, r);
	return dir;
}

pair<int, int> query(int p, int loc, int csum = 0, int ccnt = 0, int l = 1, int r = n) {
	if(l == r) return {csum + tree[p].sum, ccnt + tree[p].cnt};
	int mid = l + r >> 1;
	if(loc <= mid) return query(tree[p].ls, loc, csum + tree[p].sum, ccnt + tree[p].cnt, l, mid);
	else return query(tree[p].rs, loc, csum + tree[p].sum, ccnt + tree[p].cnt, mid + 1, r);
}

signed main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> m >> n;
	for(int i = 1; i <= m; i++) cin >> a[i].s >> a[i].e >> a[i].p, Map[ a[i].p ] = 1;
	sort(a + 1, a + 1 + m, [&](const node &a, const node &b) { return a.p < b.p; });
	for(int i = 1; i <= m; i++) root[i] = modify(root[i - 1], a[i].s, a[i].e, a[i].p);
	int pre = 1;
	for(int i = 1; i <= n; i++) {
		int x, a, b, c, k; cin >> x >> a >> b >> c;
		k = 1 + (a * pre % c + b) % c;
		int l = 1, r = m;
		while(l < r) {
			int mid = l + r - 1 >> 1;
			if(query(root[mid], x).second < k) l = mid + 1;
			else r = mid;
		}
		pre = query(root[l], x).first;
		cout << pre << "\n";
	}
	return 0;
}
