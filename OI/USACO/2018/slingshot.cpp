#include <bits/stdc++.h>

#define long long long
#define iii tuple<int, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 4e5 + 5;
const long INF = 1e18;

struct SegTree {
    long t[N << 1];

    void init() { fill_n(t, N << 1, INF); }

    void update(int x, long k) {
        t[x + N] = min(t[x + N], k);
        for (x += N; x != 1; x >>= 1)
            t[x >> 1] = min(t[x], t[x ^ 1]);
    }

    long query(int l, int r) {
        long ret = INF;
        for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                ret = min(ret, t[l++]);
            if (r & 1)
                ret = min(ret, t[--r]);
        }
        return ret;
    }
} t1, t2;

vector<int> coord;

int get(int x) {
    return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1;
}

int n, m;
long ans[N];
vector<iii> sling, query;
vector<pii> S[N], Q[N];

int main() {
    freopen("slingshot.in", "r", stdin);
    freopen("slingshot.out", "w", stdout);

    fill_n(ans, N, INF);

    scanf("%d %d", &n, &m);
    for (int i = 1, a, b, c; i <= n; i++) {
        scanf("%d %d %d", &a, &b, &c);
        sling.emplace_back(a, b, c);
        coord.emplace_back(a), coord.emplace_back(b);
    }
    for (int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        query.emplace_back(a, b, i);
        coord.emplace_back(a), coord.emplace_back(b);
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());

    for (iii s : sling) {
        int a, b, c;
        tie(a, b, c) = s;
        S[get(a)].emplace_back(b, c);
    }
    for (iii q : query) {
        int a, b, c;
        tie(a, b, c) = q;
        Q[get(a)].emplace_back(b, c);
    }

    t1.init(), t2.init();
    for (int i = 1; i <= coord.size(); i++) {
        for (pii p : S[i]) {
            t1.update(get(p.x), -coord[i - 1] - p.x + p.y);
            t2.update(get(p.x), -coord[i - 1] + p.x + p.y);
        }
        for (pii p : Q[i]) {
            ans[p.y] =
                min(ans[p.y], coord[i - 1] + p.x + t1.query(1, get(p.x)));
            ans[p.y] = min(ans[p.y], coord[i - 1] - p.x +
                                         t2.query(get(p.x), coord.size()));
        }
    }

    t1.init(), t2.init();
    for (int i = coord.size(); i; i--) {
        for (pii p : S[i]) {
            t1.update(get(p.x), coord[i - 1] - p.x + p.y);
            t2.update(get(p.x), coord[i - 1] + p.x + p.y);
        }
        for (pii p : Q[i]) {
            ans[p.y] =
                min(ans[p.y], -coord[i - 1] + p.x + t1.query(1, get(p.x)));
            ans[p.y] = min(ans[p.y], -coord[i - 1] - p.x +
                                         t2.query(get(p.x), coord.size()));
        }
    }
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        tie(a, b, c) = query[i - 1];
        printf("%lld\n", min(ans[i], 1ll * abs(a - b)));
    }

    return 0;
}