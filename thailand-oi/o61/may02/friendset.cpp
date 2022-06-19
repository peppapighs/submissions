#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;
const int B = 1e9 + 7;

int n, m;
long ans, ppow[N], hsh[N];
vector<pii> E;
map<long, int> mp;

int main() {
    ppow[0] = 1;
    for (int i = 1; i < N; i++)
        ppow[i] = ppow[i - 1] * B;

    scanf("%d %d", &n, &m);
    for (int i = 1, u, v; i <= m; i++) {
        scanf("%d %d", &u, &v);
        hsh[u] += ppow[v], hsh[v] += ppow[u];
        E.emplace_back(u, v);
    }

    for (int i = 1; i <= n; i++)
        ++mp[hsh[i]];
    for (auto p : mp)
        ans += 1ll * (p.y) * (p.y - 1) / 2;
    for (pii e : E)
        if (hsh[e.x] - ppow[e.y] == hsh[e.y] - ppow[e.x])
            ++ans;
    printf("%lld", ans);

    return 0;
}