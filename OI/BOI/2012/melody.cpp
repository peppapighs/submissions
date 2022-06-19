#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 105;
const int M = 1e5 + 5;

int n, m, s, g;
char S[N][N];

bool edge[N][N];

void bfs(int src, int *dist, int *par) {
    fill_n(dist, N, 1e9), memset(par, -1, sizeof par);

    queue<pii> Q;
    Q.emplace(src, dist[src] = 0), par[src] = 0;
    while (!Q.empty()) {
        pii u = Q.front();
        Q.pop();
        if (dist[u.x] != u.y)
            continue;
        for (int i = 1; i <= n; i++)
            if (edge[u.x][i] && dist[i] == 1e9)
                Q.emplace(i, dist[i] = u.y + 1), par[i] = u.x;
    }
}

int dist[N][N], par[N][N];

int A[M], dp[M], pre[M];
vector<int> last[N];

int main() {
    fill_n(dp, M, 1e9), memset(pre, -1, sizeof pre);

    scanf("%d %d %d", &n, &s, &g);
    for (int i = 1; i <= n; i++)
        scanf(" %s", S[i] + 1), last[i].emplace_back(0);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            int cnt = 0;
            for (int k = 1; k <= s; k++)
                cnt += (S[i][k] != S[j][k]);
            if (cnt <= g)
                edge[i][j] = true;
        }
    for (int i = 1; i <= n; i++)
        bfs(i, dist[i], par[i]);

    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", A + i);
        last[A[i]].emplace_back(i);
    }

    dp[0] = 0;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            auto it = upper_bound(last[j].begin(), last[j].end(),
                                  i - dist[A[i]][j] - (A[i] == j));
            if (it == last[j].begin())
                continue;

            int idx = *--it;
            if (dp[idx] + i - idx - 1 < dp[i]) {
                dp[i] = dp[idx] + i - idx - 1;
                pre[i] = idx;
            }
        }

    int mn = 1e9, cur = -1;
    vector<int> ans;
    for (int i = 1; i <= m; i++)
        if (dp[i] + m - i < mn)
            mn = dp[i] + m - i, cur = i;

    printf("%d\n", mn);
    for (int i = cur; i <= m; i++)
        ans.emplace_back(A[cur]);
    while (cur) {
        int nex = pre[cur];
        if (!nex)
            for (int i = 1; i < cur; i++)
                ans.emplace_back(A[cur]);
        else {
            int sz = cur - nex, now = A[cur];
            while (now != A[nex]) {
                ans.emplace_back(par[A[nex]][now]);
                now = par[A[nex]][now];
                --sz;
            }
            for (int i = 1; i <= sz; i++)
                ans.emplace_back(A[nex]);
        }
        cur = nex;
    }
    assert((int)ans.size() == m);
    reverse(ans.begin(), ans.end());

    for (int x : ans)
        printf("%d ", x);
    printf("\n");

    return 0;
}