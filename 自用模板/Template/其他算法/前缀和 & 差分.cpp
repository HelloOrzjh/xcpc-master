// 二维前缀和 & 二维差分
sum[i][j] = a[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
d[i][j] = a[i][j] - a[i - 1][j] - a[i][j - 1] + a[i - 1][j - 1];

int QuerySum() {
	// 以(x1, y1)为左上角，(x2, y2)为右下角的子矩阵的和为：
	return sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
}
void ModifyD() {
	// 给以(x1, y1)为左上角，(x2, y2)为右下角的子矩阵中的所有元素加上c：
	d[x1][y1] += c, d[x2 + 1][y1] -= c, d[x1][y2 + 1] -= c, d[x2 + 1][y2 + 1] += c;
}

/*
树上差分
注意对差分数组进行前缀和操作，得到原数组时顺序是 自叶子节点开始 到 根结束 ！
*/
void SolveNode(int u, int v, int t) { //u--v之间的点全部加上c
	val[u] += t, val[v] += t;
	int lca = LCA(u, v);
	val[lca] -= t, val[fa[lca]] -= t;
}

void SolveEdge(int u, int v, int t) { //u--v之间的边全部加上c
	val[u] += t, val[v] += t;
	val[LCA(u, v)] -= 2 * t;
}