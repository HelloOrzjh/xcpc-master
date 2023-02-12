/*
S����С��ʾ����Sѭ��ͬ���������ַ������ֵ�����С���ַ���������ʾͬ�� 
*/
int getMin(string S) {
	int n = S.length(), i = 0, j = 1, k = 0;
	while(i < n && j < n && k < n) {
		if(S[(i + k) % n] == S[(j + k) % n]) k++;
		else {
			if(S[(i + k) % n] > S[(j + k) % n]) i = i + k + 1;
			else j = j + k + 1;
			
			if(i == j) i++;
			k = 0;
		}
	}
	return min(i, j);
}

int getMax(string S) {
  	int n = S.length(), i = 0, j = 1, k = 0;
	while(i < n && j < n && k < n) {
		if(S[(i + k) % n] == S[(j + k) % n]) k++;
		else {
			if(S[(i + k) % n] < S[(j + k) % n]) i = i + k + 1;
			else j = j + k + 1;
			
			if(i == j) i++;
			k = 0;
		}
	}
	return min(i, j);
}


