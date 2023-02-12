// 求n个矩形的面积并
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = (int)1e5 + 5;

struct ScanLine {
	int x, lowy, highy, io;	//io记录 入边/出边 
	ScanLine(){}
	ScanLine(int x, int y1, int y2, int io) : x(x), lowy(y1), highy(y2), io(io){}
	bool operator < (const ScanLine &a) const { return x < a.x; }
}line[MAXN << 1];

int n, ans = 0, tot, cnt, yy[MAXN << 1];
int length[MAXN << 3], tag[MAXN << 3];

int ls(int x) { return x << 1; }
int rs(int x) { return x << 1 | 1; }

void PushUp(int p, int l, int r) {
	if(tag[p]) length[p] = yy[r] - yy[l];
	else if(l + 1 == r) length[p] = 0;
	else length[p] = length[ls(p)] + length[rs(p)];
}

void Build(int l, int r, int p) {	//注意叶子节点的结构（用区间表示 如[1,2] [2,3]） 
	if(l >= r) return ;
	tag[p] = length[p] = 0;
	if(l + 1 == r) return ;
	int mid = (l + r) >> 1;
	Build(l, mid, ls(p));
	Build(mid, r, rs(p));
}

void Update(int nl, int nr, int l, int r, int p, int io) {
	if(nl > r || nr < l) return ;
	if(nl <= l && nr >= r) {
		tag[p] += io;
		PushUp(p, l, r);
		return ;
	}
	if(l + 1 == r) return ;
	int mid = (l + r) >> 1;
	if(nl <= mid) Update(nl, nr, l, mid, ls(p), io);
	if(nr >= mid) Update(nl, nr, mid, r, rs(p), io);
	PushUp(p, l, r);
}

signed main()
{
	scanf("%lld", &n);
	cnt = 0;
	for(int i = 1; i <= n; i++) {
		int x1, y1, x2, y2;
		scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);	//(x1, y1)为左下角坐标, (x2, y2)为右上角坐标 
		line[++cnt] = ScanLine(x1, y1, y2, 1);
		yy[cnt] = y1;
		line[++cnt] = ScanLine(x2, y1, y2, -1);
		yy[cnt] = y2;
	}
	sort(yy + 1, yy + 1 + cnt);
	sort(line + 1, line + 1 + cnt);
	tot = unique(yy + 1, yy + 1 + cnt) - (yy + 1);	// 离散化, tot记录去重后共多少y值 
	ans = 0;
	Build(1, tot, 1);
	for(int i = 1; i <= cnt; i++) {
		ans += length[1] * (line[i].x - line[i - 1].x);
		int yl = lower_bound(yy + 1, yy + 1 + tot, line[i].lowy) - yy;
		int yr = lower_bound(yy + 1, yy + 1 + tot, line[i].highy) - yy;
		Update(yl, yr, 1, tot, 1, line[i].io);
	} 
	printf("%lld", ans);
	return 0;
}
