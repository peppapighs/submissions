#include <bits/stdc++.h>

using namespace std;

const int N = 2e4 + 5;

int n, m;

int t[N];

void update(int x) {
    for (int i = x; i <= n; i += i & -i)
        ++t[i];
}

int query(int x, int ret = 0) {
    for (int i = x; i; i -= i & -i)
        ret += t[i];
    return ret;
}

int x[N], y[N], pos[N];
vector<int> coordx, coordy;

int main() {
    iota(pos, pos + N, 0);
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", x + i, y + i);
        coordx.emplace_back(x[i]);
        coordy.emplace_back(y[i]);
    }
    sort(pos + 1, pos + n + 1,
         [&](const int &a, const int &b) { return x[a] < x[b]; });
    sort(coordx.begin(), coordx.end());
    sort(coordy.begin(), coordy.end());
    for (int i = 1; i <= n; i++) {
        x[i] = lower_bound(coordx.begin(), coordx.end(), x[i]) -
               coordx.begin() + 1;
        y[i] = lower_bound(coordy.begin(), coordy.end(), y[i]) -
               coordy.begin() + 1;
    }
    int ans = INT_MAX, a1, a2;
    for (int i = 1; i <= n; i++) {
        memset(t, 0, sizeof t);
        update(y[pos[i]]);
        for (int j = i + 1; j <= n; j++) {
            update(y[pos[j]]);
            int val;
            if (y[pos[j]] > y[pos[i]])
                val = query(y[pos[j]]) - query(y[pos[i]] - 1);
            else
                val = query(y[pos[i]]) - query(y[pos[j]] - 1);
            if (val < ans && val >= m)
                ans = val, a1 = pos[i], a2 = pos[j];
            if (ans == m)
                break;
        }
        if (ans == m)
            break;
    }
    printf("%d %d\n", a1, a2);

    return 0;
}
