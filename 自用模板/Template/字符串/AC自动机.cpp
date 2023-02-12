#include<bits/stdc++.h>
using namespace std;
const int MAXN = (int)1e6 + 5;

char S[MAXN], T[MAXN];
int n, cnt, trie[MAXN][30], fail[MAXN * 30], num[MAXN * 30];
queue<int> Q;

inline int Hash(char x) { return x - 'a' + 1; }

void Trie(char* S) {
	int cur = 1;
	int len = strlen(S);
	for(int i = 0; i < len; i++) {
		int x = Hash(S[i]);
		if(!trie[cur][x]) trie[cur][x] = ++cnt;
		cur = trie[cur][x];
	}
	num[cur]++;
}

void GetFail() {
	for(int i = 1; i <= 26; i++) trie[0][i] = 1;
	Q.push(1);
	fail[1] = 0;
	while(!Q.empty()) {
		int u = Q.front();
		Q.pop();
		int faFail = fail[u];
		for(int i = 1; i <= 26; i++) {
			int v = trie[u][i];
			if(v) fail[v] = trie[faFail][i], Q.push(v);
			else trie[u][i] = trie[faFail][i];
		}
	}
}

int main()
{
	scanf("%d", &n);
	cnt = 1;
	for(int i = 1; i <= n; i++) {
		scanf("%s", S);
		Trie(S);
	}
	GetFail(); 
	scanf("%s", T);
	
	int cur = 1, ans = 0, len = strlen(T);
	for(int i = 0; i < len; i++) {
		cur = trie[cur][Hash(T[i])];
		for(int t = cur; t && ~num[t]; t = fail[t]) ans += num[t], num[t] = -1;
	}
	printf("%d\n", ans);
	return 0;
}

