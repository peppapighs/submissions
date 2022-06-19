#include "rescuelib.h"
#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

int X, Y, R, C, cnt;
vector<pii> vec;
vector<int> ret;

int solve(pii x, pii y, int a, int b) {
    if (x.x == X && y.x == X) {
        int row = (a + b - (C - Y + 1) + 1) / 2 + 1;
        answer(row + X - 1, a - row + 2 + Y - 1);
    } else if (x.y == C && y.y == C) {
        int col = (a + b - (R - X + 1) + 1) / 2 + 1;
        answer(a - col + 2 + X - 1, C - col + 1 + Y - 1);
    } else if (x.x == R && y.x == R) {
        int row = (a + b - (C - Y + 1) + 1) / 2 + 1;
        answer(R - row + 1 + X - 1, b - row + 2 + Y - 1);
    } else {
        int col = (a + b - (R - X + 1) + 1) / 2 + 1;
        answer(b - col + 2 + X - 1, col + Y - 1);
    }
}

void init() {
    vec.clear(), ret.clear();
    vec.emplace_back(X, Y);
    vec.emplace_back(X, C);
    vec.emplace_back(R, C);
    vec.emplace_back(R, Y);

    for (int i = 0; i < 4; i++) {
        ret.emplace_back(drop_robot(vec[i].x, vec[i].y));
        if (ret.back() != -1)
            ++cnt;
    }
}

int main() {
    get_size(R, C);
    X = 1, Y = 1;
    init();

    if (cnt > 1)
        for (int i = 0; i < 4; i++) {
            pii p1 = vec[i], p2 = vec[(i + 1) % 4];
            int a = ret[i], b = ret[(i + 1) % 4];
            if (a != -1 && b != -1)
                solve(p1, p2, a, b);
        }
    else {
        if (ret[0] != -1) {
            int l = 1, r = C;
            while (l < r) {
                int mid = (l + r + 1) >> 1;
                if (drop_robot(1, mid) != -1)
                    l = mid;
                else
                    r = mid - 1;
            }
            C = l;
            l = 1, r = R;
            while (l < r) {
                int mid = (l + r + 1) >> 1;
                if (drop_robot(mid, 1) != -1)
                    l = mid;
                else
                    r = mid - 1;
            }
            R = l;
        } else if (ret[1] != -1) {
            int l = 1, r = C;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (drop_robot(1, mid) != -1)
                    r = mid;
                else
                    l = mid + 1;
            }
            Y = r;
            l = 1, r = R;
            while (l < r) {
                int mid = (l + r + 1) >> 1;
                if (drop_robot(mid, C) != -1)
                    l = mid;
                else
                    r = mid - 1;
            }
            R = l;
        } else if (ret[2] != -1) {
            int l = 1, r = C;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (drop_robot(R, mid) != -1)
                    r = mid;
                else
                    l = mid + 1;
            }
            Y = r;
            l = 1, r = R;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (drop_robot(mid, C) != -1)
                    r = mid;
                else
                    l = mid + 1;
            }
            X = r;
        } else {
            int l = 1, r = C;
            while (l < r) {
                int mid = (l + r + 1) >> 1;
                if (drop_robot(R, mid) != -1)
                    l = mid;
                else
                    r = mid - 1;
            }
            C = l;
            l = 1, r = R;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (drop_robot(mid, 1) != -1)
                    r = mid;
                else
                    l = mid + 1;
            }
            X = r;
        }
        init();
        solve(vec[0], vec[1], ret[0], ret[1]);
    }

    return 0;
}