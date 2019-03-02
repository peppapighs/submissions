#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1<<18;

int k, l, q;
int n, par[N], dep[N];
int ap[15][15];
vector<int> g[N], coord;
vector<pii> brid;

void dfs(int u, int p) {
       par[u] = p, dep[u] = dep[p] + 1;
       for(int v : g[u]) if(v != p) dfs(v, u);
}

int lca(int a, int b) {
       if(a > b) swap(a, b);
       if(a < n && b > n) return 1e8;
       if(dep[a] < dep[b]) swap(a, b);
       while(dep[a] > dep[b]) a = par[a];
       if(a == b) return a;
       while(a != b) a = par[a], b = par[b];
       return a;
}

int dist(int a, int b) { 
       if(lca(a, b) == 1e8) return 1e8;
       return dep[a] + dep[b] - 2*dep[lca(a, b)]; 
}

int get(int x) { return lower_bound(coord.begin(), coord.end(), x) - coord.begin(); }

int main() {
       scanf("%d %d %d", &k, &l, &q);
       n = (1<<k);
       for(int i = 1; i < (1<<(k-1)); i++) {
              g[i].emplace_back(i<<1);
              g[i<<1].emplace_back(i);
              g[i].emplace_back(i<<1|1);
              g[i<<1|1].emplace_back(i);
              g[n+i].emplace_back(n+(i<<1));
              g[n+(i<<1)].emplace_back(n+i);
              g[n+i].emplace_back(n+(i<<1|1));
              g[n+(i<<1|1)].emplace_back(n+i);
       }
       dfs(1, 1), dfs(n+1, n+1);
       for(int i = 1, a, b; i <= l; i++) {
              scanf("%d %d", &a, &b);
              brid.emplace_back(a, b);
              coord.emplace_back(a), coord.emplace_back(b);
       }
       fill_n(ap[0], 15*15, 1e8);
       sort(coord.begin(), coord.end());
       coord.erase(unique(coord.begin(), coord.end()), coord.end());
       for(pii p : brid) {
              ap[get(p.x)][get(p.y)] = 1;
              ap[get(p.y)][get(p.x)] = 1;
       }
       for(int i = 0; i < coord.size(); i++)
              for(int j = 0; j < coord.size(); j++)
                     ap[i][j] = min(ap[i][j], dist(coord[i], coord[j]));
       for(int k = 0; k < coord.size(); k++)
              for(int i = 0; i < coord.size(); i++)
                     for(int j = 0; j < coord.size(); j++)
                            ap[i][j] = min(ap[i][j], ap[i][k] + ap[k][j]);
       while(q--) {
              int a, b;
              scanf("%d %d", &a, &b);
              if(a > b) swap(a, b);
              int ans = dist(a, b);
              for(int i = 0; i < coord.size(); i++)
                     for(int j = 0; j < coord.size(); j++)
                            ans = min(ans, dist(a, coord[i]) + ap[i][j] + dist(coord[j], b));
              printf("%d\n", ans);
       }

       return 0;
}