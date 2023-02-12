#include<bits/stdc++.h>
//#pragma GCC optimize(2)

using namespace std;

const int MAXN = 50000 + 5;
int BLOCK_SIZE;

struct Query {
	int l, r, id;
	bool operator < (const Query &a) const {
		if(l / BLOCK_SIZE != a.l / BLOCK_SIZE) return l < a.l;
		return (l / BLOCK_SIZE) & 1 ? r < a.r : r > a.r;
	}
}q[MAXN];

int n, m, col[MAXN], cnt[MAXN];
long long sum = 0;
pair<long long, long long> ans[MAXN];

void Update(int c, int num) {
	sum -= 1ll * cnt[c] * (cnt[c] - 1) / 2;
	cnt[c] += num;
	sum += 1ll * cnt[c] * (cnt[c] - 1) / 2;
}

signed main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	BLOCK_SIZE = (int)ceil( sqrt(1.0 * n) );
	for(int i = 1; i <= n; i++) cin >> col[i];
	for(int i = 1; i <= m; i++) cin >> q[i].l >> q[i].r, q[i].id = i;
	sort(q + 1, q + m + 1);
	for(int i = 1, l = 1, r = 0; i <= m; i++) {
		if(q[i].l == q[i].r) {
			ans[ q[i].id ] = make_pair(0ll, 1ll);
			continue;
		}
		while(l > q[i].l) Update(col[--l], 1);
		while(r < q[i].r) Update(col[++r], 1);
		while(l < q[i].l) Update(col[l++], -1);
		while(r > q[i].r) Update(col[r--], -1);
		long long tot = 1ll * (r - l + 1) * (r - l) / 2;
		ans[ q[i].id ] = make_pair(sum, tot);
	}
	for(int i = 1; i <= m; i++) {
		if(ans[i].first) {
			long long g = __gcd(ans[i].first, ans[i].second);
			ans[i].first /= g, ans[i].second /= g;
		} else ans[i].second = 1;
		cout << ans[i].first << "/" << ans[i].second << "\n";
	}
	return 0;
}
