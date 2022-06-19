#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int n, k;
int t[N << 1];

void update(int x, int k) {
    for (t[x += N] = k; x != 1; x >>= 1)
        t[x >> 1] = max(t[x], t[x ^ 1]);
}

int query(int l, int r) {
    int ret = 0;
    for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            ret = max(ret, t[l++]);
        if (r & 1)
            ret = max(ret, t[--r]);
    }
    return ret;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1, a, b; i <= k; i++) {
        scanf("%d %d", &a, &b);
        update(a, b);
        if (query(0, n - 1) <= b)
            printf("%d\n", n);
        else {
            int l = 0, r = n - 1;
            while (l < r) {
                int mid = (l + r + 1) >> 1;
                if (max(query(max(0, a - mid), max(0, a - 1)),
                        query(min(a + 1, n - 1), min(a + mid, n - 1))) <= b)
                    l = mid;
                else
                    r = mid - 1;
            }
            printf("%d\n", l);
        }
    }

    return 0;
}
