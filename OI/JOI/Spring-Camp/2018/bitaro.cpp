#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;
const int B = 320;

int n, m, q;
vector<int> g[N];

int dp[N], chk[N];

void bruteforce(vector<int> &block) {
    fill_n(dp, N, -1e9);
    for (int i : block)
        chk[i] = 1;
    for (int u = 1; u <= n; u++) {
        if (!chk[u])
            dp[u] = max(dp[u], 0);
        if (dp[u] == -1e9)
            continue;
        for (int v : g[u])
            dp[v] = max(dp[v], dp[u] + 1);
    }
    for (int i : block)
        chk[i] = 0;
}

int mx[N];
pii ret[N];
vector<pii> pre[N];

void pre_process() {
    fill_n(mx, N, -1);
    for (int i = 1; i <= n; i++)
        pre[i].emplace_back(0, i);

    for (int u = 1; u <= n; u++)
        for (int v : g[u]) {
            for (pii p : pre[u])
                mx[p.y] = max(mx[p.y], p.x + 1);
            for (pii p : pre[v])
                mx[p.y] = max(mx[p.y], p.x);

            int l = 0, r = 0, ptr = 0;
            while (l < pre[u].size() && r < pre[v].size()) {
                pii a = pii(pre[u][l].x + 1, pre[u][l].y), b = pre[v][r];
                if (a > b)
                    ret[++ptr] = a, l++;
                else
                    ret[++ptr] = b, r++;
            }
            while (l < pre[u].size()) {
                pii a = pii(pre[u][l].x + 1, pre[u][l].y);
                ret[++ptr] = a, l++;
            }
            while (r < pre[v].size()) {
                pii b = pre[v][r];
                ret[++ptr] = b, r++;
            }
            pre[v].clear();
            for (int i = 1; i <= ptr; i++)
                if (ret[i].x == mx[ret[i].y]) {
                    mx[ret[i].y] = -1;
                    pre[v].emplace_back(ret[i]);
                }
            while (pre[v].size() > B)
                pre[v].pop_back();
        }
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b);
    }
    pre_process();
    for (int x = 1, t, y; x <= q; x++) {
        vector<int> block;
        scanf("%d %d", &t, &y);
        for (int i = 1, a; i <= y; i++) {
            scanf("%d", &a);
            block.emplace_back(a);
        }
        if (y >= B) {
            bruteforce(block);
            if (dp[t] == -1e9)
                printf("-1\n");
            else
                printf("%d\n", dp[t]);
        } else {
            bool valid = false;
            for (int i : block)
                chk[i] = 1;
            for (pii p : pre[t])
                if (!chk[p.y]) {
                    printf("%d\n", p.x);
                    valid = true;
                    break;
                }
            if (!valid)
                printf("-1\n");
            for (int i : block)
                chk[i] = 0;
        }
    }

    return 0;
}