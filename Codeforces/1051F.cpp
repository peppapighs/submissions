#include <bits/stdc++.h>

using namespace std;

#define pii pair<int, int>
#define x first
#define y second
#define iii tuple<int, int, int>
#define long long long

const int N = 1e5+5;

int n, m, P[N];
int dep[N], par[N][17];
long d[N];
vector<pii> g[N];

int find(int x) { return P[x] = P[x] == x ? x : find(P[x]); }

void dfs(int u, int p) {
    for(int i = 1; i < 17; ++i) par[u][i] = par[par[u][i-1]][i-1];
    for(pii v : g[u]) if(v.x != p) dep[v.x] = dep[u] + 1, par[v.x][0] = u, d[v.x] = d[u] + v.y, dfs(v.x, u);
}

int get_lca(int a, int b) {
    if(dep[a] < dep[b]) swap(a, b);
    for(int i = 16; ~i; --i) if(dep[par[a][i]] >= dep[b]) a = par[a][i];
    if(a == b) return a;
    for(int i = 16; ~i; --i) if(par[a][i] != par[b][i]) a = par[a][i], b = par[b][i]; 
    return par[a][0];
}

long ap[45][45], di[50][N];

vector<int> coor;

int get(int x) { return lower_bound(coor.begin(), coor.end(), x) - coor.begin(); }
long getd(int a, int b) { return d[a] + d[b] - 2 * d[get_lca(a, b)]; }

int main() {
    scanf("%d %d", &n, &m);
    iota(P, P+N, 0);    
    vector<iii> E;
    for(int i = 0, u, v, w; i < m; ++i) {
        scanf("%d %d %d", &u, &v, &w);
        int a = find(u), b = find(v);
        if(a != b) P[a] = b, g[u].emplace_back(v, w), g[v].emplace_back(u, w);
        else E.emplace_back(u, v, w), coor.emplace_back(u), coor.emplace_back(v);
    }
    dfs(1, 0);
    sort(coor.begin(), coor.end());
    coor.resize(unique(coor.begin(), coor.end()) - coor.begin());
    fill_n(ap[0], 45*45, 1e18);
    for(auto x : E) {
        int u, v, w; tie(u, v, w) = x;
        ap[get(u)][get(v)] = ap[get(v)][get(u)] = w;
    } 
    for(int i = 0; i < coor.size(); ++i) for(int j = 1; j <= n; ++j) di[i][j] = getd(coor[i], j);
    for(int i = 0; i < coor.size(); ++i) for(int j = 0; j < coor.size(); ++j) ap[i][j] = min(ap[i][j], getd(coor[i], coor[j]));
    for(int k = 0; k < coor.size(); ++k) for(int i = 0; i < coor.size(); ++i) for(int j = 0; j < coor.size(); ++j) 
        ap[i][j] = min(ap[i][j], ap[i][k] + ap[k][j]);
    int T; scanf("%d", &T);
    while(T--) {
        int a, b; scanf("%d %d", &a, &b);
        long ans = getd(a, b);
        for(int i = 0; i < coor.size(); ++i) for(int j = 0; j < coor.size(); ++j) ans = min(ans, di[i][a]  + di[j][b] + ap[i][j]);
        printf("%lld\n", ans);
    }

    return 0;
}