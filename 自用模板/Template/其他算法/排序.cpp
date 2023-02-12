void QuickSort(int l, int r) { //øÏ≈≈
	int mid = a[(l + r) / 2];
	int i = l, j = r;
	do {
		while(a[i] < mid) i++;
		while(a[j] > mid) j--;
		if(i <= j) swap(a[i], a[j]), i++, j--;
	} while(i <= j);
	if(j > l) QuickSort(l, j);
	if(i < r) QuickSort(i, r);
}

void MergeSort(int l, int r) { //πÈ≤¢≈≈–Ú
	if (l >= r) return;
	int mid = (l + r) >> 1;
	MergeSort(l, mid);
	MergeSort(mid + 1, r);
	int k = 0, i = l, j = mid + 1;
	while(i <= mid && j <= r) {
		if(a[i] <= a[j]) tmp[k++] = a[i++];
		else tmp[k++] = a[j++];
	}
	while(i <= mid) tmp[k++] = a[i++];
	while(j <= r) tmp[k++] = a[j++];
	for(i = l, j = 0; i <= r; i++, j++) a[i] = tmp[j];
}
