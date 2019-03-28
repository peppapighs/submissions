#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 2e5+5;
const long iden = 98765431;

int n, ans;
long mpow[N], all;
vector<int> g[2][N];
vector<pii> hsh[2][N], E[2];
set<pii> S;

long dfs(int u, int p, int i) {
    long ret = g[i][u].size() == 1 ? mpow[u] : 0;
    for(int v : g[i][u]) if(v != p) {
        hsh[i][u].emplace_back(dfs(v, u, i), v);
        ret += hsh[i][u].back().x;
    }
    if(u != p) hsh[i][u].emplace_back(all - ret, p);
    return ret;
}

int main() {
    scanf("%d", &n);
    mpow[0] = 1;
    for(int i = 1; i <= n; i++) mpow[i] = mpow[i-1] * iden, all += mpow[i];
    for(int i = 1, a, b; i < 2*n - 2; i++) {
        scanf("%d %d", &a, &b);
        g[0][a].emplace_back(b), g[0][b].emplace_back(a);
        E[0].emplace_back(a, b);
    }
    for(int i = 1, a, b; i < 2*n - 2; i++) {
        scanf("%d %d", &a, &b);
        g[1][a].emplace_back(b), g[1][b].emplace_back(a);
        E[1].emplace_back(a, b);
    }
    dfs(n + 1, n + 1, 0), dfs(n + 1, n + 1, 1);
    for(pii e : E[0]) {
        int a = e.x, b = e.y;
        long ha = g[0][a].size() == 1 ? mpow[a] : 0, hb = g[0][b].size() == 1 ? mpow[b] : 0;
        for(pii h : hsh[0][a]) if(h.y != b) ha += h.x;
        for(pii h : hsh[0][b]) if(h.y != a) hb += h.x;
        if(ha > hb) swap(ha, hb);
        S.emplace(ha, hb);
    }
    for(pii e : E[1]) {
        int a = e.x, b = e.y;
        long ha = g[1][a].size() == 1 ? mpow[a] : 0, hb = g[1][b].size() == 1 ? mpow[b] : 0;
        for(pii h : hsh[1][a]) if(h.y != b) ha += h.x;
        for(pii h : hsh[1][b]) if(h.y != a) hb += h.x;
        if(ha > hb) swap(ha, hb);
        if(S.find(pii(ha, hb)) == S.end()) ++ans;
    }
    printf("%d\n", ans);

    return 0;
}