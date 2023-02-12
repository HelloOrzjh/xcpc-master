/* 区间加法 区间乘法 区间求和 */

#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN = (int)1e5 + 5;

int n, m, MOD;
ll mul[MAXN << 2], add[MAXN << 2], sum[MAXN << 2], a[MAXN];

inline int ls(int x) { return x << 1; }
inline int rs(int x) { return x << 1 | 1; }

void PushUp(int p) {
	sum[p] = (sum[ls(p)] + sum[rs(p)]) % MOD;
}

void PushDown(int p, int l, int r) {
	int mid = l + r >> 1;
	mul[ls(p)] = mul[ls(p)] * mul[p] % MOD;
	mul[rs(p)] = mul[rs(p)] * mul[p] % MOD;
	add[ls(p)] = (add[ls(p)] * mul[p] % MOD + add[p]) % MOD;
	add[rs(p)] = (add[rs(p)] * mul[p] % MOD + add[p]) % MOD;
	sum[ls(p)] = (sum[ls(p)] * mul[p] % MOD + add[p] * (mid - l + 1) % MOD) % MOD;
	sum[rs(p)] = (sum[rs(p)] * mul[p] % MOD + add[p] * (r - mid) % MOD) % MOD;	
	add[p] = 0, mul[p] = 1;
}

void Build(int l, int r, int p) {
	add[p] = 0, mul[p] = 1; // significant
	if(l == r) {
		sum[p] = a[l];
		return ;
	}
	int mid = l + r >> 1;
	Build(l, mid, ls(p));
	Build(mid + 1, r, rs(p));
	PushUp(p);
}

void ModifyAdd(int nl, int nr, int l, int r, int p, ll k) {
	if(nl <= l && nr >= r) {
		add[p] = (add[p] + k) % MOD;
		sum[p] = (sum[p] + 1ll * (r - l + 1) * k % MOD) % MOD;
		return ;
	}
	PushDown(p, l, r);
	int mid = l + r >> 1;
	if(nl <= mid) ModifyAdd(nl, nr, l, mid, ls(p), k);
	if(nr > mid) ModifyAdd(nl, nr, mid + 1, r, rs(p), k);
	PushUp(p);
}

void ModifyMul(int nl, int nr, int l, int r, int p, ll k) {
	if(nl <= l && nr >= r) {
		mul[p] = mul[p] * k % MOD;
		add[p] = add[p] * k % MOD;
		sum[p] = sum[p] * k % MOD;
		return ;
	}
	PushDown(p, l, r);
	int mid = l + r >> 1;
	if(nl <= mid) ModifyMul(nl, nr, l, mid, ls(p), k);
	if(nr > mid) ModifyMul(nl, nr, mid + 1, r, rs(p), k);
	PushUp(p);
}

ll Query(int nl, int nr, int l, int r, int p) {
	if(nl <= l && nr >= r) return sum[p];
	PushDown(p, l, r);
	int mid = l + r >> 1, res = 0;
	if(nl <= mid) res = (res + Query(nl, nr, l, mid, ls(p)) ) % MOD;
	if(nr > mid) res = (res + Query(nl, nr, mid + 1, r, rs(p)) ) % MOD;
	return res;
}

signed main()
{
	scanf("%d%d%d", &n, &m, &MOD);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	Build(1, n, 1);
	while(m--) {
		int op, l, r; ll k;
		scanf("%d%d%d", &op, &l, &r);
		if(op == 1) {
			scanf("%lld", &k);
			ModifyMul(l, r, 1, n, 1, k);
		} else if(op == 2) {
			scanf("%lld", &k);
			ModifyAdd(l, r, 1, n, 1, k);
		} else {
			printf("%lld\n", Query(l, r, 1, n, 1) );
		}
		
	}
	return 0;
}
