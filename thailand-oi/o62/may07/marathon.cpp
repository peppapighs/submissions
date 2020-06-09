#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n, s, t, m, q;
int mssp[N], cnt[N], d[200][N];
vector<pii> g[N];
vector<int> S;

void bfs() {
    fill_n(mssp, N, 1e9);
    queue<int> Q;
    for(int u : S) mssp[u] = 0, Q.emplace(u);
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        for(pii v : g[u]) if(mssp[u] + 1 < mssp[v.x])
            mssp[v.x] = mssp[u] + 1, Q.emplace(v.x);
    }
}

void dijkstra(int st, int d[]) {
    fill_n(d, N, 1e9);
    priority_queue<pii, vector<pii>, greater<pii> > Q;
    Q.emplace(d[st] = 0, st);
    while(!Q.empty()) {
        pii u = Q.top(); Q.pop();
        if(u.x != d[u.y]) continue;
        for(pii v : g[u.y]) if(u.x + v.y < d[v.x])
            Q.emplace(d[v.x] = u.x + v.y, v.x);
    }
}

int main() {
    scanf("%d %d %d %d %d", &n, &s, &t, &m, &q);
    for(int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b, c), g[b].emplace_back(a, c);
    }
    for(int i = 1, a; i <= s; i++) {
        scanf("%d", &a);
        S.emplace_back(a);
    }
    for(int i = 1, a; i <= t; i++) scanf("%d", &a);
    bfs();
    for(int i = 1; i <= n; i++) ++cnt[mssp[i]];
    int mn = n, idx = n;
    for(int i = 1; i <= 1000; i++) if(cnt[i] < mn)
        mn = cnt[i], idx = i;
    int ptr = 0;
    for(int i = 1; i <= n; i++) if(mssp[i] == idx)
        dijkstra(i, d[++ptr]);
    for(int i = 1, a, b; i <= q; i++) {
        scanf("%d %d", &a, &b);
        int ans = 1e9;
        for(int j = 1; j <= ptr; j++)
            ans = min(ans, d[j][a] + d[j][b]);
        printf("%d\n", ans);
    }

    return 0;
}