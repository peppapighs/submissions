#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5 + 5;

void update(vector<int> &t, int x, int k) {
    for (int i = x; i < t.size(); i += i & -i)
        t[i] += k;
}

int query(vector<int> &t, int x) {
    int ret = 0;
    for (int i = x; i; i -= i & -i)
        ret += t[i];
    return ret;
}

int n, k;
vector<int> coord[N];
vector<int> t[N];

void update_2d(int x, int y) {
    for (int i = x; i <= n; i += i & -i) {
        int idx = lower_bound(coord[i].begin(), coord[i].end(), y) -
                  coord[i].begin() + 1;
        update(t[i], idx, 1);
    }
}

int query_2d(int x, int y) {
    int ret = 0;
    for (int i = x; i; i -= i & -i) {
        int idx =
            upper_bound(coord[i].begin(), coord[i].end(), y) - coord[i].begin();
        ret += query(t[i], idx);
    }
    return ret;
}

int x[N], y[N];

int main() {
    freopen("friendcross.in", "r", stdin);
    freopen("friendcross.out", "w", stdout);

    scanf("%d %d", &n, &k);
    for (int i = 1, a; i <= n; i++)
        scanf("%d", &a), x[a] = i;
    for (int i = 1, a; i <= n; i++)
        scanf("%d", &a), y[a] = i;

    for (int i = 1; i <= n; i++)
        for (int j = x[i]; j <= n; j += j & -j)
            coord[j].emplace_back(y[i]);
    for (int i = 1; i <= n; i++) {
        sort(coord[i].begin(), coord[i].end());
        coord[i].resize(unique(coord[i].begin(), coord[i].end()) -
                        coord[i].begin());
        t[i].resize(coord[i].size() + 5);
    }

    long ans = 0;
    for (int i = 1, j = k + 2; j <= n; i++, j++) {
        update_2d(x[i], y[i]);
        ans +=
            query_2d(n, y[j]) + query_2d(x[j], n) - 2ll * query_2d(x[j], y[j]);
    }
    printf("%lld\n", ans);

    return 0;
}