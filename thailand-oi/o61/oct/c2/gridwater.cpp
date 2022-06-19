#include <bits/stdc++.h>

#define iii tuple<int, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 180005;

int m, n;
int dsu[N], par[N][18], mx[N][18], dep[N];
vector<iii> E, L;
vector<pii> g[N];

int get(int r, int c) { return n * (r - 1) + c; }

int find(int x) { return dsu[x] = x == dsu[x] ? x : find(dsu[x]); }

void dfs(int u, int p) {
    par[u][0] = p, dep[u] = dep[p] + 1;
    for (int i = 1; i < 18; i++) {
        par[u][i] = par[par[u][i - 1]][i - 1];
        mx[u][i] = max(mx[u][i - 1], mx[par[u][i - 1]][i - 1]);
    }
    for (pii v : g[u])
        if (v.x != p) {
            mx[v.x][0] = v.y;
            dfs(v.x, u);
        }
}

int lca(int a, int b) {
    int ret = 0;
    if (dep[a] < dep[b])
        swap(a, b);
    for (int i = 17; ~i; i--)
        if (dep[par[a][i]] >= dep[b]) {
            ret = max(ret, mx[a][i]);
            a = par[a][i];
        }
    if (a == b)
        return ret;
    for (int i = 17; ~i; i--)
        if (par[a][i] != par[b][i]) {
            ret = max({ret, mx[a][i], mx[b][i]});
            a = par[a][i], b = par[b][i];
        }
    return max({ret, mx[a][0], mx[b][0]});
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> m >> n;

    for (int i = 1; i < N; i++)
        dsu[i] = i;
    for (int i = 1; i < 2 * m; i++) {
        if (i & 1)
            for (int j = 1, a; j < n; j++) {
                cin >> a;
                E.emplace_back(a, get((i + 1) / 2, j), get((i + 1) / 2, j + 1));
            }
        else
            for (int j = 1, a; j <= n; j++) {
                cin >> a;
                E.emplace_back(a, get(i / 2, j), get(i / 2 + 1, j));
            }
    }
    sort(E.begin(), E.end());
    for (iii e : E) {
        int a, b, c;
        tie(c, a, b) = e;
        int pa = find(a), pb = find(b);
        if (pa != pb) {
            dsu[pa] = pb;
            g[a].emplace_back(b, c), g[b].emplace_back(a, c);
        } else
            L.emplace_back(a, b, c);
    }
    dfs(1, 1);

    int ans = 2e9;
    for (iii e : L) {
        int a, b, c;
        tie(a, b, c) = e;
        ans = min(ans, c - lca(a, b));
    }
    cout << ans << endl;

    return 0;
}