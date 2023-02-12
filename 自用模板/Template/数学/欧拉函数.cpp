int phi(int n) {
    int res = n;
    for(int i = 2; i * i <= n; i++) {
        if(n % i == 0) res = res / i * (i - 1);
        while(n % i == 0) n /= i;
    }
    if(n > 1) res = res / n * (n - 1);
    return res;
}

int phi[MAXN];
void init(int n) {
    // 复杂度 O(nloglogn)
    for(int i = 1; i <= n; i++) phi[i] = i; // 除1外没有数的欧拉函数是本身，所以如果phi[i] = i则说明未被筛到
    for(int i = 2; i <= n; i++) {
        if(phi[i] == i) { // 未被筛到
            for(int j = i; j <= n; j += i) phi[j] = phi[j] / i * (i - 1); // 所有含有该因子的数都进行一次操作
        }
    }

    // 复杂度 O(n)
    phi[1] = 1;
    for(int i = 2; i <= n; i++) {
        if(!isnp[i]) primes.push_back(i), phi[i] = i - 1;
        for(int p : primes) {
            if(p * i > n) break;
            isnp[p * i] = 1;
            if(i % p == 0) {
                phi[p * i] = phi[i] * p;
                break;
            } else {
                phi[p * i] = phi[p] * phi[i];
            }
        }
    }
}

int EulerPow(int a, string b, int MOD) {
    int phiMOD = phi(MOD), power = 0, flag = 0;
    for(auto i : b) {
        power = power * 10 + i - '0';
        if(power >= phiMOD) flag = 1;
        power %= phiMOD;
    }
    if(flag) power += phiMOD;
    return qpow(a, power, MOD);
}