#include<bits/stdc++.h>

using namespace std;

const int SIZE = (int)1e5 + 5;
const int INF = 0x3f3f3f3f;

int son[SIZE][2], fa[SIZE];	// 左右子节点(son[0]代表左儿子，son[1]代表右儿子)、父亲节点
int val[SIZE];	// 权值 
int cnt[SIZE], size[SIZE];	// 副本数、子树大小 
int tot = 0, root = 0;	// 节点个数、根节点 
int n;

void Update(int p) {	// 更新子树大小 
	size[p] = size[ son[p][0] ] + size[ son[p][1] ] + cnt[p];
}

bool CheckRson(int p) {	// 判断节点p是不是右儿子 
	return p == son[ fa[p] ][1];
}

void Clear(int p) {	// 销毁节点p 
	son[p][0] = son[p][1] = fa[p] = val[p] = cnt[p] = size[p] = 0;
}

void Rotate(int p) {	//旋转p(根据p的儿子类型判断左旋还是右旋) 
	int f = fa[p], gf = fa[f];	// f->father gf->grandfather
	bool isRson = CheckRson(p);
	son[f][isRson] = son[p][isRson ^ 1];
	if(son[p][isRson ^ 1]) fa[ son[p][isRson ^ 1] ] = f;
	son[p][isRson ^ 1] = f;
	fa[f] = p, fa[p] = gf;
	if(gf) son[gf][ f == son[gf][1] ] = p;
	Update(p), Update(f);
}

void Splay(int p, int target = 0) { 	// 节点p旋转到节点target target=0表示根节点 
	for(int f = fa[p]; (f = fa[p]) != target, f; Rotate(p)) {
		if(fa[f] != target) Rotate( CheckRson(p) == CheckRson(f) ? f : p );
	}
	if(!target) root = p;
}

int GetPre() {	// 求x的前驱(将x插入 查询x左子树中最右边的节点 删除x)
	int cur = son[root][0];
	if(!cur) return cur;
	while(son[cur][1]) cur = son[cur][1];
	Splay(cur);
	return cur;
}

int GetNext() {	// 求x的前驱(将x插入 查询x右子树中最左边的节点 删除x)
	int cur = son[root][1];
	if(!cur) return cur;
	while(son[cur][0]) cur = son[cur][0];
	Splay(cur);
	return cur;
}

int GetRankByVal(int k) {	// 查询k数的排名 
	int res = 0, cur = root;
	while(1) {
		if(k < val[cur]) cur = son[cur][0];
		else {
			res += size[ son[cur][0] ];
			if(k == val[cur]) {
				Splay(cur);
				return res + 1;
			}
			res += cnt[cur];
			cur = son[cur][1];
		}
	}
}

int GetValByRank(int k) {	// 查询排名为k的数 
	int cur = root;
	while(1) {
		if(son[cur][0] && k <= size[ son[cur][0] ]) cur = son[cur][0];
		else {
			k -= size[ son[cur][0] ] + cnt[cur];
			if(k <= 0) {
				Splay(cur);
				return val[cur];
			}
			cur = son[cur][1];
		}
	}
}

void Insert(int k) {	// 插入k数
	if(!root) {
		val[++tot] = k, ++cnt[tot];
		root = tot, Update(root);
		return ;
	}
	int cur = root, f = 0;
	while(1) {
		if(val[cur] == k) {
			++cnt[cur];
			Update(cur), Update(f);
			Splay(cur);
			break;
		}
		f = cur;
		cur = son[cur][ val[cur] < k ];
		if(cur == 0) {
			val[++tot] = k, ++cnt[tot];
			fa[tot] = f, son[f][ val[f] < k ] = tot;
			Update(tot), Update(f);
			Splay(tot);
			break;
		}
	}
}

void Remove(int k) {	// 删除k数 
	GetRankByVal(k);
	if(cnt[root] > 1) {
		--cnt[root];
		Update(root);
		return ;
	}
	if(son[root][0] == 0 && son[root][1] == 0) {
		Clear(root);
		root = 0;
	} else if(son[root][0] == 0) {
		int cur = root;
		root = son[root][1];
		fa[root] = 0;
		Clear(cur);
	} else if(son[root][1] == 0) {
		int cur = root;
		root = son[root][0];
		fa[root] = 0;
		Clear(cur);
	} else {
		int cur = root, pre = GetPre();
		fa[ son[cur][1] ] = pre;
		son[pre][1] = son[cur][1];
		Clear(cur);
		Update(root);
	}
}

signed main()
{
	scanf("%d", &n);
	while(n--) {
		int opt, x;
		scanf("%d%d", &opt, &x);
		switch(opt) {
			case 1 : Insert(x); break;
			case 2 : Remove(x); break;
			case 3 : printf("%d\n", GetRankByVal(x) ); break;	// 存在-INF 
			case 4 : printf("%d\n", GetValByRank(x) ); break;	// 存在-INF 
			case 5 : Insert(x), printf("%d\n", val[GetPre()] ), Remove(x); break;
			case 6 : Insert(x), printf("%d\n", val[GetNext()] ), Remove(x); break;
		}
	}
	return 0;
}
