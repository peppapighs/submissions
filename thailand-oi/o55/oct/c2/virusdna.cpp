#include <bits/stdc++.h>

using namespace std;

const int N = 1 << 21;

int n, q;
int t[2][N + 1];

int update(int a, int x, int k) {
    for (int i = x; i <= N; i += i & (-i))
        t[a][i] += k;
}

int get(int a, int x) {
    int ret = 0;
    for (int i = x; i > 0; i -= i & (-i))
        ret += t[a][i];
    return ret;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++)
        update(0, i << 1 | 1, 1);

    while (q--) {
        char c;
        int a, b;
        scanf(" %c %d", &c, &a);
        if (c == 'g') {
            ++a;
            int l = 1, r = N;
            while (l < r) {
                int m = (l + r) >> 1;
                if (get(0, m) >= a)
                    r = m;
                else
                    l = m + 1;
            }
            if (r & 1)
                ++r;
            update(0, r, 1), update(1, r, 1);
        } else if (c == 'd') {
            ++a;
            int l = 1, r = N;
            while (l < r) {
                int m = (l + r) >> 1;
                if (get(0, m) >= a)
                    r = m;
                else
                    l = m + 1;
            }
            update(0, r, -1), update(1, r, r & 1 ? 1 : -1);
        } else {
            scanf("%d", &b);
            --a;
            printf("%d\n", get(1, 2 * b - 1) - get(1, 2 * a));
        }
    }

    return 0;
}
