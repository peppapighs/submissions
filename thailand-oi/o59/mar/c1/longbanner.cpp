#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, h, l, ans;
int x[N], y[N], t[N];
vector<int> coord;

void update(int x, int k) {
    for (int i = x + 1; i < N; i += i & -i)
        t[i] += k;
}

int query(int x) {
    int ret = 0;
    for (int i = x + 1; i; i -= i & -i)
        ret += t[i];
    return ret;
}

int low(int x) {
    return lower_bound(coord.begin(), coord.end(), x) - coord.begin();
}
int up(int x) {
    return upper_bound(coord.begin(), coord.end(), x) - coord.begin();
}

int main() {
    scanf("%d %d %d", &n, &h, &l);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", x + i, y + i);
        coord.emplace_back(y[i]);
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
    int L = 1;
    for (int i = 1; i <= n; i++) {
        update(low(y[i]), 1);
        while (x[i] - x[L] > h)
            update(low(y[L++]), -1);
        for (int j = 0; j <= l; j++) {
            int a = y[i] + j - l, b = y[i] + j;
            ans = max(ans, query(up(b) - 1) - query(low(a) - 1));
        }
    }
    printf("%d\n", ans);

    return 0;
}
