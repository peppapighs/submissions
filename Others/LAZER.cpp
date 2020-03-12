#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5+5;

int n, q;
int A[N], t[N], ans[N];
vector<pii> L[N], R[N];

void update(int x, int k) {
    for(int i = x; i < N; i += i & -i)
        t[i] += k;
}

int query(int x) {
    int ret = 0;
    for(int i = x; i; i -= i & -i)
        ret += t[i];
    return ret;
}

void solve() {
    memset(A, 0, sizeof A), memset(t, 0, sizeof t), memset(ans, 0, sizeof ans);
    for(int i = 1; i < N; i++) L[i].clear(), R[i].clear();

    scanf("%d %d", &n, &q);

    vector<int> coord;
    for(int i = 1; i <= n; i++) scanf("%d", A + i);
    for(int i = 1, a, b, c; i <= q; i++) {
        scanf("%d %d %d", &a, &b, &c);
        L[a].emplace_back(c, i);
        R[b].emplace_back(c, i);
        coord.emplace_back(c);
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());

    for(int i = 1; i <= n; i++) {
        for(pii p : L[i]) {
            int idx = lower_bound(coord.begin(), coord.end(), p.x) - coord.begin() + 1;
            ans[p.y] -= query(idx);
        }
        for(pii p : R[i]) {
            int idx = lower_bound(coord.begin(), coord.end(), p.x) - coord.begin() + 1;
            ans[p.y] += query(idx);
        }
        int x = A[i], y = A[i + 1];
        if(x > y) swap(x, y);
        int l = lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1;
        int r = upper_bound(coord.begin(), coord.end(), y) - coord.begin() + 1;
        update(l, 1), update(r, -1);
    }
    for(int i = 1; i <= q; i++) printf("%d\n", ans[i]);
}

int T;

int main() {
    scanf("%d", &T);
    while(T--) solve();

    return 0;
}