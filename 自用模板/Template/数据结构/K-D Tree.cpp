//#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define x1 x123456789
#define y1 y123456789
using namespace std;

const int MAXN = 5e5 + 5;
const double alpha = 0.725;

struct node {
	int x, y, v;
}a[MAXN];

int n, cnt;
int rt, L[MAXN], R[MAXN], D[MAXN], U[MAXN], d[MAXN], sze[MAXN], sum[MAXN], ls[MAXN], rs[MAXN];
int g[MAXN], t;

bool cmp1(int x, int y) { return a[x].x < a[y].x; }
bool cmp2(int x, int y) { return a[x].y < a[y].y; }

void maintain(int p) {
	sze[p] = sze[ ls[p] ] + sze[ rs[p] ] + 1;
	sum[p] = sum[ ls[p] ] + sum[ rs[p] ] + a[p].v;
	L[p] = R[p] = a[p].x;
	D[p] = U[p] = a[p].y;
	if(ls[p]) {
		L[p] = min(L[p], L[ ls[p] ]), R[p] = max(R[p], R[ ls[p] ]);
		D[p] = min(D[p], D[ ls[p] ]), U[p] = max(U[p], U[ ls[p] ]);
	}
	if(rs[p]) {
		L[p] = min(L[p], L[ rs[p] ]), R[p] = max(R[p], R[ rs[p] ]);
		D[p] = min(D[p], D[ rs[p] ]), U[p] = max(U[p], U[ rs[p] ]);
	}
}

int build(int l, int r) {
	if(l > r) return 0;
	int mid = l + r >> 1;
	double ave1 = 0, ave2 = 0, var1 = 0, var2 = 0;
	for(int i = l; i <= r; i++) ave1 += a[ g[i] ].x, ave2 += a[ g[i] ].y;
	ave1 /= (r - l + 1), ave2 /= (r - l + 1);
	for(int i = l; i <= r; i++) {
		var1 += (a[ g[i] ].x - ave1) * (a[ g[i] ].x - ave1);
		var2 += (a[ g[i] ].y - ave2) * (a[ g[i] ].y - ave2);
	}
	if(var1 > var2) {
		nth_element(g + l, g + mid, g + r + 1, cmp1);
		d[ g[mid] ] = 1;
	} else {
		nth_element(g + l, g + mid, g + r + 1, cmp2);
		d[ g[mid] ] = 2;
	}
	ls[ g[mid] ] = build(l, mid - 1);
	rs[ g[mid] ] = build(mid + 1, r);
	maintain(g[mid]);
	return g[mid];
}

void print(int p) {
	if(!p) return ;
	print(ls[p]);
	g[++t] = p;
	print(rs[p]);
}

void rebuild(int &p) {
	t = 0;
	print(p);
	p = build(1, t);
}

bool bad(int p) {
	return alpha * sze[p] <= (double) max(sze[ ls[p] ], sze[ rs[p] ]);
}

void insert(int &p, int k) {
	if(!p) {
		p = k;
		maintain(p);
		return ;
	}
	if(d[p] == 1) {
		if(a[k].x <= a[p].x) insert(ls[p], k);
		else insert(rs[p], k);
	} else {
		if(a[k].y <= a[p].y) insert(ls[p], k);
		else insert(rs[p], k);
	}
	maintain(p);
	if( bad(p) ) rebuild(p);
}

int query(int p, int xl, int yl, int xr, int yr) {
	if(!p || xr < L[p] || xl > R[p] || yr < D[p] || yl > U[p]) return 0;
	if(xl <= L[p] && R[p] <= xr && yl <= D[p] && U[p] <= yr) return sum[p];
	int res = 0;
	if(xl <= a[p].x && a[p].x <= xr && yl <= a[p].y && a[p].y <= yr) res += a[p].v;
	return query(ls[p], xl, yl, xr, yr) + query(rs[p], xl, yl, xr, yr) + res;
}

signed main()
{
	int lastans = 0, op, x1, y1, x2, y2, A; 
	scanf("%d", &n); cnt = 0;
	while( scanf("%d", &op) ) {
		if(op == 1) {
			cin >> x1 >> y1 >> A;
			x1 ^= lastans;
			y1 ^= lastans;
			A ^= lastans;
			a[++cnt] = (node){x1, y1, A};
			insert(rt, cnt);
		}
		if(op == 2) {
			cin >> x1 >> y1 >> x2 >> y2;
			x1 ^= lastans;
			y1 ^= lastans;
			x2 ^= lastans;
			y2 ^= lastans;
			printf("%d\n", lastans = query(rt, x1, y1, x2, y2) );
		}
		if(op == 3) break;
	}
	return 0;
}
