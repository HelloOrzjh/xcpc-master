//#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2010, MAXM = 2010;

struct Node {
	char ch[MAXM + 5];
	int sze, lnode, rnode;	
	void push_back(char c) { ch[sze++] = c; }
}p[MAXN + 5];

int pos1 = 0, pos2 = 0;	//光标在块中/块内位置
int id[MAXN + 5], idx = 0; //可分配的编号池

void Add(int u, int v) {	//将节点v插到节点u的右边
	p[v].rnode = p[u].rnode; 
	p[ p[v].rnode ].lnode = v;
	p[u].rnode = v; 
	p[v].lnode = u;
}

void Del(int u) {	//删除节点u
	p[ p[u].lnode ].rnode = p[u].rnode;
	p[ p[u].rnode ].lnode = p[u].lnode;
	p[u].lnode = p[u].rnode = p[u].sze = 0;
	id[++idx] = u;
}

void Merge() {
	for(int k = p[0].rnode; k; k = p[k].rnode) {
		while(p[k].rnode && p[k].sze + p[ p[k].rnode ].sze < MAXM) {
			int rnode = p[k].rnode;
			if(pos1 == rnode) pos1 = k, pos2 += p[k].sze;	// 与下一条语句顺序不能调换
			for(int i = 0; i < p[rnode].sze; i++) p[k].push_back( p[rnode].ch[i] ); 
			Del(rnode);
		}
	}
}

void Move(int k) {	//移动到第k个字符后面
	pos1 = p[0].rnode;
	while (k > p[pos1].sze) k -= p[pos1].sze, pos1 = p[pos1].rnode;
	pos2 = k - 1;
}

void Insert(string S, int n) {	//在光标后面插入字符串S, 长度为n
	if(pos2 + 1 != p[pos1].sze) {	//分裂
		int u = id[idx--];
		for(int i = pos2 + 1; i < p[pos1].sze; i++) p[u].push_back( p[pos1].ch[i] );
		p[pos1].sze = pos2 + 1;
		Add(pos1, u);
	}
	int cur = pos1, i = 0;
	while(i < n) {
		int u = id[idx--];
		for(; i < n && p[u].sze < MAXN; i++) p[u].push_back(S[i]);
		Add(cur, u);
		cur = u;
	}
	Merge();
}

void Delete(int n) {	//删除光标后的n个字符
	if(pos2 + 1 + n <= p[pos1].sze) {
		for(int i = pos2 + 1, j = pos2 + 1 + n; j < p[pos1].sze; i++, j++) {
			p[pos1].ch[i] = p[pos1].ch[j];
		}
		p[pos1].sze -= n;
	} else {
		n -= (p[pos1].sze - pos2 - 1);
		p[pos1].sze = pos2 + 1;
		while(p[pos1].rnode && n >= p[ p[pos1].rnode ].sze) {
			n -= p[ p[pos1].rnode ].sze;
			Del(p[pos1].rnode);
		}
		int u = p[pos1].rnode;
		for(int i = 0, j = n; j < p[u].sze; i++, j++) {
			p[u].ch[i] = p[u].ch[j];
		}
		p[u].sze -= n;
	}
	Merge();
}

void Get(int n) {	//获取光标后n个字母
	if(pos2 + 1 + n <= p[pos1].sze) {
		for(int i = pos2 + 1; i <= pos2 + n; i++) cout << p[pos1].ch[i];
	} else {
		n -= (p[pos1].sze - pos2 - 1);
		for(int i = pos2 + 1; i < p[pos1].sze; i++) cout << p[pos1].ch[i];
		int cur = pos1;
		while(p[cur].rnode && n >= p[ p[cur].rnode ].sze) {
			n -= p[ p[cur].rnode ].sze;
			for(int i = 0; i < p[ p[cur].rnode ].sze; i++) cout << p[ p[cur].rnode ].ch[i];
			cur = p[cur].rnode;
		}
		int u = p[cur].rnode;
		for(int i = 0; i < n; i++) cout << p[u].ch[i];
	}
	cout << "\n";
}

void Prev() {	//光标前移
	if(pos2) pos2--;
	else pos1 = p[pos1].lnode, pos2 = p[pos1].sze - 1; 
}

void Next() {	//光标后移
	if(pos2 != p[pos1].sze - 1) pos2++;
	else pos1 = p[pos1].rnode, pos2 = 0;
}

void Solve() {
	for(int i = 1; i <= MAXN; i++) id[++idx] = i;
	Insert("\n", 1); Move(1);	//预防越界
	int t; cin >> t;
	while(t--) {
		string op, S;
		int n;
		cin >> op;
		if(op == "Insert") {
			cin >> n;
			int cur = 0; S = "";
			while(cur < n) {
				char ch = getchar();
				if(32 <= ch && ch <= 126) S.push_back(ch), cur++;
			}
			Insert(S, n);
		} 
		else if(op == "Move") cin >> n, Move(n + 1);
		else if(op == "Delete") cin >> n, Delete(n);
		else if(op == "Get") cin >> n, Get(n);
		else if(op == "Prev") Prev();
		else if(op == "Next") Next();	
	}
}

signed main() { Solve(); return 0; }