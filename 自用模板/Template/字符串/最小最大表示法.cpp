/*
S的最小表示：与S循环同构的所有字符串中字典序最小的字符串（最大表示同理） 
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


