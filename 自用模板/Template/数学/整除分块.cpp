for(int l = 1, r; l <= n; l = r + 1) r = n / (n / l);	// [l, r]为当前整除分块 区间内每个 n / i 相同 
