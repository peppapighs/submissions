#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;

int n, m, q;
int t[N], x[N], block[N];
int chk1[N], chk2[N];
vector<int> g[N], h[N];

void dfs1(int u) {
    chk1[u] = 1;
    for (int v : g[u])
        if (!chk1[v] && !block[v])
            dfs1(v);
}

void dfs2(int u) {
    chk2[u] = 1;
    for (int v : h[u])
        if (!chk2[v] && !block[v])
            dfs2(v);
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b);
        h[b].emplace_back(a);
    }
    for (int i = 1; i <= q; i++) {
        scanf("%d %d", t + i, x + i);
        if (t[i] == 1)
            block[x[i]] = 1;
    }
    dfs1(1), dfs2(n);
    vector<int> ans;
    for (int i = q; i; i--) {
        if (t[i] == 1) {
            int u = x[i];
            block[u] = 0;
            for (int v : g[u])
                if (!block[v]) {
                    if (chk1[v])
                        dfs1(v);
                    if (chk2[v])
                        dfs2(v);
                }
            for (int v : h[u])
                if (!block[v]) {
                    if (chk1[v])
                        dfs1(v);
                    if (chk2[v])
                        dfs2(v);
                }
        } else
            ans.emplace_back(chk1[x[i]] && chk2[x[i]]);
    }
    reverse(ans.begin(), ans.end());
    for (int i : ans)
        printf("%d\n", i);

    return 0;
}