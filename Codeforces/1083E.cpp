#include <bits/stdc++.h>

#define long long long
#define iii tuple<long, long, long>

using namespace std;

struct cht {
    struct line {
        long m, b;
        line(long m, long b) : m(m), b(b) {}
        long get(long x) { return m*x + b; }
    };
    vector<line> f;
    int ptr = 0;
    bool bad(line a, line b, line c) { return 1.0*(c.b - a.b)/(a.m - c.m) <= 1.0*(b.b - a.b)/(a.m - b.m); }
    void add(long m, long b) {
        line l(m, b);
        while(f.size() >= 2 && bad(f[f.size() - 2], f[f.size() - 1], l)) f.pop_back();
        if(f.size() == 1 && f.back().m > m) {
            if(f.back().b >= b) return;
            else f.pop_back();
        }
        f.emplace_back(l);
    }
    long query(long x) {
        while(ptr + 1 < f.size() && f[ptr].get(x) <= f[ptr+1].get(x)) ++ptr;
        return f[ptr].get(x);
    }
} hull;

const int N = 1e6+5;

int n;
long ans;
vector<iii> rect, V;

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        long a, b, c;
        scanf("%lld %lld %lld", &a, &b, &c);
        rect.emplace_back(a, b, c);
    }
    sort(rect.begin(), rect.end());
    V.emplace_back(-1, -1, -1);
    for(iii rec : rect) {
        while(V.size() > 1 && get<1>(V.back()) <= get<1>(rec)) V.pop_back();
        V.emplace_back(rec);
    }
    n = V.size() - 1;
    hull.add(0, 0);
    for(int i = 1; i <= n; i++) {
        long x, y, a;
        tie(x, y, a) = V[i];
        long now = hull.query(-y) + x*y - a;
        ans = max(ans, now);
        hull.add(x, now);
    }
    printf("%lld\n", ans);

    return 0;
}