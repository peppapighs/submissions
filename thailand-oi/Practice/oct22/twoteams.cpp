#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n, m;
int chk[N];
vector<pii> g[N];

bool dfs(int u, int m, int c = 0) {
    bool valid = true;
    chk[u] = c + 1;
    for (pii v : g[u])
        if (v.y <= m) {
            if (!chk[v.x])
                valid &= dfs(v.x, m, c ^ 1);
            else
                valid &= (chk[v.x] - 1 == c ^ 1);
        }
    return valid;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b, i), g[b].emplace_back(a, i);
    }
    int l = 0, r = m;
    while (l < r) {
        int m = (l + r + 1) >> 1;
        memset(chk, 0, sizeof chk);
        bool valid = true;
        for (int i = 1; i <= n; i++)
            if (!chk[i])
                valid &= dfs(i, m);
        if (valid)
            l = m;
        else
            r = m - 1;
    }
    printf("%d\n", l);

    return 0;
}
