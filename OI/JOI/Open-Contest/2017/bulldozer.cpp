#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1 << 11;
const long INF = 1e18;

struct Point {
    int x, y, c;
    Point() {}
    Point(int x, int y, int c) : x(x), y(y), c(c) {}
    friend bool operator<(const Point &a, const Point &b) {
        return make_pair(pii(a.x, -a.y), a.c) < make_pair(pii(b.x, -b.y), b.c);
    }
};

struct Line {
    int dx, dy, x, y;
    Line() {}
    Line(int dx, int dy, int x, int y) : dx(dx), dy(dy), x(x), y(y) {}
    friend bool operator<(const Line &a, const Line &b) {
        long d = 1ll * a.dy * b.dx - 1ll * b.dy * a.dx;
        if (d == 0)
            return pii(a.x, a.y) < pii(b.x, b.y);
        return d > 0;
    }
};

int n, pos[N];
vector<Point> point;
vector<Line> line;

struct item {
    long pre, suf, sum, ans;
    item() : pre(-INF), suf(-INF), sum(-INF), ans(-INF) {}
    item(long x) : pre(x), suf(x), sum(x), ans(x) {}
    friend item operator+(const item &a, const item &b) {
        item ret;
        ret.pre = max(a.pre, a.sum + b.pre);
        ret.suf = max(b.suf, a.suf + b.sum);
        ret.sum = a.sum + b.sum;
        ret.ans = max({a.ans, b.ans, a.suf + b.pre});
        return ret;
    }
} t[N << 1];

void build(int p = 1, int l = 0, int r = n - 1) {
    if (l == r)
        return void(t[p] = item(point[l].c));
    int mid = (l + r) >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
    t[p] = t[p << 1] + t[p << 1 | 1];
}

void update(int x, int k, int p = 1, int l = 0, int r = n - 1) {
    if (l == r)
        return void(t[p] = item(k));
    int mid = (l + r) >> 1;
    if (x <= mid)
        update(x, k, p << 1, l, mid);
    else
        update(x, k, p << 1 | 1, mid + 1, r);
    t[p] = t[p << 1] + t[p << 1 | 1];
}

int main() {
    iota(pos, pos + N, 0);

    scanf("%d", &n);
    point.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d %d %d", &point[i].x, &point[i].y, &point[i].c);

    sort(point.begin(), point.end());
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            if (point[i].x == point[j].x)
                continue;
            line.emplace_back(point[j].x - point[i].x, point[j].y - point[i].y,
                              i, j);
        }
    sort(line.begin(), line.end());

    build();

    long ans = max(0ll, t[1].ans);
    for (int i = 0; i < line.size(); i++) {
        int a = line[i].x, b = line[i].y;

        update(pos[a], point[b].c), update(pos[b], point[a].c);
        swap(pos[a], pos[b]);

        if (i == line.size() - 1 || 1ll * line[i].dy * line[i + 1].dx !=
                                        1ll * line[i].dx * line[i + 1].dy)
            ans = max(ans, t[1].ans);
    }
    printf("%lld\n", ans);

    return 0;
}