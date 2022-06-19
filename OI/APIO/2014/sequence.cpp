#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5 + 5;

struct line {
    long m, b;
    int idx;
    line(long m, long b, int idx) : m(m), b(b), idx(idx) {}
    long f(long x) { return m * x + b; }
};

struct cht {
    int ptr = 0;
    vector<line> l;
    bool bad(line a, line b, line c) {
        return (c.b - a.b) * (a.m - b.m) <= (b.b - a.b) * (a.m - c.m);
    }
    void add(long m, long b, int idx) {
        line now(m, b, idx);
        while (l.size() > 1 && bad(l[l.size() - 2], l[l.size() - 1], now))
            l.pop_back();
        l.emplace_back(now);
    }
    line query(long x) {
        if (ptr >= l.size())
            ptr = l.size() - 1;
        while (ptr + 1 < l.size() && l[ptr].f(x) < l[ptr + 1].f(x))
            ++ptr;
        return l[ptr];
    }
    void clear() { l.clear(), ptr = 0; }
} hull[2];

int n, k, pv[205][N];
long dp[N], pref[N];

int main() {
    scanf("%d %d", &n, &k), ++k;
    for (int i = 1; i <= n; i++)
        scanf("%lld", pref + i);
    for (int i = 1; i <= n; i++)
        pref[i] += pref[i - 1];
    hull[0].add(0, 0, 0);
    for (int j = 1; j <= k; j++) {
        int now = j & 1, pre = now ^ 1;
        hull[now].clear();
        for (int i = j; i <= n; i++) {
            line ret = hull[pre].query(pref[i]);
            dp[i] = ret.f(pref[i]);
            pv[j][i] = ret.idx;
            hull[now].add(pref[i], dp[i] - pref[i] * pref[i], i);
        }
    }
    vector<int> ans;
    for (int j = k, i = n; j > 1; j--)
        ans.emplace_back(i = pv[j][i]);
    reverse(ans.begin(), ans.end());
    printf("%lld\n", dp[n]);
    for (int i : ans)
        printf("%d ", i);
    printf("\n");

    return 0;
}