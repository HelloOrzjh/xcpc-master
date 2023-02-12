#include<bits/stdc++.h>

using namespace std;

const int SIZE = (int)1e5 + 5;
const int INF = 0x3f3f3f3f;

int son[SIZE][2], fa[SIZE];	// 左右子节点(son[0]代表左儿子，son[1]代表右儿子)、父亲节点
int val[SIZE];	// 权值 
int cnt[SIZE], size[SIZE];	// 副本数、子树大小 
bool tag[SIZE]; 	// 标记 
int tot = 0, root = 0;	// 节点个数、根节点 
int n, m, a[SIZE];

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

void Splay(int p, int target = 0) { 	// 节点p旋转到节点target的儿子下面 target=0表示根节点 
	for(int f; (f = fa[p]) != target; Rotate(p)) {
		if(fa[f] != target) Rotate( CheckRson(p) == CheckRson(f) ? f : p );
	}
	if(!target) root = p;
}

void PushDown(int p) {	// 下传反转标记 
	if(p && tag[p]) {
		int ls = son[p][0];
		int rs = son[p][1];
		tag[ls] ^= 1;
		tag[rs] ^= 1;
		swap(son[p][0], son[p][1]);
		tag[p] = 0;
	}
}

int FindNodeByRank(int k) {	// 查询值为k的节点 
	int cur = root;
	while(1) {
		PushDown(cur);
		if(son[cur][0] && k <= size[ son[cur][0] ]) cur = son[cur][0];
		else {
			k -= size[ son[cur][0] ] + 1;
			if(!k) return cur;
			else cur = son[cur][1];
		}
	}
}

int Build(int l, int r, int f) {	// 建树 
	if(l > r) return 0;
	int mid = l + r >> 1;
	int cur = ++tot;
	fa[cur] = f;
	cnt[cur] = 1;
	tag[cur] = 0;
	val[cur] = a[mid];	
	son[cur][0] = Build(l, mid - 1, cur);
	son[cur][1] = Build(mid + 1, r, cur);
	Update(cur);
	return cur;
}

void Traverse(int p) {	// 中序遍历 
	if(!p) return ;
	PushDown(p); 
	Traverse(son[p][0]);
	if(abs(val[p]) < INF) printf("%d ", val[p]);
	Traverse(son[p][1]);
}

void Reverse(int l, int r) {	// 反转区间[l,r] 
	int x = FindNodeByRank(l - 1 + 1);	// 存在-INF 
	int y = FindNodeByRank(r + 1 + 1);
	Splay(x, 0);
	Splay(y, x);
	PushDown(root);
	tag[ son[ son[root][1] ][0] ] ^= 1;
}

signed main()
{
	scanf("%d%d", &n, &m);
	a[1] = -INF, a[n + 2] = INF;
	for(int i = 1; i <= n; i++) a[i + 1] = i;
	root = Build(1, n + 2, 0);
	while(m--) {
		int l, r;
		scanf("%d%d", &l, &r);
		Reverse(l, r);
	}
	Traverse(root);
	return 0;
}
