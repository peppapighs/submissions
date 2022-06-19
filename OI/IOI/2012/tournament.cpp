#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1 << 17;

struct node {
    int mx, pos;
    vector<int> child;
} g[N << 1];

int n, R;
int idx[N], t[N], tmx[N << 1];

void update(int x, int k) {
    if (x <= n)
        t[x] += k, update(x + (x & -x), k);
}

int query(int x) { return t[x] + (x ? query(x - (x & -x)) : 0); }

int get(int x) {
    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (query(mid) >= x)
            r = mid;
        else
            l = mid + 1;
    }
    return r;
}

int query(int l, int r) {
    int ret = 0;
    for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            ret = max(ret, tmx[l++]);
        if (r & 1)
            ret = max(ret, tmx[--r]);
    }
    return ret;
}

int ans, ans_pos;

pii dfs(int u) {
    if (g[u].child.empty())
        return pii(g[u].pos, g[u].pos);
    int l = n + 1, r = 0;
    g[u].pos = 1e9;
    for (int v : g[u].child) {
        pii now = dfs(v);
        l = min(l, now.x), r = max(r, now.y);
        if (g[v].mx > g[u].mx)
            g[u].mx = g[v].mx, g[u].pos = 1e9;
        if (g[v].mx == g[u].mx && g[v].pos < g[u].pos)
            g[u].pos = g[v].pos;
    }
    ++g[u].mx;
    if (query(l, r - 1) < R) {
        if (g[u].mx > ans)
            ans = g[u].mx, ans_pos = 1e9;
        if (g[u].mx == ans && g[u].pos < ans_pos)
            ans_pos = g[u].pos;
    }
    return pii(l, r);
}

int GetBestPosition(int _n, int C, int R, int *K, int *S, int *E) {
    n = _n, ::R = R;
    for (int i = 1; i <= n; i++) {
        update(i, 1);
        idx[i] = i, g[i].pos = i;
        tmx[i + N] = K[i - 1];
    }
    for (int i = N - 1; i; i--)
        tmx[i] = max(tmx[i << 1], tmx[i << 1 | 1]);
    for (int i = 1; i <= C; i++) {
        int s = S[i - 1] + 1, e = E[i - 1] + 1;
        vector<int> vec;
        for (int j = s; j <= e; j++)
            vec.emplace_back(get(j));
        for (int v : vec) {
            g[i + n].child.emplace_back(idx[v]);
            if (v != vec[0])
                update(v, -1);
        }
        idx[vec[0]] = i + n;
    }
    dfs(n + C);
    return ans_pos - (ans_pos ? 1 : 0);
}