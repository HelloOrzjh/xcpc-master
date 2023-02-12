int Hash(char ch) { return ch - 'a' + 1; }

void Insert(string S) {
	int u = 0;
	for(auto i : S) {
		if(!trie[u][Hash(i)]) trie[u][Hash(i)] = ++cnt;
		u = trie[u][Hash(i)];
	}
	sum[u]++;
}
