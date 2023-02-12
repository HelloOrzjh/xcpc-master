#include<bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 505;
const int INF = (int)1e16;

int n, m;
int G[MAXN][MAXN];
int lmatch[MAXN], rmatch[MAXN];
int pre[MAXN];
int lexpect[MAXN], rexpect[MAXN];	
int lvis[MAXN], rvis[MAXN];
int slack[MAXN];
queue<int> Q;

void aug(int v) {
	int temp;
	while(v) {
		temp = lmatch[ pre[v] ];
		lmatch[ pre[v] ] = v;
		rmatch[v] = pre[v];
		v = temp;
	}
}

void BFS(int s) {
	for(int i = 1; i <= n; i++) lvis[i] = rvis[i] = 0, slack[i] = INF;

	while(!Q.empty()) Q.pop(); 
	Q.push(s);
	
	while(1) {
		while(!Q.empty()) {
			int u = Q.front(); Q.pop();
			lvis[u] = 1;
			for(int v = 1; v <= n; v++) {
				if(!rvis[v]) {
					int gap = lexpect[u] + rexpect[v] - G[u][v];
					if(slack[v] > gap) {
						slack[v] = gap;
						pre[v] = u;
						if(slack[v] == 0) {
							rvis[v] = 0;
							if(!rmatch[v]) { aug(v); return ; } 
							else Q.push(rmatch[v]);
						} 
					}
				}
			}
		}
		
		int d = INF;
		for(int i = 1; i <= n; i++) 
			if(!rvis[i]) d = min(d, slack[i]);
			
		for(int i = 1; i <= n; i++) {
			if(lvis[i]) lexpect[i] -= d;
			
			if(rvis[i]) rexpect[i] += d;
			else slack[i] -= d;
		}
		
		for(int i = 1; i <= n; i++) {
			if(!rvis[i]) {
				if(slack[i] == 0) {
					rvis[i] = 1;
					if(!rmatch[i]) { aug(i); return ; } 
					else Q.push(rmatch[i]);
				}
			}
		}
	}
}

int KM() {
	for(int i = 1; i <= n; i++) lmatch[i] = rmatch[i] = lexpect[i] = rexpect[i] = 0;

	for(int i = 1; i <= n; i++) {
		lexpect[i] = G[i][1];
		for(int j = 2; j <= n; j++) lexpect[i] = max(lexpect[i], G[i][j]);
	}
	
	for(int i = 1; i <= n; i++) BFS(i);
	
	int res = 0;
	for(int i = 1; i <= n; i++) 
		if(rmatch[i]) res += G[rmatch[i]][i];
		
	return res;
}

signed main()
{
	scanf("%lld%lld", &n, &m); 
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) G[i][j] = -INF;
	for(int i = 1; i <= m; i++) {
		int u, v, w; scanf("%lld%lld%lld", &u, &v, &w);
		G[u][v] = w;
	}
	printf("%lld\n", KM());
	for(int i = 1; i <= n; i++) printf("%lld ", rmatch[i]);
	return 0;
}
