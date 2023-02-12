/*
悬线法的用途：针对求给定矩阵中满足某条件的极大矩阵，比如“面积最大的长方形、正方形”“周长最长的矩形”等等。适合障碍点较密集的情况。
设给定一个n*m的矩形，其中存在障碍点若干。
维护三个二维数组，left,right,up数组。
left[i][j]: 代表从(i, j)能到达的最左位置 初始left[i][j] = j;
right[i][j]: 代表从(i, j)能到达的最右位置 初始right[i][j] = j;
up[i][j]: 代表从(i, j)向上扩展最长长度 初始up[i][j] = 1;
*/

void Solve() {
	for(int i = 1; i <= n; i++) for(int j = 2; j <= m; j++) left[i][j] = right[i][j] = j, up[i][j] = 1;

	for(int i = 1; i <= n; i++) {
		for(int j = 2; j <= m; j++) if(map[i][j]和map[i][j - 1]不是障碍点) left[i][j] = left[i][j - 1];
		for(int j = m - 1; j >= 1; j--) if(map[i][j]和map[i][j + 1]不是障碍点) right[i][j] = right[i][j + 1];
	}
	
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(map[i][j]和map[i - 1][j]都不是限制点) {
				up[i][j] = up[i - 1][j] + 1;
				left[i][j] = max(left[i][j], left[i - 1][j]);
				right[i][j] = min(right[i][j], right[i - 1][j]);
			}
			int width = (right[i][j] - left[i][j] + 1);
			ans = max(ans, width * up[i][j]); //求矩形
		}
	}
}
