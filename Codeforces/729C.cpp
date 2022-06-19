#include <bits/stdc++.h>

using namespace std;

bool check(int m, int *gas, int k, int t) {
    if (m < gas[0]) {
        return false;
    } else {
        int l = 0;
        if (gas[0] * 2 <= m) {
            l += gas[0];
        } else {
            l += (3 * gas[0] - m);
        }
        for (int i = 1; i < k; i++) {
            int delta = gas[i] - gas[i - 1];
            if (m < delta) {
                return false;
            }
            if (delta * 2 <= m) {
                l += delta;
            } else {
                l += (3 * delta - m);
            }
        }
        if (l > t) {
            return false;
        }
        return true;
    }
}

int main() {
    int n, k, s, t;
    scanf("%d%d%d%d", &n, &k, &s, &t);
    pair<int, int> car[n];
    for (int i = 0; i < n; i++) {
        int c, v;
        scanf("%d%d", &c, &v);
        car[i] = {c, v};
    }
    int gas[k + 1];
    for (int i = 0; i < k; i++) {
        scanf("%d", &gas[i]);
    }
    gas[k] = s;

    sort(gas, gas + k + 1);
    int low = 1, high = s;
    int res = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (check(mid, gas, k + 1, t)) {
            res = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    if (res == -1) {
        printf("-1");
        return 0;
    }

    sort(car, car + n);
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (car[i].second >= res) {
            ans = min(ans, car[i].first);
        }
    }

    if (ans == INT_MAX) {
        printf("-1");
    } else {
        printf("%d", ans);
    }

    return 0;
}
