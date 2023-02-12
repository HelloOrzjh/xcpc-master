#include<bits/stdc++.h>
using namespace std;
const int MAXN = (int)2e7 + 5;

char S[MAXN], T[MAXN];
int z[MAXN], lcp[MAXN];

void Z_Function(char* T) {	// z[i] = lcp(s[i ... n-1], s)
	int n = strlen(T);
	z[0] = n;
	int l = 0, r = 0;
	
	for(int i = 1; i < n; i++) {
		if(i <= r) z[i] = min(z[i - l], r - i + 1);
		while(i + z[i] < n && T[z[i]] == T[i + z[i]]) z[i]++;
		if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}
	
	//for(int i = 0; i < n; i++) cout << z[i] << " "; cout << endl;
}

void exKMP(char* S, char* T) {
	int sLen = strlen(S);
	int tLen = strlen(T);
	Z_Function(T);
	
	int p = 0;
	while(S[p] == T[p] && p < min(sLen, tLen)) p++;
	lcp[0] = p;
	
	int l = 0, r = 0;
	for(int i = 1; i < sLen; i++) {
		if(i <= r) lcp[i] = min(z[i - l], r - i + 1);
		while(i + lcp[i] < sLen && lcp[i] < tLen && S[i + lcp[i]] == T[lcp[i]]) lcp[i]++;
		if(i + lcp[i] - 1 > r) l = i, r = i + lcp[i] - 1;
	}
	
	//for(int i = 0; i < sLen; i++) cout << lcp[i] << " "; cout << endl;
}

signed main()
{
	scanf("%s%s", S, T);
	exKMP(S, T);
	return 0;
}

/*
input:
aaaabaa
aaaaa

z function : {5 4 3 2 1}
lcp function : {4 3 2 1 0 2 1} 
*/
