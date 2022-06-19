#include <bits/stdc++.h>

using namespace std;

struct prob {
    int a, t, id;
};

bool compare(const prob &a, const prob &b) { return a.t < b.t; }

int main() {
    int n, t;
    scanf("%d%d", &n, &t);
    prob p[n];
    for (int i = 0; i < n; i++) {
        prob x;
        scanf("%d%d", &p[i].a, &p[i].t);
        p[i].id = i + 1;
    }

    sort(p, p + n, compare);
    int low = 0, high = n;
    int res;
    int *d;
    while (low <= high) {
        int mid = (low + high) / 2;
        int *ans = new int[mid];
        int k = 0;
        int tsum = 0;
        for (int i = 0; i < n && k < mid; i++) {
            if (mid <= p[i].a) {
                tsum += p[i].t;
                ans[k++] = p[i].id;
            }
        }

        if (tsum <= t && k == mid) {
            low = mid + 1;
            res = mid;
            d = ans;
        } else {
            high = mid - 1;
        }
    }

    printf("%d\n%d\n", res, res);
    for (int i = 0; i < res; i++) {
        printf("%d ", d[i]);
    }

    return 0;
}
