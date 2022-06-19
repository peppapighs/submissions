#include <bits/stdc++.h>

#define iii tuple<int, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e3 + 5;

struct node {
    int u;
    node *l, *r;
    node(int u) : u(u), l(NULL), r(NULL) {}
};

int n, m, s, t, ans;
int pre[N], low[N], inv[N], par[N];
int sig[N], chk[N], pos[N], ptr;
vector<int> g[N];
vector<iii> E;
map<int, node *> M;

void tarjan(int u, int p) {
    static int idx = 0;
    pre[u] = low[u] = ++idx, inv[idx] = u;
    par[u] = p;
    for (int v : g[u])
        if (v != p) {
            if (!pre[v]) {
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
            } else
                low[u] = min(low[u], pre[v]);
        }
}

void dfs(int u) {
    chk[u] = true;
    if (u != s && u != t) {
        if (sig[inv[low[u]]] == -1) {
            node *now = new node(u);
            now->l = M[par[u]]->l, now->r = M[par[u]];
            if (M[par[u]]->l)
                M[par[u]]->l->r = now;
            M[par[u]]->l = now;
            M[u] = now;
        } else {
            node *now = new node(u);
            now->l = M[par[u]], now->r = M[par[u]]->r;
            if (M[par[u]]->r)
                M[par[u]]->r->l = now;
            M[par[u]]->r = now;
            M[u] = now;
        }
        sig[par[u]] = -sig[inv[low[u]]];
    }
    for (int v : g[u])
        if (!chk[v])
            dfs(v);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        E.emplace_back(c, a, b);
    }
    sort(E.begin(), E.end());

    tie(ans, s, t) = E[0];
    g[s].emplace_back(t), g[t].emplace_back(s);
    for (int i = 1; i < (int)E.size(); i++) {
        int a, b, c;
        tie(c, a, b) = E[i];
        g[a].emplace_back(b), g[b].emplace_back(a);
    }

    sig[s] = -1;
    node *hd = new node(s), *tl = new node(t);
    hd->r = tl, tl->l = hd;
    M[s] = hd, M[t] = tl;

    tarjan(s, 0), dfs(s);

    for (node *now = M[s]; now; now = now->r)
        pos[now->u] = ++ptr;
    printf("%d 1\n", ans);
    printf("%d %d 1\n", t, s);
    for (int i = 1; i < (int)E.size(); i++) {
        int a, b, c;
        tie(c, a, b) = E[i];
        if (pos[a] > pos[b])
            swap(a, b);
        printf("%d %d 0\n", a, b);
    }

    return 0;
}
