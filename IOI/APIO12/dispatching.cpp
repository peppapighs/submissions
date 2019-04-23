#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, m, c[N], l[N];
int in[N], out[N], pos[N], hv[N];
vector<int> g[N];

int pre(int u, int p) {
    static int idx = 0;
    in[u] = ++idx, pos[idx] = u;
    int sz = 1; pii ret(0, -1);
    for(int v : g[u]) if(v != p) {
        int z = pre(v, u);
        sz += z, ret = max(ret, pii(z, v));
    }
    out[u] = idx, hv[u] = ret.y;
    return sz;
}

long ans, sum;
priority_queue<int> Q;

void add(int u) {
    sum += c[u];
    Q.emplace(c[u]);
    while(sum > m) {
        sum -= Q.top(); 
        Q.pop();
    }
}

void dfs(int u, int p, bool keep) {
    for(int v : g[u]) if(v != p && v != hv[u]) dfs(v, u, 0);
    if(hv[u] != -1) dfs(hv[u], u, 1);

    add(u);
    for(int v : g[u]) if(v != p && v != hv[u])
        for(int i = in[v]; i <= out[v]; i++)
            add(pos[i]);
    ans = max(ans, 1ll * l[u] * (int)Q.size());
    if(!keep) sum = 0, Q = priority_queue<int>();
}

int main() {
    scanf("%d %d", &n, &m);
    int rot;
    for(int i = 1, a; i <= n; i++) {
        scanf("%d %d %d", &a, c+i, l+i);
        if(a) g[a].emplace_back(i), g[i].emplace_back(a);
        else rot = i;
    }
    pre(rot, rot), dfs(rot, rot, 1);
    
    printf("%lld\n", ans);

    return 0;
}