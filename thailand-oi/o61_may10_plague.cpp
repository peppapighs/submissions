#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#define pii pair<int, int>

using namespace std;
using namespace __gnu_pbds;

typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int N = 1e5+5;

int n, m;
int sz[N], chk[N];
int mxnode, mxsub, book;
int cpar[N], cdep[N], par[N][18], dep[N];
vector<int> g[N];
ordered_set S1[N], S2[N];

int getsz(int u, int p) {
       sz[u] = 1;
       for(int v : g[u]) if(v != p && !chk[v]) sz[u] += getsz(v, u);
       return sz[u];
}

int findcen(int u, int p, int all) {
       int ret = all - sz[u];
       for(int v : g[u]) if(v != p && !chk[v])
              ret = max(ret, findcen(v, u, all));
       if(ret < mxsub) mxnode = u, mxsub = ret;
       return sz[u];
}

void build(int u, int p) {
       getsz(u, u);
       mxsub = sz[u]+1;
       findcen(u, u, sz[u]);
       u = mxnode;
       cpar[u] = p, cdep[u] = cdep[p] + 1, chk[u] = true;
       for(int v : g[u]) if(!chk[v]) build(v, u);
}

void dfs(int u, int p) {
       par[u][0] = p, dep[u] = dep[p] + 1;
       for(int i = 1; i <= 17; i++) par[u][i] = par[par[u][i-1]][i-1];
       for(int v : g[u]) if(v != p) dfs(v, u);
}

int lca(int a, int b) {
       if(dep[a] < dep[b]) swap(a, b);
       for(int i = 17; ~i; i--) if(dep[par[a][i]] >= dep[b]) a = par[a][i];
       if(a == b) return a;
       for(int i = 17; ~i; i--) if(par[a][i] != par[b][i]) a = par[a][i], b = par[b][i];
       return par[a][0];
}

int d(int a, int b) { return dep[a] + dep[b] - 2*dep[lca(a, b)]; }

int get(ordered_set &S, int x) { return S.size() - S.order_of_key(pii(x, 0)); }

int main() {
       scanf("%d %d", &n, &m);
       for(int i = 1, a, b; i < n; i++) {
              scanf("%d %d", &a, &b);
              g[a].emplace_back(b), g[b].emplace_back(a);
       }
       build(1, 0);
       dfs(1, 1);
       while(m--) {
              int T, a, b;
              scanf("%d %d", &T, &a);
              if(T == 1) {
                     scanf("%d", &b);
                     S1[a].insert(pii(b, ++book));
                     for(int i = cpar[a], j = a; i; i = cpar[i], j = cpar[j]) if(b - d(a, i) >= 0)
                            S1[i].insert(pii(b - d(a, i), ++book)), S2[j].insert(pii(b - d(a, i), ++book));
              } else {
                     int ret = get(S1[a], 0);
                     for(int i = cpar[a], j = a; i; i = cpar[i], j = cpar[j])
                            ret += get(S1[i], d(a, i)) - get(S2[j], d(a, i));
                     printf("%d\n", ret);
              }
       }

       return 0;
}