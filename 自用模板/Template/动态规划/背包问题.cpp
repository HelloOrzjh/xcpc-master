/*
N种物品 容量为V的背包 第i种物品的代价为w[i] 价值为v[i] 数量为m[i] 
*/

void Prework() {
	dp[0] = 0;
	for(int i = 1; i <= V; i++) {
		//dp[i] = INF;	//要求必须装满背包 
		dp[i] = 0;	//不一定要装满背包 
	}
}

void ZeroOnePack() {	//01背包
	Prework();
	for(int i = 1; i <= N; i++) {
		for(int j = V; j >= w[i]; j--) {
			dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
		}
	}
}

void CompletePack() {	//完全背包 
	Prework();
	for(int i = 1; i <= N; i++) {
		for(int j = w[i]; j <= V; j++) {
			dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
		}
	}
}

void MultiplePack() {	//多重背包 利用二进制优化 
	Prework();
	
	int cnt = 0;
	for(int i = 1; i <= N; i++) {
		int cur = 1;	//将cur个相同物品合并 
		int cur_w, cur_v;
		while(m[i] >= cur) {
			cur_w = w[i] * cur;
			cur_v = v[i] * cur;
			for(int j = V; j >= cur_w; j--) {
				dp[j] = max(dp[j], dp[j - cur_w] + cur_v);
			}
			m[i] -= cur;
			cur <<= 1;	 
		}
		
		cur_w = w[i] * m[i];
		cur_v = v[i] * m[i];
		for(int j = V; j >= cur_w; j--) {
			dp[j] = max(dp[j], dp[j - cur_w] + cur_v);
		}
	}
	
}

void MixedPack() {	//混合背包 
	for(int i = 1; i <= n; i++) {
		if(m[i] == 0) {	
			//代表无限个 采用完全背包策略 
			for(int j = w[i]; j <= V; j++) {
				dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
			}	
		} else if(m[i] == 1) {	
			//01背包策略 
			for(int j = V; j >= w[i]; j--) {
				dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
			}			
		} else if(m[i] > 1) {		
			//多重背包策略 
			int cur = 1;	//将cur个相同物品合并 
			int cur_w, cur_v;
			while(m[i] >= cur) {
				cur_w = w[i] * cur;
				cur_v = v[i] * cur;
				for(int j = V; j >= cur_w; j--) {
					dp[j] = max(dp[j], dp[j - cur_w] + cur_v);
				}
				m[i] -= cur;
				cur <<= 1;	 
			}
		
			cur_w = w[i] * m[i];
			cur_v = v[i] * m[i];
			for(int j = V; j >= cur_w; j--) {
				dp[j] = max(dp[j], dp[j - cur_w] + cur_v);
			}
		}
	}
}

void TwoDimensionPack() {	
	/*
	二维费用背包问题
	设第二维容量为T 第i个物品的代价为g[i]
	
	01背包下变量j和k采用逆序循环
	完全背包下采用顺序循环
	多重背包时拆分物品
	*/
	
	for(int i = 1; i <= n; i++) {	//二维01背包 
		for(int j = V; j >= w[i]; j--) {
			for(int k = T; k >= g[i]; k--) {
				dp[j][k] = max(dp[j][k], dp[j - w[i]][k - g[i]]);
			}
		}
	}
	 
} 

void DivideGroupPack() {	//分组背包
	/*
	这些物品被划分为若干组，每组中的物品互相冲突，最多选一件。
	求解将哪些物品装入背包可使这些物品的费用总和不超过背包容量，且价值总和最大。
	
	设第i件物品的类型为type[i]，共有k个类型。
	每组物品有若干种策略：是选择本组的某一件，还是一件都不选。
	设dp[i][j]表示前i组物品花费代价j所获得的最大价值
	dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[cur]] + v[cur]);
	cur代表属于组别i的当前物品
	可用滚动数组优化 优化时注意三层循环的顺序不能更改 
	*/ 
	
	for(int i = 1; i <= N; i++) Items[ type[i] ].push_back(i);	//进行分类 
	
	for(int i = 1; i <= K; i++) {
		int num = Items[i].size();
		for(int j = V; j >= 0; j--) {
			for(int k = 0; k < num; k++) {
				//对k的循环要在对j的循环里面 这样能保证每个组别最多选一个物品 
                int cur = Items[i][k];
				if(w[cur] > j) continue;
				dp[j] = max(dp[j], dp[j - w[cur]] + v[cur]);
			}
		}
	}
	
}

void PackOnTree(int u) {	//树上背包 利用上下界优化 
	Size[u] = 1;
	for(int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		PackOnTree(v);
		for(int j = min(m + 1, Size[u] + Size[v]); j >= 0; j--) {
			for(int k = max(1, j - Size[u]); k < j && k <= Size[v]; k++) {
				f[u][j] = max(f[u][j], f[u][j - k] + f[v][k]);
			}
		}
		Size[u] += Size[v];
	}
}

void RollbackPack() {	//回退背包
	// select
	for(int i = son[u]; i >= 1; i--) {
		for(int j = sze[u]; j >= sze[v]; j--) f[i][j] = (f[i][j] + f[i - 1][j - sze[v] ]) % MOD;
	}
	
	// delete
	for(int i = 1; i <= son[u]; i++) {
		for(int j = sze[v]; j <= sze[u]; j++) f[i][j] = (f[i][j] - f[i - 1][j - sze[v] ] + MOD) % MOD;
	} 
}