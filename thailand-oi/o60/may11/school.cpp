#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int N = 7e4 + 5;

int n, q, ptr;
ordered_set<pii> t[N << 1];
vector<int> coord;
vector<pii> V;

int get(int x) {
    return lower_bound(coord.begin(), coord.end(), x) - coord.begin();
}

int query(int l, int r, int x, int y) {
    auto f = [&](int i) {
        return t[i].order_of_key(pii(y + 1, 0)) - t[i].order_of_key(pii(x, 0));
    };
    int ret = 0;
    for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            ret += f(l++);
        if (r & 1)
            ret += f(--r);
    }
    return ret;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        V.emplace_back(a, b);
        coord.emplace_back(b);
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
    for (pii v : V)
        t[get(v.y) + N].insert(pii(v.x, ++ptr));
    for (int i = N - 1; i; i--) {
        for (pii x : t[i << 1])
            t[i].insert(x);
        for (pii x : t[i << 1 | 1])
            t[i].insert(x);
    }
    int sz = (int)coord.size();
    for (int i = 1, a, b; i <= q; i++) {
        scanf("%d %d", &a, &b);
        vector<int> v(5);
        int ida = get(a), idb = get(b) - (coord[get(b)] != b);
        v[1] = query(idb + 1, sz - 1, a, b);
        v[2] = query(ida, idb, 1, a - 1);
        v[3] = query(ida, idb, a, b);
        v[4] = query(idb + 1, sz - 1, 1, a - 1);
        v[0] = v[1] + v[2] + v[3] + v[4];
        for (int j = 0; j < 5; j++)
            printf("%d ", v[j]);
        printf("\n");
    }

    return 0;
}
