#include "dreaming.h"
#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

vector<vector<pii>> g(N);
pii dp[N];
bitset<N> vis;
vector<int> center;
int dm;

pii dfs1(int u, int p, int d) {
    vis[u] = 1;
    dp[u] = pii(p, d);
    pii ret = {d, u};
    for (pii v : g[u])
        if (v.x != p)
            ret = max(ret, dfs1(v.x, u, d + v.y));
    return ret;
}

bool comp(const int &a, const int &b) { return a > b; }

int travelTime(int N, int M, int L, int A[], int B[], int T[]) {
    for (int i = 0; i < M; i++) {
        g[A[i]].emplace_back(B[i], T[i]);
        g[B[i]].emplace_back(A[i], T[i]);
    }

    for (int i = 0; i < N; i++)
        if (!vis[i]) {
            vector<pii> path;
            int root = dfs1(i, i, 0).y;
            pii leaf = dfs1(root, root, 0);

            int now = leaf.y;
            int diameter = leaf.x;
            dm = max(dm, diameter);

            if (M == N - 1)
                return diameter;

            while (dp[now].x != now) {
                path.emplace_back(now, dp[now].y);
                now = dp[now].x;
            }
            path.emplace_back(root, 0);
            int mxd = INT_MAX;
            for (pii node : path)
                if (max(node.y, diameter - node.y) < mxd)
                    mxd = max(node.y, diameter - node.y);
            center.emplace_back(mxd);
        }

    sort(center.begin(), center.end(), comp);
    if (center.size() == 2)
        return max(center[0] + center[1] + L, dm);
    else
        return max(
            dm, max(center[0] + center[1] + L, center[1] + center[2] + 2 * L));
}

/*int main() {
        int n, m, l;
        scanf("%d%d%d", &n, &m, &l);
        int a[m], b[m], t[m];
        for(int i = 0; i < m; i++) {
                scanf("%d%d%d", &a[i], &b[i], &t[i]);
        }

        printf("%d", travelTime(n, m, l, a, b, t));

        return 0;
}*/