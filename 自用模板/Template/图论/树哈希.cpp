// 复杂度O(nlogn), n为节点数量
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 5;

vector<int> g[MAXN];
unordered_map<int, int> num;
map<vector<int>, int> Hash;
int hash_cnt;

int dfs(int u, int f) {
	vector<int> vec;
	for(auto &v : g[u]) {
		if(v == f) continue;
		vec.push_back( dfs(v, u) );
	} 
	sort(vec.begin(), vec.end() );
	if(Hash[vec] == 0) Hash[vec] = ++hash_cnt;
 	return Hash[vec];
}

void init() {
	hash_cnt = 0;
	Hash.clear();
}

signed main() {
	//ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	init(); int m; cin >> m;
	for(int i = 1; i <= m; i++) {
		int n; cin >> n;
		for(int j = 1; j <= n; j++) {
			int f; cin >> f;
			if(f == 0) continue;
			g[f].push_back(j); g[j].push_back(f);
		}
		
		/*
		树哈希返回对应子树的哈希值，
		如需要比较两棵树的哈希值，可以通过求重心的方式固定根节点；
		若重心有两个，分别固定根节点求哈希值即可。
		*/
		int h = dfs(centroid, 0);
		if(num[h] == 0) num[h] = i;
		cout << num[h] << "\n";
		
		for(int j = 0; j <= n; j++) g[j].clear();
	}
} 