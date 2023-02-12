const double eps = 1e-10;
double l, r, a[MAXN];
int n;
double F(double x) {}

void Solve() {
	// 单调递增序列a中查找 >=x 的数中最小的一个 
	while(l < r) {
		int mid = l + r >> 1;
		if(a[mid] >= x) r = mid;
		else l = mid + 1;
	}
	
	// 单调递增序列a中查找 <=x 的数中最大的一个
	while(l < r) {
		int mid = l + r + 1 >> 1;
		if(a[mid] <= x) l = mid;
		else r = mid - 1;
	}
}

void Solve() {	
	// 浮点数三分 求单峰函数的极大值
	while(r - l > eps) {
		double lmid = 1.0 * l + 1.0 * (r - l) / 3.0;
		double rmid = 1.0 * r - 1.0 * (r - l) / 3.0;
		if(F(lmid) > F(rmid)) r = rmid;
		else l = lmid;
	}
	
	// 整数三分 注意特判边界等各种情况 较毒瘤
	while(l < r) {
		int lmid = l + (r - l) / 3;
		int rmid = r - (r - l) / 3;
		if(F(lmid) > F(rmid)) r = rmid;
		else l = lmid;		
	}
}
