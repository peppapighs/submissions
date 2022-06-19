#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n, m, par[N], sz[N];
set<int> in[N], out[N], E[N];
long ans;

void update(int x, int sign) {
    ans += sign *
           (1ll * (E[x].size() - sz[x]) * sz[x] + 1ll * sz[x] * (sz[x] - 1));
}

int find(int x) { return x == par[x] ? x : find(par[x]); }

queue<pii> Q;

void unite(int a, int b) {
    a = find(a), b = find(b);
    if (a == b)
        return;
    update(a, -1), update(b, -1);
    if (in[a].size() + out[a].size() + E[a].size() >
        in[b].size() + out[b].size() + E[b].size())
        swap(a, b);

    in[a].erase(b), out[a].erase(b);
    in[b].erase(a), out[b].erase(a);
    for (int x : in[a]) {
        if (out[b].count(x))
            Q.emplace(x, b);
        out[x].erase(a), out[x].emplace(b);
    }
    for (int x : out[a]) {
        if (in[b].count(x))
            Q.emplace(x, b);
        in[x].erase(a), in[x].emplace(b);
    }
    for (int x : in[a])
        in[b].emplace(x);
    for (int x : out[a])
        out[b].emplace(x);
    for (int x : E[a])
        E[b].emplace(x);
    in[a].clear(), out[a].clear(), E[a].clear();

    par[a] = b, sz[b] += sz[a];
    update(b, 1);
}

int main() {
    iota(par, par + N, 0), fill_n(sz, N, 1);

    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        E[i].emplace(i);

    for (int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        int pa = find(a), pb = find(b);
        if (out[pb].count(pa)) {
            Q.emplace(a, b);
            while (!Q.empty()) {
                pii now = Q.front();
                Q.pop();
                unite(now.x, now.y);
            }
        } else {
            update(pb, -1);
            E[pb].emplace(a);
            update(pb, 1);
            out[pa].emplace(pb), in[pb].emplace(pa);
        }
        printf("%lld\n", ans);
    }

    return 0;
}