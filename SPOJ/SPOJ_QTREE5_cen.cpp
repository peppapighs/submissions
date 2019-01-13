#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, q;
int cdep[N], cpar[N], d[N][18], sz[N];
bool chk[N], wht[N];
vector<int> g[N];
multiset<int> S[N];

int getsz(int u, int p) { sz[u] = 1; for(int v : g[u]) if(v != p && !chk[v]) sz[u] += getsz(v, u); return sz[u]; }

void find_cen(int u, int p, int all, pii &ret) {
    int mx = all - sz[u];
    for(int v : g[u]) if(v != p && !chk[v]) {
        find_cen(v, u, all, ret);
        mx = max(mx, sz[v]);
    }
    if(mx < ret.x) ret = pii(mx, u);
}

void get_dist(int u, int p, int i) {
    for(int v : g[u]) if(v != p && !chk[v]) {
        d[v][i] = d[u][i] + 1;
        get_dist(v, u, i);
    }
}

void gen_tree(int u, int p) {
    getsz(u, u);
    pii ret(sz[u] + 1, -1);
    find_cen(u, u, sz[u], ret);
    u = ret.y, cpar[u] = p, cdep[u] = cdep[p] + 1;
    get_dist(u, u, cdep[u]);
    chk[u] = true;
    for(int v : g[u]) if(!chk[v]) gen_tree(v, u);
}

int main() {
    scanf("%d", &n);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    gen_tree(1, 0);
    scanf("%d", &q);
    while(q--) {
        int T, a;
        scanf("%d %d", &T, &a);
        auto del = [&](int i, int x) {
            auto it = S[i].find(x);
            if(it != S[i].end()) S[i].erase(it);
        };
        if(T == 0) {
            wht[a] ^= 1;
            for(int u = a ; u; u = cpar[u]) {
                if(wht[a]) S[u].emplace(d[a][cdep[u]]);
                else del(u, d[a][cdep[u]]);
            }
        } else {
            int ans = 1e9;
            for(int u = a; u; u = cpar[u]) if(!S[u].empty()) ans = min(ans, *S[u].begin() + d[a][cdep[u]]);
            if(ans == 1e9) printf("-1\n");
            else printf("%d\n", ans);
        }
    }

    return 0;
}