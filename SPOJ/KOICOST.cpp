#include <bits/stdc++.h>

#define long long long
#define iii tuple<int, int, int>

using namespace std;

const int N = 1e5+5;
const int M = 1e9;

struct UnionFind {
    int par[N], sz[N];
    UnionFind() { iota(par, par + N, 0), fill_n(sz, N, 1); }

    int find(int x) { return par[x] = x == par[x] ? x : find(par[x]); }

    void unite(int a, int b) {
        a = find(a), b = find(b);
        if(a == b) return;
        par[a] = b, sz[b] += sz[a];
    }

    int get_size(int x) { return sz[find(x)]; }
} dsu;

int n, m;
long total, ans;
vector<iii> E;

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        E.emplace_back(c, a, b);
        total += c;
    }
    sort(E.begin(), E.end(), greater<iii>());
    for(iii e : E) {
        int a, b, c; tie(c, a, b) = e;
        if(dsu.find(a) != dsu.find(b)) {
            ans += total * dsu.get_size(a) * dsu.get_size(b);
            ans %= M;
            dsu.unite(a, b);
        }
        total -= c;
    }
    printf("%lld\n", ans);

    return 0;
}