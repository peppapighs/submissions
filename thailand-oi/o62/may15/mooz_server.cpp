#include "mooz_server.h"
#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 305;

int n, ecnt;
bitset<N> chk;
vector<int> g[N];
vector<pii> ans;

void gen_tree(int u) {
    chk[u] = true;
    while (true) {
        if (ecnt == n - 1)
            return;
        vector<int> cand;
        for (int i = 1; i <= n; i++)
            if (!chk[i])
                cand.emplace_back(i);
        if (cand.empty())
            break;

        int l = 0, r = (int)cand.size() - 1, res = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;

            vector<int> now(cand.begin(), cand.begin() + mid + 1);
            int t1 = get_component(now);
            now.emplace_back(u);
            int t2 = get_component(now);

            if (t1 + 1 == t2)
                l = mid + 1;
            else
                res = mid, r = mid - 1;
        }
        if (res == -1)
            break;
        g[u].emplace_back(cand[res]), g[cand[res]].emplace_back(u);
        ++ecnt;
        gen_tree(cand[res]);
    }
}

int pre[N], low[N];

void solve(int u, int p) {
    static int idx = 0;
    static vector<int> path;

    pre[u] = low[u] = ++idx;
    path.emplace_back(u);
    for (int v : g[u])
        if (v != p) {
            solve(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > pre[u])
                ans.emplace_back(min(u, v), max(u, v));
        }
    vector<int> cand = path;
    if (cand.size() > 2) {
        cand.pop_back(), cand.pop_back();
        int l = 0, r = (int)cand.size() - 1, res = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;

            vector<int> now(cand.begin(), cand.begin() + mid + 1);
            int t1 = get_component(now);
            now.emplace_back(u);
            int t2 = get_component(now);

            if (t1 + 1 == t2)
                l = mid + 1;
            else
                res = mid, r = mid - 1;
        }
        if (res != -1 && cand[res] != p)
            low[u] = min(low[u], pre[cand[res]]);
    }

    path.pop_back();
}

vector<pii> find_bridge(int _n) {
    n = _n;
    gen_tree(1), solve(1, 0);

    sort(ans.begin(), ans.end());
    ans.resize(unique(ans.begin(), ans.end()) - ans.begin());

    return ans;
}