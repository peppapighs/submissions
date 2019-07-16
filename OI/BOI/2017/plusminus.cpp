#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int M = 1e9+7;

long modpow(long a, long b) {
    long ret = 1;
    for( ; b; b >>= 1) {
        if(b & 1) ret = (ret * a) % M;
        a = (a * a) % M;
    }
    return ret;
} 


int n, m, k, valid;
long ans;

void solve(int sz, vector<int> &x, vector<int> &y, vector<int> &val) {
    map<int, int> mp;
    for(int i = 0; i < x.size(); i++) {
        int now = x[i], f = val[i];
        if(y[i] % 2 == 0) f ^= 1;
        if(!mp.count(now)) mp[now] = f;
        else if(mp[now] != f) return;
    }
    ans = (ans + modpow(2, sz - (int)mp.size())) % M;
    int b = -1;
    for(pii p : mp) {
        int now = ((p.x & 1) == p.y);
        if(b == -1) b = now;
        else if(b != now) return;
    }
    ++valid;
}

vector<int> x, y, val;

int main() {
    scanf("%d %d %d", &n, &m, &k);
    if(k == 0) return !printf("%lld\n", (modpow(2, n) + modpow(2, m) - 2 + M) % M);
    for(int i = 1; i <= k; i++) {
        int a, b; char c;
        scanf(" %c %d %d", &c, &a, &b);
        x.emplace_back(a), y.emplace_back(b);
        val.emplace_back(c == '+');
    }
    solve(n, x, y, val), solve(m, y, x, val);
    if(valid == 2) ans = (ans - 1 + M) % M;
    printf("%lld\n", ans);

    return 0;
}