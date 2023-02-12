# hdu 2021“MINIEYE杯”中国大学生算法设计超级联赛（7）部分题题解

## 1004 Link with Balls

知识点：组合数学

将编号为$2x$和$2x+1$的桶合并起来 那么这两个桶可以取**任意**一个数 合并完之后我们有n个这样的桶和一个能取n以内数字的桶

暴力枚举第2n个桶取多少数 设其为i 利用隔板法求出前n个桶取m-i的方案

答案为$\sum_{i=0}^{n} C_{m - i + n - 1}^{n - 1}=C_{m+n}^{n} - C_{m-1}^{n}$

```cpp
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long

const int MAXN = (int)2e6 + 5;
const int MOD = (int)1e9 + 7;

using namespace std;

int fact[MAXN];

int qpow(int a, int p) {
	int res = 1;
	while(p > 0) {
		if(p & 1) {
			res = res * a % MOD;
		}
		p >>= 1;
		a = a * a % MOD;
	}
	return res;
}

int inv(int x) {
	return qpow(x, MOD - 2) % MOD;
}

int C(int n, int m) {
	if(n < m) return 0;
	return fact[n] * inv(fact[m]) % MOD * inv(fact[n - m]) % MOD;
}

int Solve(int n, int m) {
	return ( C(n + m, n) - C(m - 1, n) + MOD ) % MOD;
}

signed main()
{
	int n = 2e6;
	fact[0] = 1;
	for(int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD;
	int TT; cin >> TT;
	while(TT--) {
		int n, m;
		cin >> n >> m;
		cout << Solve(n, m) % MOD << "\n"; 
	}
	return 0;
}

```



## 1005 Link with EQ

知识点：概率

梦幻联动：www.bilibili.com/video/BV1RT4y1j7pP

设$f(n)$表示有n个位子且**第一个人一定选第1个位置**时最多能承受多少人 $f(n)$的求法毕导视频讲的很清楚了

统计答案时计算$\sum_{i=1}^{n} \frac{ f(i) + f(n - i + 1) - 1 }{n}$即可

转化式子 用前缀和维护即可

```cpp
#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long

using namespace std;

const int MAXN = (int)1e6 + 5;
const int MOD = (int)1e9 + 7;

int f[MAXN], sum[MAXN], n;

int qpow(int a, int p) {
	int res = 1;
	while(p > 0) {
		if(p & 1) {
			res = res * a % MOD;
		}
		p >>= 1;
		a = a * a % MOD;
	}
	return res;
}

signed main()
{
	FAST
	n = 1e6;
	f[1] = 1; f[2] = 1; f[3] = 2; f[4] = 2;
	for(int i = 5; i <= n; i++) {
		if(i % 2 == 1) {
			f[i] = ( 2 * f[(i + 1) / 2] - 1 ) % MOD;
		} else {
			f[i] = ( f[i / 2] + f[i / 2 + 1] - 1 ) % MOD;
		}
	}
	for(int i = 1; i <= n; i++) sum[i] = ( sum[i - 1] + f[i] ) % MOD;
	
	int TT;
	cin >> TT;
	while(TT--) {
		int n;
		cin >> n;
		cout << (2 * sum[n] - n + MOD * 5) % MOD * qpow(n, MOD - 2) % MOD << "\n";
	}
	return 0;
}

```



## 1007 Link with Limit

知识点：图论

对于题中式子 答案一定可以表示为一个**循环节( 循环执行x=f(x) )**的平均值

对每个i建立从i到f(i)的有向边 求出每一个环 判断环的平均值是否相等即可

时间复杂度$O(n)$

```cpp
#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long
#define reg 

using namespace std;

const int MAXN = (int)1e6 + 5;

int n, vis[MAXN], vis2[MAXN], a[MAXN], r[MAXN], f[MAXN], sum;

int find(int x) {
    return (x == f[x] ? x : f[x] = find(f[x]));
}

signed main()
{
    FAST
    int T;
    cin >> T;
    while(T--) {
        cin >> n;
        sum = 0;
        for(reg int i = 1; i <= n; ++i) vis[i] = r[i] = vis2[i] = 0, f[i] = i;
        for(reg int i = 1; i <= n; ++i) {
            cin >> a[i];
            f[ find(a[i]) ] = find(i);
            f[i] = find(a[i]);
        }
        
        for(reg int i = 1; i <= n; ++i) {
            if(vis2[find(i)] == 0) {
                ++sum;
                int u = i;
                while(vis[u] == 0) {
                    vis[u] = sum;
                    u = a[u];
                }
                r[sum] = u;
                vis2[find(u)] = 1;
            }
        }
        /*
        cout << sum << " sum\n";
        for(int i = 1; i <= sum; i++) cout << r[i] << " "; cout << " r\n";
        */
        double same = 0.0;
        bool flag = 1;
        for(reg int i = 1; i <= sum; ++i) {
            int cnt = 0, cur = 0, u = a[ r[i] ];
            while(u != r[i]) {
                cur += u;
                ++cnt;
                u = a[u];
            } 
            cur += r[i];
            ++cnt;
            //cout << r[i] << " " << cur << " " << cnt << "\n"; 
            
            if(same == 0.0) {
                same = 1.0 * cur / cnt;
            } else if(same != 1.0 * cur / cnt) {
                flag = 0;
                break;
            }
        }
        if(flag) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
```



## 1010 Smzzl with Tropical Taste

知识点：签到

判断p是否小于等于q即可

```cpp
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
//#define int long long

using namespace std;

signed main()
{
	int T; 
	cin >> T;
	while(T--) {
		double p, q;
		cin >> p >> q;
		cout << (p <= q ? "N0 M0R3 BL4CK 1CE TEA!" : "ENJ0Y YOURS3LF!") << "\n";
	}
	return 0;
}

```



## 1012 Yiwen with Sqc

知识点：前缀和

考虑计算单个字母对答案的贡献

我们先从小到大存储对应字母出现的位置 设其为$idx[1...n]$ n为字母个数

对于单个字母 我们考虑枚举右端点 设其位置在$idx[j]$

这样对于左端点(设其位置在$idx[i]$) 我们有贡献$(idx[i] - idx[i - 1]) * (j - i + 1) ^ 2$

右端点为j的总贡献为$\sum_{i=0}^{j} (idx[i] - idx[i - 1]) * (j - i + 1) ^ 2$ 其中**idx[0] = 0**

观察到式子可化为
$$
\sum_{i=0}^{j}(idx[i] - idx[i - 1]) * ( \ (j + 1) ^ 2 - 2 * (j + 1) * i + i ^ 2 \ ) \\
$$
我们可以用三个前缀和分别维护
$$
(idx[i] - idx[i - 1]) \\
(idx[i] - idx[i - 1]) * i \\
(idx[i] - idx[i - 1]) * i ^ 2 \\
$$
的值 枚举到右端点时O(1)查询即可

时间复杂度$O(n)$ 注意常数问题

```cpp
#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long

using namespace std;

const int MAXN = (int)1e5 + 5;
const int MOD = 998244353;

char S[MAXN];
int n;
vector<int> G[40], Sum[7], Len;

void Solve() {
    
    int ans = 0;
    for(int k = 1; k <= 26; k++) {
        if(G[k].size() <= 1) continue;
        /*
        cout << k << "\n";
        for(int j = 0; j < G[k].size(); j++) cout << G[k][j] << " "; cout << " qwq\n";
        */
        int last = 0;
        Len.clear();
        Sum[1].clear();
        Sum[2].clear();
        Sum[3].clear();
        
        for(int i = 0; i < G[k].size(); i++) {
            Len.push_back(G[k][i] - last);
            last = G[k][i];
        }
        //for(int i = 0; i < Len.size(); i++) cout << Len[i] << " "; cout << " len \n";
        Sum[1].push_back(0ll);
        Sum[2].push_back(0ll);
        Sum[3].push_back(0ll);
        for(int i = 1; i < Len.size(); i++) {
            //cout << i << "\n" << Len[i] << " " << Len[i] * i << " " << Len[i] * i * i << "\n";
            
            int cur1 = Sum[1][i - 1] + Len[i];
            int cur2 = Sum[2][i - 1] + Len[i] * i;
            int cur3 = Sum[3][i - 1] + Len[i] * i * i;
            
            //cout << cur1 << " " << cur2 << " " << cur3 << "  q\n";
            
            Sum[1].push_back( cur1 );
            Sum[2].push_back( cur2 );
            Sum[3].push_back( cur3 );
            //cout << i << "qwq\n";
        }
        /*
        for(int i = 0; i < Sum[1].size(); i++) cout << Sum[1][i] << " "; cout << " sum1 \n";
        for(int i = 0; i < Sum[1].size(); i++) cout << Sum[2][i] << " "; cout << " sum2 \n";
        for(int i = 0; i < Sum[1].size(); i++) cout << Sum[3][i] << " "; cout << " sum3 \n";
        */
        G[k].push_back(n + 1);
        for(int j = 1; j < G[k].size() - 1; j++) {
            int cur = Sum[1][j] * (j + 1) * (j + 1) - 2 * (j + 1) * Sum[2][j] + Sum[3][j];
            //cout << cur << " " << G[k][j + 1] - G[k][j] << "ovo\n";
            cur = cur * (G[k][j + 1] - G[k][j]) % MOD;
            //cout << cur << "qwq\n";            
            cur = (cur + 100 * MOD) % MOD;
            
            ans = (ans + cur) % MOD;
        }
        //cout << ans << "ovo\n";
    }
    cout << ans % MOD << "\n";
}

signed main()
{
    FAST
    int T;
    cin >> T;
    while(T--) {
        for(int i = 1; i <= 26; i++) G[i].clear(), G[i].push_back(0);
        cin >> S + 1;
        n = strlen(S + 1);
        for(int i = 1; i <= n; i++) G[S[i] - 'a' + 1].push_back(i);
        Solve();
    }
    return 0;
}
```