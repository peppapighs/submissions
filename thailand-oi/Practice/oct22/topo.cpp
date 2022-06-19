#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, m;
int deg[N], chk[N];
vector<int> g[N], topo;

int main() {
    scanf("%d %d", &n, &m);
    while (m--) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].emplace_back(v);
        deg[v]++;
    }
    queue<int> Q;
    for (int i = 1; i <= n; i++)
        if (!deg[i])
            Q.emplace(i);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        topo.emplace_back(u);
        for (int v : g[u])
            if (!--deg[v])
                Q.emplace(v);
    }
    for (int i : topo)
        chk[i] = true;
    for (int i = 1; i <= n; i++)
        if (!chk[i])
            return !printf("no\n");
    for (int i : topo)
        printf("%d\n", i);

    return 0;
}
