//#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 10;

char S[MAXN];
int n, m, sa[MAXN], rk[MAXN], oldrk[MAXN << 1], id[MAXN], px[MAXN], cnt[MAXN]; 

bool cmp(int x, int y, int w) {
	return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
}

void SuffixArray(char *s) {
	// getSA	
	n = strlen(s + 1);
	int w, p, i, m = 300, k;
	for(i = 1; i <= n; ++i) ++cnt[ rk[i] = s[i] ];
	for(i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
	for(i = n; i >= 1; --i) sa[ cnt[ rk[i] ]-- ] = i;
	
	for(w = 1; ; w <<= 1, m = p) {
		for(p = 0, i = n; i > n - w; --i) id[++p] = i;
		for(i = 1; i <= n; ++i) if(sa[i] > w) id[++p] = sa[i] - w;
		for(i = 0; i <= m; ++i) cnt[i] = 0;
		for(i = 1; i <= n; ++i) ++cnt[ px[i] = rk[ id[i] ] ];
		for(i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
		for(i = n; i >= 1; --i) sa[ cnt[ px[i] ]-- ] = id[i];
		for(i = 1; i <= n; ++i) oldrk[i] = rk[i];
		for(p = 0, i = 1; i <= n; ++i) rk[ sa[i] ] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
	
		if(p == n) {
			for(int i = 1; i <= n; ++i) sa[ rk[i] ] = i;	
			break;
		}
	}
	//for(int i = 1; i <= n; ++i) cout << sa[i] << " "; cout << "\n";
	
	//getHeight
	for(i = 1, k = 0; i <= n; ++i) {
		if(rk[i] == 0) continue;
		if(k) --k;
		while(S[i + k] == S[ sa[ rk[i] - 1 ] + k ]) ++k;
		height[ rk[i] ] = k;
	}
}

signed main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> S + 1;
	SuffixArray(S);
	return 0;
}
