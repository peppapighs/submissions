#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, m, l;
int low[N], disc[N], d[N];
bool ap[N];
vector<int> g[N];

bool tarjan(int u, int p) {
    static int idx = 0;
    low[u] = disc[u] = ++idx;
    bool valid = (u == n);
    for (int v : g[u])
        if (v != p) {
            if (!disc[v]) {
                bool b = tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (b && low[v] >= disc[u])
                    ap[u] = true;
                valid |= b;
            } else
                low[u] = min(low[u], disc[v]);
        }
    return valid;
}

int main() {
    fill_n(d, N, 1e9);
    scanf("%d %d %d", &n, &m, &l);
    for (int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    tarjan(1, 1);
    vector<int> vec;
    queue<int> Q;
    d[1] = 0, Q.emplace(1);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int v : g[u])
            if (d[v] > d[u] + 1) {
                d[v] = d[u] + 1;
                Q.emplace(v);
            }
    }

    for (int i = 2; i < n; i++)
        if (ap[i])
            vec.emplace_back(i);
    sort(vec.begin(), vec.end(),
         [&](const int &a, const int &b) { return d[a] < d[b]; });

    if (vec.empty())
        return !printf("0\n");
    int ans = 1, prev = 0;
    for (int i = 1; i < (int)vec.size(); i++)
        if (d[vec[i]] - d[vec[prev]] > 2 * l)
            ++ans, prev = i;

    printf("%d\n", ans);

    return 0;
}
