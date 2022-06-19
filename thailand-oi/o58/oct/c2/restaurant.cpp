#include <bits/stdc++.h>

using namespace std;

int n, t;
int par[305];

struct edge {
    int u, v, w;
    edge(int u, int v, int w) : u(u), v(v), w(w) {}
    friend bool operator<(const edge &a, const edge &b) { return a.w < b.w; }
};

vector<int> g[305];
vector<edge> E;

int find(int i) { return par[i] = par[i] == i ? i : find(par[i]); }

int main() {
    scanf("%d %d", &n, &t);
    for (int i = 1; i <= n; i++) {
        par[i] = i;
        for (int j = 1; j <= n; j++) {
            int w;
            scanf("%d", &w);
            if (i < j)
                E.emplace_back(i, j, w);
        }
    }
    sort(E.begin(), E.end());
    int cnt = 0;
    for (edge e : E) {
        int pu = find(e.u), pv = find(e.v);
        if (pu != pv) {
            par[pu] = pv;
            g[e.u].emplace_back(e.v);
            g[e.v].emplace_back(e.u);
            cnt++;
        }
        if (cnt == n - 1)
            break;
    }

    for (int i = 1; i <= n; i++)
        if (g[i].size() >= 3) {
            printf("%d\n", i);
            if (t == 2)
                printf("%d\n", g[i].size());
            return 0;
        }

    return 0;
}