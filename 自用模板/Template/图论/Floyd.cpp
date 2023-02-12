void Solve1() {
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if(i == j) dp[i][j] = 0;
			else dp[i][j] = INF;
		}
	}
	for(int k = 1; k <= n; k++) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
			}
		}
	}
}

/*
已知一个有向图中任意两点之间是否有连边，要求判断任意两点是否连通。
Floyd实现传递闭包 bitset优化 
*/
void Solve2()
{
	for(int k = 1; k <= n; k++) {
		for(int i = 1; i <= n; i++) {
			if(G[i][k]) G[i] |= G[k];
		}
	} 
	for(int k = 1; k <= n; k++) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				G[i][j] |= G[i][k] & G[k][j];
			}
		}
	}
	
}


