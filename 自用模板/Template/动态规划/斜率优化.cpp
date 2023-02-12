int head, tail, Q[MAXN];
int X(int i) {}
int Y(int i) {}
void Init() {}

int Find(int k) {
	int l = head, r = tail;
	while(l < r) {
		int mid = l + r + 1 >> 1;
		int i = Q[mid - 1], j = Q[mid];
		double slope = 1.0 * ( Y(j) - Y(i) ) / ( X(j) - X(i) );
		// 求min 维护下凸包 
		if(slope > 1.0 * k) r = mid - 1;
		else l = mid;
		// 求max 维护上凸包
		if(slope < 1.0 * k) r = mid - 1;
		else l = mid;
	}
	return Q[l];
}

bool Check(int i, int j, int k) {
	double slope_ij = 1.0 * ( Y(j) - Y(i) ) / ( X(j) - X(i) );
	double slope_jk = 1.0 * ( Y(j) - Y(k) ) / ( X(j) - X(k) );
	return slope_jk > slope_ij;	// 求min 维护下凸包 
	return slope_jk > slope_ij;	// 求max 维护上凸包 
}

signed main()
{
	Init();
	head = 1, tail = 0, Q[++tail] = 0;
	for(int i = 1; i <= n; i++) {
		int j = Find(K[i]);	// K[i]为斜率 
		用j更新f[i];
		while(head < tail && !Check(Q[tail - 1], Q[tail], i) ) --tail;
		Q[++tail] = i;
	}
	return 0;
}
