#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, m, x, sz;
int suf[N], pos[N], lcp[N << 1];
int dp[35][N];
char A[N];

int query_rmq(int l, int r) {
    int mn = 1e9;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            mn = min(mn, lcp[l++]);
        if (r & 1)
            mn = min(mn, lcp[--r]);
    }
    return mn;
}

int get_lcp(int a, int b) {
    a = pos[a], b = pos[b];
    if (a > b)
        swap(a, b);
    return query_rmq(a, b);
}

int main() {
    scanf("%d %s", &n, A);
    A[n] = '#';
    scanf("%d %s %d", &m, A + n + 1, &x);

    sz = n + m + 1;
    for (int i = 0; i < sz; i++)
        suf[i] = i, pos[i] = A[i];
    for (int k = 1; k <= sz; k <<= 1) {
        auto cmp = [&](int a, int b) {
            if (pos[a] != pos[b])
                return pos[a] < pos[b];
            if (a + k < sz && b + k < sz)
                return pos[a + k] < pos[b + k];
            return a > b;
        };
        sort(suf, suf + sz, cmp);
        int tmp[N];
        tmp[0] = 0;
        for (int i = 1; i < sz; i++)
            tmp[i] = tmp[i - 1] + cmp(suf[i - 1], suf[i]);
        for (int i = 0; i < sz; i++)
            pos[suf[i]] = tmp[i];
    }

    for (int i = 0, k = 0; i < sz; i++)
        if (pos[i] != sz - 1) {
            for (int j = suf[pos[i] + 1]; A[j + k] == A[i + k]; k++)
                ;
            lcp[pos[i] + N] = k;
            if (k)
                --k;
        }
    for (int i = N - 1; i; i--)
        lcp[i] = min(lcp[i << 1], lcp[i << 1 | 1]);

    bool valid = false;
    for (int i = 0; i <= x; i++)
        for (int j = 0; j <= n; j++) {
            if (j + 1 < n)
                dp[i][j + 1] = max(dp[i][j + 1], dp[i][j]);
            int lcp = get_lcp(j, dp[i][j] + n + 1);
            if (i + 1 <= x && j + lcp <= n)
                dp[i + 1][j + lcp] = max(dp[i + 1][j + lcp], dp[i][j] + lcp);
            if (dp[i][j] == m)
                valid = true;
        }

    if (valid)
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}