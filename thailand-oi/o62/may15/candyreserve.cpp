#include <bits/stdc++.h>

#define long long long
#define iii tuple<int, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1 << 18;

vector<int> coord;
long t[4][N << 1], lz[4][N << 1];

void push(int p, int l, int r) {
    for (int i = 0; i <= 3; i++) {
        if (lz[i][p] == 0)
            continue;
        t[i][p] += lz[i][p];
        if (l != r) {
            lz[i][p << 1] += lz[i][p];
            lz[i][p << 1 | 1] += lz[i][p];
        }
        lz[i][p] = 0;
    }
}

template <typename T>
void travel(int x, int y, const T &f, int p = 1, int l = 1,
            int r = coord.size()) {
    push(p, l, r);
    if (x > r || l > y)
        return;
    if (x <= l && r <= y)
        return f(p, l, r);
    int mid = (l + r) >> 1;
    travel(x, y, f, p << 1, l, mid), travel(x, y, f, p << 1 | 1, mid + 1, r);
    for (int i = 0; i <= 3; i++)
        t[i][p] = max(t[i][p << 1], t[i][p << 1 | 1]);
}

int n;
long dp[N][4], ans;
vector<pii> v[N];
vector<iii> E;

int get(int x) {
    return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 1, a, b, c; i <= n; i++) {
        scanf("%d %d %d", &a, &b, &c);
        coord.emplace_back(a);
        coord.emplace_back(b + 1);
        E.emplace_back(a, b, c);
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
    for (iii e : E) {
        int a, b, c;
        tie(a, b, c) = e;
        v[get(b + 1)].emplace_back(a, c);
    }
    for (int i = 1; i <= coord.size(); i++) {
        for (pii q : v[i]) {
            travel(get(q.x), i - 1, [&](int p, int l, int r) {
                for (int z = 0; z <= 3; z++)
                    lz[z][p] += q.y;
                push(p, l, r);
            });
        }
        for (int j = 1; j <= 3; j++) {
            dp[i][j] = dp[i - 1][j];
            long now = 0;
            travel(1, i,
                   [&](int p, int l, int r) { now = max(now, t[j - 1][p]); });
            dp[i][j] = max(dp[i][j], now);
            travel(i, i, [&](int p, int l, int r) {
                lz[j][p] += dp[i][j];
                push(p, l, r);
            });
            ans = max(ans, dp[i][j]);
        }
    }
    printf("%lld\n", ans);

    return 0;
}