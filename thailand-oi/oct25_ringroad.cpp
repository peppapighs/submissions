#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5+5;

int n, k, q;
int t[N+1], A[N], par[N], dep[N];
vector<pii> g[N];

void update(int x, int k) { for(int i = x; i < N; i += i & -i) t[i] += k; }

int get(int x) {
        int ret = 0;
        for(int i = x; i; i -= i & -i) ret += t[i];
        return ret;
}

void dfs(int u, int p, int st) {
        par[u] = st;
        for(pii v : g[u]) if(v.x != p) dep[v.x] = dep[u] + v.y, dfs(v.x, u, st);
}

int main() {
        scanf("%d %d %d", &n, &k, &q);
        for(int i = 1; i <= k; i++) {
                scanf("%d", A+i);
                update(i, A[i]);
        }
        for(int i = k+1; i <= n; i++) {
                int a, b;
                scanf("%d %d", &a, &b);
                g[i].emplace_back(a, b), g[a].emplace_back(i, b);
        }
        for(int i = 1; i <= k; i++) dfs(i, i, i);
        while(q--) {
                int T, a, b;
                scanf("%d %d %d", &T, &a, &b);
                if(T == 0) update(a, b-A[a]), A[a] = b;
                else if(par[a] == par[b]) printf("%d\n", abs(dep[a] - dep[b]));
                else {
                        int pa = par[a], pb = par[b];
                        if(pa > pb) swap(pa, pb);
                        int dist = min(get(pb-1) - get(pa-1), get(pa-1) + get(k) - get(pb-1));
                        printf("%d\n", dist + dep[a] + dep[b]);
                }
        }

        return 0;
}
