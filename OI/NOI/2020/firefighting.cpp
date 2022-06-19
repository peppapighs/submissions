#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 3e5 + 5;

int n, e[N];
long k, d[N];
vector<pii> g[N];

void pre_process(int u, int p) {
    for (pii v : g[u])
        if (v.x != p) {
            d[v.x] = d[u] + v.y, e[v.x] = v.y;
            pre_process(v.x, u);
        }
}

multiset<long> S[N];
vector<int> ans;

long solve(int u, int p) {
    long rad = -1;
    for (pii v : g[u])
        if (v.x != p) {
            rad = max(rad, solve(v.x, u) - v.y);
            if (S[v.x].size() > S[u].size())
                swap(S[v.x], S[u]);
            for (long x : S[v.x])
                S[u].emplace(x);
            S[v.x].clear();
        }
    S[u].emplace(d[u]);
    while (!S[u].empty() && *S[u].begin() - d[u] <= rad)
        S[u].erase(S[u].begin());
    if (u != 1) {
        if (!S[u].empty() && *S[u].rbegin() - d[p] > k) {
            ans.emplace_back(u), S[u].clear();
            rad = k;
        }
    } else if (!S[u].empty())
        ans.emplace_back(u);
    return rad;
}

int main() {
    scanf("%d %lld", &n, &k);
    for (int i = 1, a, b, c; i < n; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }
    pre_process(1, 0);
    solve(1, 0);
    printf("%d\n", ans.size());
    for (int x : ans)
        printf("%d ", x);
    printf("\n");

    return 0;
}