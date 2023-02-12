#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;

char S1[MAXN], S2[MAXN];
int l1, l2, pmt[MAXN], p;	//pmt数组(部分匹配表) 向右偏移一位为next数组 并让next[0] = -1

int main()
{
	cin >> S1 + 1 >> S2 + 1;
	l1 = strlen(S1 + 1), l2 = strlen(S2 + 1);
	p = pmt[0] = 0;
	for(int i = 2; i <= l2; i++) {
		while(p && S2[p + 1] != S2[i]) p = pmt[p];
		if(S2[p + 1] == S2[i]) p++;
		pmt[i] = p;
	}
	p = 0;
	for(int i = 1; i <= l1; i++) {
		while(p && S2[p + 1] != S1[i]) p = pmt[p];
		if(S2[p + 1] == S1[i]) p++;
		if(p == l2) {
			printf("%d\n", i - p + 1);
			p = pmt[p];
		}
	}
	for(int i = 1; i <= l2; i++) printf("%d ", pmt[i]);
	return 0;
}
