int lowbit(int x) { return x & (-x); }

void Modify(int x, int k) {
	while(x <= n) c[x] += k, x += lowbit(x);
} 

int Query(int x) {
	int res = 0;
	while(x > 0) res += c[x], x -= lowbit(x);
	return res;
}

// 树状数组二分 O(logn)求全局第k小
int Kth(int k) {
	int cnt = 0, res = 0;
	for(int i = log2(n); i >= 0; --i) {
		res += (1 << i);
		if(res >= n || cnt + c[res] >= k) res -= (1 << i);
		else cnt += c[res];
	}
	return res + 1;
}
