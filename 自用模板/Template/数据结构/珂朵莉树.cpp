#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 1e5 + 5;

namespace ODT {
	struct node {
		ll l, r;
		mutable ll v;
		node(ll l, ll r, ll v) : l(l), r(r), v(v) {}
		bool operator < (const node& a) const { return l < a.l; }
	};
	
	set<node> tree;
	int n, q, sum;
	
	set<node>::iterator split(ll pos) {
		auto it = tree.lower_bound( node(pos, 0, 0) );
		if(it != tree.end() && it->l == pos) return it;
		it--;
		ll l = it->l, r = it->r, v = it->v;
		tree.erase(it);
		tree.insert( node(l, pos - 1, v) );
		return tree.insert( node(pos, r, v) ).first;
	}
	
	void assign(ll l, ll r, ll v) {
		int tot = 0, len = 0;
		auto end = split(r + 1), begin = split(l);
		
		for(auto it = begin; it != end; it++) {
			len += (it->r - it->l + 1);
			tot += it->v * (it->r - it->l + 1);
		}
		
		tree.erase(begin, end);
		tree.insert( node(l, r, v) );
		
		if(v == 1) sum += (len - tot);
		else sum -= tot;
	}
	
	// codeforces 915e
	void solve() {
		cin >> n >> q;
		tree.insert( node(1, n, 1) );
		sum = n;
		while(q--) {
			int l, r, k; cin >> l >> r >> k;
			assign(l, r, k == 1 ? 0 : 1);
			cout << sum << "\n";
		}
	}
}
using namespace ODT;

signed main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ODT::solve();
    return 0;
}

