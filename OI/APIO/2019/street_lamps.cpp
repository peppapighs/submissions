#include <bits/stdc++.h>

#define iii tuple<int, int, int>

using namespace std;

const int N = 3e5 + 5;

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

int n, q, state[N];
char str[N];
set<iii> S;
vector<iii> ask;
vector<int> coord[N], t[N];

void update_2d(int x, int l, int r, int k) {
    for (int i = x; i <= n; i += i & -i) {
        auto it = lower_bound(coord[i].begin(), coord[i].end(), l + 1);
        if (it == coord[i].begin())
            update(t[i], 1, k);
        else if (it != coord[i].end())
            update(t[i], it - coord[i].begin(), k);
        it = upper_bound(coord[i].begin(), coord[i].end(), r);
        if (it != coord[i].end())
            update(t[i], it - coord[i].begin() + 1, -k);
    }
}

int query_2d(int l, int r) {
    int ret = 0;
    for (int i = l; i; i -= i & -i) {
        int idx = lower_bound(coord[i].begin(), coord[i].end(), r) -
                  coord[i].begin() + 1;
        ret += query(t[i], idx);
    }
    return ret;
}

void set_time(iii seg, int time) {
    int l, r, t;
    tie(l, r, t) = seg;
    update_2d(l, l, r, time - t);
    update_2d(r + 1, l, r, t - time);
}

int main() {
    scanf("%d %d %s", &n, &q, str + 1);
    for (int i = 1; i <= n; i++)
        state[i] = (str[i] == '1');
    for (int i = 1, j; i <= n + 1; i = j + 1) {
        for (j = i; state[j] && j <= n; j++)
            ;
        S.emplace(i, j, 0);
    }
    for (int i = 1; i <= q; i++) {
        char T[10];
        int a, b;
        scanf(" %s", T);
        if (T[0] == 't') {
            scanf("%d", &a);
            ask.emplace_back(0, a, 0);
        } else {
            scanf("%d %d", &a, &b);
            for (int j = a; j; j -= j & -j)
                coord[j].emplace_back(b);
            ask.emplace_back(1, a, b);
        }
    }
    for (int i = 1; i <= n; i++) {
        sort(coord[i].begin(), coord[i].end());
        coord[i].resize(unique(coord[i].begin(), coord[i].end()) -
                        coord[i].begin());
        if (coord[i].size())
            t[i].resize(coord[i].size() + 1);
    }
    int time = 0;
    for (iii p : ask) {
        ++time;
        int T, a, b;
        tie(T, a, b) = p;
        auto find = [&](int x) { return *prev(S.lower_bound({x + 1, 0, 0})); };
        if (T == 0) {
            if (state[a]) {
                iii seg = find(a);
                set_time(seg, time);
                S.erase(seg);
                S.emplace(get<0>(seg), a, time),
                    S.emplace(a + 1, get<1>(seg), time);
            } else {
                iii seg_l = find(a), seg_r = find(a + 1);
                set_time(seg_l, time), set_time(seg_r, time);
                S.erase(seg_l), S.erase(seg_r);
                S.emplace(get<0>(seg_l), get<1>(seg_r), time);
            }
            state[a] ^= 1;
        } else {
            int ans = query_2d(a, b);
            iii seg = find(a);
            if (get<1>(seg) >= b)
                ans += time - get<2>(seg);
            printf("%d\n", ans);
        }
    }

    return 0;
}