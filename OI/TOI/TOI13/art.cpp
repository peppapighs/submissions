#include <bits/stdc++.h>

using namespace std;

struct side {
    int x, id;
    bool right = false;
};

struct line {
    int n;
    int *tree;
    void construct() { tree = new int[n + 2]{0}; }
    void update(int x, int index) {
        while (index <= n) {
            tree[index] += x;
            index += index & (-index);
        }
    }
    int sum(int index) {
        int res = 0;
        while (index > 0) {
            res += tree[index];
            index -= index & (-index);
        }
        return res;
    }
};

bool compare(const side &a, const side &b) { return a.x < b.x; }

int main() {
    int n, t;
    scanf("%d %d", &n, &t);
    pair<int, int> val[n];
    vector<side> plane;
    int hmax = 0, xmin = 1e9;
    for (int i = 0; i < n; i++) {
        int s, h, w, o;
        scanf("%d %d %d %d", &s, &h, &w, &o);
        side l, r;
        l.x = s;
        l.id = i;
        r.x = s + w;
        r.id = i;
        r.right = true;
        val[i] = {h, o};
        hmax = h > hmax ? h : hmax;
        xmin = s < xmin ? s : xmin;
        plane.push_back(l);
        plane.push_back(r);
    }

    sort(plane.begin(), plane.end(), compare);

    line swp;
    swp.n = hmax;
    swp.construct();
    int px = xmin;
    int col = 0;

    int res = 0;

    for (int i = 0; i < plane.size(); i++) {
        res += (col * (plane[i].x - px));
        col = 0;

        if (plane[i].right) {
            swp.update(-val[plane[i].id].second, 1);
            swp.update(val[plane[i].id].second, val[plane[i].id].first + 1);
        } else {
            swp.update(val[plane[i].id].second, 1);
            swp.update(-val[plane[i].id].second, val[plane[i].id].first + 1);
        }

        int low = 1, high = hmax;
        int upper = -1, lower = 0;
        while (high >= low) {
            int mid = (low + high) / 2;
            if (swp.sum(mid) > t) {
                low = mid + 1;
            } else if (swp.sum(mid) == t) {
                upper = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        low = 1;
        high = hmax;
        while (high >= low) {
            int mid = (low + high) / 2;
            if (swp.sum(mid) < t) {
                high = mid - 1;
            } else if (swp.sum(mid) == t) {
                high = mid - 1;
                lower = mid;
            } else {
                low = mid + 1;
            }
        }

        col = upper - lower + 1;

        px = plane[i].x;
    }

    printf("%d", res);

    return 0;
}
