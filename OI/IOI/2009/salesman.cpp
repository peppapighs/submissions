#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 5e5 + 5;
const int INF = 1e9 + 1;

void update(int t[], int x, int k) {
    for (t[x += N] = k; x != 1; x >>= 1)
        t[x >> 1] = max(t[x], t[x ^ 1]);
}

int query(int t[], int l, int r) {
    int ret = -INF;
    for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            ret = max(ret, t[l++]);
        if (r & 1)
            ret = max(ret, t[--r]);
    }
    return ret;
}

int n, u, d, s;
int dp[N], t1[N << 1], t2[N << 1];
vector<pii> fair[N];

int main() {
    scanf("%d %d %d %d", &n, &u, &d, &s);
    for (int i = 1, d, a, b; i <= n; i++) {
        scanf("%d %d %d", &d, &a, &b);
        fair[d].emplace_back(a, b);
    }
    fair[N - 1].emplace_back(s, 0);
    for (int i = 0; i < N; i++) {
        dp[i] = (i == s ? 0 : -INF);
        update(t1, i, dp[i] + i * d);
        update(t2, i, dp[i] - i * u);
    }

    for (int i = 0; i < N; i++) {
        sort(fair[i].begin(), fair[i].end());
        int mx = -INF;
        map<int, int> mp;
        for (int j = 0, pos, m; j < fair[i].size(); j++) {
            tie(pos, m) = fair[i][j];
            int down_stream = max(mx, query(t1, 0, pos)) - pos * d;
            int up_stream = query(t2, pos, N - 1) + pos * u;
            mp[pos] = max(down_stream, up_stream) + m;
            mx = max(mx, mp[pos] + pos * d);
        }
        mx = -INF;
        for (int j = fair[i].size() - 1, pos, m; ~j; j--) {
            tie(pos, m) = fair[i][j];
            int down_stream = query(t1, 0, pos) - pos * d;
            int up_stream = max(mx, query(t2, pos, N - 1)) + pos * u;
            dp[pos] = max(down_stream, up_stream) + m;
            mx = max(mx, dp[pos] - pos * u);
        }
        for (int j = 0, pos, m; j < fair[i].size(); j++) {
            tie(pos, m) = fair[i][j];
            dp[pos] = max(dp[pos], mp[pos]);
            update(t1, pos, dp[pos] + pos * d);
            update(t2, pos, dp[pos] - pos * u);
        }
    }

    printf("%d\n", dp[s]);

    return 0;
}