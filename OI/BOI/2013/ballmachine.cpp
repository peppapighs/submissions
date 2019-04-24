#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, q, rot;
int mn[N], dep[N], par[N][18];
int pos[N], chk[N];
vector<int> g[N], V;
priority_queue<pii, vector<pii>, greater<pii> > Q;

int proc(int u, int p) {
    par[u][0] = p, dep[u] = dep[p] + 1, mn[u] = u;
    for(int i = 1; i <= 17; i++) par[u][i] = par[par[u][i-1]][i-1];

    for(int v : g[u]) mn[u] = min(mn[u], proc(v, u));
    sort(g[u].begin(), g[u].end(), [&](const int &a, const int &b) {
        return mn[a] < mn[b];
    });
    return mn[u];
}

void dfs(int u) {
    for(int v : g[u]) dfs(v);
    V.emplace_back(u);
}

int main() {
    scanf("%d %d", &n, &q);
    for(int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        if(a) g[a].emplace_back(i);
        else rot = i;
    }
    proc(rot, 0), dfs(rot);
    for(int i = 1; i <= n; i++) pos[V[i-1]] = i;
    for(int i = 1; i <= n; i++) Q.emplace(pos[i], i);
    for(int i = 1, T, a; i <= q; i++) {
        scanf("%d %d", &T, &a);
        if(T == 1) {
            int now = -1;
            while(a--) {
                pii u = Q.top(); Q.pop();
                chk[u.y] = true;
                now = u.y;
            }
            printf("%d\n", now);
        } else {
            int b = a;
            for(int i = 17; ~i; i--) if(chk[par[b][i]]) b = par[b][i];
            chk[b] = false;
            Q.emplace(pos[b], b);
            printf("%d\n", dep[a] - dep[b]);
        }
    }

    return 0;
}
