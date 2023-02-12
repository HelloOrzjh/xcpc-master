const double eps = 1e-10;
double l, r, a[MAXN];
int n;
double F(double x) {}

void Solve() {
	// ������������a�в��� >=x ��������С��һ�� 
	while(l < r) {
		int mid = l + r >> 1;
		if(a[mid] >= x) r = mid;
		else l = mid + 1;
	}
	
	// ������������a�в��� <=x ����������һ��
	while(l < r) {
		int mid = l + r + 1 >> 1;
		if(a[mid] <= x) l = mid;
		else r = mid - 1;
	}
}

void Solve() {	
	// ���������� �󵥷庯���ļ���ֵ
	while(r - l > eps) {
		double lmid = 1.0 * l + 1.0 * (r - l) / 3.0;
		double rmid = 1.0 * r - 1.0 * (r - l) / 3.0;
		if(F(lmid) > F(rmid)) r = rmid;
		else l = lmid;
	}
	
	// �������� ע�����б߽�ȸ������ �϶���
	while(l < r) {
		int lmid = l + (r - l) / 3;
		int rmid = r - (r - l) / 3;
		if(F(lmid) > F(rmid)) r = rmid;
		else l = lmid;		
	}
}
