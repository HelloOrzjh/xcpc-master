/* 
定义函数f[i]代表数列中第i个元素之后第一个大于a[i]的元素的下标 求(f数组)
*/
void Query() {
	int top = 0;
	for(int i = 1; i <= n; i++) {
		while(top > 0 && Value[top] < a[i]) { //单调栈保持降序
			f[Index[top]] = i;
			top--;
		}
		Value[++top] = a[i];
		Index[top] = i;
	}
}
