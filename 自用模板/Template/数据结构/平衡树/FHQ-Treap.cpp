#include<bits/stdc++.h>
using namespace std;

const int MaxSize = (int)1e5 + 5;
const int INF = 0x3f3f3f3f;

// T为pair等类型时需要重载运算符
template <typename T, int MAXN>
class Treap {
private:
	struct Node {
		T val;
		int ls, rs, sze, priority;
	} tree[MaxSize];
	int seed, tot, root;
	int Top, Stack[MaxSize];
	
	int rand() { return seed = (int)(seed * 104831ll % 0x7fffffff); }
	
	void pushup(int p) {
		if(p) tree[p].sze = tree[ tree[p].ls ].sze + tree[ tree[p].rs ].sze + 1;
	} 
	
	int create(T val) {
		int p = Top ? Stack[Top--] : ++tot;
		tree[p].val = val;
		tree[p].sze = 1;
		tree[p].ls = tree[p].rs = 0;
		tree[p].priority = rand();
		return p;
	}
	
	// 将根为 p 的子树分裂成 x,y 两部分，x子树中全部小于等于val，y子树中全部大于val
	void split(int p, T val, int &x, int &y) {
		if(!p) return void(x = y = 0);
		if(val >= tree[p].val) {
			x = p;
			split(tree[p].rs, val, tree[p].rs, y);
		} else {
			y = p;
			split(tree[p].ls, val, x, tree[p].ls);
		}
		pushup(p);
	}
	/*
	// 将根为 p 的子树分裂成 x,y 两部分，x子树大小为sze
	void split(int p, int sze, int &x, int &y) {
		if(!p) return void(x = y = 0);
		if(tree[ tree[p].ls ].sze + 1 <= sze) {
			x = p;
			split(tree[p].rs, sze - (tree[ tree[p].ls ].sze + 1), tree[p].rs, y);
		} else {
			y = p;
			split(tree[p].ls, sze, x, tree[p].ls);
		}
		pushup(p);
	}
	*/
	int merge(int x, int y) {
		if(!x || !y) return x + y;
		if(tree[x].priority > tree[y].priority) {
			tree[x].rs = merge(tree[x].rs, y);
			pushup(x);
			return x;
		} else {
			tree[y].ls = merge(x, tree[y].ls);
			pushup(y);
			return y;
		}
	}
public:
	Treap() { seed = (int)(MAXN * 565463ll % 0x7fffffff); }
		
	void insert(T val) {
		int x, y;
		split(root, val - 1, x, y);
		root = merge( merge(x, create(val) ), y );
	}
	
	void remove(T val) {
		int x, y, z;
		split(root, val, x, z);
		split(x, val - 1, x, y);
		if(y) {
			Stack[++Top] = y;
			y = merge(tree[y].ls, tree[y].rs);
		}
		root = merge(merge(x, y), z);
	}
	
	int rank(T val) {
		int x, y, res;
		split(root, val - 1, x, y);
		res = tree[x].sze + 1;
		root = merge(x, y);
		return res;
	}
	
	int val(int rank) {
		int p = root;
		while(1) {
			if(tree[ tree[p].ls ].sze + 1 == rank) break;
			if(tree[ tree[p].ls ].sze + 1 > rank) p = tree[p].ls;
			else rank -= (tree[ tree[p].ls ].sze + 1), p = tree[p].rs;
		}
		return tree[p].val;
	}
	
	T prev(T val) {
		int x, y, p; T res;
		split(root, val - 1, x, y);
		p = x;
		while(tree[p].rs) p = tree[p].rs;
		res = tree[p].val;
		root = merge(x, y);
		return res;
	}
	
	T next(T val) {
		int x, y, p; T res;
		split(root, val, x, y);
		p = y;
		while(tree[p].ls) p = tree[p].ls;
		res = tree[p].val;
		root = merge(x, y);
		return res;
	}
	
	bool find(T val) {
		int x, y, z;
		split(root, val, x, z);
		split(x, val - 1, x, y);
		bool res = (tree[y].sze > 0);
		root = merge(merge(x, y), z);
		return res;
	}
	
	int size() { return tree[root].sze; }
};

Treap<int, 100005> fhqTreap;

signed main()
{
	int q, opt, x; scanf("%d", &q);
	while(q--) {
		scanf("%d%d", &opt, &x);
		switch(opt) {
			case 1 : fhqTreap.insert(x); break;
			case 2 : fhqTreap.remove(x); break;
			case 3 : printf("%d\n", fhqTreap.rank(x) ); break;
			case 4 : printf("%d\n", fhqTreap.val(x) ); break;
			case 5 : printf("%d\n", fhqTreap.prev(x) ); break;
			case 6 : printf("%d\n", fhqTreap.next(x) ); break;
		}
	}
	return 0;
}
