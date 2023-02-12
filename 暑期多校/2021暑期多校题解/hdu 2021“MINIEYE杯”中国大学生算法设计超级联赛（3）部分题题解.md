# hdu 2021“MINIEYE杯”中国大学生算法设计超级联赛（3）部分题题解

## 1007 Photoshop Layers

知识点：线段树 前缀和

前缀和其实可做的 而且思路并不难 但我用了线段树（~~还吃了两发T~~）

前缀和大概就是对于每一个i 记录前一个操作1出现的位置 询问时分情况讨论即可

线段树维护RGB的值，flag表示这个节点是否出现操作1

合并节点时先判断右儿子flag是否为1 是的话直接让节点等于右儿子 否则让节点等于左右儿子的和

然后通过左右儿子的flag更新节点的flag

线段树时间复杂度$O(nlogn)$ 用了各种优化降常数 成功卡过hdu的评测机(~~包括但不限于氧气优化，快读，寄存器变量，内联函数~~)

![](C:\Users\28459\Desktop\暑期题解\pic\segmentTree.png)

```cpp
#pragma GCC optimize(2)

#include<bits/stdc++.h>
//#define FAST ios::sync_with_stdio(false); cin.tie(0);
//#define int long long
#define min(a, b) (a < b ? a : b)

using namespace std;

const int MAXN = 1e5 + 5;

struct Node {
    int r, g, b, op;
}a[MAXN];

struct Tree {
    int r, g, b, flag;
}tree[MAXN << 2];

int n, m;

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

inline int Hash(char x) {
    if(x >= '0' && x <= '9') return x - '0';
    else return x - 'A' + 10;
}

inline char Hash2(int x) {
    if(x >= 0 && x <= 9) return x + '0';
    else return x - 10 + 'A';    
}

inline int ls(int x) {
    return x << 1;
} 

inline int rs(int x) {
    return x << 1 | 1;
}

inline Tree PushUp(Tree L, Tree R) {
    Tree cur;
    if(R.flag) {
        cur.r = R.r;
        cur.g = R.g;
        cur.b = R.b;
        cur.flag = R.flag;
        return cur;
    } else if(L.flag) {
        cur.flag = L.flag;
        cur.r = min(L.r + R.r, 255);
        cur.g = min(L.g + R.g, 255);
        cur.b = min(L.b + R.b, 255);
        return cur;
    } else {
        cur.flag = 0;
        cur.r = min(L.r + R.r, 255);
        cur.g = min(L.g + R.g, 255);
        cur.b = min(L.b + R.b, 255);
        return cur;        
    }
}

void Build(int l, int r, int p) {
    if(l == r) {
        tree[p].r = a[l].r;
        tree[p].g = a[l].g;
        tree[p].b = a[l].b;
        if(a[l].op == 1) tree[p].flag = l;
        else tree[p].flag = 0;
        return ;
    } 
    int mid = (l + r) >> 1;
    Build(l, mid, ls(p));
    Build(mid + 1, r, rs(p));
    tree[p] = PushUp(tree[ls(p)], tree[rs(p)]);
    return ;
}

Tree Query(int nl, int nr, int l, int r, int p) {
    if(nl <= l && nr >= r) {
        return tree[p];
    } 
    
    int mid = (l + r) >> 1;
    
    if(nr <= mid && nl <= mid) {
        return Query(nl, nr, l, mid, ls(p));
    } else if(nl > mid && nr > mid) {
        return Query(nl, nr, mid + 1, r, rs(p));
    } else {
        return PushUp(Query(nl, nr, l, mid, ls(p)), Query(nl, nr, mid + 1, r, rs(p)));
    }
}

inline void Solve() {
    n = read();
    m = read();
    //cin >> n >> m;
    char T[10]; 
    for(register int i = 1; i <= n; ++i) {
        a[i].op = read();
        gets(T);
        //cin >> a[i].op >> T;
        a[i].r = Hash(T[0]) * 16 + Hash(T[1]);
        a[i].g = Hash(T[2]) * 16 + Hash(T[3]);
        a[i].b = Hash(T[4]) * 16 + Hash(T[5]);
    }
    Build(1, n, 1);
    while(m--) {
        int l, r;
        l = read();
        r = read();
        //cin >> l >> r;
        Tree cur = Query(l, r, 1, n, 1);
        cur.r = min(cur.r, 255);
        cur.g = min(cur.g, 255);
        cur.b = min(cur.b, 255);
        putchar(Hash2(cur.r >> 4)); putchar(Hash2(cur.r % 16));
        putchar(Hash2(cur.g >> 4)); putchar(Hash2(cur.g % 16));
        putchar(Hash2(cur.b >> 4)); putchar(Hash2(cur.b % 16));
        putchar('\n');
        
        /*
        cout << Hash2(cur.r / 16) << Hash2(cur.r % 16);
        cout << Hash2(cur.g / 16) << Hash2(cur.g % 16);
        cout << Hash2(cur.b / 16) << Hash2(cur.b % 16);
        cout << endl;    
        */
    }
}

signed main()
{
    //FAST
    int T;
    //cin >> T;
    T = read();
    while(T--) {
        Solve();
    }
    return 0;
}
```



## 1009 Rise in Price

知识点：DP 决策优化

设$f[i][j][k]$表示走到$(i,j)$时收集了k个钻石所能达到的最大单价

有
$$
f[i][j][k] = max(f[i - 1][j][k - a[i][j]] + b[i][j], f[i][j - 1][k - a[i][j]] + b[i][j])
$$
结果为$max(f[n][n][k] * k)$

观察$f[i][j][k]$ 注意到k的值由$(i - 1, j)$和$(i, j - 1)$的状态合并而来 不同的k最多有$n^2$个

而且如果有$x<y且f[i][j][x] < f[i][j][y]$,则$f[i][j][x]$必然不会成为最优解 可以直接剔去

利用vector来存$k$和$f[i][j][k]$ 暴力枚举合并

时间复杂度为$O(n^2k)$ 其中k最多为几千

```cpp
#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long
#define pii pair<int, int>

using namespace std;

const int MAXN = 105;

int n, a[MAXN][MAXN], b[MAXN][MAXN], vis1[MAXN], vis2[MAXN];
vector<pii> f[MAXN][MAXN];

void Merge(int x, int y) {
	int len1 = f[x - 1][y].size();
	int len2 = f[x][y - 1].size();
	/*
	for(int i = 0; i < len1; i++) vis1[i] = 0;
	for(int i = 0; i < len2; i++) vis2[i] = 0;
	
	for(int i = 0; i < len1; i++) {
		for(int j = 0; j < len2; j++) {
			int x1 = f[x - 1][y][i].first, x2 = f[x - 1][y][i].second;
			int y1 = f[x][y - 1][j].first, y2 = f[x][y - 1][j].second;
			if(x1 <= y1 && x2 <= y2) {
				vis1[i] = 1;
			}
		}
	}
	
	for(int j = 0; j < len2; j++) {
		for(int i = 0; i < len1; i++) {
			if(vis1[i]) continue;
			int x1 = f[x - 1][y][i].first, x2 = f[x - 1][y][i].second;
			int y1 = f[x][y - 1][j].first, y2 = f[x][y - 1][j].second;			
			if(x1 >= y1 && x2 >= y2) {
				vis2[j] = 1;
			}
		}
	}	
	*/
	int p1 = 0, p2 = 0;
	while(p1 < len1 && p2 < len2) {
		//while(vis1[p1]) p1++;
		//while(vis2[p2]) p2++;
		if(f[x - 1][y][p1].first < f[x][y - 1][p2].first) {
			if(f[x - 1][y][p1].second > f[x][y - 1][p2].second) f[x][y].push_back(f[x - 1][y][p1]);
			p1++;
		} else if(f[x - 1][y][p1].first > f[x][y - 1][p2].first) {
			if(f[x - 1][y][p1].second < f[x][y - 1][p2].second) f[x][y].push_back(f[x][y - 1][p2]);
			p2++;
		} else if(f[x - 1][y][p1].first == f[x][y - 1][p2].first) {
			if(f[x - 1][y][p1].second >= f[x][y - 1][p2].second) f[x][y].push_back(f[x - 1][y][p1]);
			else f[x][y].push_back(f[x][y - 1][p2]);
			p1++, p2++;
		}
	}
	while(p1 < len1) {
		//while(vis1[p1]) p1++;
		f[x][y].push_back(f[x - 1][y][p1]);
		p1++;
	}
	while(p2 < len2) {
		//while(vis2[p2]) p2++;
		f[x][y].push_back(f[x][y - 1][p2]);
		p2++;
	}
	
	for(int i = 0; i < f[x][y].size(); i++) {
		f[x][y][i].first += a[x][y];
		f[x][y][i].second += b[x][y];
	}
}

void Solve() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
	} 
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cin >> b[i][j];
		}
	}
	
	for(int i = 0; i <= n; i++) {
		for(int j = 0; j <= n; j++) {
			f[i][j].clear();
		}
	}
	
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if(i == 1 && j == 1) {
				f[i][j].push_back(make_pair(a[i][j], b[i][j]));
			} else if(i == 1) {
				//f[i][j] = f[i][j - 1];
				for(int k = 0; k < f[i][j - 1].size(); k++) {
					f[i][j].push_back(f[i][j - 1][k]);
				}
				for(int k = 0; k < f[i][j].size(); k++) {
					f[i][j][k].first += a[i][j];
					f[i][j][k].second += b[i][j];
				}				
			} else if(j == 1) {
				//f[i][j] = f[i - 1][j];
				for(int k = 0; k < f[i - 1][j].size(); k++) {
					f[i][j].push_back(f[i - 1][j][k]);
				}				
				for(int k = 0; k < f[i][j].size(); k++) {
					f[i][j][k].first += a[i][j];
					f[i][j][k].second += b[i][j];
				}				
			} else {
				Merge(i, j);
			}
		}
	}
	
	int ans = 0;
	for(int i = 0; i < f[n][n].size(); i++) {
		//cout << f[n][n][i].first << " ";
		ans = max(ans, f[n][n][i].first * f[n][n][i].second);
	}
	cout << ans << endl;
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



## 1010 Road Discount

知识点：最小生成树

相关题目：hdu4253 Two Famous Companies



```cpp
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long
#define pii pair<int, int>

using namespace std;

const int MAXN = 1005;
const int MAXM = (int)2e5 + 5;

struct Edge {
    int u, v, w;
}a[MAXM], b[MAXM];

pii tree[2005];
int n, m, f[MAXN];

int find(int x) {
    return x == f[x] ? x : (f[x] = find(f[x]));
}

void Add(int u, int v, int w, Edge &cur) {
    cur.u = u;
    cur.v = v;
    cur.w = w;
}

bool cmp(Edge &a, Edge &b) {
    return a.w < b.w;
}

void Kruskal(Edge* e) {
    sort(e + 1, e + 1 + m, cmp);
    for(int i = 1; i <= n; i++) f[i] = i;
    int cnt = 0;
    
    for(int i = 1; i <= m; i++) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        if(find(u) == find(v)) {
            
        } else {
            e[++cnt] = e[i];
            f[find(u)] = find(v);
            f[find(v)] = find(u);
        }
    }
    return ;
}

pii Query(int x) {
    int cnt = 0, sum = 0;
    int pa = 1, pb = 1;
    
    for(int i = 1; i <= n; i++) f[i] = i;
    
    while(pa < n && pb < n) {
        if(a[pa].w <= b[pb].w + x) {
            int u = a[pa].u, v = a[pa].v, w = a[pa].w;
            if(find(u) == find(v)) {
                
            } else {
                f[find(u)] = find(v);
                f[find(v)] = find(u);
                sum += w;
            }
            pa++;
        } else {
            int u = b[pb].u, v = b[pb].v, w = b[pb].w;
            if(find(u) == find(v)) {
                
            } else {
                f[find(u)] = find(v);
                f[find(v)] = find(u);
                sum += w + x;
                cnt++;                
            }
            pb++;
        }
    }
    
    while(pa < n) {
        int u = a[pa].u, v = a[pa].v, w = a[pa].w;
        if(find(u) == find(v)) {
            
        } else {
            sum += w;
        }
        pa++;
    }
    
    while(pb < n) {
        int u = b[pb].u, v = b[pb].v, w = b[pb].w;
        if(find(u) == find(v)) {
            
        } else {
            cnt++;
            sum += w + x;
        }
        pb++;
    }
    
    return make_pair(cnt, sum);
}

int Answer(int k) {
    int l = 0, r = 1000;
    while(r > l) {
        int mid = (l + r - 1) >> 1;
        if(tree[mid].first > k) {
            l = mid + 1;
        } else {
            r = mid; 
        }
    }
    return tree[l].second - k * l;
}

void Solve() {
    cin >> n >> m;
        
    for(int i = 1; i <= m; i++) {
        int u, v, c, d;
        cin >> u >> v >> c >> d;
        Add(u, v, c, a[i]);
        Add(u, v, d, b[i]);
    }
    Kruskal(a);
    Kruskal(b);
    sort(a + 1, a + n, cmp);
    sort(b + 1, b + n, cmp);
    
    for(int i = 0; i <= 1000; i++) {
        tree[i] = Query(i);
    }
    
    for(int k = 0; k < n; k++) cout << Answer(k) << endl;
    
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



## 1011 Segment Tree with Pruning

知识点：线段树的概念 ~~记忆化搜索~~

从线段树的区间长度（设其为n）考虑

①n为偶数 分成两个$\frac{n}{2}$的区间

②n为奇数 分成两个长度分别为$\frac{n-1}{2}$和$\frac{n+1}{2}$的区间

从记忆化搜索的角度来考虑 设答案为$f[n]$ 有$f[n] = 2 * f[\frac{n}{2}] + 1$或$f[n] = f[\frac{n-1}{2}]+f[\frac{n+1}{2}] + 1$

注意到n过大 且线段树节点中相同长度的区间有很多 不同长度的区间大概有$\log{n}$个

我们用个Map或Hash表来表示映射关系 直接进行记忆化搜索即可

时间复杂度大概是$O(\log{n})$

```cpp
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int __int128

using namespace std;

int T, n, k;
map<int, int> Map;

inline __int128 read() {
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

int DFS(int x) {
    //cout << x << "\n";
    if(Map[x] != 0) return Map[x];
    if(x <= k) return Map[x] = 1;
    int l, r;
    if(x % 2 == 0) l = r = x / 2;
    else l = (x - 1) / 2, r = (x + 1) / 2;
    return Map[x] = DFS(l) + DFS(r) + 1;
}

signed main()
{
    T = read();
    //cin >> T;
    while(T--) {
        Map.clear();
        n = read();
        k = read();
        write(DFS(n));
        cout << endl;
        //cin >> n >> k;
        //cout << DFS(n) << endl;
    }
    return 0;
}
```

