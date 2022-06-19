#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii mul(pii a, pii b) { return pii(a.x * b.x, a.y * b.y); }

int n, m;
int c;
int deg[N], chk[N];
vector<int> g[N];
set<pair<int, pii>> hsh;
pii hpow[N], iden(69, 6969);

void dfs(int u, int p, pii &h, int cnt) {
    chk[u] = true;
    ++c;
    if (g[u].size() == 3)
        h = add(h, hpow[cnt]), cnt = -1;
    ++cnt;
    if (g[u].size() == 1 && p)
        h = add(h, hpow[cnt]);
    for (int v : g[u])
        if (v != p) {
            if (chk[v])
                h = add(h, pii(-123, -456));
            else
                dfs(v, u, h, cnt);
        }
}

int main() {
    hpow[0] = pii(1, 1);
    for (int i = 1; i < N; i++)
        hpow[i] = mul(hpow[i - 1], iden);
    scanf("%d %d", &n, &m);
    while (m--) {
        int a, b;
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
        ++deg[a], ++deg[b];
    }
    for (int i = 1; i <= n; i++)
        if (g[i].size() <= 1 && !chk[i]) {
            c = 0;
            pii p(0, 0);
            dfs(i, 0, p, 0);
            hsh.emplace(c, p);
        }
    for (int i = 1; i <= n; i++)
        if (!chk[i]) {
            c = 0;
            pii p(0, 0);
            dfs(i, 0, p, 0);
            hsh.emplace(c, p);
        }
    printf("%d\n", (int)hsh.size());

    return 0;
}
