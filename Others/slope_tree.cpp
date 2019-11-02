#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, k;
int C[N], hv[N];
long high[N], lz[N];
vector<int> g[N];

void sack(int u, int p, multiset<long> &L, multiset<long> &R) {
    if(hv[u] == -1) {
        high[u] = C[u];
        L.emplace(C[u]), R.emplace(C[u]);
    } else {
        sack(hv[u], u, L, R);
        high[u] = high[hv[u]], lz[u] = lz[hv[u]];
        multiset<long> S, E;
        for(int v : g[u]) if(v != p && v != hv[u]) {
            sack(v, u, S, E);
            high[u] += high[v];
            while(!S.empty()) L.emplace(*S.begin() + (lz[u] - lz[v]) * k), S.erase(S.begin());
            while(!E.empty()) R.emplace(*E.begin() - (lz[u] - lz[v]) * k), E.erase(E.begin());
        }
        L.emplace(C[u] + lz[u] * k), R.emplace(C[u] - lz[u] * k);
        high[u] += C[u];
        while(*L.rbegin() - lz[u] * k > *R.begin() + lz[u] * k) {
            int l = *L.rbegin(), r = *R.begin();
            L.erase(L.find(l)), R.erase(R.find(r));
            L.emplace(r + 2ll * lz[u] * k), R.emplace(l - 2ll * lz[u] * k);
        }
    }
    long pv = 0;
    while(!L.empty() && *L.begin() - (lz[u] + 1) * k <= 0) {
        high[u] -= 1ll * L.size() * abs(pv - *L.begin() + lz[u] * k);
        pv = *L.begin() - lz[u] * k, L.erase(L.begin());
    }
    high[u] -= 1ll * L.size() * abs(pv - k);
    ++lz[u];
}

int pre_process(int u, int p) {
    int sz = 1; pii ret(0, -1);
    for(int v : g[u]) if(v != p) {
        int z = pre_process(v, u);
        sz += z;
        ret = max(ret, pii(z, v));
    }
    hv[u] = ret.y;
    return sz;
}

int main() {
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i++) scanf("%d", C + i);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    pre_process(1, 1);
    multiset<long> L, R;
    sack(1, 1, L, R);

    long pv = 0, m = L.size(), ans = high[1];
    for(long x : L) {
        ans -= 1ll * abs(x - lz[1] * k - pv) * m--;
        pv = x - lz[1] * k;
    }
    printf("%lld\n", ans);

    return 0;
}