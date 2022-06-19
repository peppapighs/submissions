#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;

int n, m, A, B;
int cnt[N], hv[N];
vector<int> g[N];
long ans;

int pre_process(int u) {
    int sz = 1;
    pii ret(0, -1);
    for (int v : g[u]) {
        int z = pre_process(v);
        sz += z, ret = max(ret, pii(z, v));
    }
    hv[u] = ret.y;
    return sz;
}

void sack(int u, set<int, greater<int>> &S) {
    set<int, greater<int>> tmp;
    if (hv[u] != -1)
        sack(hv[u], S);
    for (int v : g[u])
        if (v != hv[u]) {
            sack(v, tmp);
            while (!tmp.empty()) {
                S.emplace(*tmp.begin());
                tmp.erase(tmp.begin());
            }
        }
    S.emplace(u);
    while (cnt[u]-- && !S.empty()) {
        ans += *S.begin();
        S.erase(S.begin());
    }
}

long solve() {
    ans = 0;
    scanf("%d %d %d %d", &n, &m, &A, &B);
    for (int i = 0; i < n; i++)
        cnt[i] = 0, g[i].clear();
    for (int i = 0; i < m; i++)
        ++cnt[(1ll * A * i + B) % n];
    for (int i = 1, p; i < n; i++) {
        scanf("%d", &p);
        g[p].emplace_back(i);
    }
    set<int, greater<int>> S;
    pre_process(0), sack(0, S);
    return ans;
}

int T;

int main() {
    scanf("%d", &T);
    for (int i = 1; i <= T; i++)
        printf("Case #%d: %lld\n", i, solve());

    return 0;
}