# hdu 2021“MINIEYE杯”中国大学生算法设计超级联赛（2）部分题题解

## 1001 I love cube

知识点：数学

由题易得

一个边长为$1$的小正方体共有$8$个边长为$\sqrt{2}$的等边三角形符合条件

一个边长为$2$的小正方体共有$8$个边长为$2\sqrt{2}$的等边三角形符合条件

依此类推 若大正方体边长为$n-1$ 则边长为$k$的小正方体共有$(n-k)^3$个 符合条件的等边三角形共$8(n-k)^3$个

答案为$\sum_{i=1}^{n-1}8(n-i)^3 = 2 * n^2 * (n - 1)^2$

注意到计算过程中可能爆long long 我们直接开int128

```cpp
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int __int128

using namespace std;

const int MOD = (int)1e9 + 7;

int n;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		x = x * 10 + (ch - '0');
		ch = getchar();
	}
	return x * f;
}

inline void write(int x) {
	if(x < 0) {
		x = -x;
		putchar('-');
	}
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

signed main()
{
	FAST
	int T;
	T = read();
	while(T--) {
		n = read();
		int ans = 2 * n % MOD * n % MOD * (n - 1) % MOD * (n - 1) % MOD;
		write(ans);
		putchar('\n');
	}
	return 0;
}

```



## 1002 I love tree

知识点：线段树 树链剖分

看到1e5的数据范围 看到树上区间修改 单点查询 我们可以想到树链剖分（~~应该不难想吧~~）

难点在于树上的区间修改 增加的数与位置有关

我们先考虑对于一段连续的区间$[l,r]$执行1操作，设维护一个a数组 有
$$
sum[l] += 1 ^ 2;\\
sum[l + 1] += 2 ^ 2;\\
...\\
sum[r] += (r - (l - 1) ) ^ 2;
$$
即
$$
sum[i] += (i - (l - 1)) ^ 2
$$
即
$$
sum[i] += i ^ 2 - 2 * (l - 1) * i + (l - 1) ^ 2
$$
注意到右式各项满足加法结合律 我们可以维护右式各项的系数 单点查询时直接用下标乘以相应系数即可 有
$$
sum[x] = Query2(x) * x ^ 2 + Query1(x) * x + Query0(x)
$$
Query0,1,2分别维护$x^0, x^1, x^2$项的系数

利用树剖，我们可以创建两个变量minn,maxx表示目前加给区间的最小值和最大值 在修改的时候维护这两个变量即可

注意可能有反着加的情况 即
$$
sum[r] += 1 ^ 2;\\
sum[r - 1] += 2 ^ 2;\\
...
$$
有
$$
sum[i] += (r + 1 - i) ^ 2;
$$
分类讨论即可

```cpp
#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long

using namespace std;

const int MAXN = (int)1e5 + 5;

int n, cnt = 0, vis[MAXN], idx[MAXN], fa[MAXN], dep[MAXN], sze[MAXN], son[MAXN], top[MAXN];
vector<int> G[MAXN];

struct Tree {
	int sum[MAXN << 2], tag[MAXN << 2];
		
	int ls(int x) {	return x << 1; }
	int rs(int x) { return x << 1 | 1; }
	
	void PushUp(int p) {
		sum[p] = sum[ls(p)] + sum[rs(p)];
	}
	
	void PushDown(int l, int r, int p) {
		int mid = (l + r) >> 1;
		
		tag[ls(p)] += tag[p];
		tag[rs(p)] += tag[p];
		sum[ls(p)] += (mid - l + 1) * tag[p];
		sum[rs(p)] += (r - (mid + 1) + 1) * tag[p];
		
		tag[p] = 0;
	}
	
	void Modify(int nl, int nr, int l, int r, int p, int k) {
		if(nl <= l && nr >= r) {
			sum[p] += (r - l + 1) * k;
			tag[p] += k;
			return ;
		}
		int mid = (l + r) >> 1;
		PushDown(l, r, p);
		if(nl <= mid) Modify(nl, nr, l, mid, ls(p), k);
		if(nr > mid) Modify(nl, nr, mid + 1, r, rs(p), k);
		PushUp(p);
	}
	
	int Query(int x, int l, int r, int p) {
		if(l == r) {	
			return sum[p];
		}
		int mid = (l + r) >> 1;
		PushDown(l, r, p);
		if(x <= mid) return Query(x, l, mid, ls(p));
		if(x > mid) return Query(x, mid + 1, r, rs(p));
	}
	
}x2, x1, x0;

void DFS1(int u, int ftr) {
	fa[u] = ftr;
	vis[u] = 1;
	sze[u] = 1;
	dep[u] = dep[ftr] + 1;
	
	int maxsize = -1;
	for(int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if(vis[v]) continue;
		DFS1(v, u);
		sze[u] += sze[v];
		
		if(sze[v] > maxsize) {
			son[u] = v;
			maxsize = sze[v];
		}
		
	}
	
}

void DFS2(int u, int topu) {
	idx[u] = ++cnt;
	top[u] = topu;
	if(son[u] == 0) return ;
	DFS2(son[u], topu);
	for(int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if(v == fa[u] || v == son[u]) continue;
		DFS2(v, v);
	}
}

int LCA(int u, int v) {
	while(top[u] != top[v]) {
		if(dep[ top[u] ] > dep[ top[v] ]) u = fa[ top[u] ];
		else v = fa[ top[v] ];
	}
	return dep[u] <= dep[v] ? u : v;
}

int dist(int u, int v) {
	return dep[u] + dep[v] - 2 * dep[LCA(u, v)];
} 

void Modify(int u, int v) {
	int minn = 1, maxx = dist(u, v) + 1;
	int l, r;
	while(top[u] != top[v]) {
		if(dep[top[u]] >= dep[top[v]]) {
			l = idx[top[u]], r = idx[u];
			x2.Modify(l, r, 1, n, 1, 1);
			x1.Modify(l, r, 1, n, 1, -2 * (minn + r));
			x0.Modify(l, r, 1, n, 1, (minn + r) * (minn + r));
			minn += (r - l + 1);
			u = fa[top[u]];
		} else {
			l = idx[top[v]], r = idx[v];
			int cur = maxx - (r - l);
			x2.Modify(l, r, 1, n, 1, 1);
			x1.Modify(l, r, 1, n, 1, -2 * (l - cur));
			x0.Modify(l, r, 1, n, 1, (l - cur) * (l - cur));			
			v = fa[top[v]];
			maxx = cur;
		}
	}
	if(dep[u] < dep[v]) {
		l = idx[u], r = idx[v];
		x2.Modify(l, r, 1, n, 1, 1);
		x1.Modify(l, r, 1, n, 1, -2 * (l - minn));
		x0.Modify(l, r, 1, n, 1, (l - minn) * (l - minn));		
	} else {
		l = idx[v], r = idx[u];
		x2.Modify(l, r, 1, n, 1, 1);
		x1.Modify(l, r, 1, n, 1, -2 * (minn + r));
		x0.Modify(l, r, 1, n, 1, (minn + r) * (minn + r));
	}
}

int Query(int x) {
	return x2.Query(idx[x], 1, n, 1) * x * x + x1.Query(idx[x], 1, n, 1) * x + x0.Query(idx[x], 1, n, 1);
}

signed main()
{
	FAST
	cin >> n;
	for(int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	DFS1(1, 0);
	DFS2(1, 1);
	//cout << "top : "; for(int i = 1; i <= n; i++) cout << top[i] << " "; cout << endl;
	int q;
	cin >> q;
	while(q--) {
		int op, a, b, x;
		cin >> op;
		if(op == 1) {
			cin >> a >> b;
			Modify(a, b); 
		} else {
			cin >> x;
			//cout << "ans : ";
			cout << Query(x) << endl;
		}
	}
	return 0;
}

```



## 1005 I love string

知识点：贪心

除了第一段连续相等的字母序列以外 后面的字母已经决定好位置

我们先设遍历到的字符为ch 已经插入的序列为S[0...n-1] n为序列长度

为了保证字符串的字典序最小 我们有如下贪心策略：

①ch<S[0] 插入到最左端使得新序列的S[0]=ch 字母序一定比ch插入到最右端的新序列小

②ch>S[0]同理 应该插入到最右端

③ch==S[0]且前面已有不相同的字母 根据上述贪心策略 我们插入到最左端 因为上述两种贪心策略 此时我们的字母序一定比ch插入到最右端的新序列小

根据上述贪心策略 我们发现只有前面一段连续相同的字母序列 才能向左端或向右端插入 种类数为$2^k$(k为连续相同的字母序列的长度)

```cpp
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
//#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long

using namespace std;

const int MOD = 1000000007;

int T, n, pow2[100005];
char S[1000005];

signed main()
{
    scanf("%lld", &T);
    pow2[0] = 1;
    for(int i = 1; i <= 100000; i++) pow2[i] = pow2[i - 1] * 2 % MOD;
    while(T--) {
        scanf("%lld", &n);
        scanf("%s", S + 1);
        int k = 1;
        for(int i = 2; i <= n; i++) {
            if(S[i] == S[i - 1]) k++; 
            else break; 
        }
        cout << pow2[k - 1] << endl;
    }
    return 0;
}
```



## 1008 I love exam

知识点：DP

先对m个复习资料按考试科目进行划分 a[i]保存了第i个复习资料的对应考试科目 所需天数和得分

```cpp
#define SCORE 110
struct Node {
    int type, x, y;
}a[MAXM];
```

开两个数组f,g进行转移

定义$g[i][j]$为对于第i个科目 拿到j分所需的最小天数 直接对每个不同的科目进行01背包即可 有

```cpp
for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= SCORE; j++) g[i][j] = INF;
    g[i][0] = 0;
}

for(int i = 1; i <= m; i++) {
    for(int j = SCORE; j >= a[i].x; j--) {
		g[a[i].type][j] = min(g[a[i].type][j], g[a[i].type][j - a[i].x] + a[i].y);
    }
}
```

再定义$f[i][j][k]$为枚举到第i个考试科目 花了j天复习 总共挂了k门的**最大得分**

而我们有如下转移方程
$$
当k=0时,f[i][j][k] = \max_{l >= 60}^{} (f[i - 1][j - g[i][l]][k] + \min(l, 100))\\
当k≠0时,f[i][j][k] = \max(\max(f[i - 1][j][k - 1], f[i - 1][j - g[i][l] ][k - (l < 60)] + \min(l, 100))))
$$
代码如下

```cpp
    for(int i = 1; i <= n; i++) {
        for(int l = 0; l <= SCORE - 10; l++) {
            for(int k = p; k >= 0; k--) {
                for(int j = t; j >= g[i][l]; j--) {
                    if(k == 0) {
                        if(l >= 60) 
                            f[i][j][k] = max(f[i][j][k], f[i - 1][j - g[i][l]][k] + min(l, 100ll));
                        else continue;
                    } else 
                        f[i][j][k] = max(f[i][j][k],
                      	max(f[i - 1][j][k - 1], f[i - 1][j - g[i][l] ][k - (l < 60)] + min(l, 100ll)));
                } 
            }
        }
    }
```

亿点细节：

① g数组中注意到有可能出现大于100分的情况 又看见y<=10这一限制条件 将SCORE设为110以方便进行转移(当然我这边保险起见 将SCORE设成150)

② 多组数据 数组初始化

③ g数组已经滚动了一维 f数组理论上也可以滚动掉一维 注意循环顺序（当然不滚动也行 空间是够的）

```cpp
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
//#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long

using namespace std;

const int MAXN = 55;
const int MAXM = 15005;
const int INF = 0x3f3f3f3f;
const int SCORE = 150;

struct Node {
    int type, x, y;
}a[MAXM];

int n, m, t, p, g[55][155], f[55][505][5];
map<string, int> Map;

bool cmp(Node& a, Node& b) {
    return a.type < b.type;
}

void Solve() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        string S;
        cin >> S;
        Map[S] = i;
    }
    scanf("%d", &m);
    for(int i = 1; i <= m; i++) {
        string S;
        cin >> S;
        a[i].type = Map[S];
        scanf("%d%d", &a[i].x, &a[i].y);    
    }
    scanf("%d%d", &t, &p);
    sort(a + 1, a + 1 + m, cmp);

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= SCORE; j++) g[i][j] = INF;
        g[i][0] = 0;
    }
    for(int i = 1; i <= n; i++) {
        for(int k = 0; k <= p; k++) {
            for(int j = 0; j <= t; j++) {
                f[i][j][k] = -INF;
            }
        }
    }
    f[0][0][0] = 0;

    for(int i = 1; i <= m; i++) {
        for(int j = SCORE; j >= a[i].x; j--) {
            g[a[i].type][j] = min(g[a[i].type][j], g[a[i].type][j - a[i].x] + a[i].y);
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int l = 0; l <= SCORE - 10; l++) {
            for(int k = p; k >= 0; k--) {
                for(int j = t; j >= g[i][l]; j--) {
                    if(k == 0) {
                        if(l >= 60) f[i][j][k] = max(f[i][j][k], f[i - 1][j - g[i][l]][k] + min(l, 100ll));
                        else continue;
                    } else f[i][j][k] = max(f[i][j][k], max(f[i - 1][j][k - 1], f[i - 1][j - g[i][l] ][k - (l < 60)] + min(l, 100ll)));
                } 
            }
        }
    }

    int ans = -1;
    for(int j = 0; j <= t; j++) {
        for(int k = 0; k <= p; k++) ans = max(ans, f[n][j][k]);
    }
    printf("%d\n", ans);
}

signed main()
{
    int T;
    scanf("%d", &T);
    while(T--) {
        Solve();
    }
    return 0;
}

/*
1
3
mathematics physics signals
20
physics 10 1
physics 10 1
physics 10 1
physics 10 1
physics 10 1
physics 10 1
physics 10 1
mathematics 10 1
mathematics 10 1
mathematics 10 1
mathematics 10 1
mathematics 10 1
mathematics 10 1
mathematics 10 1
signals 10 1
signals 10 1
signals 10 1
signals 10 1
signals 10 1
signals 10 2
19 1
*/
```



## 1011 I love max and multiply

知识点：dp

考虑寻找 $D_k=\max{(A_iB_j)}$ 满足$i \& j = k$ 

我们可以设立$maxa[S]$代表a数组中满足$S\&k >= k$的最大$a[S]$

$mina[S]$代表a数组中满足$S\&k >= k$的最小$a[S]$（注意a数组中有负数情况）

有如下表达式
$$
maxa[S] = \max\{ a[i] \ | \ i \& k >= k \}
$$
以此类推 分别在b数组中求出满足条件的$maxb[S], minb[S]$

最后分别相乘找最大值即可

注意此时我们找的是$D_k$ 而题目要求寻找$C_k$ 我们对$D_k$倒着枚举寻找最大值即可

时间复杂度$O(18n)$

```cpp
#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long
#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

using namespace std;

const int MAXN = (1 << 20) + 5;
const int INF = 0x3f3f3f3f;
const int LONG_INF = (int)2e18;
const int MOD = 998244353;

int n, a[MAXN], b[MAXN], maxa[MAXN], maxb[MAXN], mina[MAXN], minb[MAXN], ans[MAXN];

void Solve() {
	cin >> n;
	for(int i = 0; i < n; i++) {
		cin >> a[i];
		maxa[i] = a[i];
		mina[i] = a[i];
	} 
	for(int i = 0; i < n; i++) {
		cin >> b[i];
		maxb[i] = b[i];
		minb[i] = b[i];
	}
	
	int m = 0, cur = 1;
	while(cur < n) m++, cur <<= 1; 
	
	for(int i = n; i <= (1 << m); i++) {
		maxa[i] = maxb[i] = -INF;
		mina[i] = minb[i] = INF;
	}
	
	//for(int i = 0; i <= (1 << m); i++) cout << mina[i] << " "; cout << endl;
	
	for(int i = (1 << m) - 1; i >= 0; i--) {
		for(int j = 1; j < (1 << m); j <<= 1) {
        	if(!(i & j)) {
				maxa[i] = max(maxa[i], maxa[i ^ j]);
				maxb[i] = max(maxb[i], maxb[i ^ j]);
				mina[i] = min(mina[i], mina[i ^ j]);
				minb[i] = min(minb[i], minb[i ^ j]);
			}
		}
	}
	
	ans[n] = -LONG_INF;
	for(int i = n - 1; i >= 0; i--) {
		ans[i] = -LONG_INF;
		if(maxa[i] != -INF && maxb[i] != -INF) ans[i] = max(ans[i], maxa[i] * maxb[i]);
		if(maxa[i] != -INF && minb[i] != INF) ans[i] = max(ans[i], maxa[i] * minb[i]);
		if(mina[i] != INF && maxb[i] != -INF) ans[i] = max(ans[i], mina[i] * maxb[i]);
		if(mina[i] != INF && minb[i] != INF) ans[i] = max(ans[i], mina[i] * minb[i]);
		//ans[i] = max( max(maxa[i] * maxb[i], mina[i] * minb[i]), max(maxa[i] * minb[i], mina[i] * maxb[i]) );
		ans[i] = max(ans[i], ans[i + 1]);
	}
	int sum = 0;
	for(int i = 0; i < n; i++) sum = (sum + ans[i]) % MOD;
	cout << (sum + 114514 * MOD) % MOD << endl;
	
	return ;
}

signed main()
{
	FAST
	int T;
	cin >> T;
	while(T--) {
		Solve();
	}
	return 0;
}

```



## 1012 I love 114514

知识点：签到 ~~KMP~~

暴力匹配即可 当然也可以用KMP,扩展KMP等方法匹配

```cpp
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
//#define FAST ios::sync_with_stdio(false); cin.tie(0);
//#define int long long

using namespace std;

int T;
char S[1000005];

signed main()
{
    scanf("%d", &T);
    while(T--) {
        scanf("%s", S + 1);
        int len = strlen(S + 1);
        bool flag = 0;
        for(int i = 6; i <= len; i++) {
            if(S[i - 5] == '1' && S[i - 4] == '1' && S[i - 3] == '4' && S[i - 2] == '5' && S[i - 1] == '1' && S[i] == '4') {
                cout << "AAAAAA\n";
                flag = 1;
            }
        }
        if(!flag) {
            cout << "Abuchulaile\n";
        }
    }
    return 0;
}
```

