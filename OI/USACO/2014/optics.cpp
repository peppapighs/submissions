#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;
const int INF = 1e9 + 1;

struct FenwickTree {
    int t[N << 1];

    void update(int x, int k) {
        for (int i = x; i < N << 1; i += i & -i)
            t[i] += k;
    }

    int query(int x, int ret = 0) {
        for (int i = x; i; i -= i & -i)
            ret += t[i];
        return ret;
    }
} tree;

int n, bx, by;
map<int, vector<pair<int, char>>> mx, my;

void add_coord(int x, int y, char c) {
    mx[x].emplace_back(y, c);
    my[y].emplace_back(x, c);
}

vector<pii> get_path(int x, int y, int dir) {
    vector<pii> ret = {pii(x, y)};
    while (true) {
        if (dir % 2 == 0) {
            int idx = lower_bound(mx[x].begin(), mx[x].end(),
                                  pair<int, char>(y, '#')) -
                      mx[x].begin();
            int nex = idx + (dir ? -1 : 1);

            if (nex < 0 || nex >= mx[x].size()) {
                ret.emplace_back(x, y = (dir ? -INF : INF));
                break;
            }
            ret.emplace_back(x, y = mx[x][nex].x);
            if (mx[x][nex].y != '/' && mx[x][nex].y != '\\')
                break;
            dir = ((mx[x][nex].y == '/') ^ (dir == 0)) ? 3 : 1;
        } else {
            int idx = lower_bound(my[y].begin(), my[y].end(),
                                  pair<int, char>(x, '#')) -
                      my[y].begin();
            int nex = idx + (dir == 3 ? -1 : 1);
            if (nex < 0 || nex >= my[y].size()) {
                ret.emplace_back(x = (dir == 3 ? -INF : INF), y);
                break;
            }
            ret.emplace_back(x = my[y][nex].x, y);
            if (my[y][nex].y != '/' && my[y][nex].y != '\\')
                break;
            dir = ((my[y][nex].y == '/') ^ (dir == 1)) ? 2 : 0;
        }
    }
    return ret;
}

vector<pair<int, pii>> vertical(vector<pii> &path) {
    vector<pair<int, pii>> ret;
    for (int i = 0; i < path.size() - 1; i++) {
        if (path[i].x != path[i + 1].x)
            continue;
        ret.emplace_back(path[i].x, pii(path[i].y, path[i + 1].y));
        if (ret.back().y.x > ret.back().y.y)
            swap(ret.back().y.x, ret.back().y.y);
    }
    return ret;
}

vector<pair<int, pii>> horizontal(vector<pii> &path) {
    vector<pair<int, pii>> ret;
    for (int i = 0; i < path.size() - 1; i++) {
        if (path[i].y != path[i + 1].y)
            continue;
        ret.emplace_back(path[i].y, pii(path[i].x, path[i + 1].x));
        if (ret.back().y.x > ret.back().y.y)
            swap(ret.back().y.x, ret.back().y.y);
    }
    return ret;
}

int sweep(vector<pair<int, pii>> vert, vector<pair<int, pii>> hori) {
    vector<int> coord;
    auto get = [&](int x) {
        return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1;
    };

    for (auto p : vert)
        coord.emplace_back(p.y.x), coord.emplace_back(p.y.y);
    for (auto p : hori)
        coord.emplace_back(p.x);

    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());

    vector<pair<int, pii>> event;
    for (auto p : hori) {
        event.emplace_back(p.y.x, pii(p.x, 1));
        event.emplace_back(p.y.y, pii(p.x, -1));
    }
    sort(event.begin(), event.end()), sort(vert.begin(), vert.end());

    int ptr = 0, ret = 0;
    for (auto e : event) {
        while (ptr < vert.size() && vert[ptr].x < e.x) {
            ret += tree.query(get(vert[ptr].y.y) - 1) -
                   tree.query(get(vert[ptr].y.x));
            ++ptr;
        }
        tree.update(get(e.y.x), e.y.y);
    }
    return ret;
}

int main() {
    freopen("optics.in", "r", stdin);
    freopen("optics.out", "w", stdout);

    scanf("%d %d %d", &n, &bx, &by);
    add_coord(0, 0, 'S'), add_coord(bx, by, 'B');

    for (int i = 1; i <= n; i++) {
        int x, y;
        char c;
        scanf("%d %d %c", &x, &y, &c);
        add_coord(x, y, c);
    }

    for (auto &p : mx)
        sort(p.y.begin(), p.y.end());
    for (auto &p : my)
        sort(p.y.begin(), p.y.end());

    int ret = 0;
    vector<pii> lpath = get_path(0, 0, 0);

    for (int i = 0; i < 4; i++) {
        vector<pii> bpath = get_path(bx, by, i);
        int inter = sweep(vertical(lpath), horizontal(bpath)) +
                    sweep(vertical(bpath), horizontal(lpath));
        if (bpath[0] == bpath.back())
            ret += inter;
        else
            ret += 2 * inter;
    }
    printf("%d\n", ret / 2);

    return 0;
}