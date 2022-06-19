#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
vector<vector<int>> tree(N);
int dp[N];
vector<long long> pre;

int dfs1(int u) {
    int mx = -1;
    for (int v : tree[u]) {
        mx = max(mx, dfs1(v));
    }
    mx = max(mx, u);
    dp[u] = mx;
    return mx;
}

bool compare(const int &a, const int &b) { return dp[a] < dp[b]; }

void dfs2(int u) {
    sort(tree[u].begin(), tree[u].end(), compare);
    for (int i = 0; i < tree[u].size(); i++) {
        dfs2(tree[u][i]);
    }
    pre.emplace_back(u + 1);
}

int main() {
    pre.emplace_back(0);
    int n, m;
    int rt;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        int v;
        scanf("%d", &v);
        if (v == 0) {
            rt = i;
        } else {
            tree[--v].emplace_back(i);
        }
    }

    dfs1(rt);
    dfs2(rt);

    for (int i = 1; i < pre.size(); i++) {
        pre[i] += pre[i - 1];
    }
    int cur = 0;
    while (m--) {
        int t;
        scanf("%d", &t);
        if (t == 1) {
            int k;
            scanf("%d", &k);
            cur += k;
            printf("%lld\n", pre[cur] - pre[cur - 1]);
        } else if (t == 2) {
            int k;
            scanf("%d", &k);
            cur -= k;
        } else {
            printf("%lld\n", pre[cur]);
        }
    }

    return 0;
}