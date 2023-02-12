#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;

const int MAXN = (int)1e5 + 5;
const int MAXM = (int)2e5 + 5;

stack<int> S;
vector<int> G[MAXN];
int del[MAXN], in[MAXN], out[MAXN], n, m;

void DFS(int u) {
	for(int i = del[u]; i < G[u].size(); i = del[u]) del[u] = i + 1, DFS(G[u][i]);
	S.push(u);
}

signed main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= m; i++) {
		int u, v; cin >> u >> v;
		G[u].push_back(v); out[u]++; in[v]++;
	}
	for(int i = 1; i <= n; i++) sort(G[i].begin(), G[i].end());
	int s = 1, cnt0 = 0, cnt1 = 0, flag = 1;
	for(int i = 1; i <= n; i++) {
		if(in[i] != out[i]) flag = 0;
		if(out[i] == in[i] + 1) s = i, cnt1++;
		if(in[i] == out[i] + 1) cnt0++;
	}
	if(!flag && !(cnt0 == cnt1 && cnt0 == 1) ) return cout << "No", 0;
	DFS(s);
	while(!S.empty()) cout << S.top() << " ", S.pop();
	return 0;
}

