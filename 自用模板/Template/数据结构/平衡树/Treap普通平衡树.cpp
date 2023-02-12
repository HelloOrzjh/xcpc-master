#include<bits/stdc++.h>

using namespace std;

const int SIZE = (int)1e5 + 5;
const int INF = 0x3f3f3f3f;

struct Treap {
	int l, r;	// �����ӽڵ� 
	int val, dat;	// �ؼ��롢Ȩֵ 
	int cnt, size;	//  ��������������С 
}a[SIZE];
int tot = 0, root, n;

int New(int val) {	// �����½ڵ� 
	a[++tot].val = val;
	a[tot].dat = rand();
	a[tot].cnt = a[tot].size = 1;
	return tot;
}

void Update(int p) {	// ����������С 
	a[p].size = a[ a[p].l ].size + a[ a[p].r ].size + a[p].cnt;
}

void Build() {	// ���� 
	New(-INF), New(INF);
	root = 1, a[1].r = 2;
	Update(root);
}

void zig(int &p) {	// ���� 
	int q = a[p].l;
	a[p].l = a[q].r, a[q].r = p, p = q;
	Update(a[p].r), Update(p);
}

void zag(int &p) {	// ���� 
	int q = a[p].r;
	a[p].r = a[q].l, a[q].l = p, p = q;
	Update(a[p].l), Update(p);
}

void Insert(int &p, int val) {	// ����val��
	if(p == 0) {
		p = New(val);
		return ;
	}
	if(val == a[p].val) {
		a[p].cnt++, Update(p);
		return ;
	}
	
	if(val < a[p].val) {
		Insert(a[p].l, val);
		if( a[p].dat < a[ a[p].l ].dat ) zig(p);	// �������������� ���� 
	} else {
		Insert(a[p].r, val);
		if( a[p].dat < a[ a[p].r ].dat ) zag(p);	// �������������� ����		
	}
	Update(p);
}

void Remove(int &p, int val) {	// ɾ��val�� 
	if(p == 0) return ;
	if(val == a[p].val) {
		if(a[p].cnt > 1) {
			a[p].cnt--, Update(p);
			return ;
		}
		if(a[p].l || a[p].r) {	// ����Ҷ�ӽڵ� 
			if(a[p].r == 0 || a[ a[p].l ].dat > a[ a[p].r ].dat ) 
				zig(p), Remove(a[p].r, val);	// ����
			else 
				zag(p), Remove(a[p].l, val);	// ���� 
			
			Update(p);
		} else p = 0;
		return ;
	}
	
	val < a[p].val ? Remove(a[p].l, val) : Remove(a[p].r, val);
	Update(p);
}

int GetRankByVal(int p, int val) {	// ��ѯval�������� 
	if(p == 0) return 0;
	if(val == a[p].val) return a[ a[p].l ].size + 1;
	if(val < a[p].val) return GetRankByVal(a[p].l, val);
	else return GetRankByVal(a[p].r, val) + a[ a[p].l ].size + a[p].cnt;
}

int GetValByRank(int p, int rank) {	// ��ѯ����Ϊrank���� 
	if(p == 0) return 0;
	if(a[ a[p].l ].size >= rank) return GetValByRank(a[p].l, rank);
	else if(a[ a[p].l ].size + a[p].cnt >= rank) return a[p].val;
	else return GetValByRank(a[p].r, rank - a[ a[p].l ].size - a[p].cnt);
}

int GetPre(int val) {	// ��val��ǰ�� 
	int ans = 1;	// a[ans].val == -INF;
	int p = root;
	while(p) {
		if(val == a[p].val) {
			if(a[p].l > 0) {
				p = a[p].l;
				while(a[p].r > 0) p = a[p].r;	// ��������һֱ������
				ans = p; 
			}
			break;
		}
		if(a[p].val < val && a[p].val > a[ans].val) ans = p;	// ���´� 
		
		val < a[p].val ? p = a[p].l : p = a[p].r;
	}
	return a[ans].val;
}

int GetNext(int val) {	// ��val�ĺ�� 
	int ans = 2;	// a[ans].val = INF;
	int p = root;
	while(p) {
		if(val == a[p].val) {
			if(a[p].r > 0) {
				p = a[p].r;
				while(a[p].l > 0) p = a[p].l;
				ans = p;
			}
			break;
		}
		if(a[p].val > val && a[p].val < a[ans].val) ans = p;
		
		val < a[p].val ? p = a[p].l : p = a[p].r;
	}
	return a[ans].val;
}

signed main()
{
	Build();
	srand((unsigned)time(NULL));
	scanf("%d", &n);
	while(n--) {
		int opt, x;
		scanf("%d%d", &opt, &x);
		switch(opt) {
			case 1 : Insert(root, x); break;
			case 2 : Remove(root, x); break;
			case 3 : printf("%d\n", GetRankByVal(root, x) - 1 ); break;	// ����-INF 
			case 4 : printf("%d\n", GetValByRank(root, x + 1) ); break;	// ����-INF 
			case 5 : printf("%d\n", GetPre(x) ); break;
			case 6 : printf("%d\n", GetNext(x) ); break;
		}
	}
	return 0;
}
