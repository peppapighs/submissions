#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

double dp[N];

int main() {
    dp[0] = 0.0;
    for (int i = 1; i < N; i++) {
        dp[i] = dp[i - 1] + log10(i);
    }
    int q;
    scanf("%d", &q);
    while (q--) {
        int a;
        scanf("%d", &a);
        printf("%.0lf\n", floor(dp[a]) + 1.0);
    }

    return 0;
}