# hdu 2021“MINIEYE杯”中国大学生算法设计超级联赛（10）部分题题解

## 1003 Pty loves lines

知识点：记忆化搜索

设$f[j][k]$为j条线k个交点的合法情况

如果$f[j][k]$合法 那么对于$i>j, f[i][(i-j)*j + k]$也合法 其意义是在j条边的基础上新加了i-j条**两两平行**的边

发现正着转移状态的话 会有很多重复状态被访问($f[i][(i-j)*j+k]$已经合法 但$f[j][k]$依然继续被访问) 我们改用记忆化搜索 当前状态如果合法就直接返回

但是还是会TLE

emmm我们先换成bitset来表示状态 这样常数会除以32

再打表观察一下规律 发现方案后面会有一段**连续上升**的序列 不合法的最大位置大约在30000左右

直接设置一个35000的枚举上界 当超过35000后直接输出即可 当有n条线时 交点最多有$n(n-1)/2$个

时间复杂度$O(35000n^2/32)$

```cpp
#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
//#define int long long

using namespace std;

//unordered_map<int, int> f[705];
//int g[705][30005];
bitset<350 * 704> f[705], g[705];
//bool f[705][350 * 704], g[705][350 * 704];
int cnt;

bool DFS(int x, int t) {
    if(t == 0) return f[x][t] = 1;
    if(f[x][t] == 1 && g[x][t] == 0) return 1;
    if(g[x][t] == 1 && f[x][t] == 0) return 0;
    if(t < 0) return 0;
    
    int res = 0;
    for(int i = x - 1; i >= 1; i--) {
        if(t - (x - i) * i < 0) continue;
        if(DFS(i, t - (x - i) * i)) {
            g[x][t] = 0;
            return f[x][t] = 1;
            break;
        } 
    }
    
    g[x][t] = 1; f[x][t] = 0;
    return 0;
}

void Solve(int n) {
    cnt = 0;
    printf("0 ");
    for(int i = 1; i <= min(n * (n - 1) / 2 - 1, 35000); ++i) {
        if(DFS(n, i)) printf("%d ", i);
    }
    for(int i = 35001; i < n * (n - 1) / 2; i++) printf("%d ", i);
    printf("%d\n", n * (n - 1) / 2);
}

signed main()
{
    //freopen("qwq.out", "w", stdout);
    //Solve(700);
    
    int TT; scanf("%d", &TT);
    while(TT--) {
        int n;
        scanf("%d", &n);
        Solve(n); 
    }
    return 0;
}
```



## 1008 Pty loves string

知识点：KMP 主席树

给定前缀x和后缀y 如果有S[l,r]满足条件 那么有S[l,l+x-1] = S[1,x]且S[r-y+1,r] = S[n-y+1,n]且l+x=r-y+1

分别对正着写的串和反着写的串做一次KMP 求出pmt(border)数组

再对于每个i 连一条从pmt[i]到i的边

这样对于每个点u 其子树中所有节点v表示的意义为具有S[1...u]前缀的S[1..v]

问题转化为第一个树中**根为x的子树**的编号在第二个树中**根为y的子树**中出现的次数

用主席树维护即可

```cpp
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
//#define int long long

using namespace std;

const int MAXN = (int)2e5 + 5;

struct Tree {
	int ls, rs, val;
}tree[MAXN << 5];

vector<int> G1[MAXN], G2[MAXN];
int n, Q, tot1, tot2, cnt, root[MAXN], p1[MAXN], p2[MAXN], dfn1[MAXN], dfn2[MAXN], sze1[MAXN], sze2[MAXN], hash1[MAXN], hash2[MAXN];
char S[MAXN];

void DFS1(int u) {
	dfn1[u] = ++tot1;
	sze1[u] = 1;
	hash1[tot1] = u;
	
	for(auto v : G1[u]) {
		DFS1(v);
		sze1[u] += sze1[v];
	}
}

void DFS2(int u) {
	dfn2[u] = ++tot2;
	sze2[u] = 1;
	hash2[tot2] = u;
	
	for(auto v : G2[u]) {
		DFS2(v);
		sze2[u] += sze2[v];
	}
}

int Build(int l, int r) {
	int dir = ++cnt;
	tree[dir].val = 0;
	if(l == r) return dir;
	int mid = l + r >> 1;
	tree[dir].ls = Build(l, mid);
	tree[dir].rs = Build(mid + 1, r);
	return dir;
}

int Modify(int p, int l, int r, int loc) {
	int dir = ++cnt;
	tree[dir] = tree[p];
	tree[dir].val++;
	if(l == r) return dir;
	int mid = l + r >> 1;
	if(loc <= mid) tree[dir].ls = Modify(tree[dir].ls, l, mid, loc);
	if(loc > mid) tree[dir].rs = Modify(tree[dir].rs, mid + 1, r, loc);
	return dir;
}

int Query(int dl, int dr, int l, int r, int nl, int nr) {
	if(nl <= l && nr >= r) return tree[dr].val - tree[dl].val;
	int res = 0;
	int mid = l + r >> 1;
	if(nl <= mid) res += Query(tree[dl].ls, tree[dr].ls, l, mid, nl, nr);
	if(nr > mid) res += Query(tree[dl].rs, tree[dr].rs, mid + 1, r, nl, nr);
	return res;
}

signed main()
{
	
	int TT; cin >> TT;
	while(TT--) {
		cin >> n >> Q;
		cin >> S + 1;
		
		p1[0] = p1[1] = 0;
		p2[n + 1] = p2[n] = n + 1;
		int p = 0;
		for(int i = 2; i <= n; i++) {
			while(p && S[i] != S[p + 1]) p = p1[p];
			if(S[i] == S[p + 1]) p++;
			p1[i] = p;
		}
		p = n + 1;
		for(int i = n - 1; i >= 1; i--) {
			while(p <= n && S[i] != S[p - 1]) p = p2[p];
			if(S[i] == S[p - 1]) p--;
			p2[i] = p;
		}
		
		for(int i = 1; i <= n; i++) {
			G1[ p1[i] ].push_back(i);
			G2[ p2[i] ].push_back(i);
		}
		/*
		for(int i = 0; i <= n + 1; i++) {
			cout << i << " : ";
			for(auto v : G2[i]) cout << v << " "; 
			cout << "\n";
		}
		*/
		tot1 = 0; DFS1(0);
		tot2 = 0; DFS2(n + 1);
		
		cnt = 0;
		root[0] = Build(1, n + 1);
		for(int i = 1; i <= n + 1; i++) {
			root[i] = Modify(root[i - 1], 1, n + 1, dfn2[ hash1[i] + 1 ]);
		}
		
		while(Q--) {
			int l, r;
			cin >> l >> r;
			r = n + 1 - r;
			cout << Query(root[dfn1[l] - 1], root[dfn1[l] + sze1[l] - 1], 1, n + 1, dfn2[r], dfn2[r] + sze2[r] - 1) << endl;
		}
		
		for(int i = 0; i <= n + 1; i++) G1[i].clear(), G2[i].clear();
	}
	return 0;
}

```

