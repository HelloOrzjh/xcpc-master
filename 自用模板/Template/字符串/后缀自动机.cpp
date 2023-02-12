#include<bits/stdc++.h>
#pragma GCC optimize("-Ofast")
using namespace std;
const int MAXN = (int)4e5 + 5;

struct state {
	int len, link, size;
	int next[30];
}st[MAXN << 1];

int sz, last, n, p, q;
long long f[MAXN];
char s[MAXN];

void init() {
	for(int i = 0; i < sz; i++) {
		for(int j = 0; j < 26; j++) st[i].next[j] = 0;
		st[i].len = st[i].link = st[i].size = 0;
	}
	sz = 0;
	
	st[0].len = 0;
	st[0].link = -1;
	sz++;
	last = 0; 
}

void extend(int c) {
	int cur = sz++;
	st[cur].size = 1;
	st[cur].len = st[last].len + 1;
	int p = last;
	while(p != -1 && !st[p].next[c]) {
		st[p].next[c] = cur;
		p = st[p].link;
	} 
	if(p == -1) st[cur].link = 0;
	else {
		int q = st[p].next[c];
		if(st[p].len + 1 == st[q].len) st[cur].link = q;
		else {
			int clone = sz++;
			st[clone].len = st[p].len + 1;
			for(int i = 0; i < 26; i++) st[clone].next[i] = st[q].next[i];
			st[clone].link = st[q].link;
			while(p != -1 && st[p].next[c] == q) {
				st[p].next[c] = clone;
				p = st[p].link;
			}
			st[q].link = st[cur].link = clone;
		}
	}
	last = cur;
}
