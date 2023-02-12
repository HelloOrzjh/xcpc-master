/*
Manacher算法:
先在两个字符串中插入某个字符('$') 避免分别处理奇回文和偶回文的情况
设置两个指针maxR(前i个字符能回文扩展到的最右端) pos(前i个字符中哪个字符能回文扩展到最右端)

每次扫描到第i个字符时
①如果i<maxR,更新f[i] ②暴力拓展maxR(maxR从起点到终点且不会往回退) ③maxR增大时更新maxR和pos
*/

#include<bits/stdc++.h>
using namespace std;

const int MAXN = (int)1.1e7 + 5;
char S[MAXN << 1], T[MAXN << 1];
int f[MAXN << 1], n;

void Manacher() {
	T[0] = '#'; T[1] = '$';
	for(int i = 1; i <= n; i++) T[i * 2] = S[i], T[i * 2 + 1] = '$';
	n = n * 2 + 1;
	for(int i = 0; i <= n; i++) S[i] = T[i];
	
	int maxR = 0, pos = 0;
	for(int i = 1; i <= n; i++) {
		if(i < maxR) f[i] = min(f[pos * 2 - i], maxR - i);
		while(i - f[i] - 1 > 0 && i + f[i] + 1 <= n && S[i + f[i] + 1] == S[i - f[i] - 1]) f[i]++;
		if(i + f[i] > maxR) maxR = i + f[i], pos = i;
	}
}

int main()
{
	scanf("%s", S + 1); n = strlen(S + 1);
	Manacher();
	int ans = 0;
	for(int i = 1; i <= n; i++) ans = max(ans, f[i]);
	printf("%d", ans);
	return 0;
}

