#include "aliens.h"
#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

struct cht {
    struct line {
        long m, b;
        int cnt;
        line(long m, long b, int cnt) : m(m), b(b), cnt(cnt) {}
        long get(long x) { return m * x + b; }
    };
    vector<line> f;
    int ptr = 0;
    bool bad(line a, line b, line c) {
        return (c.b - a.b) * (a.m - b.m) <= (b.b - a.b) * (a.m - c.m);
    }
    void add(long m, long b, int cnt) {
        line l(m, b, cnt);
        while (f.size() >= 2 && bad(f[f.size() - 2], f.back(), l))
            f.pop_back();
        f.emplace_back(l);
    }
    pii query(long x) {
        while (ptr + 1 < f.size() && f[ptr + 1].get(x) < f[ptr].get(x))
            ++ptr;
        return pii(f[ptr].get(x), f[ptr].cnt);
    }
    void clear() { f.clear(), ptr = 0; }
} hull;

int n;
long mx = 0;
vector<long> l = {-1}, r = {-1};

long sq(long a) { return a * a; }

pii solve(long C) {
    vector<pii> dp = vector<pii>(n + 1);
    hull.clear();
    dp[0] = {0, 0};
    hull.add(-2ll * (l[1] - 1), sq(l[1] - 1), 0);
    for (int i = 1; i <= n; i++) {
        pii now = hull.query(r[i]);
        dp[i] = pii(now.x + sq(r[i]) + C, now.y + 1);
        if (i == n)
            continue;
        hull.add(-2ll * (l[i + 1] - 1),
                 sq(l[i + 1] - 1) + dp[i].x - sq(max(0ll, r[i] - l[i + 1] + 1)),
                 dp[i].y);
    }
    return dp[n];
}

long take_photos(int _n, int _m, int k, vector<int> _r, vector<int> _c) {
    vector<pii> coord;
    for (int i = 0; i < _n; i++) {
        if (_r[i] > _c[i])
            swap(_r[i], _c[i]);
        coord.emplace_back(_c[i], _r[i]);
    }
    sort(coord.begin(), coord.end());
    coord.erase(unique(coord.begin(), coord.end()), coord.end());
    for (pii p : coord) {
        if (p.x == r.back())
            continue;
        while (!l.empty() && p.x >= r.back() && p.y <= l.back())
            l.pop_back(), r.pop_back();
        l.emplace_back(p.y), r.emplace_back(p.x);
    }
    n = l.size() - 1;
    k = min(k, n);
    long a = 0, b = 1e17;
    while (a < b) {
        long mid = (a + b) >> 1;
        if (solve(mid).y <= k)
            b = mid;
        else
            a = mid + 1;
    }
    return solve(b).x - b * k;
}
