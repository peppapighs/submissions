#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e6+5;

struct cht {
    struct line {
        long m, c;
        line(long m, long c) : m(m), c(c) { }
        long f(long x) { return m * x + c; }
    };
    int ptr = 0;
    vector<line> l;
    bool bad(line a, line b, line c) { return 1.0 * (c.c - a.c) / (a.m - c.m) <= 1.0 * (b.c - a.c) / (a.m - b.m); }
    void add(long m, long c) {
        line now(m, c);
        while(l.size() > 1 && bad(l[l.size()-2], l[l.size()-1], now))
            l.pop_back();
        l.emplace_back(now);
    }
    long query(long x) {
        if(ptr >= l.size()) ptr = l.size() - 1;
        while(ptr + 1 < l.size() && l[ptr].f(x) <= l[ptr+1].f(x)) ++ptr;
        return l[ptr].f(x);
    }
    void clear() { ptr = 0, l.clear(); }
} hull;

int n;
long a, b, c;
long pref[N], dp[N];

void solve() {
    hull.clear(), hull.add(0, 0);
    scanf("%d %lld %lld %lld", &n, &a, &b, &c);
    for(int i = 1; i <= n; i++) {
        scanf("%lld", pref+i), pref[i] += pref[i-1];
        dp[i] = hull.query(pref[i]) + (a * pref[i] * pref[i] + b * pref[i] + c);
        hull.add(-2ll * a * pref[i], a * pref[i] * pref[i] - b * pref[i] + dp[i]);
    }
    printf("%lld\n", dp[n]);
}

int T;

int main() {
    scanf("%d", &T);
    while(T--) solve();

    return 0;
}