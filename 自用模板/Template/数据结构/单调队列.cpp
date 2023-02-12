void QueryMin() {
	memset(Index, 0, sizeof(Index)); memset(Value, 0, sizeof(Value));
	int head = 1, tail = 0;
	for(int i = 1; i <= n; i++) {
		while(head <= tail && Index[head] < i - k + 1) head++;
		while(head <= tail && Value[tail] > a[i]) tail--; 
		Index[++tail] = i;
		Value[tail] = a[i];
	}
}

void QueryMax() {
	memset(Index, 0, sizeof(Index)); memset(Value, 0, sizeof(Value));
	int head = 1, tail = 0;
	for(int i = 1; i <= n; i++) {
		while(head <= tail && Index[head] < i - k + 1) head++;
		while(head <= tail && Value[tail] < a[i]) tail--;
		Index[++tail] = i;
		Value[tail] = a[i];
	}
}

void Init() {
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	QueryMin(); QueryMax();
}

