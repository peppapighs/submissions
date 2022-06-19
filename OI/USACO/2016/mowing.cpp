#include <bits/stdc++.h>

#define long long long
#define iii tuple<int, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;

int get(vector<int> &coord, int x) {
    return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1;
}

void update(vector<int> &t, int x, int k) {
    for (int i = x; i < t.size(); i += i & -i)
        t[i] += k;
}

int query(vector<int> &t, int x, int ret = 0) {
    for (int i = x; i; i -= i & -i)
        ret += t[i];
    return ret;
}

struct Fenwick2D {
    vector<int> coord[N], t[N];

    void add(int x, int y) {
        for (int i = x; i < N; i += i & -i)
            coord[i].emplace_back(y);
    }

    void init() {
        for (int i = 1; i < N; i++) {
            sort(coord[i].begin(), coord[i].end());
            coord[i].resize(unique(coord[i].begin(), coord[i].end()) -
                            coord[i].begin());
            t[i].resize(coord[i].size() + 5);
        }
    }

    void update2d(int x, int y, int k) {
        for (int i = x; i < N; i += i & -i)
            update(t[i], get(coord[i], y), k);
    }

    int query2d(int x, int y1, int y2, int ret = 0) {
        for (int i = x; i; i -= i & -i) {
            int idx = upper_bound(coord[i].begin(), coord[i].end(), y1) -
                      coord[i].begin();
            ret += query(t[i], idx) + query(t[i], t[i].size() - 1) -
                   query(t[i], get(coord[i], y2) - 1);
        }
        return ret;
    }
} tree;

int n, T;
vector<pii> vec, in[N], out[N];
vector<iii> Q[N];
vector<int> X, Y;

int main() {
    freopen("mowing.in", "r", stdin);
    freopen("mowing.out", "w", stdout);

    scanf("%d %d", &n, &T);
    for (int i = 1, a, b, x, y; i <= n; i++) {
        scanf("%d %d", &a, &b);
        X.emplace_back(a), Y.emplace_back(b);
        vec.emplace_back(a, b);
        x = a, y = b;
    }
    sort(X.begin(), X.end()), sort(Y.begin(), Y.end());
    X.resize(unique(X.begin(), X.end()) - X.begin());
    Y.resize(unique(Y.begin(), Y.end()) - Y.begin());
    for (int i = 1; i < n; i++) {
        if (vec[i].x == vec[i - 1].x) {
            int a = vec[i - 1].y, b = vec[i].y;
            if (a > b)
                swap(a, b);
            Q[get(X, vec[i].x)].emplace_back(a, b, i);
        } else {
            int a = vec[i - 1].x, b = vec[i].x;
            if (a > b)
                swap(a, b);
            in[get(X, a)].emplace_back(vec[i].y, i);
            out[get(X, b)].emplace_back(vec[i].y, i);
            tree.add(get(Y, vec[i].y), i);
        }
    }
    tree.init();

    long ans = 0;
    for (int i = 1; i <= X.size(); i++) {
        for (pii p : out[i])
            tree.update2d(get(Y, p.x), p.y, -1);
        for (iii e : Q[i]) {
            int a, b, idx;
            tie(a, b, idx) = e;
            ans += tree.query2d(get(Y, b) - 1, idx - T, idx + T) -
                   tree.query2d(get(Y, a), idx - T, idx + T);
        }
        for (pii p : in[i])
            tree.update2d(get(Y, p.x), p.y, 1);
    }
    printf("%lld\n", ans);

    return 0;
}