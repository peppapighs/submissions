#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, C[N];
int par[N], dep[N], spi[N], pos[N], rot[N];
deque<pii> Q[N];
vector<int> g[N];
vector<pii> E;

int dfs(int u, int p) {
    int sz = 1; pii ret(0, -1);
    par[u] = p, dep[u] = dep[p] + 1;
    for(int v : g[u]) if(v != p) {
        int z = dfs(v, u);
        ret = max(ret, pii(z, v));
        sz += z;
    }
    spi[u] = ret.y;
    return sz;
}

void hld() {
    dfs(1, 0);
    for(int i = 1, idx = 0; i <= n; i++) if(spi[par[i]] != i)
        for(int j = i; j != -1; j = spi[j])
            rot[j] = i, pos[j] = ++idx;
}

long query(int u) {
    vector<pii> ret; vector<int> coord;
    while(u) {
        int sz = pos[u] - pos[rot[u]] + 1;
        vector<pii> now;
        for(pii x : Q[rot[u]]) {
            if(x.y < sz) now.emplace_back(x), sz -= x.y;
            else { now.emplace_back(x.x, sz); break; }
        }
        reverse(now.begin(), now.end());
        for(pii x : now) ret.emplace_back(x), coord.emplace_back(x.x);
        u = par[rot[u]];
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());

    long sum = 0;
    vector<long> t((int)coord.size() + 1, 0);
    auto get = [&](int x) { return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1; };
    auto upd = [&](int x, long k) { for(int i = x; i <= coord.size(); i += i & -i) t[i] += k; };
    auto que = [&](int x, long k = 0) { for(int i = x; i; i -= i & -i) k += t[i]; return k; };

    for(pii x : ret) {
        sum += que(get(x.x) - 1) * x.y;
        upd(get(x.x), x.y);
    }    
    return sum;
}

void update(int u, int k) {
    while(u) {
        int sz = pos[u] - pos[rot[u]] + 1;
        deque<pii> &now = Q[rot[u]];
        while(!now.empty()) {
            if(now.front().y <= sz) sz -= now.front().y, now.pop_front();
            else { now.front().y -= sz; break; }
        }
        Q[rot[u]].emplace_front(k, pos[u] - pos[rot[u]] + 1);
        u = par[rot[u]];
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", C + i);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        E.emplace_back(a, b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    hld();
    Q[1].emplace_back(C[1], 1);
    for(pii p : E) {
        int u, v; tie(u, v) = p;
        printf("%lld\n", query(u));
        update(v, C[v]);
    }

    return 0;
}