#include <bits/stdc++.h>
 
#define long long long
#define pii pair<int, int>
#define x first
#define y second
 
using namespace std;
 
const int N = 3e5+5;
 
int n, m;
int pre[N], low[N], ap[N], id[N];
vector<vector<int> > g(N), bcc;
vector<int> sz;
 
void tarjan(int u, int p) {
    static int idx = 0;
    static stack<int> S;
    pre[u] = low[u] = ++idx, S.emplace(u);
    int cnt = 0;
    for(int v : g[u]) if(v != p) {
        if(!pre[v]) {
            ++cnt;
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if((!p && cnt > 1) || (p && low[v] >= pre[u])) ap[u] = 1;
            if(low[v] >= pre[u]) {
                bcc.emplace_back(vector<int>(1, u));
                while(bcc.back().back() != v) {
                    bcc.back().emplace_back(S.top());
                    S.pop();
                } 
            }
        } else low[u] = min(low[u], pre[v]);
    }
}
 
bitset<N> idart;
 
void gen_bct() {
    g.clear();
    g.emplace_back(vector<int>());
    sz.emplace_back(0);
    for(int i = 1; i <= n; i++) if(ap[i]) {
        idart[id[i] = g.size()] = true;
        g.emplace_back(vector<int>());
        sz.emplace_back(1);
    }
    for(vector<int> &cc : bcc) {
        g.emplace_back(vector<int>());
        sz.emplace_back(cc.size());
        for(int v : cc) {
            if(ap[v]) g[id[v]].emplace_back(g.size()-1), g[g.size()-1].emplace_back(id[v]);
            else id[v] = g.size()-1;
        }
    }
}
 
bitset<N> chk;
int siz[N];
long ans, sum_sz, sum_sz2;
 
int getsz(int u, int p) { siz[u] = 1; for(int v : g[u]) if(v != p && !chk[v]) siz[u] += getsz(v, u); return siz[u]; }
 
int find_cen(int u, int p, int all, pii &ret) {
    int mx = all - siz[u];
    for(int v : g[u]) if(v != p && !chk[v])
        mx = max(mx, find_cen(v, u, all, ret));
    ret = min(ret, pii(mx, u));
    return siz[u];
}
 
int noap_sz(int u) { return idart[u] ? 1 : sz[u] - g[u].size(); } //Non-overlap Size
int noad_sz(int u) { return sz[u] - 2 * (int)!idart[u]; } //Size with no 2 adjacent APs
 
void dfs(int u, int p, long all, bool fill) {
    if(!fill) ans += 1ll * noap_sz(u) * (sum_sz2 + sum_sz * (all - idart[u])); //Start * (Change another subtree + Change this subtree)
    else {
        sum_sz += noap_sz(u); //Finish
        sum_sz2 += 1ll * (all - idart[u]) * noap_sz(u); //Change and Finish
    }
    for(int v : g[u]) if(v != p && !chk[v]) dfs(v, u, all + noad_sz(v), fill);
}
 
void proc(int u) {
    getsz(u, u);
    pii ret(siz[u] + 1, -1);
    find_cen(u, u, siz[u], ret);
    chk[u = ret.y] = true;
    
    if(sz[u] > 2) ans += 1ll * (sz[u] - 2ll) * (noap_sz(u) * (noap_sz(u)-1ll) / 2ll);
    sum_sz = noap_sz(u);
    sum_sz2 = idart[u] ? 0 : 1ll * noad_sz(u) * noap_sz(u);
    for(int v : g[u]) if(!chk[v]) {
        dfs(v, u, noad_sz(v), 0);
        dfs(v, u, noad_sz(u) + noad_sz(v), 1);
    }
    for(int v : g[u]) if(!chk[v]) proc(v);
}
 
int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    for(int i = 1; i <= n; i++) if(!pre[i]) tarjan(i, 0);
    gen_bct();
 
    for(int i = 1; i < (int)g.size(); i++) if(!chk[i]) proc(i);
    printf("%lld\n", 2ll * ans);
 
    return 0;
}