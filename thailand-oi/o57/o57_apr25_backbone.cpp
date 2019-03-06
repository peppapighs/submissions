#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 305;

int n, m, par[N], dep[N], lca[N], srt[N];
int mn = 11, col[N];
bool chk[N], dis[N];
vector<pii> g[N], E[N], ans, st;
map<pii, int> M;
pii Q[N];

void dfs(int u, int p) {
    par[u] = p, dep[u] = dep[p] + 1;
    for(pii v : g[u]) if(v.x != p) 
        dfs(v.x, u);
}

void flood(int a, int C) {
    queue<int> Q;
    col[a] = C;
    Q.emplace(a);
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        for(pii v : g[u]) if(!col[v.x] && !dis[v.y]) {
            col[v.x] = C;
            Q.emplace(v.x);
        }
    }
}

void solve(int now, int k) {
    if(k > mn) return;
    bool valid = true;
    for(int i = 1; i <= m; i++) valid &= chk[i];
    if(valid) {
        ans = st, mn = k;
        return;
    }
    if(now > m) return;
    if(!chk[srt[now]]) {
        for(pii e : E[srt[now]]) {
            memset(col, 0, sizeof col);
            vector<int> V;
            int a = e.x, b = e.y, idx = 0;
            if(a > b) swap(a, b);
            dis[M[pii(a, b)]] = true;
            for(int i = 1; i <= n; i++) if(!col[i]) flood(i, ++idx);
            for(int i = 1; i <= m; i++) if(col[Q[i].x] != col[Q[i].y]) {
                V.emplace_back(i);
                chk[i] = true;
            }
            st.emplace_back(a, b);
            solve(now+1, k+1);
            st.pop_back();
            dis[M[pii(a, b)]] = false;
            for(int i : V) chk[i] = false;
        }
    } else solve(now+1, k);
}

int main() {
    iota(srt, srt+N, 0);
    scanf("%d %d", &n, &m);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        if(a > b) swap(a, b);
        g[a].emplace_back(b, i), g[b].emplace_back(a, i);
        M[pii(a, b)] = i;
    }
    dfs(1, 1);
    for(int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        Q[i] = pii(a, b);
        if(dep[a] < dep[b]) swap(a, b);
        while(dep[a] > dep[b]) {
            if(par[a] == b) E[i].emplace_back(a, b);
            a = par[a];
        }
        if(a != b) while(a != b) {
            if(par[a] == par[b]) E[i].emplace_back(a, par[a]), E[i].emplace_back(b, par[b]);
            a = par[a], b = par[b];
        }
        lca[i] = a;
    }
    sort(srt+1, srt+m+1, [&](const int &a, const int &b) {
        return dep[lca[a]] > dep[lca[b]];
    });
    solve(1, 0);
    printf("%d\n", (int)ans.size());
    for(pii e : ans) printf("%d %d\n", e.x, e.y);

    return 0;
}
