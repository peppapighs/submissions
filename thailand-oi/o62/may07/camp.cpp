#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 5e5 + 5;

int n, a[N], b[N];
long w[N], dp[N];
vector<int> coord;
vector<pii> v[N];
pii opt[N];
map<int, bool> chk;

int get(int x) {
    return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %lld", a + i, b + i, w + i);
        coord.emplace_back(a[i]);
        coord.emplace_back(b[i]);
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
    for (int i = 1; i <= n; i++)
        v[get(b[i])].emplace_back(a[i], w[i]);
    for (int i = 1; i <= coord.size(); i++) {
        dp[i] = dp[i - 1], opt[i] = opt[i - 1];
        for (pii p : v[i]) {
            long a, b, w;
            b = coord[i - 1], tie(a, w) = p;
            if (dp[i] < w + dp[get(a) - 1]) {
                dp[i] = w + dp[get(a) - 1];
                opt[i] = pii(get(a) - 1, a);
            }
        }
    }
    for (int i = coord.size(); i; i = opt[i].x)
        chk[opt[i].y] = true;
    long mx = 0;
    for (int i = 1; i <= n; i++)
        if (!chk.count(a[i]))
            mx = max(mx, w[i]);
    printf("%lld\n", dp[coord.size()] + mx);

    return 0;
}