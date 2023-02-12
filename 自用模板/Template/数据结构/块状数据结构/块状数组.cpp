#include<bits/stdc++.h>
using namespace std;
const int MAXN = (int)50005;
int a[MAXN], tag[MAXN], ValueAllOne[MAXN], id[MAXN], sum[MAXN], n, S;
vector<int> b[MAXN];
pair<int, int> block[MAXN];
 
void Init() {
	S = sqrt(n);
	memset(id, -1, sizeof(id));
	for(int i = 1; i <= n; i++) id[i] = (i - 1) / S + 1;
	
	int j = 1;
	for(int i = id[1]; i <= id[n]; i++) {
		// 维护区间和
		block[i].first = j;
		for(; id[j] == i; j++) sum[i] += a[j];
		block[i].second = j - 1;
		
		// 维护区间排序
		for(; id[j] == i; j++) b[i].push_back(a[j]);
		sort(b[i].begin(), b[i].end());		
	}
}

void PushDownSqrt(int cid) {
	int l = block[cid].first, r = block[cid].second;
	if(ValueAllOne[cid] == 1 || tag[cid] == 0) return ;
	
	bool flag = true;
	for(int i = l; i <= r; i++) {
		for(int j = 1; j <= tag[cid]; j++) {
			if(a[i] == 1) break;
			a[i] = floor(sqrt(1.0 * a[i]));
		}
		if(a[i] > 1) flag = false;
	}
	
	tag[cid] = 0;
	if(flag) ValueAllOne[cid] = 1;
	sum[cid] = 0;
	for(int i = l; i <= r; i++) sum[cid] += a[i];
}

void ModifySqrt(int l, int r) {	// 区间元素开根号
	int lid = id[l], rid = id[r];
	if(lid == rid) {
		SqrtPushDown(lid);
		for(int i = l; i <= r; i++) {
			int cur = floor(sqrt(1.0 * a[i]));
			sum[lid] -= a[i], sum[lid] += cur;
			a[i] = cur;
		}
	} else {
		PushDown(lid); PushDown(rid);
		for(int i = l; id[i] == lid; i++) {
			int cur = floor(sqrt(1.0 * a[i]));
			sum[lid] -= a[i], sum[lid] += cur;
			a[i] = cur;			
		}
		for(int i = r; id[i] == rid; i--) {
			int cur = floor(sqrt(1.0 * a[i]));
			sum[rid] -= a[i], sum[rid] += cur;
			a[i] = cur;	
		}
		for(int i = lid + 1; i < rid; i++) ++tag[i];
	}
}

int QuerySum(int l, int r) {	// 区间求和
	int lid = id[l], rid = id[r];
	if(lid == rid) {
		PushDown(lid);
		int res = 0;
		for(int i = l; i <= r; i++) res += a[i];
		return res;
	} else {
		int res = 0;
		PushDown(lid); PushDown(rid);
		for(int i = l; id[i] == lid; i++) res += a[i];
		for(int i = r; id[i] == rid; i--) res += a[i];
		for(int i = lid + 1; i < rid; i++) PushDown(i), res += sum[i];
		return res;
	}
}

void ModifyAdd(int l, int r, int c) { // 区间元素都+c
	int lid = id[l], rid = id[r];
	if(lid == rid) {
		b[lid].clear();
		for(int i = l; i <= r; i++) {
			a[i] += c;
			b[lid].push_back(a[i]);	
		}
		for(int i = l - 1; id[i] == lid; i--) b[lid].push_back(a[i]);
		for(int i = r + 1; id[i] == lid; i++) b[lid].push_back(a[i]);
		sort(b[lid].begin(), b[lid].end());
	} else {
		b[lid].clear();
		for(int i = l; id[i] == lid; i++) {
			a[i] += c;
			b[lid].push_back(a[i]);
		}
		for(int i = l - 1; id[i] == lid; i--) b[lid].push_back(a[i]);
		sort(b[lid].begin(), b[lid].end());
		
		b[rid].clear();
		for(int i = r; id[i] == rid; i--) {
			a[i] += c;
			b[rid].push_back(a[i]);
		}
		for(int i = r + 1; id[i] == rid; i++) b[rid].push_back(a[i]);
		sort(b[rid].begin(), b[rid].end());
		
		for(int i = lid + 1; i < rid; i++) tag[i] += c;
	}
}

int QuerySumOfSmaller(int l, int r, int c) { // 区间查询小于c的数字个数
	int lid = id[l], rid = id[r];
	if(lid == rid) {
		int res = 0;
		for(int i = l; i <= r; i++) {
			res += (a[i] + tag[lid] < c);
		}
		return res;
	} else {
		int res = 0;
		for(int i = l; id[i] == lid; i++) {
			res += (a[i] + tag[lid] < c);
		}
		for(int i = r; id[i] == rid; i--) {
			res += (a[i] + tag[rid] < c);
		}
		for(int i = lid + 1; i < rid; i++) {
			res += lower_bound(b[i].begin(), b[i].end(), c - tag[i]) - b[i].begin();
		}
		return res;
	}
}

int QueryPre(int l, int r, int c) { // 区间内查询c的前驱(比其小的最大元素)
	int lid = id[l], rid = id[r];
	if(lid == rid) {
		int res = -INF;
		for(int i = l; i <= r; i++) {
			if(a[i] + tag[lid] < c) res = max(res, a[i] + tag[lid]);
		}
		return res;
	} else {
		int res = -INF;
		for(int i = l; id[i] == lid; i++) {
			if(a[i] + tag[lid] < c) res = max(res, a[i] + tag[lid]);
		}
		for(int i = r; id[i] == rid; i--) {
			if(a[i] + tag[rid] < c) res = max(res, a[i] + tag[rid]);
		}
		for(int i = lid + 1; i < rid; i++) {
			int cur = lower_bound(b[i].begin(), b[i].end(), c - tag[i]) - b[i].begin() - 1;
			if(cur >= 0) res = max(res, b[i][cur] + tag[i]);
		}
		return res;	
	}
}

signed main()
{	
	Init();
	//Solve();
	return 0;
}