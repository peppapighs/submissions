#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n, m;
vector<pii> line, hi, lo;

bool bad(pii a, pii b, pii c) {
    return (c.y - a.y) * (a.x - b.x) <= (b.y - a.y) * (a.x - c.x);
}

long f(pii l, long x) { return l.x * x + l.y; }

long find_max(long x) {
    int l = 0, r = hi.size() - 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (f(hi[mid], x) > f(hi[mid + 1], x))
            r = mid;
        else
            l = mid + 1;
    }
    return f(hi[r], x);
}

long find_min(long x) {
    int l = 0, r = lo.size() - 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (f(lo[mid], x) < f(lo[mid + 1], x))
            r = mid;
        else
            l = mid + 1;
    }
    return f(lo[r], x);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        line.emplace_back(1ll * a * a, -b);
    }
    sort(line.begin(), line.end());
    for (pii l : line) {
        while (!hi.empty() && hi.back().x == l.x && hi.back().y <= l.y)
            hi.pop_back();
        while (hi.size() > 1 && bad(hi[hi.size() - 2], hi.back(), l))
            hi.pop_back();
        hi.emplace_back(l);
    }
    sort(line.begin(), line.end(), greater<pii>());
    for (pii l : line) {
        while (!lo.empty() && lo.back().x == l.x && lo.back().y >= l.y)
            lo.pop_back();
        while (lo.size() > 1 && bad(lo[lo.size() - 2], lo.back(), l))
            lo.pop_back();
        lo.emplace_back(l);
    }

    for (int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        if (a > 0) {
            if (find_max(a) <= -b)
                printf("ALL\n");
            else if (find_min(a) > -b)
                printf("NONE\n");
            else
                printf("SOME\n");
        } else {
            if (find_min(a) >= -b)
                printf("ALL\n");
            else if (find_max(a) < -b)
                printf("NONE\n");
            else
                printf("SOME\n");
        }
    }

    return 0;
}
