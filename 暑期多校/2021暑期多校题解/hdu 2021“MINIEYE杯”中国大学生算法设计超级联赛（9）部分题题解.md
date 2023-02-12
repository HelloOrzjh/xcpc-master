# hdu 2021“MINIEYE杯”中国大学生算法设计超级联赛（9）部分题题解

## 1002 Just another board game

知识点：贪心

选择不走 答案为$a[1][1]$

选择走k步 有

①k为偶数时 找到每一列的最小值 使这个最小值最大

②k为奇数时 找到每一行的最大值 使这个最大值最小

特判k==1的情况即可

```cpp
#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long

using namespace std;

const int MAXN = (int)1e5 + 5;
const int INF = 2e18;

int n, m, k;
vector<int> a[MAXN];

signed main()
{
    int TT; scanf("%lld", &TT);
    while(TT--) {
        scanf("%lld%lld%lld", &n, &m, &k);
        
        for(int i = 1; i <= n; i++) {
            a[i].push_back(0);
            for(int j = 1; j <= m; j++) {
                int cur;
                scanf("%lld", &cur);
                a[i].push_back(cur);
            }
        }
        
        if(k == 1) {
            int maxx = -1;
            for(int i = 1; i <= m; i++) maxx = max(maxx, a[1][i]);
            printf("%lld\n", maxx);
        } else if(k % 2 == 0) {
            int maxx = -1;
            for(int i = 1; i <= m; i++) {
                int minn = INF;
                for(int j = 1; j <= n; j++) {
                    minn = min(minn, a[j][i]);
                }
                maxx = max(maxx, minn);
            }
            maxx = max(maxx, a[1][1]);
            printf("%lld\n", maxx); 
        } else {
            int minn = INF;
            for(int i = 1; i <= n; i++) {
                int maxx = -1;
                for(int j = 1; j <= m; j++) {
                    maxx = max(maxx, a[i][j]);
                }
                minn = min(minn, maxx);
            }
            minn = max(minn, a[1][1]);
            printf("%lld\n", minn); 
        }
        
        for(int i = 1; i <= n; i++) a[i].clear();
    }
    return 0;
}
```



## 1003 Dota2 Pro Circuit

知识点：模拟

让当前分数尽量高

将剩下的a数组和b数组排序一下 用双指针直接寻找最多有多少个$a[i]+b[j]<=curValue$且不出现重复元素

直接计算排名即可 这样就能记录best排名

worst排名同理

时间复杂度$O(n^2)$

```cpp
#pragma GCC optimize(2)

#include<bits/stdc++.h>
//#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long
#define pii pair<int, int>
#define pir make_pair
#define reg register 

using namespace std;

const int MAXN = 5005;

int b[MAXN], tmpa[MAXN], tmpb[MAXN], n;
pii a[MAXN], ans[MAXN];

inline int Solve1(int id, int val) {    //b[i] <= val - a[i]
    int cnt1 = 0, cnt2 = 0;
    for(reg int i = 1; i <= n; ++i) {
        if(i != id) tmpa[++cnt1] = val - a[i].first;
        if(i != n) tmpb[++cnt2] = b[i];
    }    
    /*
    cout << val << " || " << id << "\n";
    for(int i = 1; i < n; i++) cout << tmpa[i] << " "; cout << " ta\n";
    for(int i = 1; i < n; i++) cout << tmpb[i] << " "; cout << " tb\n";
    */
    for(reg int i = 1, j = 1; i <= cnt2; ++i) {
        while(tmpb[i] > tmpa[j] && j <= cnt2) ++j;
        if(j > cnt2) return i - 1;
        ++j;
        //cout << i << " " << j << " qwq\n";
        if(j > cnt2) return i;
    }
    return cnt2;
}

inline int Solve2(int id, int val) { //-b[i] < -val + a[i]
    int cnt1 = 0, cnt2 = 0;
    for(reg int i = 1; i <= n; ++i) {
        if(i != id) tmpa[++cnt1] = - val + a[i].first;
        if(i != 1) tmpb[++cnt2] = - b[i];
    }    
    
    reverse(tmpa + 1, tmpa + 1 + cnt1);
    reverse(tmpb + 1, tmpb + 1 + cnt2);
    /*
    cout << val << " ?? " << id << "\n";
    for(int i = 1; i < n; i++) cout << tmpa[i] << " "; cout << " tmpa\n";
    for(int i = 1; i < n; i++) cout << tmpb[i] << " "; cout << " tmpb\n";    
    */
    for(reg int i = 1, j = 1; i <= cnt2; ++i) {
        while(tmpb[i] >= tmpa[j] && j < n) ++j;
        if(j > cnt2) return i - 1;
        ++j;
        //cout << i << " " << j << " qwq\n";
        if(j > cnt2) return i;
    }
    return cnt2;    
}

signed main()
{
    int TT;
    scanf("%lld", &TT);
    while(TT--) {
        scanf("%lld", &n);
        for(reg int i = 1; i <= n; ++i) {
            scanf("%lld", &a[i].first);
            a[i].second = i;
        }
        for(reg int i = 1; i <= n; ++i) {
            scanf("%lld", &b[i]);
        }
        sort(b + 1, b + 1 + n);    
        sort(a + 1, a + 1 + n, greater<pii>() );
        
        //for(int i = 1; i <= n; i++) cout << a[i].first << " "; cout << "\n";
        
        for(reg int k = 1; k <= n; ++k) {
            int curmax = a[k].first + b[n];
            int curmin = a[k].first + b[1];
            int maxx = n - Solve1(k, curmax);
            int minn = 1 + Solve2(k, curmin);
            ans[ a[k].second ] = pir(maxx, minn);
            //printf("%lld %lld\n", maxx, minn);
        }
        for(reg int i = 1; i <= n; ++i) {
            printf("%lld %lld\n", ans[i].first, ans[i].second);
            //cout << ans[i].first << " " << ans[i].second << "\n";
        }
    }
    return 0;
}
```



## 1005 Unfair contest

知识点：贪心

对a,b数组排序完后将$a_n(b_n)$分为三类：①小于$a_t(b_t)$ ②大于$a_{n-s}(b_{n-s})$  ③其他

分类讨论即可

具体看代码

```cpp
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long

using namespace std;

const int INF = (int)1e16;
const int MAXN = (int)1e5 + 5;

int n, s, t, h, a[MAXN], b[MAXN];

signed main()
{
	int TT; scanf("%lld", &TT);
	while(TT--) {
		scanf("%lld%lld%lld%lld", &n, &s, &t, &h);
		for(int i = 1; i < n; i++) scanf("%lld", &a[i]); 
		for(int i = 1; i < n; i++) scanf("%lld", &b[i]);
		sort(a + 1, a + n); sort(b + 1, b + n);
		a[0] = b[0] = 1; a[n] = b[n] = h;
		int suma = 0, sumb = 0;
		for(int i = t + 1; i < n - s; i++) suma += a[i], sumb += b[i];
		int la = suma + a[t], ra = suma + a[n - s];
		int lb = sumb + b[t], rb = sumb + b[n - s];
		if(ra <= lb) {
			printf("IMPOSSIBLE\n");
		} else if(la > rb) {
			printf("%lld\n", 1 - h);
		} else {
			int res = sumb + 1 - suma;
			if(ra > rb) res = min(res, sumb + 1 - suma - (h - b[n - s]) );
			if(la > lb) res = min(res, sumb + 1 - suma - (a[t] - 1) );
			printf("%lld\n", res);
		}
	}
	return 0;
}

```



## 1007 Boring data structure problem

知识点：双端队列

借鉴一下**对顶堆**的思想

维护两个双端队列L,R

直接进行插入操作 标记已删除的元素 操作完之后维护两个类似于对顶堆的双端队列

询问时直接输出R的队首即可

具体看代码

时间复杂度约为$O(q)$

```cpp
#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
//#define int long long

using namespace std;

const int MAXN = (int)2e7 + 5;

deque<int> L, R;
char op[3];
int del[MAXN], num = 0, szeL = 0, szeR = 0, vis[MAXN];

void Update() {
	int tot = szeL + szeR;
	while(1) {
		while(!L.empty() && del[L.front()]) L.pop_front();
		while(!R.empty() && del[R.back()]) R.pop_back();
		while(!L.empty() && del[L.back()]) L.pop_back();
		while(!R.empty() && del[R.front()]) R.pop_front();
		
		if(tot == 0 || szeR == (tot + 1) / 2) break;
		
		while(szeR > (tot + 1) / 2) {
			while(!R.empty() && del[R.front()]) R.pop_front();
			vis[ R.front() ] = 1;
			L.push_back( R.front() );
			R.pop_front();
			szeR--;
			szeL++;
		}
		while(szeR < (tot + 1) / 2) {
			while(!L.empty() && del[L.back()]) L.pop_back();
			vis[ L.back() ] = 2;
			R.push_front( L.back() );
			L.pop_back();
			szeL--;
			szeR++;
		}
	}
	/*
	for(auto i : L) cout << i << " "; cout << " szeL : " << szeL << "\n";
	for(auto i : R) cout << i << " "; cout << " szeR : " << szeR << "\n";
	*/
}

signed main()
{
	int Q; scanf("%d", &Q);
	while(Q--) {
		int x;
		scanf("%s", op);
		if(op[0] == 'L') {
			L.push_front(++num);
			vis[num] = 1;
			++szeL;
		} else if(op[0] == 'R') {
			R.push_back(++num);
			vis[num] = 2;
			++szeR;
		} else if(op[0] == 'G') {
			scanf("%d", &x);
			del[x] = 1;
			if(vis[x] == 1) --szeL;
			else --szeR;
		}
		Update(); 
		if(op[0] == 'Q') {
			printf("%d\n", R.front());
		}
	}
	return 0;
}

```



## 1008 Integers Have Friends 2.0

知识点：随机化 ~~乱搞~~

设m==2 可以将a数组分为奇数和偶数两部分 易得其中有一部分的数量大于等于$\lceil \frac{n}{2} \rceil$ 即答案大于等于$\lceil \frac{n}{2} \rceil$

然后随机枚举a数组中两个元素 并用$|a_i - a_j|$的**质因数**暴力求符合条件的最长子序列长度（合因数为模数的结果小于等于其某个质因数为模数的结果）

$a_i,a_j$在答案序列里的概率一定大于$\frac{1}{4}$ 设随机K次 那么失误率为$(\frac{3}{4})^K$  当K取得足够大的时候 其失误率逐渐趋于0

单组数据最坏时间复杂度约为$O(KN + 11nK)$ 其中$N=\lfloor \sqrt{4*10^{12}} \rfloor$ 出现常数11的原因是4e12最多有11个不同的质因数 通过$O(N)$的预处理可以除掉$O(KN)$

```cpp
//#pragma GCC optimize(2)

#include<bits/stdc++.h>
#define FAST ios::sync_with_stdio(false); cin.tie(0);
#define int long long
#define reg register
#define pii pair<int, int>
#define pir make_pair 

using namespace std;

const int MAXN = (int)4e6 + 5;

int n, cnt, prime[MAXN], isprime[MAXN], a[MAXN];
mt19937_64 qwq(time(0));

inline int rd() {
    return qwq() % n + 1;
    //return rand() % n + 1;
}

inline void Init() {
        
    n = 2e6;
    cnt = 0;
    isprime[1] = 1;
    for(int i = 2; i <= n; i++) {
        if(!isprime[i]) {
            prime[++cnt] = i;
        }
        for(int j = 1; j <= cnt && i * prime[j] <= n; j++) {
            isprime[i * prime[j]] = 1;
            if(i % prime[j] == 0) break;
        }
    }
    //cout << cnt << "\n";
    //for(int i = 1; i <= cnt; i++) cout << prime[i] << " "; cout << endl;
    //int cur = 1;
    //for(int i = 1; i <= 13; i++) cur *= prime[i], cout << cur << " "; cout << "\n";
}

inline int calc(int x, int k) {
    int res = 0;
    for(int i = 1; i <= n; i++) {
        res += (a[i] % x == k);    
    }
    return res;
}

inline void Solve() {
    cin >> n;
    for(reg int i = 1; i <= n; ++i) cin >> a[i];
        
    int ans = ceil(1.0 * n / 2);
    for(reg int K = 1; K <= 50; ++K) {
        int p = rd(), q = rd();
        while(p == q) q = rd();
        int tmp = abs(a[p] - a[q]);
        for(reg int j = 1; prime[j] * prime[j] <= tmp && j <= cnt; ++j) {
            if(tmp % prime[j] == 0) {
                ans = max(ans, calc(prime[j], a[p] % prime[j]));
                while(tmp % prime[j] == 0) tmp /= prime[j];
            }
        }
        if(tmp > 1) ans = max(ans, calc(tmp, a[p] % tmp));
    }
    
    cout << ans << endl;
}

signed main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("1.out", "w", stdout);
    
    //srand( (unsigned)time(NULL) );
    FAST
    Init();
    int TT;
    cin >> TT;
    while(TT--) {
        Solve();
    }
    return 0;
}
```

