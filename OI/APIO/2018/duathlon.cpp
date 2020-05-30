#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e5+5;

int n, m;
int pre[N], low[N], c_sz[N];
vector<vector<int> > g(N), bcc;

void tarjan(int u, int p) {
    static int idx = 0;
    static stack<int> S;
    pre[u] = low[u] = ++idx;
    S.emplace(u);
    for(int v : g[u]) if(v != p) {
        if(!pre[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] >= pre[u]) {
                bcc.emplace_back(1, u);
                while(bcc.back().back() != v) {
                    bcc.back().emplace_back(S.top());
                    S.pop();
                }
            }
        } else low[u] = min(low[u], pre[v]);
    } 
}

void build_tree() {
    for(int i = 1; i <= n; i++) if(!pre[i])
        tarjan(i, 0);
    g.clear(), g.resize(n + 1);
    for(vector<int> &cc : bcc) {
        c_sz[g.size()] = cc.size();
        g.emplace_back(0);
        for(int u : cc) {
            g[g.size() - 1].emplace_back(u);
            g[u].emplace_back(g.size() - 1);
        }
    }
}

int subsz[N];
long ans;

int get_sz(int u, int p) {
     if(u <= n) subsz[u] = 1;
     for(int v : g[u]) if(v != p)
        subsz[u] += get_sz(v, u);
    return subsz[u];
}

void bad_triplet(int u, int p, int all) {
    if(u <= n) for(int v : g[u]) {
        if(v != p) ans -= 1ll * (c_sz[v] - 1) * (all - subsz[v]) * (all - subsz[v] - 1);
        else ans -= 1ll * (c_sz[v] - 1) * subsz[u] * (subsz[u] - 1);
    }
    for(int v : g[u]) if(v != p)
        bad_triplet(v, u, all);
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    build_tree();
    for(int i = 1; i <= n; i++) if(!subsz[i]) {
        get_sz(i, 0);
        ans += 1ll * subsz[i] * (subsz[i] - 1) * (subsz[i] - 2);
        bad_triplet(i, 0, subsz[i]);
    }
    printf("%lld\n", ans);

    return 0;
}