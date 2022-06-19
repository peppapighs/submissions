#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 3e5 + 5;

long ans;
int par[N << 1], sz[N << 1], x_cnt[N << 1], y_cnt[N << 1];
stack<int> st;

int find(int u) { return u == par[u] ? u : find(par[u]); }

void add(int a, int b) {
    a = find(a), b = find(b);
    if (a == b)
        return;
    if (sz[a] > sz[b])
        swap(a, b);
    par[a] = b, sz[b] += sz[a];
    ans -= 1ll * x_cnt[b] * y_cnt[b] + 1ll * x_cnt[a] * y_cnt[a];
    x_cnt[b] += x_cnt[a], y_cnt[b] += y_cnt[a];
    ans += 1ll * x_cnt[b] * y_cnt[b];
    st.emplace(a);
}

void rollback(int x) {
    while ((int)st.size() > x) {
        int a = st.top(), b = par[a];
        st.pop();
        ans -= 1ll * x_cnt[b] * y_cnt[b];
        x_cnt[b] -= x_cnt[a], y_cnt[b] -= y_cnt[a];
        ans += 1ll * x_cnt[b] * y_cnt[b] + 1ll * x_cnt[a] * y_cnt[a];
        sz[b] -= sz[a], par[a] = a;
    }
}

int n;
int x[N << 1], y[N << 1], o[N << 1];
map<pii, int> mp;

void solve(int l, int r) {
    if (l == r) {
        if (l % 2 == 0)
            printf("%lld ", ans);
        return;
    }
    int mid = (l + r) >> 1, now = st.size();
    for (int i = mid + 1; i <= r; i++)
        if (o[i] < l && (i & 1))
            add(x[i], y[i]);
    solve(l, mid), rollback(now);
    for (int i = l; i <= mid; i++)
        if (o[i] > r && (i & 1))
            add(x[i], y[i]);
    solve(mid + 1, r), rollback(now);
}

int main() {
    iota(par, par + (N << 1), 0), fill_n(sz, (N << 1), 1);
    for (int i = 1; i <= N; i++)
        x_cnt[i] = 1;
    for (int i = N + 1; i < N << 1; i++)
        y_cnt[i] = 1;

    scanf("%d", &n);
    for (int i = 1; i <= 2 * n; i += 2) {
        scanf("%d %d", x + i, y + i), y[i] += N;
        pii p(x[i], y[i]);
        if (mp.count(p)) {
            o[i] = mp[p];
            o[o[i]] = i;
            mp.erase(p);
        } else
            mp[p] = i;
    }
    for (auto it : mp)
        o[it.y] = 1e9;

    solve(1, 2 * n);
    printf("\n");

    return 0;
}