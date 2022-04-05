#include <bits/stdc++.h>

#define long long long

using namespace std;

long mult(long a, long b, long M) {
    return (__int128)a * b % M;
}

long modpow(long a, long b, long M) {
    long ret = 1;
    for( ; b; b >>= 1) {
        if(b & 1) ret = mult(ret, a, M);
        a = mult(a, a, M);
    }
    return ret;
}

bool is_prime(long n) {
    if(n == 2 || n == 3 || n == 5 || n == 7)
        return 1;
    if(n % 2 == 0 || n % 3 == 0 || n % 5 == 0 || n % 7 == 0)
        return 0;
    if(n < 121) return n > 1;

    long d = (n - 1) >> __builtin_ctzll(n - 1);
    function<bool(long)> ok = [&](long a) {
        long y = modpow(a, d, n), t = d;
        while(y != 1 && y != n - 1 && t != n - 1)
            y = mult(y, y, n), t <<= 1;
        if(y != n - 1 && t % 2 == 0) return 0;
        return 1;
    };
    if(n < (1ll << 32)) {
        for(long a : {2, 7, 61}) if(!ok(a))
            return 0;
    } else {
        for(long a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
            if(n <= a) return 1;
            if(!ok(a)) return 0;
        }
    }
    return 1;
}

long rho(long n, long c) {
    function<long(long)> f = [&](long x) {
        return (mult(x, x, n) + c) % n;
    };
    long x = 1, y = 2, z = 1, q = 1, g = 1;
    long m = 1ll << (__lg(n) / 5);
    for(long r = 1; g == 1; r <<= 1) {
        x = y;
        for(long _ = 0; _ < r; _++) y = f(y);
        for(long k = 0; k < r && g == 1; k += m) {
            z = y;
            for(long _ = 0; _ < min(m, r - k); _++)
                y = f(y), q = mult(q, (x - y + n) % n, n);
            g = __gcd(q, n);
        }
    }
    if(g == n) do {
        z = f(z);
        g = __gcd((x - z + n) % n, n);
    } while(g == 1);
    return g;
}

mt19937 rng(time(0));

long find_prime_factor(long n) {
    if(is_prime(n)) return n;
    for(int _ = 0; _ < 100; _++) {
        long m = rho(n, rng() % n);
        if(is_prime(m))
            return m;
        n = m;
    }
    return -1;
}

vector<long> factor(long n) {
    vector<long> ret;
    for(int p = 2; p < 100 && p * p <= n; p++) {
        if(n % p != 0) continue;
        while(n % p == 0) {
            ret.emplace_back(p);
            n /= p;
        }
    }
    while(n > 1) {
        long p = find_prime_factor(n);
        while(n % p == 0)  {
            ret.emplace_back(p);
            n /= p;
        }
    }
    sort(ret.begin(), ret.end());
    return ret;
}

int T;
long n;
map<long, int> cnt;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%lld", &n);
        vector<long> vec = factor(n);
        cnt.clear();

        for(long &x : vec) {
            cnt[x]++;
        }

        long ans = 1;
        for(auto p : cnt) {
            ans *= (p.second + 1);
        }
        printf("%lld\n", ans);
    }

    return 0;
}