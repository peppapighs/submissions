#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5+5;

int n, d[N];
long A[N], sum[2][2], ans;
vector<pii> g[N];

void dfs(int u, int p) {
    sum[d[u] & 1][A[u] > 0] += A[u];
    for(pii v : g[u]) if(v.x != p) {
        d[v.x] = d[u] + v.y;
        dfs(v.x, u);
    }
}

int main() {
    scanf("%d %lld", &n, A);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%lld %d %d", A+i, &a, &b);
        g[i].emplace_back(a, b), g[a].emplace_back(i, b);
    }
    dfs(0, 0);
    for(int i = 0; i < n; i++) {
        ans += (sum[d[i] & 1][A[i] > 0] - A[i]) * A[i];
        ans -= (sum[~d[i] & 1][A[i] < 0]) * A[i];
    }
    printf("%lld\n", ans / 2ll);

    return 0;
}
