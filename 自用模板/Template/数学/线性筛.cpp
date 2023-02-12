#include<bits/stdc++.h>

using namespace std;

const int MAXN = 2e7 + 5;

int n, m, isprime[MAXN], prime[MAXN], cnt;

void Init(int n = 2e7) {
	cnt = 0;
	isprime[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!isprime[i]) prime[++cnt] = i;
		for(int j = 1; j <= cnt && i * prime[j] <= n; j++) {
			isprime[i * prime[j]] = 1;
			if(i % prime[j] == 0) break;
		}
	}
	//for(int i = 1; i <= cnt; i++) cout << prime[i] << " "; cout << endl;
}

int main()
{
	scanf("%d", &n);
	Init(n);
	return 0;
}
