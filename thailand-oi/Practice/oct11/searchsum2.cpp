#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;

int n, k;
int A[N], mn[N];

int main() {
    fill_n(mn, N, INT_MAX);
    mn[0] = 0;
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", A + i), A[i] += A[i - 1];
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
            mn[i - j] = min(mn[i - j], A[i] - A[j]);
    while (k--) {
        int a;
        scanf("%d", &a);
        int l = 0, r = n;
        while (l < r) {
            int m = (l + r + 1) >> 1;
            if (mn[m] <= a)
                l = m;
            else
                r = m - 1;
        }
        printf("%d\n", l);
    }

    return 0;
}
