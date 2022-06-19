#include <bits/stdc++.h>

using namespace std;

#define pii pair<int, int>
#define x first
#define y second

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii sub(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
pii mul(pii a, pii b) { return pii(a.x * b.x, a.y * b.y); }

//-----------------------------------------------------------

const int N = 2e5 + 5;

int n;
// vector<int> g[N];
int deg[N], par[N], cost[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &cost[i]);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &par[i]);
        deg[par[i]]++;
    }
    queue<int> Q;
    for (int i = 1; i <= n; i++)
        if (!deg[i])
            Q.emplace(i);
    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();
        deg[par[now]]--;
        if (!deg[par[now]])
            Q.emplace(par[now]);
    }
    long long ans = 0LL;
    for (int i = 1; i <= n; i++)
        if (deg[i]) {
            int p = i, mn = INT_MAX;
            while (deg[p]) {
                deg[p]--;
                mn = min(mn, cost[p]);
                p = par[p];
            }
            ans += (long long)mn;
        }

    printf("%lld", ans);

    return 0;
}