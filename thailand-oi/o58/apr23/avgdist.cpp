#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 3e4 + 5;

int n, k, q, A[N], col[15];
int chk[N], sz[N], par[N], dep[N];
long d[N][17], sum1[15][N], sum2[15][N], ans[15];
int cnt1[15][N], cnt2[15][N];
vector<pii> g[N];

int getsz(int u, int p) {
    sz[u] = 1;
    for (pii v : g[u])
        if (v.x != p && !chk[v.x])
            sz[u] += getsz(v.x, u);
    return sz[u];
}

int find_cen(int u, int p, int all, pii &ret) {
    int mx = all - sz[u];
    for (pii v : g[u])
        if (v.x != p && !chk[v.x])
            mx = max(mx, find_cen(v.x, u, all, ret));
    ret = min(ret, pii(mx, u));
    return sz[u];
}

void dfs(int u, int p, int lvl) {
    for (pii v : g[u])
        if (v.x != p && !chk[v.x]) {
            d[v.x][lvl] = d[u][lvl] + v.y;
            dfs(v.x, u, lvl);
        }
}

void centroid(int u, int p) {
    getsz(u, u);
    pii ret(sz[u] + 1, -1);
    find_cen(u, u, sz[u], ret);
    par[u = ret.y] = p, dep[u] = dep[p] + 1, chk[u] = true;
    dfs(u, u, dep[u]);
    for (pii v : g[u])
        if (!chk[v.x])
            centroid(v.x, u);
}

void getans(int a, bool del) {
    ans[A[a]] += sum1[A[a]][a] * (del ? -1ll : 1ll);
    for (int i = par[a], pv = a; i; pv = i, i = par[i]) {
        ans[A[a]] += (sum1[A[a]][i] - sum2[A[a]][pv]) * (del ? -1ll : 1ll);
        ans[A[a]] += (d[a][dep[i]] * (cnt1[A[a]][i] - cnt2[A[a]][pv])) *
                     (del ? -1ll : 1ll);
    }
}

void update(int a, bool del) {
    if (del)
        --col[A[a]], --cnt1[A[a]][a];
    else
        ++col[A[a]], ++cnt1[A[a]][a];
    for (int i = par[a], pv = a; i; pv = i, i = par[i]) {
        sum1[A[a]][i] += d[a][dep[i]] * (del ? -1ll : 1ll);
        sum2[A[a]][pv] += d[a][dep[i]] * (del ? -1ll : 1ll);
        if (del)
            --cnt1[A[a]][i], --cnt2[A[a]][pv];
        else
            ++cnt1[A[a]][i], ++cnt2[A[a]][pv];
    }
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", A + i);
    for (int i = 1, a, b, c; i < n; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b, c), g[b].emplace_back(a, c);
    }
    centroid(1, 0);
    for (int i = 1; i <= n; i++)
        getans(i, 0), update(i, 0);
    scanf("%d", &q);
    for (int i = 1, T, a, b; i <= q; i++) {
        scanf("%d %d", &T, &a);
        if (T == 1) {
            if (col[a] < 2)
                printf("0\n");
            else
                printf("%f\n", (double)ans[a] /
                                   (double)(1ll * col[a] * (col[a] - 1) / 2ll));
        } else {
            scanf("%d", &b);
            update(a, 1), getans(a, 1);
            A[a] = b;
            getans(a, 0), update(a, 0);
        }
    }

    return 0;
}