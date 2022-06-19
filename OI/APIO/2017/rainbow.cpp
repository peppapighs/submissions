#include "rainbow.h"
#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;

struct FenwickSet {
    vector<pii> add;
    vector<int> v[N];

    void update(int x, int k) {
        for (int i = x; i < N; i += i & -i)
            v[i].emplace_back(k);
    }

    int query(int x, int l, int r) {
        int ret = 0;
        for (int i = x; i; i -= i & -i) {
            auto L = lower_bound(v[i].begin(), v[i].end(), l);
            auto R = upper_bound(v[i].begin(), v[i].end(), r);
            ret += R - L;
        }
        return ret;
    }

    void init() {
        sort(add.begin(), add.end());
        add.resize(unique(add.begin(), add.end()) - add.begin());
        for (pii p : add)
            update(p.x, p.y);
        for (int i = 1; i < N; i++)
            sort(v[i].begin(), v[i].end());
    }

    int count(int x1, int x2, int y1, int y2) {
        if (x1 > x2 || y1 > y2)
            return 0;
        return query(x2, y1, y2) - query(x1 - 1, y1, y2);
    }
} t[4];

// t[0] = River cells
// t[1] = River vertices
// t[2] = Vertical edges
// t[3] = Horizontal edges

int min_r, min_c, max_r, max_c;

void add_river(pii p) {
    min_r = min(min_r, p.x), max_r = max(max_r, p.x);
    min_c = min(min_c, p.y), max_c = max(max_c, p.y);
    t[0].add.emplace_back(p);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            t[1].add.emplace_back(p.x + i, p.y + j);
    for (int i = 0; i < 2; i++) {
        t[2].add.emplace_back(p.x, p.y + i);
        t[3].add.emplace_back(p.x + i, p.y);
    }
}

// f = 1 - v + e
int solve(int x1, int x2, int y1, int y2) {
    int v = t[1].count(x1 + 1, x2, y1 + 1,
                       y2); // + 4 sides vertices with no corner + 4 corners
    int e = t[2].count(x1, x2, y1 + 1, y2) +
            t[3].count(x1 + 1, x2, y1,
                       y2); // + 4 sides vertices + 4(+1 each side for edge)
    int river = t[0].count(x1, x2, y1, y2);
    return 1 - v + e - river; // 4 sides and corners cancel each other
}

void init(int R, int C, int sr, int sc, int M, char *S) {
    min_r = min_c = 1e9, max_r = max_c = -1e9;
    pii now(sr, sc);
    add_river(now);
    for (int i = 0; i < M; i++) {
        if (S[i] == 'N')
            --now.x;
        if (S[i] == 'S')
            ++now.x;
        if (S[i] == 'E')
            ++now.y;
        if (S[i] == 'W')
            --now.y;
        add_river(now);
    }
    for (int i = 0; i < 4; i++)
        t[i].init();
}

int colour(int ar, int ac, int br, int bc) {
    if (ar < min_r && max_r < br && ac < min_c && max_c < bc)
        return solve(min_r - 1, max_r + 1, min_c - 1, max_c + 1) + 1;
    else
        return solve(ar, br, ac, bc);
}
