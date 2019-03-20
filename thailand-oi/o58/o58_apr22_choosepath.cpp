#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5+5;

int n, A[N], d[N], hv[N], in[N], out[N], pos[N];
long sum[2][2], ans;
vector<pii> g[N];

int proc(int u, int p) {
    static int idx = 0;
    int sz = 1; pii ret(0, -1);
    in[u] = ++idx, pos[idx] = u;
    for(pii v : g[u]) if(v.x != p) {
        d[v.x] = d[u] + v.y;
        int z = proc(v.x, u);
        sz += z;
        ret = max(ret, pii(z, v.x));
    }
    out[u] = idx, hv[u] = ret.y;
    return sz;
}

void calc(int u) {
    ans += sum[d[u] & 1][A[u] > 0] * A[u];
    ans -= sum[~d[u] & 1][A[u] < 0] * A[u];
}

void add(int u, bool b) {
    sum[d[u] & 1][A[u] > 0] += b ? -A[u] : A[u];
}

void dfs(int u, int p, bool keep) {
    for(pii v : g[u]) if(v.x != p && v.x != hv[u]) dfs(v.x, u, 0);
    if(hv[u] != -1) dfs(hv[u], u, 1);
    calc(u), add(u, 0);
    for(pii v : g[u]) if(v.x != p && v.x != hv[u]) {
        for(int i = in[v.x]; i <= out[v.x]; i++) calc(pos[i]);
        for(int i = in[v.x]; i <= out[v.x]; i++) add(pos[i], 0);
    }
    if(!keep) for(int i = in[u]; i <= out[u]; i++) add(pos[i], 1);
}

int main() {
    scanf("%d %d", &n, A);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d %d", A+i, &a, &b);
        g[i].emplace_back(a, b), g[a].emplace_back(i, b);
    }
    proc(0, 0), dfs(0, 0, 1);
    printf("%lld\n", ans);

    return 0;
}
