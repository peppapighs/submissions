#include "garden.h"
#include "gardenlib.h"
#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;

int d[N << 1];
vector<pii> pre[N];
vector<int> g[N << 1];

void count_routes(int n, int m, int p, int r[][2], int q, int _g[]) {
    for (int i = 0; i < m; i++) {
        int a = r[i][0], b = r[i][1];
        if (pre[a].size() < 2)
            pre[a].emplace_back(b, i);
        if (pre[b].size() < 2)
            pre[b].emplace_back(a, i);
    }
    for (int i = 0; i < n; i++)
        if (pre[i].size() == 1)
            pre[i].emplace_back(pre[i][0]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < (int)pre[i].size(); j++) {
            int v = pre[i][j].x, id = pre[i][j].y;
            if (pre[v][0].y == id)
                v += n;
            g[v].emplace_back(i + (j ? n : 0));
        }
    int cyc_sz = 0;
    auto get_dist = [&](int a) {
        vector<int> chk(n << 1), S;
        fill_n(d, N << 1, 1e9 + 1);
        function<void(int)> dfs = [&](int u) {
            chk[u] = 1, S.emplace_back(u);
            for (int v : g[u]) {
                if (!chk[v])
                    d[v] = d[u] + 1, dfs(v);
                else if (chk[v] == 1)
                    for (int i = S.size() - 1; ~i; i--) {
                        ++cyc_sz;
                        if (S[i] == v)
                            break;
                    }
            }
            chk[u] = 2, S.pop_back();
        };
        d[a] = cyc_sz = 0;
        dfs(a);
    };
    auto get_ans = [&](int len) {
        int ret = 0;
        for (int i = 0; i < n; i++) {
            if (d[i] > len)
                continue;
            if (cyc_sz)
                ret += ((len - d[i]) % cyc_sz == 0);
            else
                ret += (d[i] == len);
        }
        return ret;
    };
    vector<int> ans(q, 0);
    get_dist(p);
    for (int i = 0; i < q; i++)
        ans[i] += get_ans(_g[i]);
    get_dist(p + n);
    for (int i = 0; i < q; i++)
        answer(ans[i] + get_ans(_g[i]));
}