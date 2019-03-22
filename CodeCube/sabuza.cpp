#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 5e4+5;

struct cht {
    struct line {
        long m, c;
        line(long m, long c) : m(m), c(c) { }
        long f(long x) { return m*x + c; }
    };
    vector<line> l;
    int ptr = 0;
    bool bad(line a, line b, line c) {
        return (c.c - a.c) * (a.m - b.m) <= (b.c - a.c) * (a.m - c.m);
    }
    void add(long x, long c) {
        line now(x, c);
        while(l.size() > 1 && bad(l[l.size()-2], l[l.size()-1], now)) l.pop_back();
        l.emplace_back(now);
    }
    long query(long x) {
        while(ptr < (int)l.size()-1 && l[ptr+1].f(x) < l[ptr].f(x)) ++ptr;
        return l[ptr].f(x);
    }
} hull;

int n;
long dp[N];
vector<pii> V, rect(1, pii(1e18, 1e18));

int main() {
    scanf("%d", &n); 
    for(int i = 1; i <= n; i++) {
        long a, h, z;
        scanf("%lld %lld %lld", &a, &h, &z);
        V.emplace_back(a*h, z);
    }
    sort(V.begin(), V.end());
    for(pii v : V) {
        while(rect.back().y <= v.y) rect.pop_back();
        rect.emplace_back(v);
    }
    for(int i = 1; i < (int)rect.size(); i++) {
        hull.add(rect[i].y, dp[i-1]);
        dp[i] = hull.query(rect[i].x);
    }
    printf("%lld\n", dp[(int)rect.size()-1]);

    return 0;
}
