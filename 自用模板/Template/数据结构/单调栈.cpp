/* 
���庯��f[i]���������е�i��Ԫ��֮���һ������a[i]��Ԫ�ص��±� ��(f����)
*/
void Query() {
	int top = 0;
	for(int i = 1; i <= n; i++) {
		while(top > 0 && Value[top] < a[i]) { //����ջ���ֽ���
			f[Index[top]] = i;
			top--;
		}
		Value[++top] = a[i];
		Index[top] = i;
	}
}
