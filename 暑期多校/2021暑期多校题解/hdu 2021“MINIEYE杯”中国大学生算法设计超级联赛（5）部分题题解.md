# hdu 2021“MINIEYE杯”中国大学生算法设计超级联赛（5）部分题题解

## 1003 VC Is All You Need

知识点：猜结论(~~不是~~)

考虑k维空间下 最多有几个点满足条件 易得最多有k+1个点

完整证明看官方题解orz

```cpp
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long

using namespace std;

signed main()
{
	int T; cin >> T;
	while(T--) {
		int n, k; cin >> n >> k; 
		cout << ((n <= k + 1 ? "Yes" : "No")) << "\n";
	}
	return 0;
}

```



## 1004 Another String

知识点：双指针 思维

首先设$f[i][j]$为$S[i,i + L - 1]$和$S[j,j + L - 1]$符合k-matching的最大L

考虑如何求f数组 我们可以先设一个差值d

设两个指针$l,r$  $r$为在$l$位置时最大能跑到的位置且符合k-matching  $r-l$即为L

这部分的处理为$O(n^2)$

考虑得到答案

当S分割为$A[1,l]和B[l+1,n]$ 易得此时答案为$\sum_{i=1}^{l}\sum_{j=l+1}^{n}min(f[i][j], l - i + 1)$

直接枚举 时间复杂度为$O(n^3)$

发现在l情况下 第i行只需要[l+1,n]列的数据

考虑倒序枚举l 计算完答案后用$f[i][l]$更新贡献

我们需要三个数组b,sum,cnt

$b[i][j]$为[l+1,n]中值为j的个数

$sum[i]$为[l+1,n]中**小于l-i+1**的$f[i][j]$的和

$cnt[i]$为[l+1,n]中**小于l-i+1**的$f[i][j]$的个数

倒序枚举l的时候用$f[i][l]$更新这三个数组即可

这部分的处理为$O(n^2)$

总时间复杂度为$O(n^2)$

```cpp
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long

using namespace std;

const int MAXN = (int)3005;

int n, k, f[MAXN][MAXN], b[MAXN][MAXN], sum[MAXN], cnt[MAXN], ans[MAXN];
char S[MAXN];

void Solve() {
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j <= n + 1; j++) {
			b[i][j] = 0;
		}
		sum[i] = 0;
		cnt[i] = 0;
	}
	
	for(int i = 1; i <= n; i++) f[i][i] = n - i + 1;
	for(int d = 1; d <= n; d++) {
		for(int l = 1, r = 0, cur = 0; l + d <= n; l++) {
			while(r + d <= n && cur <= k) {
				r++;
				cur += (S[r] != S[r + d]);
			}
			f[l][l + d] = r - l;
			cur -= (S[l] != S[l + d]);
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			f[j][i] = f[i][j];
		}
	}
	
	//for(int i = 1; i <= n; i++) { for(int j = 1; j <= n; j++) cout << f[i][j] << " "; cout << "\n"; }
	
	for(int l = n; l >= 1; l--) {
		int res = 0;
		for(int i = 1; i <= l; i++) {
			//for(int j = l + 1; j <= n; j++) { res += min(f[i][j], l - i + 1); }
			
			res += sum[i] + (n - l - cnt[i]) * (l - i + 1);
			if(f[i][l] < l - i + 1) {
				b[i][ f[i][l] ]++;
				sum[i] += f[i][l];
				cnt[i]++;
			}
			sum[i] -= b[i][l - i + 1] * (l - i + 1);
			cnt[i] -= b[i][l - i + 1];
		}
		ans[l] = res;
		//printf("%d\n", ans);
	}
	
	for(int i = 1; i < n; i++) {
		printf("%lld\n", ans[i]);
	}
}

signed main()
{
	int T; cin >> T;
	while(T--) {
		cin >> n >> k >> S + 1;
		Solve();
	}
	return 0;
}

```



## 1006 Cute Tree

知识点：模拟

这道题和前几场比赛中某道签到题的case有点像啊

~~怎么会事呢~~

对一个区间三等分 总层数不超过$\log_{3}n$层

直接按题目中伪代码深搜即可

和之前那道签到题不同 这题不需要用Map 只要暴力搞一搞就好了

时间复杂度$O(n\log_{3}n)$

```cpp
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
//#define int long long

using namespace std;

int n, a[(int)2e5 + 5];

int DFS(int l, int r) {
    if(l == r) return 1;
    if(r - l == 1) return 3;
    else {
        int cur = 0;
        int b = l + ceil(1.0 * (r - l) / 3) - 1;
        int c = floor(1.0 * (b + r) / 2);
        cur = DFS(l, b) + DFS(b + 1, c) + DFS(c + 1, r) + 1;
        return cur;
    }
}

signed main()
{
    //FAST
    int T;
    cin >> T;
    while(T--) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        cout << DFS(1, n) << "\n";
    }
    return 0;
}
```



## 1007 Banzhuan

知识点：数学

考虑最大花费 一定要填满整个空间 而且每次都从$(i,j,n)$放 让他自然掉落 总花费为
$$
(1 + 2 + ... + n) \cdot (1 + 2 ^ 2 + ... + n ^ n) \cdot (n + n + ... + n) = \\
(n \cdot (n + 1) / 2) \cdot (n \cdot (n + 1) \cdot (2n + 1) / 6) \cdot (n * n)
$$
考虑最小花费 我们可以将方块放到三个坐标面$Oxy,Oxz,Oyz$上并铺满

容易发现(1,1,z)(z>1)的方块可以除去 除去之后从左边和前面也可以观察到n*n的矩阵

此时总花费为
$$
\sum_{x=1}^{n}\sum_{y=1}^{n}xy^2+\sum_{x=2}^{n}\sum_{z=2}^{n}xz+\sum_{y=2}^{n}\sum_{z=2}^{n}y^2z
$$

需要特别注意精度问题 除法需要用逆元处理一下orz

```cpp
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int __int128

using namespace std;

const int MOD = (int)1e9 + 7;

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

inline int qpow(int a, int p) {
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

inline int inv(int x) {
	return qpow(x, MOD - 2) % MOD;
}

int Max(int n) {
	int cur1 = n * (n + 1) % MOD * inv(2) % MOD;
	int cur2 = n * (n + 1) % MOD * (2 * n + 1) % MOD * inv(6) % MOD;
	int cur3 = n * n % MOD;
	return cur1 * cur2 % MOD * cur3 % MOD;
}

int Min(int n) {
	int sumx = n * (n + 1) % MOD * inv(2) % MOD;
	int sumy = n * (n + 1) % MOD * (2 * n + 1) % MOD * inv(6) % MOD;
	int sumz = n * (n + 1) % MOD * inv(2) % MOD;
	int cur1 = sumx * sumy % MOD;
	int cur2 = (sumx - 1 + MOD) * (sumz - 1 + MOD) % MOD;
	int cur3 = (sumy - 1 + MOD) * (sumz - 1 + MOD) % MOD;
	return (cur1 + cur2 + cur3) % MOD;
}

signed main()
{
	int T;
	T = read();
	while(T--) {
		int n = read();
		write( Min(n) );
		cout << "\n";
		write( Max(n) );
		cout << "\n";
	}
	return 0;
}

```



## 1009 Array

知识点：树状数组 线段树

双倍经验：https://www.luogu.com.cn/problem/P4062

具体题解请看 **luogu P4062 [Code+#1]Yazid 的新生舞会 题解**

```cpp
#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long

using namespace std;

const int MAXN = (int)2e6 + 5;
const int INF = 0x3f3f3f3f;

int c1[MAXN], c2[MAXN], c3[MAXN], a[MAXN], n;
vector<int> b[MAXN];

int lowbit(int x) { return x & (-x); }

void Modify(int x, int k) {
	int i = x;
	while(i <= 2 * n + 1) {
		c1[i] += k;
		c2[i] += k * x;
		c3[i] += k * x * x;
		i += lowbit(i);
	}
}

int Query(int x) {
	int res = 0;
	int i = x; 
	while(i > 0) {
		res += c1[i] * (x + 2) * (x + 1) - c2[i] * (2 * x + 3) + c3[i];
		i -= lowbit(i); 
	}
	return res / 2;
}

int Sum(int l, int r) {
	return Query(r) - ( l == 0 ? 0 : Query(l - 1) );
}

void Add(int l, int r, int k) {
	Modify(l, k);
	Modify(r + 1, -k);
}

void Solve() {
	
	cin >> n;
	int maxx = -1;
	const int D = n + 1;	//[1,2*n+1]
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		b[ a[i] ].push_back(i);
		maxx = max(maxx, a[i]);
	}
	
	int ans = 0;
	for(int i = 0; i <= maxx; i++) {
		if(b[i].size() == 0) continue;
		//cout << i << "\n";
		b[i].push_back(n + 1);
		int last = 0;
		for(int j = 0; j < b[i].size(); j++) {
			int l = 2 * j - (b[i][j] - 1) + D, r = 2 * j - last + D;
			//cout << last << " " << b[i][j] << ":\n";
			//cout << l - D << " " << r - D << "\n";
			ans += Sum(l - 1, r - 1);
			Add(l, r, 1);
			last = b[i][j];
		}
		
		last = 0;
		for(int j = 0; j < b[i].size(); j++) {
			int l = 2 * j - (b[i][j] - 1) + D, r = 2 * j - last + D;
			Add(l, r, -1);
			last = b[i][j];
		}
		
		b[i].clear();
	}
	cout << ans << "\n";
	
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

