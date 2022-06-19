#include <bits/stdc++.h>

#define long long long
#define iii tuple<int, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int dsu[N];

void init() { iota(dsu, dsu + N, 0); }

int find(int x) { return dsu[x] = x == dsu[x] ? x : find(dsu[x]); }

int n, m, k;
long ans;
vector<iii> E, sure, cmp;
vector<pii> toll;
vector<int> g[25];

int cid[N], sz[N];
int par[25], dep[25], weight[25], chk[25];
long csz[25], subsz[25];

void dfs(int u, int p) {
    par[u] = p, dep[u] = dep[p] + 1;
    for (int v : g[u])
        if (v != p) {
            dfs(v, u);
            subsz[u] += subsz[v];
        }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        E.emplace_back(c, a, b);
    }

    sort(E.begin(), E.end());
    init();
    vector<iii> mst_edge;
    for (iii e : E) {
        int a, b, c;
        tie(c, a, b) = e;
        if (find(a) != find(b)) {
            dsu[find(a)] = find(b);
            mst_edge.emplace_back(e);
        }
    }
    swap(E, mst_edge);

    init();
    for (int i = 1, a, b; i <= k; i++) {
        scanf("%d %d", &a, &b);
        toll.emplace_back(a, b);
        dsu[find(a)] = find(b);
    }
    for (int i = 1; i <= n; i++)
        scanf("%d", sz + i);
    for (iii e : E) {
        int a, b, c;
        tie(c, a, b) = e;
        if (find(a) != find(b)) {
            dsu[find(a)] = find(b);
            sure.emplace_back(e);
        } else
            cmp.emplace_back(e);
    }

    init();
    for (iii e : sure) {
        int a, b, c;
        tie(c, a, b) = e;
        dsu[find(a)] = find(b);
    }
    int ptr = 0;
    for (int i = 1; i <= n; i++)
        if (find(i) == i)
            cid[i] = ++ptr;
    for (int i = 1; i <= n; i++)
        if (find(i) != i)
            cid[i] = cid[find(i)];
    for (int i = 1; i <= n; i++)
        csz[cid[i]] += sz[i];

    for (int bit = 0; bit < (1 << k); bit++) {
        memset(chk, 0, sizeof chk);
        for (int i = 1; i <= ptr; i++) {
            g[i].clear();
            subsz[i] = csz[i];
            dsu[i] = i;
        }

        bool valid = true;
        for (int i = 0; i < k; i++)
            if (bit >> i & 1) {
                int a = toll[i].x, b = toll[i].y;
                if (find(cid[a]) == find(cid[b])) {
                    valid = false;
                    break;
                } else {
                    g[cid[a]].emplace_back(cid[b]);
                    g[cid[b]].emplace_back(cid[a]);
                    dsu[find(cid[a])] = find(cid[b]);
                }
            }
        if (!valid)
            continue;
        for (int i = 0; i < cmp.size(); i++) {
            int a, b, c;
            tie(c, a, b) = cmp[i];
            if (find(cid[a]) != find(cid[b])) {
                g[cid[a]].emplace_back(cid[b]);
                g[cid[b]].emplace_back(cid[a]);
                dsu[find(cid[a])] = find(cid[b]);
                chk[i] = true;
            }
        }
        dfs(cid[1], 0);

        for (int i = 0; i < cmp.size(); i++)
            if (chk[i]) {
                int a, b, c;
                tie(c, a, b) = cmp[i];
                if (par[cid[b]] == cid[a])
                    swap(a, b);
                weight[cid[a]] = 0;
            }
        for (int i = 0; i < k; i++)
            if (bit >> i & 1) {
                int a, b;
                tie(a, b) = toll[i];
                if (par[cid[b]] == cid[a])
                    swap(a, b);
                weight[cid[a]] = 1e9;
            }

        for (int i = 0; i < cmp.size(); i++)
            if (!chk[i]) {
                int a = get<1>(cmp[i]), b = get<2>(cmp[i]), c = get<0>(cmp[i]);
                a = cid[a], b = cid[b];
                if (dep[a] < dep[b])
                    swap(a, b);

                while (dep[a] > dep[b]) {
                    weight[a] = min(weight[a], c);
                    a = par[a];
                }
                while (a != b) {
                    weight[a] = min(weight[a], c);
                    weight[b] = min(weight[b], c);
                    a = par[a], b = par[b];
                }
            }

        long ret = 0;
        for (int i = 1; i <= ptr; i++)
            ret += 1ll * weight[i] * subsz[i];
        ans = max(ans, ret);
    }
    printf("%lld\n", ans);

    return 0;
}