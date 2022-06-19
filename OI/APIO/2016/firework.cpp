#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 3e5 + 5;

int n, m;
vector<pii> g[N];

int sz[N], hv[N], par[N];

int pre_process(int u, int p) {
    pii ret(0, -1);
    sz[u] = 1;
    for (pii v : g[u])
        if (v.x != p) {
            par[v.x] = v.y;
            int z = pre_process(v.x, u);
            sz[u] += z, ret = max(ret, pii(z, v.x));
        }
    hv[u] = ret.y;
    return sz[u];
}

long high[N], slope[N];

void sack(int u, int p, priority_queue<long> &Q) {
    if (sz[u] == 1) {
        high[u] = par[u], slope[u] = -1;
        Q.emplace(par[u]);
        Q.emplace(par[u]);
    } else {
        sack(hv[u], u, Q);
        high[u] = high[hv[u]], slope[u] = slope[hv[u]];
        priority_queue<long> T;
        for (pii v : g[u])
            if (v.x != p && v.x != hv[u]) {
                sack(v.x, u, T);
                high[u] += high[v.x], slope[u] += slope[v.x];
                while (!T.empty()) {
                    Q.emplace(T.top());
                    T.pop();
                }
            }
        if (u == 1) {
            vector<long> v;
            while (!Q.empty()) {
                v.emplace_back(Q.top());
                Q.pop();
            }
            reverse(v.begin(), v.end());
            long pv = 0, ans = high[u];
            for (int i = 0; slope[u] < 0; i++) {
                ans += (v[i] - pv) * slope[u]++;
                pv = v[i];
            }

            printf("%lld\n", ans);
        } else {
            long a, b;
            while (slope[u] + (int)Q.size() >= 0) {
                swap(a, b);
                a = Q.top();
                Q.pop();
            }
            Q.emplace(a + par[u]), Q.emplace(b + par[u]);
            high[u] += par[u];
        }
    }
}

int main() {
    scanf("%d %d", &n, &m), n += m;
    for (int i = 2, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        g[i].emplace_back(a, b);
        g[a].emplace_back(i, b);
    }
    pre_process(1, 1);
    priority_queue<long> Q;
    sack(1, 1, Q);

    return 0;
}