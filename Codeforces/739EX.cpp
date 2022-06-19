#include <bits/stdc++.h>

using namespace std;

const int N = 2e3 + 5;

struct item {
    double p;
    int a, b;
    item() {}
    item(double p, int a, int b) : p(p), a(a), b(b) {}
};

int n, a, b;
double pa[N], pb[N], pab[N];
item dp[N];

pair<int, int> solve(double C1, double C2) {
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        if (dp[i].p < dp[i - 1].p + pa[i] - C1)
            dp[i] =
                item(dp[i - 1].p + pa[i] - C1, dp[i - 1].a + 1, dp[i - 1].b);
        if (dp[i].p < dp[i - 1].p + pb[i] - C2)
            dp[i] =
                item(dp[i - 1].p + pb[i] - C2, dp[i - 1].a, dp[i - 1].b + 1);
        if (dp[i].p < dp[i - 1].p + pab[i] - C1 - C2)
            dp[i] = item(dp[i - 1].p + pab[i] - C1 - C2, dp[i - 1].a + 1,
                         dp[i - 1].b + 1);
    }
    return make_pair(dp[n].a, dp[n].b);
}

int main() {
    scanf("%d %d %d", &n, &a, &b);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &pa[i]);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &pb[i]);
    for (int i = 1; i <= n; i++)
        pab[i] = pa[i] + pb[i] - pa[i] * pb[i];

    double l1 = 0, r1 = 1, mid1, l2, r2, mid2;
    for (int it1 = 1; it1 <= 100; it1++) {
        mid1 = (l1 + r1) / 2.0;
        l2 = 0, r2 = 1;
        for (int it2 = 1; it2 <= 100; it2++) {
            mid2 = (l2 + r2) / 2.0;
            if (solve(mid1, mid2).second <= b)
                r2 = mid2;
            else
                l2 = mid2;
        }
        if (solve(mid1, r2).first <= a)
            r1 = mid1;
        else
            l1 = mid1;
    }
    solve(r1, r2);
    printf("%lf\n", dp[n].p + r2 * b + r1 * a);

    return 0;
}