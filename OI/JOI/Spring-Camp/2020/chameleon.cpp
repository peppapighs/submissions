#include "chameleon.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;

int same[N], nex[N], pre[N];
vector<int> g[N];

bool find_edge(vector<int> v, int x) {
    v.emplace_back(x);
    return Query(v) < v.size();
}

void Solve(int n) {
    n *= 2;
    for (int i = 1; i <= n; i++) {
        vector<int> col(n + 1), vec[3];
        function<void(int, int)> dfs = [&](int u, int c) {
            col[u] = c;
            for (int v : g[u])
                if (!col[v])
                    dfs(v, c ^ 3);
        };
        for (int j = 1; j < i; j++) {
            if (!col[j])
                dfs(j, 1);
            vec[col[j]].emplace_back(j);
        }
        for (int j = 1; j <= 2; j++) {
            vector<int> now = vec[j];
            while (find_edge(now, i)) {
                int l = 0, r = now.size() - 1;
                while (l < r) {
                    int mid = (l + r) >> 1;
                    vector<int> v(now.begin(), now.begin() + mid + 1);
                    if (find_edge(v, i))
                        r = mid;
                    else
                        l = mid + 1;
                }
                g[now[r]].emplace_back(i), g[i].emplace_back(now[r]);
                now = vector<int>(now.begin() + r + 1, now.end());
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (g[i].size() == 1)
            same[i] = g[i][0];
        else {
            while (Query({i, g[i][0], g[i][1]}) != 1) {
                int x = g[i][0];
                g[i].erase(g[i].begin()), g[i].emplace_back(x);
            }
            nex[i] = g[i][2], pre[g[i][2]] = i;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!same[i])
            same[i] = g[i][0] + g[i][1] + g[i][2] - nex[i] - pre[i];
        if (i < same[i])
            Answer(i, same[i]);
    }
}
