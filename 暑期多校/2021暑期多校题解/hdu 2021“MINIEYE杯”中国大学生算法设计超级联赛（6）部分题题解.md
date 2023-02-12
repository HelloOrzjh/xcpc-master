# hdu 2021“MINIEYE杯”中国大学生算法设计超级联赛（6）部分题题解

## 1001 Yes, Prime Minister

知识点：贪心

容易发现最后质数最多有两个**正数**组成

考虑答案的形式为$l,l+1,l+2...$的总和 共有n项

那么答案为$nl + \frac{n(n-1)}{2}$

提取系数求最大公约数$gcd(n, \frac{n(n-1)}{2})$ 

易得当$n>2$时 gcd不为1

又可以通过打质数表发现两个质数相隔并不远

我们可以采用较为暴力的做法 循环枚举单独的一个数或两个连续的数 直到找到合法区间

具体看代码

```cpp
#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long

using namespace std;

const int MAXN = (int)2e7 + 15;
int isprime[MAXN], prime[MAXN], cnt, sum[MAXN];

void Init() {
    int n = 2e7 + 10;
    cnt = 0;
    isprime[1] = 1;
    for(int i = 2; i <= n; i++) {
        if(!isprime[i]) {
            prime[++cnt] = i;
        }
        for(int j = 1; j <= cnt && prime[j] * i <= n; j++) {
            isprime[i * prime[j]] = 1;
            if(i % prime[j] == 0) break;
        } 
    }
    /*
    cout << cnt << "\n"; 
    for(int i = 1; i <= cnt; i++) cout << prime[i] << " "; cout << "\n";
    */
}

signed main()
{
    Init();
    //FAST
    int T;
    cin >> T;
    while(T--) {
        int x;
        cin >> x;
        int ans;
        if(x == 0) {
            ans = 3;
        } else if(x == 1) {
            ans = 2;
        } else if(x < 0) {
            int cur = (-x) + 1;
            if(!isprime[cur]) ans = 2 * (-x) + 2;
            else if(!isprime[2 * cur + 1]) ans = 2 * (-x) + 3;
            else {
                int cur2 = 0, len = 1;
                for(int i = cur + 1; i <= MAXN - 15; i++) {
                    if(!isprime[i]) {
                        cur2 = 1;
                        break;
                    } else if(!isprime[i * 2 + 1]) {
                        cur2 = 2;
                        break;
                    } else {
                        len++;
                    }
                }
                ans = 2 * (-x) + 1 + cur2 + len * 2;
            }
        } else {
            if(!isprime[x]) ans = 1;
            else if((!isprime[2 * x + 1]) || (!isprime[2 * x - 1])) ans = 2;
            else {
                int cur = 0, len = 0;
                for(int i = x + 1; i <= MAXN - 15; i++) {
                    if(!isprime[i]) {
                        cur = 1;
                        break;     
                    } else if(!isprime[2 * i + 1]) {
                        cur = 2;
                        break;
                    } else {
                        len++;
                    }
                }
                ans = 2 * x + 1 + cur + len * 2;
              }
        }
        cout << ans << "\n";
        //cout << ans << " ans : " << x << "\n";
    } 
    return 0;
}
```



## 1004 Decomposition

知识点：欧拉回路 

将n个点的无向完全图分出k个简单图 使得每个简单图有$l_k$条边

观察限制 $∑_{i=1}^{k}l_i=n(n−1)/2$ 且n为奇数 易得总有一条欧拉回路经过所有边 依次分割成k个部分即可

问题转化为求无向完全图的欧拉回路

时间复杂度$O(n^2)$

```cpp
#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
//#define int long long

using namespace std;

int n, k;
queue<int> Q;

void Solve() {
	cin >> n >> k; 
	
	while(!Q.empty()) Q.pop();
	Q.push(n - 1);
	for(int i = 0; i <= n / 2; i++) {
		int sign = 1, cur = i;
		for(int j = 1; j < n; j++) {
			Q.push(cur);
			cur = cur + sign * j + (n - 1);
			cur %= (n - 1);
			sign *= -1;
		}
		Q.push(n - 1);
	}
	
	for(int i = 1; i <= k; i++) {
		int q;
		cin >> q;
		q++;
		while(q--) {
			cout << Q.front() + 1;
			if(q > 0) cout << " ", Q.pop();
		} 
		cout << "\n";
	}
}

signed main()
{
	FAST
	int T;
	cin >> T;
	for(int c = 1; c <= T; c++) {
		cout << "Case #" << c << ":\n";
		Solve();
	}
	return 0;
}

```



## 1005 Median

知识点：贪心

将b数组排序后按$b_i$分成m+1段 

如果最长的一段数量小于其他段的总和 那么无论如何都有合法方案 输出yes

反之 我们就看最长的一段出现在哪个位置 设其在[i,i+1] 判断减去其他段总和后剩余的数是否能放在前i个集合内 如果可行输出yes 反之输出no

时间复杂度$O(n)$

```cpp
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
//#define int long long

using namespace std;

const int MAXN = (int)1e5 + 5;

int n, m, b[MAXN];

void Solve() {
	cin >> n >> m;
	for(int i = 1; i <= m; i++) {
		cin >> b[i];
	}
	sort(b + 1, b + 1 + m);
	
	b[0] = 0, b[m + 1] = n + 1;
	int maxx = -1, p;
	for(int i = 1; i <= m + 1; i++) {
		int cur = b[i] - b[i - 1] - 1;
		if(cur >= maxx) {
			maxx = cur;
			p = i;
		}
	}
	//cout << maxx << " " << p << "\n";
	if(maxx <= n - m - maxx) {
		cout << "YES\n";
		return ;
	}
	if(maxx - (n - m - maxx) < p) {
		cout << "YES\n";
		return ;
	}
	cout << "NO\n";
	return ;
}

signed main()
{
	FAST 
    int T; cin >> T;
	while(T--) Solve();
	return 0;
}

```



## 1011 Game

知识点：记忆化搜索 博弈

设当前状态(i,j) 走零步或一步或两步后到达不了特殊状态 那么经过分类讨论 (i,j)和(i+1,j-1)的胜负状态相同

有n个特殊状态时 我们可以对$O(n)$个状态进行记忆化搜索 其他状态通过二分寻找到第一个被记录的状态  

时间复杂度$O((n+q)log(n+q))$

```cpp
#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long
#define reg register

using namespace std;

const int MAXN = (int)1e5 + 5;
const int INF = (int)1e18;

map<int, int> Map;
vector< map<int, int> > Seg;
int n, q, cnt;

struct Node {
    int l, r, z;
}a[MAXN];

bool cmp(Node &a, Node &b) {
    if(a.l == b.l) return a.r < b.r;
    return a.l < b.l; 
}

int Insert(int l, int r, int z) {
    if(Map[l + r] == 0) {
        Map[l + r] = ++cnt;
        Seg.push_back( map<int, int>() );
    } 
    int idx = Map[l + r] - 1;
    map<int, int>::iterator i = Seg[idx].find(l);
    if(i == Seg[idx].end()) {
        Seg[idx][l] = z;
        return -2;	//status
    } else if(i->second == -1) {
        Seg[idx][l] = z;
        return -1;	//status
    }
    return Seg[idx][l];
}

int Query(int l, int r) {
    int res = Insert(l, r, -1);
    if(res >= 0) return res;
    if(r - l + 1 <= 2) res = -1;
    
    int ans = 114514;
    if(res == -1) {
        if(l == r) ans = 0;
        else ans = !(Query(l + 1, r) & Query(l, r - 1)); 
    } else {
        int ll = INF, c = (l + r) >> 1;
        int idx = Map[l + r] - 1;
        map<int, int>::iterator i = Seg[idx].upper_bound(l);
        if(i == Seg[idx].end()) ans = Query(c, l + r - c);
        else ans = Query(i->first, l + r - i->first);
    }
    Insert(l, r, ans);
    return ans;
}

void Solve() {
    cnt = 0;
    Map.clear();
    Seg.clear();
    
    cin >> n >> q;
    for(reg int i = 1; i <= n; ++i) {
        //cin >> a[i].l >> a[i].r >> a[i].z;
        int l, r, z;
        cin >> l >> r >> z;
        Insert(l, r, z);
        
        for(reg int j = 0; j <= 2; ++j) {
            for(reg int k = 0; k <= 2; ++k) {
                if(j == k && j != 1) continue;
                if(l - j < 1) continue;
                Insert(l - j, r + k, -1);    //unsure
            }
        }
    }
    
    //sort(a + 1, a + 1 + n, cmp);
    
    while(q--) {
        int l, r;
        cin >> l >> r;
        cout << Query(l, r);
    }
    cout << "\n";
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

