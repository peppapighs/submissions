#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int n, p;
int t[N];

void update(int x, int k) {
    for (int i = x; i <= n; i += i & (-i))
        t[i] += k;
}

int query(int x) {
    int sum = 0;
    for (int i = x; i; i -= i & (-i))
        sum += t[i];
    return sum;
}

int deal(int l, int r, int k) {
    update(l, -k);
    update(r + 1, k);
}

int main() {
    scanf("%d %d", &n, &p);
    update(1, 10000);
    while (p--) {
        int a, k, d, q;
        scanf("%d %d %d %d", &a, &k, &d, &q);
        int l = a - k, r = a + k;
        if (l < 1)
            deal(l + n, n, d), deal(1, r, d);
        else if (r > n)
            deal(l, n, d), deal(1, r - n, d);
        else
            deal(l, r, d);
        while (q--) {
            int t, ret;
            scanf("%d", &t);
            ret = query(t);
            printf("%d ", ret > 0 ? ret : 0);
        }
        printf("\n");
    }

    return 0;
}