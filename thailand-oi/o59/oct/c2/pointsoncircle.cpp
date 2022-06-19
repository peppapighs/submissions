#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;

int n, k;
int g[N][N], ans[N];

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= k; j++) {
            int now;
            scanf("%d", &now);
            g[i][j] = min(now, n - now);
        }
    }
    ans[1] = 0;
    for (int i = 2; i <= k; i++) {
        int r1 = g[1][i], r2 = n - g[1][i];
        bool t1 = true, t2 = true;
        for (int j = 2; j < i; j++) {
            if (g[i][j] != min(abs(r1 - ans[j]), abs(n - ans[j] + r1)) ||
                r1 == ans[j])
                t1 = false;
            if (g[i][j] != min(abs(r2 - ans[j]), abs(n - r2 + ans[j])) ||
                r2 == ans[j])
                t2 = false;
        }
        if (t1)
            ans[i] = r1;
        else
            ans[i] = r2;
    }
    for (int i = 1; i <= k; i++)
        printf("%d\n", ans[i]);

    return 0;
}