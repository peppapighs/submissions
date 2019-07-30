#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, m, k;
long day[N], cost[N];
map<int, long> mp[N];
vector<int> g[N];

int sack(int u) {
    int sz = 1; pii ret(0, -1);
    for(int v : g[u]) {
        int z = sack(v);
        sz += z, ret = max(ret, pii(z, v));
    }
    if(ret.y == -1) {
        if(day[u]) mp[u][day[u]] += cost[u];
        return sz; 
    } else {
        swap(mp[u], mp[ret.y]);
        for(int v : g[u]) if(v != ret.y) 
            for(auto it : mp[v]) mp[u][it.x] += it.y;
        if(day[u]) {
            mp[u][day[u]] += cost[u];
            auto it = mp[u].upper_bound(day[u]);
            while(it != mp[u].end() && it->y <= cost[u]) {
                cost[u] -= it->y;
                it = mp[u].erase(it);
            }
            if(it != mp[u].end()) it->y -= cost[u], cost[u] = 0;
        }
        return sz;
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for(int i = 2, p; i <= n; i++) {
        scanf("%d", &p);
        g[p].emplace_back(i);
    }
    for(int i = 1, a; i <= m; i++) {
        scanf("%d", &a);
        scanf("%lld %lld", day + a, cost + a);
    }
    sack(1);
    long ans = 0;
    for(auto it : mp[1]) ans += it.y;
    printf("%lld\n", ans);

    return 0;
}
