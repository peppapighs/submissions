#include <bits/stdc++.h>

using namespace std;

int n, c;
int deg[25], chk[25];
vector<int> g[25];

int main() {
        scanf("%d %d", &n, &c);
        while(c--) {
                int a, b, c;
                scanf("%d %d %d", &a, &b, &c);
                g[b].emplace_back(a), g[a].emplace_back(c);
                ++deg[a], ++deg[c];
        }
        queue<int> Q;
        vector<int> topo;
        for(int i = 1; i <= n; i++) if(!deg[i]) Q.emplace(i);
        while(!Q.empty()) {
                int u = Q.front();
                Q.pop();
                topo.emplace_back(u);
                for(int v : g[u]) if(!--deg[v]) Q.emplace(v);
        }
        for(int v : topo) chk[v] = true;
        for(int i = 1; i <= n; i++) if(!chk[i]) return !printf("NO\n");
        printf("YES\n");
        for(int v : topo) printf("%d ", v);
        printf("\n");

        return 0;
}
