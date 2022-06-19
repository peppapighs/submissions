#include "paint.h"
#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;
const int M = 650;

int n, m, k;
int valid[N], dp[N];
vector<int> col[N];

int minimumInstructions(int _n, int _m, int _k, vector<int> C, vector<int> A,
                        vector<vector<int>> B) {
    fill_n(dp, N, 1e9);

    n = _n, m = _m, k = _k;
    C.insert(C.begin(), 0), A.insert(A.begin(), 0),
        B.insert(B.begin(), vector<int>());

    for (int i = 1; i <= m; i++)
        for (int x : B[i])
            col[x].emplace_back(i);

    vector<int> pre(M, 0);
    for (int i = 1; i <= n; i++) {
        int j = 1;
        vector<int> cur(M, 1);
        for (int idx = 0; idx < col[C[i]].size(); idx++) {
            int x = col[C[i]][idx];
            if (x != 1) {
                while (j + 1 <= col[C[i - 1]].size() &&
                       col[C[i - 1]][j] <= x - 1)
                    ++j;
                if (j > col[C[i - 1]].size() || col[C[i - 1]][j - 1] != x - 1)
                    continue;
                cur[idx + 1] = pre[j] + 1;
            } else {
                if (col[C[i - 1]].empty() || col[C[i - 1]].back() != m)
                    continue;
                cur[idx + 1] = pre[col[C[i - 1]].size()] + 1;
            }
            if (cur[idx + 1] >= m)
                valid[i] = true;
        }
        swap(cur, pre);
    }

    deque<pii> Q;
    Q.emplace_back(0, dp[0] = 0);
    for (int i = 1; i <= n; i++) {
        while (!Q.empty() && Q.front().x < i - m)
            Q.pop_front();
        if (valid[i] && !Q.empty()) {
            dp[i] = Q.front().y + 1;
            while (!Q.empty() && Q.back().y > dp[i])
                Q.pop_back();
            Q.emplace_back(i, dp[i]);
        }
    }

    return dp[n] == 1e9 ? -1 : dp[n];
}
