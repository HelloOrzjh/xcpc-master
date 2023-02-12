# hdu 2021“MINIEYE杯”中国大学生算法设计超级联赛（1）部分题题解

## 1001 Mod, Or and Everything

知识点：找规律

按二进制数位的角度考虑 

如果n=2^k（k为整数） 则除最高**两**位的其他数位都能取到1

反之 除最高位的其他数位都能取到1

（不会证明orz 赛场上通过手推样例加上模数小于ceil(n/2)的特性**感性理解**）

```C++
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long

using namespace std;

int pow2[100], T, n;

int Solve(int x) {
    int res = 0;
    while(x > 0) {
        res++;
        x >>= 1;
    }
    //cout << res << endl;
    return res;
}

signed main()
{
    FAST
    int T;
    cin >> T;
    pow2[0] = 1;
    for(int i = 1; i <= 1e12; i++) {    
        if(pow2[i - 1] > 1e12) break;
        pow2[i] = pow2[i - 1] << 1;
    }
    while(T--) {
        cin >> n;
        if(n == 1) cout << 0 << endl;
        else {
            cout << pow2[Solve(n - 1) - 1] - 1 << endl;
        }
    }
    return 0;
}
```



## 1005 Minimum spanning tree

知识点：贪心，素数筛

设f[n]为有n个点的最小生成树 

对于有n-1个点的最小生成树 加入点n 可以分两种情况讨论

①n是质数 我们就连一条点2到点n的边 增加的权值为lcm(2,n) = 2n 易得此时增加的权值最小

②n是合数 前面n-1个点肯定有n的因子 设其为k 我们则连点k到点n的边 增加的权值为lcm(k,n) = n 易得此时增加的权值最小

综上 我们先进行一波1e7以内的质数筛 然后求出f数组 O(1)查询即可

代码如下

```C++
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long

using namespace std;

const int MAXN = (int)10000000 + 5;

int n, f[MAXN], isprime[MAXN], prime[MAXN], ans[MAXN];

void Init() {
    int cnt = 0;
    isprime[1] = 1;
    for(int i = 2; i <= MAXN - 5; i++) {
        if(!isprime[i]) {
            prime[++cnt] = i;
            ans[i] = 1;
        }
        for(int j = 1; j <= cnt && i * prime[j] <= MAXN - 5; j++) {
            isprime[i * prime[j]] = 1;
            if(i % prime[j] == 0) break;
        }
    }
    //for(int i = 1; i <= 10; i++) cout << ans[i] << " "; cout << endl;
}

signed main()
{
    FAST
    Init();
    f[2] = 0;
    f[3] = 2 * 3;
    for(int i = 4; i <= MAXN - 5; i++) {
        int cur;
        if(!ans[i]) cur = i;
        else cur = 2 * i;
        f[i] = f[i - 1] + cur;
    }
    //for(int i = 1; i <= 10; i++) cout << f[i] << " "; cout << endl;;
    int T;
    cin >> T;
    while(T--) {
        cin >> n;
        cout << f[n] << endl;
    }
    return 0;
}

```



## 1006 Xor sum

知识点：前缀和 trie

首先先进行异或前缀和 题意转化为找两个相邻最小的数 使得其异或和不小于k

枚举较右边的数 同时维护一个trie树以得到较左边合法的数

如何维护？ 

首先我们定义maxl[u]定义一个节点的最大合法左端点

以样例第二组数据为例

异或前缀和（二进制）为

```
011 010 001 011 111 111 100 001 000
```

设枚举到第6位时 trie树如图所示

![](https://cdn.luogu.com.cn/upload/image_hosting/rx2bm876.png)

括号内为节点的maxl

当枚举到第6位时 我们根据数位从高到低跳一波trie 

![](https://cdn.luogu.com.cn/upload/image_hosting/zd69ws8m.png)

注意一下数组的初始化

```C++
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
//#define FAST ios::sync_with_stdio(false); cin.tie(0);
//#define int long long

using namespace std;

const int MAXN = (int)1e5 + 5;

int T, n, k, a[MAXN], sum[MAXN], trie[MAXN * 30][2], maxl[MAXN * 30], cnt;

signed main()
{
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &k);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			sum[i] = sum[i - 1] ^ a[i];
		}
		//for(int i = 1; i <= n; i++) printf("%d ", sum[i]); printf("\n");
		int l = -1, r = n;
		cnt = 1;
		//memset(trie, 0, sizeof(trie));
		//memset(maxr, -1, sizeof(maxr));
		trie[1][0] = trie[1][1] = 0;
		maxl[1] = -1;
		for(int i = 1; i <= n; i++) {
			int u = 1, cur = -1;
			for(int j = 29; j >= 0; j--) {
				int d = (sum[i] >> j) & 1;
				if(! ((k >> j) & 1) ) {
					if(trie[u][d ^ 1]) cur = max(cur, maxl[ trie[u][d ^ 1] ]);
					u = trie[u][d];
				} else {
					u = trie[u][d ^ 1];
				}
				
				if(u == 0) break;
			}
			
			if(u) cur = max(cur, maxl[u]);
			if(i - cur + 1 < r - l + 1 && cur > 0) {
				l = cur;
				r = i;
			}
			
			u = 1;
			for(int j = 29; j >= 0; j--) {
				int d = (sum[i] >> j) & 1;
				if(!trie[u][d]) {
					trie[u][d] = ++cnt;
					maxl[cnt] = -1;
					trie[cnt][0] = trie[cnt][1] = 0;
				}
				u = trie[u][d];
				maxl[u] = max(maxl[u], i);
			}
		}
		
		if(l > 0) printf("%d %d\n", l + 1, r);
		else printf("-1\n");
	}
	return 0;
}

```



## 1008 Maximal submatrix

知识点：差分 DP（悬线法）

（悬线法基本可以直接套模板）

对每一列做差分 差分数组的正数化为1 负数化为0 问题转化为求最大全1子矩阵

百度自行搜索悬线法（注意计算子矩阵大小时悬线的高度(h数组)需要+1）

```C++
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
//#define FAST ios::sync_with_stdio(false); cin.tie(0);
//#define int long long
#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

using namespace std;

const int MAXN = (int)2e3 + 5;

int T, n, m;
int l[MAXN], r[MAXN], h[MAXN], a[2][MAXN];
bool Map[MAXN][MAXN];

signed main()
{
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        
        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= m; j++) {
                Map[i][j] = 0;    
            }
        }
        for(int i = 1; i <= m; i++) a[0][i] = 0;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                scanf("%d", &a[1][j]);
                //Map[i][j] = 0;
            }
            for(int j = 1; j <= m; j++) {
                if(a[1][j] >= a[0][j]) Map[i][j] = 1;
                else Map[i][j] = 0;
                
                a[0][j] = a[1][j];
            }
        }
        /*
        for(int i = 2; i <= n; i++) {
            for(int j = 1; j <= m; j++) cout << Map[i][j] << " "; cout << endl;
        }
        */
        for(int i = 1; i <= m; i++) {
            l[i] = 1, r[i] = m, h[i] = 0;
        }
        int ans = m;
        for(int i = 2; i <= n; i++) {
            for(int lmax = 1, j = 1; j <= m; j++) {
                if(Map[i][j]) {
                    h[j]++;
                    if(lmax > l[j]) l[j] = lmax;
                } else {
                    h[j] = 0, l[j] = 1, r[j] = m, lmax = j + 1;
                }
            }
            for(int rmax = m, j = m; j; j--) {
                if(Map[i][j]) {
                    if(rmax < r[j]) r[j] = rmax;
                    if((r[j] - l[j] + 1) * (h[j] + 1) > ans) ans = (r[j] - l[j] + 1) * (h[j] + 1);
                } else {
                    rmax = j - 1;
                }
            }
        }
        
        printf("%d\n", ans);
    }
    return 0;
}

/*
1
6 7
12 12 1 1 12 12 12
11 11 2 2 11 11 11
10 10 3 3 10 10 10
7 7 4 4 7 7 7
8 8 5 5 8 8 8
9 9 6 6 9 9 9
*/
```



## 1009 KD-Graph

知识点：并查集

```
if vertices p and q ( p ≠ q ) are in the same group, there must be at least one path between p and q meet the max value in this path is less than or equal to D.
```

意思是

```
如果点p和q在同一个集合 则有一条从p到q的路径 [这条路径上的最大值]小于等于[D]
```

我们就可以通过将边按权值从小到大排序 每一阶段取出同权值的所有边加入这个图 利用并查集维护连通块数量

若某一阶段加入完边之后 连通块数量为k 则直接输出这个阶段边的权值

如果不能合并到**刚好**k个连通块 则输出-1

需要注意如果n==k 那我们就不需要连边 直接输出0即可

证明？感性理解orz（赛场上我通过推导样例得出 题解中利用反证法）



```C++
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
//#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long

using namespace std;

const int MAXN = (int)1e5 + 5;
const int MAXM = (int)5e5 + 5;

int f[MAXN], n, m, k;

struct Edge {
	int u, v, w;
}a[MAXM];

bool cmp(Edge &a, Edge &b) {
	return a.w < b.w;
}

int find(int x) {
	if(x == f[x]) return x;
	else return f[x] = find(f[x]);
}

signed main()
{
	//freopen("1.in", "r", stdin);
	int T;
	scanf("%lld", &T);
	while(T--) {
		scanf("%lld%lld%lld", &n, &m, &k);
		for(int i = 1; i <= m; i++) {
			scanf("%lld%lld%lld", &a[i].u, &a[i].v, &a[i].w);
		}
		sort(a + 1, a + 1 + m, cmp);
		for(int i = 1; i <= n; i++) f[i] = i;
		int p = 1; 
		int curk = n, cur = 0;
		if(k == n) {
			printf("0\n");
			continue;
		}
		while(p <= m) {
			cur = a[p].w;
			while(a[p].w == cur && p <= m) {
				if(find(a[p].u) != find(a[p].v)) {
					curk--;
					f[find(a[p].u)] = find(a[p].v);
					f[find(a[p].v)] = find(a[p].u);			
				}
				p++;
			}
			//cout << p << endl;
			if(curk <= k) break;
		}
		if(curk == k) {
			printf("%lld\n", cur);
		} else {
			printf("-1\n");
		}
	}
	return 0;
}

/*
1
7 6 5
1 2 1
1 3 1
1 4 2
1 5 2
1 6 5
1 7 6
*/

```

