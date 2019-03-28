#include <bits/stdc++.h>

#define iii tuple<int, int, int, int>

using namespace std;

const int N = 2e4+5;

int n, w, dsu[N], deg[N], pos[N];
bitset<N> chk;
vector<int> g[N], ans[N], topo;
vector<iii> W;

int find(int x) { return dsu[x] = x == dsu[x] ? x : find(dsu[x]); }

int main() {
    iota(dsu, dsu+N, 0);
    scanf("%d %d", &n, &w);
    for(int i = 1, T, a, b, c; i <= w; i++) {
        scanf("%d %d %d %d", &T, &a, &b, &c);
        if(T == 1 || T == 2) W.emplace_back(T, a, b, c);
        else dsu[find(b)] = dsu[find(c)] = find(a);
    }
    for(iii hint : W) {
        int T, a, b, c;
        tie(T, a, b, c) = hint;
        if(T == 1) {
            g[find(b)].emplace_back(find(a));
            g[find(c)].emplace_back(find(a));
            deg[find(a)] += 2;
        } else {
            g[find(a)].emplace_back(find(b));
            g[find(a)].emplace_back(find(c));
            ++deg[find(b)], ++deg[find(c)];
        }
    }
    queue<int> Q;
    for(int i = 1; i <= n; i++) if(!deg[find(i)] && !chk[find(i)]) {
        Q.emplace(find(i));
        chk[find(i)] = true;
    }
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        topo.emplace_back(u);
        for(int v : g[u]) if(!--deg[v])
            Q.emplace(v);
    }
    for(int i = 0; i < (int)topo.size(); i++) pos[topo[i]] = i + 1;
    for(int i = 1; i <= n; i++) ans[pos[find(i)]].emplace_back(i);
    printf("%d\n", (int)topo.size());
    for(int i = 1; i <= (int)topo.size(); i++) {
        printf("%d ", (int)ans[i].size());
        for(int x : ans[i]) printf("%d ", x);
        printf("\n");
    }

    return 0;
}