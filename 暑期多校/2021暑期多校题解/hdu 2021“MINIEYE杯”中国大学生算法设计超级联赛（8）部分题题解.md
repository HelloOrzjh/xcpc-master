# hdu 2021“MINIEYE杯”中国大学生算法设计超级联赛（8）部分题题解

**大伙给1002和1004的主角点个关注吧（逃）**

嘉然今天吃什么 https://space.bilibili.com/672328094/ 

向晚大魔王 https://space.bilibili.com/672346917/ 

乃琳Queen https://space.bilibili.com/672342685/ 

贝拉kira https://space.bilibili.com/672353429/

珈乐Carol https://space.bilibili.com/351609538/



## 1003 Ink on paper

知识点：最小生成树

每两个点连一条无向边，边的权值为两滴墨水相互接触所需的时间

容易得到答案为最小生成树中的最长边

注意稠密图用Prim，时间复杂度为$O(n^2)$

```cpp
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long

using namespace std;

const int MAXN = 5005;
const int INF = 8e18 + 5;

pair<int, int> a[MAXN];
int n, G[MAXN][MAXN], dist[MAXN], st[MAXN];

inline int Dist(int i, int j) {
	int x1 = a[i].first, y1 = a[i].second;
	int x2 = a[j].first, y2 = a[j].second;
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int Prim() {
	for(int i = 1; i <= n; i++) dist[i] = INF, st[i] = 0;
	int res = -1;
	for(int i = 0; i < n; i++) {
		int t = -1;
		for(int j = 1; j <= n; j++) {
			if(!st[j] && (t == -1 || dist[t] > dist[j])) t = j;
		}
		if(i && dist[t] == INF) return -1;
		if(i) res = max(res, dist[t]);
		st[t] = 1;
		
		for(int j = 1; j <= n; j++) dist[j] = min(dist[j], G[t][j]);
	}
	return res;
}

signed main()
{
	FAST
	//cout << INF << "\n";
	int TT; cin >> TT;
	while(TT--) {
		cin >> n;
		for(int i = 1; i <= n; i++) {
			int x, y;
			cin >> x >> y;
			a[i] = make_pair(x, y);
		}
		for(int i = 1; i <= n; i++) {
			G[i][i] = 0;
			for(int j = i + 1; j <= n; j++) {
				G[j][i] = G[i][j] = Dist(i, j);
			}
		}
		cout << Prim() << "\n";
	}
	return 0;
}

```



## 1004 Counting Stars

知识点：线段树

第一种操作等价于删去最低位，第二种操作等价于最高位往左移一位，**贝拉**需要查询区间和

看到题目的数据范围很容易想到用均摊复杂度为$O(logn)$的线段树来维护

而且因为第二种操作只和最高位有关

很容易想到将最高位和其他位分别用两个线段树存储

再想想一个数最多进行$logn$次第一种操作，我们可以采用较为暴力的方法进行第一种操作

具体做法是用一个tag保存这段区间里的数是否都为0，如果是则忽略这段区间，如果否就分成左右两部分分别判断，直到$l==r$时直接做第一种操作

区间内所有数最多被执行$O(nlogn)$次第一种操作，而对于每个数又会更新$O(logn)$个节点，所以这部分的时间复杂度为$O(nlog^2n)$

最后查询直接查询两个线段树的和即可

时间复杂度为$O(nlog^2n)$

```cpp
#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long

using namespace std;

const int MAXN = (int)1e5 + 5;
const int MOD = 998244353; 

int tag2[MAXN << 2], tag3[MAXN << 2], sum2[MAXN << 2], sum3[MAXN << 2];
int Pow2[MAXN], a[MAXN], high[MAXN], n, q;

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

int ls(int x) { return x << 1; }

int rs(int x) { return x << 1 | 1; }

int lowbit(int x) {
    return x & (-x);
} 

int highbit(int x) {
    int res = -1;
    while(x > 0) {
        x >>= 1;
        res++;
    }
    return res;
}

void PushUp2(int p) {
    sum2[p] = sum2[ls(p)] + sum2[rs(p)];
    tag2[p] = tag2[ls(p)] & tag2[rs(p)];
}

void PushUp3(int p) {
    sum3[p] = ( sum3[ls(p)] + sum3[rs(p)] ) % MOD;
}

void PushDown3(int p) {
    tag3[ls(p)] += tag3[p];
    tag3[rs(p)] += tag3[p];
    sum3[ls(p)] = sum3[ls(p)] * Pow2[ tag3[p] ] % MOD;
    sum3[rs(p)] = sum3[rs(p)] * Pow2[ tag3[p] ] % MOD;
    tag3[p] = 0;
}

void Build(int l, int r, int p) {
    tag2[p] = tag3[p] = 0;
    sum2[p] = sum3[p] = 0;
    if(l == r) {
        sum2[p] = a[l];
        sum3[p] = Pow2[ high[l] ];
        return ;
    }
    int mid = (l + r) >> 1;
    Build(l, mid, ls(p));
    Build(mid + 1, r, rs(p));
    PushUp2(p);
    PushUp3(p);
}

int Query1(int nl, int nr, int l, int r, int p) {
    if(nl <= l && nr >= r) {
        if(tag2[p]) return 0;
        else return (sum2[p] + sum3[p]) % MOD;
    }
    PushDown3(p);
    int mid = (l + r) >> 1;
    int res = 0;
    if(nl <= mid) res = (res + Query1(nl, nr, l, mid, ls(p))) % MOD;
    if(nr > mid) res = (res + Query1(nl, nr, mid + 1, r, rs(p))) % MOD;
    return res;
}

void Modify2(int nl, int nr, int l, int r, int p) {
    if(nl <= l && nr >= r && tag2[p]) return ;
    if(l == r) {
        if(sum2[p] == 0) tag2[p] = 1, sum3[p] = 0;
        else sum2[p] -= lowbit(sum2[p]);
        return ;
    }
    PushDown3(p);
    int mid = (l + r) >> 1;
    if(nl <= mid) Modify2(nl, nr, l, mid, ls(p));
    if(nr > mid) Modify2(nl, nr, mid + 1, r, rs(p));
    PushUp2(p);
    PushUp3(p);
}

void Modify3(int nl, int nr, int l, int r, int p) {
    if(nl <= l && nr >= r) {
        if(tag2[p]) {
            sum3[p] = 0; tag3[p] = 0;
        } else {
            tag3[p]++; sum3[p] = sum3[p] * 2 % MOD;
        }
        return ;
    }
    PushDown3(p);
    int mid = (l + r) >> 1;
    if(nl <= mid) Modify3(nl, nr, l, mid, ls(p));
    if(nr > mid) Modify3(nl, nr, mid + 1, r, rs(p));
    PushUp3(p);
} 

signed main()
{
    
    signed TT; scanf("%d", &TT);
    Pow2[0] = 1;
    for(int i = 1; i <= 1e5; i++) {
        Pow2[i] = Pow2[i - 1] * 2;
        if(i > 32) Pow2[i] %= MOD;
    }
    
    while(TT--) {
        //scanf("%lld", &n);
        n = read();
        for(int i = 1; i <= n; i++) {
            //scanf("%lld", &a[i]);
            a[i] = read();
            high[i] = highbit(a[i]);
            a[i] -= Pow2[ high[i] ];
        }
        
        //for(int i = 1; i <= n; i++) cout << a[i] << " "; cout << " a \n";
        //for(int i = 1; i <= n; i++) cout << high[i] << " "; cout << " high \n";
        
        //scanf("%lld", &q);
        q = read();
        Build(1, n, 1);
        while(q--) {
            int op, l, r;
            //scanf("%lld%lld%lld", &op, &l, &r);
            op = read(); l = read(); r = read();
            if(op == 1) {
                //printf("%lld\n", Query1(l, r, 1, n, 1) % MOD);
                write(Query1(l, r, 1, n, 1) % MOD); putchar('\n');
            } else if(op == 2) {
                Modify2(l, r, 1, n, 1);
            } else {
                Modify3(l, r, 1, n, 1);
            }
        }
    } 
    return 0;
}
```



## 1005 Separated Number

知识点：组合数学

考虑枚举每一位数对答案的贡献

设第$i$位数的数位为$num[i]$，位权为$10^j$，答案有两种情况

①$i+j<n$ ，此时从第$i$位开始以后的$j$个数字都被确定，需要用两次分割得到从$i$开始的$j$个数字

问题转化为在剩下的数字中至多分成$k-1$份

由于此时原来的数字已经被分割成三部分，且中间的部分已经确定，所以我们至多插入$k-2$个分割点

答案为$\sum_{i=0}^{k-2} C_{n-j-2}^{i}$

②$i+j=n$ ，和①不同的是，这时原来的数字被分割成两部分，且后面的部分已经确定，所以我们至多插入$k-1$个分割点

答案为$\sum_{i=0}^{k-1} C_{n-j-1}^{i}$

前缀和优化即可

时间复杂度$O(n)$

```cpp
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long

using namespace std;

const int MAXN = (int)1e6 + 5;
const int MOD = 998244353;

int fact[MAXN], inv[MAXN], pow10[MAXN], num[MAXN], n, k, f[MAXN][4];
char S[MAXN];

int qpow(int a, int p) {
	int res = 1;
	while(p > 0) {
		if(p & 1) res = res * a % MOD;
		p >>= 1;
		a = a * a % MOD;
	}
	return res;
}

int C(int n, int m) {
	if(m > n) return 0;
	if(n == m) return 1;
	return fact[n] * inv[m] % MOD * inv[n - m] % MOD;
}

signed main()
{
	FAST
	
	n = 1e6;
	fact[0] = 1, pow10[0] = 1;
	for(int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD, pow10[i] = pow10[i - 1] * 10 % MOD;
	inv[n] = qpow(fact[n], MOD - 2);
	for(int i = n - 1; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % MOD;
	
	int TT; cin >> TT;
	while(TT--) {
		cin >> k;
		cin >> S + 1;
		n = strlen(S + 1);
		for(int i = 1; i <= n; i++) {
			num[i] = S[i] - '0';
		}
		if(k == 1) {
			int ans = 0;
			for(int i = 1; i <= n; i++) {
				ans = ( ans * 10 % MOD + num[i] ) % MOD;
			}
			cout << ans << "\n";
			continue; 
		}
		
		f[0][1] = f[0][2] = 1;
		if(k - 1 == 0) f[1][1] = 1;
		else f[1][1] = 2;
		if(k - 2 == 0) f[1][2] = 1;
		else f[1][2] = 2;
		for(int i = 2; i <= n; i++) {
			f[i][1] = ( 2 * f[i - 1][1] % MOD - C(i - 1, k - 1) + 4 * MOD ) % MOD;
			f[i][2] = ( 2 * f[i - 1][2] % MOD - C(i - 1, k - 2) + 4 * MOD ) % MOD;
		}
		
		int ans = 0;
		int sum = 0;
		for(int i = n; i >= 1; i--) {
			ans = (ans + num[i] * pow10[n - i] % MOD * f[i - 1][1] % MOD) % MOD;
			if(i < n) sum = (sum + pow10[n - i - 1] * f[n - (n - i - 1) - 2][2] % MOD) % MOD;
			else sum = 0;
			ans = (ans + sum * num[i] % MOD) % MOD;
		}
		cout << ans % MOD << "\n";
	}
	return 0;
}

```



## 1009 Singing Superstar

知识点：字符串Hash AC自动机

### 字符串Hash解法

观察到$a_i$长度小于30，那我们可以用字符串Hash将长度为30以内的所有字符串的哈希值存起来，并按不同字符串的哈希值存储起点，并用贪心或dp等方式暴力找到最多出现次数，这部分的时间复杂度为$O(30|S|)$

存储答案，可以做到$O(1)$的单次查询

时间复杂度为$O(30|S| + n)$

```cpp
//Heil Diana!

#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long
#define reg register 

using namespace std;

const int MAXN = 1e5 + 5;
const int BASE = 27;
const int MOD = (int)1e7 + 7;

unordered_map<int, int> Map[35];
vector<int> f[35][MAXN];
int n, cnt[35], h[MAXN], slen, tlen, Pow[MAXN], Ans[35][MAXN];
char S[MAXN], T[MAXN];
int curf[MAXN], curmax[MAXN];

inline int Hash(char x) { return x - 'a' + 1; }

inline int getHash(int l, int r) { return ( h[r] - h[l - 1] * Pow[r - l + 1] % MOD + MOD * Pow[r - l + 1] ) % MOD; }

inline void Solve(int k, int idx) {
 
    f[k][idx].push_back(slen + 1);
    int sze = f[k][idx].size();

    for(int i = 0; i < sze; i++) curmax[i] = curf[i] = 1;
    curmax[sze - 1] = curf[sze - 1] = 0;
    
    for(int i = sze - 2; i >= 0; i--) {

        int l = i + 1, r = sze - 1;
        while(l < r) {
            int mid = (l + r - 1) >> 1;
            if(f[k][idx][mid] - f[k][idx][i] >= k) r = mid;
            else l = mid + 1;
        }
        
        curf[i] = max(curf[i], curmax[r] + 1);
        curmax[i] = max(curmax[i + 1], curf[i]);
    }

    Ans[k][idx] = curmax[0];
}

signed main()
{
    int TT;
    scanf("%lld", &TT);
    Pow[0] = 1;
    for(reg int i = 1; i <= 1e5; ++i) Pow[i] = Pow[i - 1] * BASE % MOD;
    
    while(TT--) {
        scanf("%s", S + 1);
        slen = strlen(S + 1);
        int curhash, idx;
        
        h[0] = 0;
        for(reg int i = 1; i <= slen; ++i) {
            h[i] = h[i - 1] * BASE + Hash(S[i]);
            h[i] %= MOD;
        }
        
        for(reg int k = 1; k <= 30; ++k) {
            Map[k].clear();
            cnt[k] = 0;
            for(reg int i = 1; i <= slen; ++i) {
                if(i + k - 1 > slen) break;
                curhash = getHash(i, i + k - 1);
                if(Map[k][curhash] == 0) Map[k][curhash] = ++cnt[k];
                idx = Map[k][curhash];
                f[k][idx].push_back(i);
            }
        }
        
        
        for(reg int k = 1; k <= 30; ++k) {
            for(reg int i = 1; i <= cnt[k]; ++i) {
                Solve(k, i);
            }
        }
        
        scanf("%lld", &n);
        for(reg int k = 1; k <= n; ++k) {
            scanf("%s", T + 1);
            tlen = strlen(T + 1);
            curhash = 0;
            for(reg int i = 1; i <= tlen; ++i) {
                curhash = curhash * BASE + Hash(T[i]);
                curhash %= MOD;
            }
            idx = Map[tlen][curhash];
            //printf("%lld %lld %lld\n", tlen, curhash, idx);
            //for(int i = 0; i < f[tlen][idx].size(); i++) printf("%lld ", f[tlen][idx][i]); printf("\n");
            if(idx == 0) printf("0\n");
            else printf("%lld\n", Ans[tlen][idx]);
        }
        
        for(int k = 1; k <= 30; k++) for(int i = 1; i <= cnt[k]; i++) f[k][i].clear();
    }
    return 0;
}
```



### AC自动机解法

参考  https://www.luogu.com.cn/problem/P3796  里的做法

数据范围较小，我们先考虑暴力跳fail指针怎么做

相比洛谷这道题，本题有一个相同字符串不相交的限制

那么我们可以再记录一个last数组，表示每个模式串最后在主串中出现的位置

那么我们在跳fail指针的时候可以多加一个条件：最后出现的位置和现在匹配到的位置大于字符串长度

时间复杂度稍劣于字符串Hash解法

```cpp
#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
//#define int long long

using namespace std;

const int MAXN = (int)1e5 + 5;

int trie[MAXN][30], ans[MAXN], num[MAXN], last[MAXN], fail[MAXN], cnt, n, Len[MAXN], tag[MAXN];
string T[MAXN];
char S[MAXN];
int Q[MAXN], head, tail;

inline int Hash(char x) {
    return x - 'a' + 1; 
}

void Insert(int idx) {
    int u = 1;
    int len = T[idx].length();
    Len[idx] = len;
    for(int i = 0; i < len; i++) {
        if(!trie[u][Hash(T[idx][i])]) trie[u][Hash(T[idx][i])] = ++cnt;
        u = trie[u][Hash(T[idx][i])];
    }
    if(!num[u]) num[u] = idx, tag[idx] = idx;
    else {
        tag[idx] = num[u];
    }
}

void GetFail() {
    for(int i = 1; i <= 26; i++) trie[0][i] = 1;
    int head = 1, tail = 0;
    Q[++tail] = 1;
    while(head <= tail) {
        int u = Q[head];
        head++;
        int uFail = fail[u];
        for(int i = 1; i <= 26; i++) {
            int v = trie[u][i];
            if(!trie[u][i]) {
                trie[u][i] = trie[uFail][i];
            } else {
                fail[v] = trie[uFail][i];
                Q[++tail] = v;
            }
        }
    }
}

void Solve() {
    int len = strlen(S + 1);
    int u = 1;
    for(int i = 1; i <= len; i++) {
        u = trie[u][Hash(S[i])];
        for(int p = u; p; p = fail[p]) {
            if(num[p] != 0 && i - last[num[p]] >= Len[num[p]]) {
                ans[num[p]]++;
                last[num[p]] = i;
            } 
        }
    }
}

signed main()
{
    FAST
    int TT; cin >> TT;
    while(TT--) {
        cin >> S + 1 >> n;
        cnt = 1;
        for(int i = 1; i <= n; i++) {
            cin >> T[i];
            Insert(i);
        }
        GetFail();
        Solve();
        for(int i = 1; i <= n; i++) {
            cout << ans[ tag[i] ] << "\n";
        }
        
        for(int i = 0; i <= max(n, cnt); i++) {
            for(int j = 1; j <= 26; j++) trie[i][j] = 0;
            ans[i] = fail[i] = num[i] = tag[i] = last[i] = 0;    
        }
    }
    return 0;
}
```

