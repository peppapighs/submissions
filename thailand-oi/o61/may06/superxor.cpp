#include <bits/stdc++.h>

#define long long long
#define iii tuple<long, long, long>
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n, m, q;
int par[N];
long dp[N];
vector<pii> g[N];
vector<iii> E;
vector<long> cal, pre;

int find(int x) { return par[x] = x == par[x] ? x : find(par[x]); }

void dfs(int u, int p) {
    for (pii v : g[u])
        if (v.x != p) {
            dp[v.x] = dp[u] ^ v.y;
            dfs(v.x, u);
        }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++)
        par[i] = i;
    while (m--) {
        long a, b, c;
        cin >> a >> b >> c;
        int pa = find(a), pb = find(b);
        if (pa != pb) {
            g[a].emplace_back(b, c), g[b].emplace_back(a, c);
            par[pa] = pb;
        } else
            E.emplace_back(a, b, c);
    }
    dfs(1, 1);
    for (iii e : E) {
        long a, b, c;
        tie(a, b, c) = e;
        cal.emplace_back(dp[a] ^ dp[b] ^ c);
    }
    for (int i = 63; ~i; i--) {
        long ret = 0;
        for (long x : cal)
            if ((x >> i) & 1)
                ret = x;
        if (ret == 0)
            continue;
        pre.emplace_back(ret);
        for (long &x : cal)
            if ((x >> i) & 1)
                x ^= ret;
    }
    while (q--) {
        int s, t;
        cin >> s >> t;
        long ans = dp[s] ^ dp[t];
        for (long x : pre)
            if ((ans ^ x) > ans)
                ans ^= x;
        cout << ans << endl;
    }

    return 0;
}
