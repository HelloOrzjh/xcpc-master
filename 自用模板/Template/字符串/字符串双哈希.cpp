#include<bits/stdc++.h>
using namespace std;

const int MAXN = 6e5 + 10;
const int INF = 0x3f3f3f3f;

namespace TwoHash {
	#define fi first
	#define se second
	#define pii pair<int, int>
	
	pii Pow[MAXN], Inv[MAXN];
	pii h[MAXN];
	int n;
	string S;
		
	const int BASE1 = 131;
	const int BASE2 = 129;
	const int MOD1 = 1e9 + 7;	
	const int MOD2 = 998244353;
	
	int qpow(int a, int p, int MOD) {
		a %= MOD, p %= MOD;
	    int res = 1;
	    while(p) {
	    	if(p & 1) res = 1ll * res * a % MOD;
	    	a = 1ll * a * a % MOD;
	    	p >>= 1;
		}
 	    return res;
	}
	
	pii Hash(int c, int p) { return {1ll * c * Pow[p].fi % MOD1, 1ll * c * Pow[p].se % MOD2}; }
	
	pii Add(pii x, pii y) {
		pii res = {0, 0};
		res.fi = 1ll * (x.fi + y.fi) % MOD1;
		res.se = 1ll * (x.se + y.se) % MOD2;
		return res;
	}
	
	pii Sub(pii x, pii y) {
		pii res = {0, 0};
		res.fi = 1ll * (x.fi - y.fi + MOD1) % MOD1;
		res.se = 1ll * (x.se - y.se + MOD2) % MOD2;
		return res;
	}
	
	pii Mul(pii x, pii y) {
		pii res = {0, 0};
		res.fi = 1ll * x.fi * y.fi % MOD1;
		res.se = 1ll * x.se * y.se % MOD2;
		return res;
	}
	
	pii Div(pii x, pii y) {
		pii res = {0, 0};
		res.fi = 1ll * x.fi * qpow(y.fi, MOD1 - 2, MOD1) % MOD1;
		res.se = 1ll * x.se * qpow(y.se, MOD1 - 2, MOD1) % MOD1;
		return res;
	}
	
	pii HashVal(int l, int r) { return Mul( Sub(h[r], h[l - 1]), Inv[l - 1]); }
	
	void Init() {
		Pow[0] = Inv[0] = {1, 1}; Inv[1] = {qpow(BASE1, MOD1 - 2, MOD1), qpow(BASE2, MOD2 - 2, MOD2)};
		for(int i = 1; i <= MAXN - 5; i++) Pow[i] = Mul(Pow[i - 1], {BASE1, BASE2});
		for(int i = 2; i <= MAXN - 5; i++) Inv[i] = Mul(Inv[i - 1], Inv[1]);	
	}
	
	void Build(string T) {
		n = T.length(); S = " " + T;
		h[0] = {0, 0};
		for(int i = 1; i <= n; i++) h[i] = Add(h[i - 1], Hash(S[i], i) );
	}
}

signed main() 
{
	TwoHash::Init();
	set<pii> Set;
	int T; cin >> T;
	while(T--) {
		string S; cin >> S;
		TwoHash::Build(S);
		Set.insert( TwoHash::h[S.length()] );
	}
	cout << Set.size();
	return 0;
}
