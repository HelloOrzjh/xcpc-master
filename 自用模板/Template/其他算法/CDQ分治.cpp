#pragma GCC optimize(2)
#define IOS ios::sync_with_stdio(false); cin.tie(0);
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = (int)1e5 + 5;

struct Node {
	int val, del, ans;
}a[MAXN];

int n, m, ans, c[MAXN], pos[MAXN];

bool cmp1(const Node &a, const Node &b) { return a.val < b.val; }
bool cmp2(const Node &a, const Node &b) { return a.del < b.del; }

void Modify(int x, int k) {
	while(x <= n) {
		c[x] += k;
		x += (x & (-x));
	}
}

int Query(int x) {
	int res = 0;
	while(x > 0) {
		res += c[x];
		x -= (x & (-x));
	}
	return res;
}

void Solve(int l, int r) {
	if(l == r) return ;
	int mid = l + r >> 1;
	Solve(l, mid), Solve(mid + 1, r);
	
	int i = l, j = mid + 1;
	while(i <= mid) {
		while(a[i].val > a[j].val && j <= r) Modify(a[j].del, 1), ++j;
		a[i].ans += Query(m + 1) - Query(a[i].del), ++i;
	}
	i = l, j = mid + 1;
	while(i <= mid) {
		while(a[i].val > a[j].val && j <= r) Modify(a[j].del, -1), ++j;
		++i;
	}
	
	i = mid, j = r;
	while(j > mid) {
		while(a[j].val < a[i].val && i >= l) Modify(a[i].del, 1), --i;
		a[j].ans += Query(m + 1) - Query(a[j].del), --j;
	}
	i = mid, j = r;
	while(j > mid) {
		while(a[j].val < a[i].val && i >= l) Modify(a[i].del, -1), --i;
		--j;
	}
	sort(a + l, a + r + 1, cmp1);
}

signed main()
{
	IOS
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i].val, pos[ a[i].val ] = i;
	for(int i = 1; i <= m; i++) {
		int cur; cin >> cur;
		a[ pos[cur] ].del = i;
	}
	for(int i = 1; i <= n; i++) if(!a[i].del) a[i].del = m + 1;
	for(int i = 1; i <= n; i++) {
		ans += Query(n) - Query(a[i].val);
		Modify(a[i].val, 1);
	}
	for(int i = 1; i <= n; i++) Modify(a[i].val, -1);
	Solve(1, n);
	sort(a + 1, a + n + 1, cmp2);
	for(int i = 1; i <= m; i++) {
		cout << ans << "\n";
		ans -= a[i].ans;
	}
	return 0;
}
