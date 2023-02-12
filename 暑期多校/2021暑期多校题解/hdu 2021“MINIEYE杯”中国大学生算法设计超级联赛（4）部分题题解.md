# hdu 2021“MINIEYE杯”中国大学生算法设计超级联赛（4）部分题题解

## 1001 Calculus

知识点：高数

给定函数集的和函数都发散 所以判断是否出现常数因子不为0的情况

（不会真有人看错题目写了个模拟吧 哦原来是我啊 那没事了）

```cpp
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
//#define int long long
#define p make_pair

using namespace std;

const int MAXN = 105;

pair<int, int> ans[MAXN];
int n, cnt;
char S[MAXN];

bool JudgeSin(int i) {
    if(i + 3 >= n) return false;
    if(S[i] == 's' && S[i + 1] == 'i' && S[i + 2] == 'n' && S[i + 3] == 'x') return true; 
    return false;
}

bool JudgeCos(int i) {
    if(i + 3 >= n) return false;
    if(S[i] == 'c' && S[i + 1] == 'o' && S[i + 2] == 's' && S[i + 3] == 'x') return true; 
    return false;    
}
 
void Solve() {
    cin >> S;
    n = strlen(S);
    cnt = 0;
    int num = 0, op = 0;
    for(int i = 0; i < n; ) {
        if(S[i] == '+') {
            ans[++cnt] = p(num, op);
            num = 0;
            op = -1;
            i++;
        } else if(S[i] >= '0' && S[i] <= '9') {
            num = num * 10 + S[i] - '0';
            i++;
        } else {
            if(S[i] == '^') {
                op = 7;    
                i++;
                i++;
            } else if(S[i] == '/') {
                i++;
                if(JudgeSin(i)) {
                    op = 4;
                    i += 4;
                } else if(JudgeCos(i)) {
                    op = 5;
                    i += 4;
                } else if(S[i] == 'x') {
                    op = 1;
                    i++;
                }
            } else {
                if(JudgeSin(i)) {
                    op = 2;
                    i += 4;
                } else if(JudgeCos(i)) {
                    op = 3;
                    i += 4;
                } else if(S[i] == 'x') {
                    op = 6;
                    i++;
                }
            }
        }
    }
    ans[++cnt] = p(num, op);
    num = 0;
    op = 0;
    
    bool flag = 1;
    for(int i = 1; i <= cnt; i++) {
        //cout << ans[i].first << " " << ans[i].second << endl;
        int cur1 = ans[i].first, cur2 = ans[i].second;
        if(cur1 > 0) flag = 0;
    }
    if(flag) cout << "YES\n";
    else cout << "NO\n";
}

signed main()
{
    //FAST
    int T;
    cin >> T;
    while(T--) {
        Solve(); 
    }
    return 0;
}
```



## 1002 Kanade Loves Maze Designing

知识点：DFS

以n个节点为根搜索整棵树 用num数组存每个数字出现的数量 cnt记录出现了多少种数字 深搜即可

```cpp
#pragma GCC optimize(2)

#include<bits/stdc++.h>
//#define FAST ios::sync_with_stdio(false); cin.tie(0);
//#define int long long
#define pir make_pair
#define pii pair<int, int>
#define reg register

using namespace std;

const int MAXN = (int)2005;

vector<int> G[MAXN];
//vector<pii> T[MAXN];
int n, vis[MAXN], num[MAXN], c[MAXN], p[MAXN], a[MAXN][MAXN];

void DFS(int u, int root, int cnt) {
    int sze = G[u].size();
    for(reg int i = 0; i < sze; ++i) {
        int v = G[u][i];
        if(vis[v]) continue;
        
        vis[v] = 1;
        if(num[c[v]] == 0) ++cnt;
        ++num[c[v]];
        a[root][v] = a[v][root] = cnt;
        DFS(v, root, cnt);
        vis[v] = 0;
        --num[c[v]];
        if(num[c[v]] == 0) --cnt;
    }
    
}

inline void Solve() {
    //cin >> n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) G[i].clear();
    
    for(reg int i = 2; i <= n; ++i) {
        //cin >> p[i];
        scanf("%d", &p[i]);
        G[i].push_back(p[i]);
        G[p[i]].push_back(i);
    }
    
    for(reg int i = 1; i <= n; ++i) {
        scanf("%d", &c[i]);    
    }
    
    for(reg int i = 1; i <= n; ++i) num[i] = vis[i] = 0;
    for(reg int i = 1; i <= n; ++i) {
        a[i][i] = 1;
        ++num[c[i]];
        vis[i] = 1;
        DFS(i, i, 1);
        vis[i] = 0;
        --num[c[i]];        
    }
    
    
    for(reg int i = 1; i <= n; ++i) {
        int MOD1 = (int)1e9 + 7;
        int MOD2 = (int)1e9 + 9;
        int d = 19560929;
        long long cur1 = 1, cur2 = 1;
        long long ans1 = 0, ans2 = 0;
        for(reg int j = 1; j <= n; ++j) {
            //cout << a[i][j] << " ";
            ans1 = (ans1 + a[i][j] * cur1) % MOD1;
            ans2 = (ans2 + a[i][j] * cur2) % MOD2;
            cur1 = (cur1 * d) % MOD1;
            cur2 = (cur2 * d) % MOD2;
        }
        printf("%d %d\n", ans1, ans2);
        //cout << ans1 << " " << ans2 << endl;
        //cout << endl;
    }
    
    
}

signed main()
{
    //FAST
    int T;
    scanf("%d", &T);
    while(T--) {
        Solve();
    }
    return 0;
}
```



## 1008 Lawn of the Dead

知识点：模拟，~~乱搞~~

看到n的数据范围 我们肯定不能直接枚举格子了

考虑按区间来计算贡献 我们可以对每一行的可走区间存起来

考虑上一行的可行区间怎么推到下一行

容易发现：只要上一行区间与当前区间有交集 那么当前区间就可以通过上一行区间来访问

通过上一行区间和当前区间的交集更新左端点 右端点还是当前区间的右端点 将这段区间存起来 以进行下一行的判断

更新左端点的话我是暴力更新  按顺序找到第一个合法的左端点 (~~hdu的数据太弱被我卡过去了~~)

```cpp
#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long
#define pir make_pair
#define pii pair<int, int>
#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)

using namespace std;

const int MAXN = (int)1e5 + 5;
const int INF = 0x3f3f3f3f;

struct Node {
    int x, y;
}a[MAXN];

int n, m, k;
vector<int> G[MAXN];
vector<pii> S, cur;

bool Judge(pii a,int l,int r) {
    if(a.first <= l) return a.second >= l;
    else if(a.first <= r) return true;
    return false;
}

int Query(int l, int r) {
    int res = INF;
    int now = l;
    
    for(int i = 0; i < S.size(); i++) {
        if(Judge(S[i], l, r)) {
            now = max(now, S[i].first);
            res = min(res, now);
            break;
        }
    }
    
    return res;
}

void Solve() {
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++) G[i].clear();
    for(int i = 1; i <= k; i++) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
    }
    for(int i = 1; i <= n; i++) G[i].push_back(m + 1), sort(G[i].begin(), G[i].end());
    S.clear();
    S.push_back(pir(1, G[1][0] - 1));
    
    int ans = G[1][0] - 1;
    for(int i = 2; i <= n; i++) {
        int l = 1;
        cur.clear();
        for(int j = 0; j < G[i].size(); j++) {
            int r = G[i][j];
            if(l >= r) {
                l = r + 1;
                continue;
            }
            l = Query(l, r - 1);
            if(l == INF) {
                l = r + 1;
                continue;
            }
            cur.push_back(pir(l, r - 1));
            ans += (r - l);
            l = r + 1;
        }
        S = cur;
        //cout << ans << "qwq\n";
    }
    
    cout << ans << "\n"; 
}

signed main()
{
    int T;
    cin >> T;
    while(T--) {
        Solve();
    }
    return 0;
}

/*
1
4 4 4
1 3
3 4
3 2
4 3
*/
```



## 1009 License Plate Recognition

知识点：模拟

注意到汉字不连通 难以求左右边界

又注意到车牌汉字只有一个且在最左边 

又注意到数字和字母都是连通的

我们可以先自右往左地枚举连通块 并存储连通块的左右边界 

因为数字和字母共有6个 所以前6个连通块的左右边界即车牌号后6个字符的左右边界

剩下的即为汉字边界 直接在连通块中找最小左端点和最大右端点合并即可

```cpp
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
//#define int long long

using namespace std;

pair<int, int> ans[114];
char ch[35][105];

void Solve() {
	for(int i = 1; i <= 30; i++) {
		for(int j = 1; j <= 100; j++) {
			ch[i][j] = getchar();
		}
		getchar();
	}
	int l = 0, r = 0, cnt = 0;
	for(int j = 100; j >= 1; j--) {
		bool flag = false;
		for(int i = 1; i <= 30; i++) {
			if(ch[i][j] == '#') {
				flag = true;
				break;
			}
		}
		if(flag) {
			if(r == 0) r = j;
			else l = j;
		} else {
			if(l && r) {
				ans[++cnt] = make_pair(l, r);
				l = r = 0;
			}
		}
	}
	
	if(cnt > 7) {
		ans[7] = make_pair(ans[cnt].first, ans[7].second);
	}
	
	for(int i = 7; i >= 1; i--) {
		printf("%d %d\n", ans[i].first, ans[i].second);
	}
}

signed main()
{
	signed T;
	scanf("%d", &T);
	getchar();
	for(int c = 1; c <= T; c++) {	
		printf("Case #%d:\n", c);
		Solve();
	}
	return 0;
}

```

