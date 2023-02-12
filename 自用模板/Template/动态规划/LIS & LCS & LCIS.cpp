/* 
LIS O(nlogn)ʵ�� 
��һ���������������������
�ڶ��������������������

input: 389 207 155 300 299 170 158 65
output: 6 2

f[i]��������������г���Ϊiʱ���ŵ�ĩβԪ��
lenΪ����������еĳ���
���������������Ϊ��
�ٵ�a[i] <= f[len] ˵�����Խ��ں���
�ڵ�a[i] > f[len] ��f���ҵ���һ��С��a[i]���� ���滻Ϊa[i]
*/

int LIS() {
	n = 0; while(cin >> a[++n]); n--;
	for(int i = 1; i <= n; i++) cout << a[i] << " "; cout << endl;
	printf("%d\n%d", LIS_Solve1(), LIS_Solve2());
	//problem1
	int len = 1; f[1] = a[1];
	for(int i = 2; i <= n; i++) {
		if(a[i] <= f[len]) f[++len] = a[i];
		else f[upper_bound(f + 1, f + 1 + len, a[i], greater<int>() ) - f] = a[i];
	}
	return len;
	//problem2
	int len = 1; f[1] = a[1];
	for(int i = 2; i <= n; i++) {
		if(a[i] > f[len]) f[++len] = a[i];
		else f[lower_bound(f + 1, f + 1 + len, a[i]) - f] = a[i];
	}
	return len;
}

int LCS() {
	scanf("%s%s", S + 1, T + 1);
	int sLen = strlen(S + 1), tLen = strlen(T + 1);
	for(int i = 1; i <= sLen; i++) {
		for(int j = 1; j <= tLen; j++) {
			if(S[i] == T[j]) dp[i][j] = dp[i - 1][j - 1] + 1;
			else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	// ��¼·�� 
	int p = 0, px = sLen, py = tLen;
	while(px != 0 && py != 0) {
		if(dp[px][py] == dp[px][py - 1]) py--;
		else if(dp[px][py] == dp[px - 1][py]) px--;
		else if(dp[px][py] == dp[px - 1][py - 1] + 1) {
			ans[++p] = S[px];
			px--, py--;
		}
	}
	for(int i = p; i >= 1; i--) printf("%c", ans[i]);	
}
	
void LCIS() { 	// O(nm)
	a[0] = b[0] = -1;
	scanf("%d", &n); for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	scanf("%d", &m); for(int i = 1; i <= m; i++) scanf("%d", &b[i]);	
	
	for(int i = 1; i <= n; i++) {
		int curmax = dp[i - 1][0] + 1, curpos = 0;
		for(int j = 1; j <= m; j++) {
			if(a[i] == b[j]) {
				if(curmax > dp[i][j]) dp[i][j] = curmax, pre[i][j] = curpos;
			} else dp[i][j] = dp[i - 1][j], pre[i][j] = pre[i - 1][j];
			
			if(b[j] < a[i] && curmax < dp[i - 1][j] + 1) curmax = dp[i - 1][j] + 1, curpos = j;
		}
	}

	int ans = 0, pos = 0;
	for(int i = 1; i <= m; i++) if(ans < dp[n][i]) ans = dp[n][i], pos = i;
	printf("%d\n", ans);
	
	while(pos) vec.push_back(b[pos]), pos = pre[n][pos];
	reverse(vec.begin(), vec.end());
	for(auto i : vec) printf("%d ", i);	
}
